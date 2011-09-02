//implementation of the NumArrayShape class

#include<iostream>
#include<string>

#include "ArrayShape.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{

ArrayShape::ArrayShape(){
    _rank = 0;
    _dimstrides = NULL;
    _shape = NULL;
    _size = 0;
}

ArrayShape::ArrayShape(const UInt32 r,const UInt32 *s){
	EXCEPTION_SETUP("ArrayShape::ArrayShape(const UInt32 r,const UInt32 *s)");
    UInt32 i;
    _rank = r;
    _shape = NULL;
    _dimstrides = NULL;
    
    //allocate memory for the shape pointer
    _shape = new UInt32[r];
    if (_shape == NULL){
    	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimensions buffer!");
    	EXCEPTION_THROW();
    }

    _dimstrides = new UInt32[r];
    if (_dimstrides == NULL){
    	if(_shape!= NULL) delete [] _shape;
    	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimension strides buffer!");
    	EXCEPTION_THROW();
    }
    for(i=0;i<r;i++) _shape[i] = s[i];
    
    //compute the dimension  strides
    _compute_dimstrides();
    
    //compute the total size of the array
    _compute_size();
    
}

ArrayShape::ArrayShape(const ArrayShape &s){
	EXCEPTION_SETUP("ArrayShape::ArrayShape(const ArrayShape &s)");
    unsigned int i;
    
    _rank = s._rank;
    _shape = new UInt32[_rank];
    if(_shape==NULL){
    	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimensions buffer!");
    	EXCEPTION_THROW();
    }
    _dimstrides = new UInt32 [_rank];
    if(_dimstrides == NULL){
    	if(_shape != NULL) delete [] _shape;
    	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimension strides buffer!");
    	EXCEPTION_THROW();
    }
    _size = s._size;
    
    for(i=0;i<_rank;i++){
        _shape[i] = s._shape[i];
        _dimstrides[i] = s._dimstrides[i];
    }
}

ArrayShape::~ArrayShape(){
    //free all occupied memory
    if(_dimstrides != NULL) delete [] _dimstrides;
    if(_shape != NULL) delete [] _shape;
    
    _rank = 0;
}

void ArrayShape::_compute_dimstrides()
{
    Int32 i;
    
    //compute the dimension  strides
    for(i=_rank-1;i>=0;i--){
        if(((UInt32)i)==_rank-1){
            _dimstrides[i] = 1;
            continue;
        }
        _dimstrides[i] = _dimstrides[i+1]*_shape[i+1];
    }
}

void ArrayShape::_compute_size(){
    UInt32 i;
    
    _size = 1;
    for(i=0;i<_rank;i++) _size *= _shape[i];
}

void ArrayShape::setRank(const UInt32 &r){
	EXCEPTION_SETUP("void ArrayShape::setRank(const UInt32 &r)");
    UInt32 i;

    
    if(_shape==NULL){
        //the shape points has not been allocated yet
    	//this is usually the case when the shape object was
    	//created using the default constructor
        _shape = new UInt32[r];
        //throw an exception if memory allocation fails
        if(_shape == NULL){
        	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimensions buffer!");
        	EXCEPTION_THROW();
        }
        _dimstrides = new UInt32[r];
        //throw an exception if memory allocation fails
        if(_dimstrides == NULL){
        	if(_shape != NULL) delete [] _shape;
        	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimension strides buffer!");
        	EXCEPTION_THROW();
        }
        //set the number of elements along each dimension to 1
        //default value
        for(i=0;i<r;i++) _shape[i] = 1;
    }else{
        //the shape pointer is already allocated - the rank is
    	//changed after initialization
        UInt32 *new_shape;
        UInt32 *new_dimstrides;
        new_shape = new UInt32[r];
        if(new_shape == NULL){
        	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimensions buffer!");
        	EXCEPTION_THROW();
        }
        new_dimstrides = new UInt32[r];
        if(new_dimstrides == NULL){
        	if(new_shape != NULL) delete [] new_shape;
        	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimension strides buffer!");
        	EXCEPTION_THROW();
        }
        
        //initialize the new shape array
        for(i=0;i<r;i++) new_shape[i] = 1;
        
        //load already existing data to the shape array
        //the second break condition here is for the case that the 
        //new rank is smaller then the old one
        for(i=0;i<_rank && i<r;i++){
            new_shape[i] = _shape[i];
        }
        
        //free the originally allocated memory
        delete [] _shape;
        //set the shape pointer to the new location
        _shape = new_shape;
        delete [] _dimstrides;
        _dimstrides = new_dimstrides;
        
    }
    //finally we have to set the new rank variable
    _rank = r;
    
    //in the end we have to compute new strides and a new array size
    _compute_dimstrides();
    _compute_size();
}

unsigned int ArrayShape::getRank() const{
    return _rank;
}

void ArrayShape::setDimensions(const UInt32 *s){
    //here the only thing we have to take care is, that the new 
    //shape is not smaller then the old one - that is up to the 
    //programmer
    UInt32 i;
    
    for(i=0;i<_rank;i++) _shape[i] = s[i];
    
    //new size and new stride values must be computed
    _compute_dimstrides();
    _compute_size();
}

void ArrayShape::setDimension(const UInt32 &i,const UInt32 &d){
	EXCEPTION_SETUP("void ArrayShape::setDimension(const UInt32 &i,const UInt32 &d)");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"The dimension index must not be equal or exceed the rank of the shape object!");
		EXCEPTION_THROW();
	}

	_shape[i] = d;

	//like for setDimensions - strides and array size must be adopted
	_compute_dimstrides();
	_compute_size();
}

const UInt32 *ArrayShape::getDimensions() const{
    return _shape;
}

UInt32 ArrayShape::getDimension(const UInt32 &i) const{
	EXCEPTION_SETUP("UInt32 ArrayShape::getDimension(const UInt32 &i) const");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"The dimension index must not be equal or exceed the rank of the shape object!");
		EXCEPTION_THROW();
	}

	return _shape[i];
}

UInt64 ArrayShape::getOffset(const UInt32 *index){
	EXCEPTION_SETUP("UInt64 ArrayShape::getOffset(const UInt32 *index)");
    UInt32 i;
    UInt64 offset = 0;
    
    for(i=0;i<_rank;i++){
    	if(index[i]>=_shape[i]){
    		EXCEPTION_INIT(IndexError,"Index out of bounds!");
    		EXCEPTION_THROW();
    	}
        offset += index[i]*_dimstrides[i];
    }
    return offset;
}

UInt64 ArrayShape::getOffset(const Index &i){
	EXCEPTION_SETUP("UInt64 ArrayShape::getOffset(const Index &i)");
	UInt64 offset = 0;
	UInt64 index = 0;

	for(UInt32 d=0;d<getRank();d++){
		index = i[d];
		if(index >= getDimension(d)){
			EXCEPTION_INIT(IndexError,"Index out of bounds!");
			EXCEPTION_THROW();
		}
		offset += index*_dimstrides[d];
	}
	return offset;
}

ArrayShape &ArrayShape::operator=(const ArrayShape &a){
	EXCEPTION_SETUP("ArrayShape &ArrayShape::operator=(const ArrayShape &a)");
    UInt32 i;
    
    //avoid assigning the object to itself
    if(this != &a){
    	//if the total number of elements described
    	//by the tow shapes is equal they can be assigned.
        _rank = a._rank;
        if(_shape != NULL) delete [] _shape;
        if(_dimstrides != NULL) delete [] _dimstrides;
        
        _shape = new UInt32[_rank];
        if(_shape==NULL){
        	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for dimensions buffer!");
        	EXCEPTION_THROW();
        }
        _dimstrides = new UInt32[_rank];
        if(_dimstrides==NULL){
        	if(_shape!= NULL) delete [] _shape;
        	EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for the dimension strides buffer!");
        	EXCEPTION_THROW();
        }
        
        for(i=0;i<_rank;i++){
            _shape[i] = a._shape[i];
            _dimstrides[i] = a._dimstrides[i];
        }
        
        _size = a._size;
    }
 
    return *this;
}

bool operator==(const ArrayShape &a,const ArrayShape &b){
    unsigned long i;
    
    //check the rank of the two shapes
    if(a._rank != b._rank) return false;
    
    //check the sizes of the two shapes
    if(a._size != b._size) return false;
    
    //check the shape of the two array shapes
    for(i=0;i<a._rank;i++){
        if(a._shape[i] != b._shape[i]) return false;
    }
    
    return true;
}

bool operator!=(const ArrayShape &a,const ArrayShape &b){
    if(a==b){
    	return false;
    }

    return true;
}

std::ostream &operator<<(std::ostream &o,const ArrayShape &s){
	o<<"Rank = "<<s.getRank()<<":";
	o<<"( ";
	for(unsigned long i=0;i<s.getRank();i++) o<<s[i]<<" ";
	o<<")";
	return o;
}

//end of namespace
}
}

