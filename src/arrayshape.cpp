//implementation of the NumArrayShape class

#include<iostream>
#include<string>

#include "arrayshape.hpp"
#include "exceptions.hpp"

const MemoryAllocationError ArrayShape::SHAPE_ALLOC_ERROR(std::string("ArrayShape"),
		                      std::string("Cannot allocate memory for shape buffer!"));
const MemoryAllocationError ArrayShape::DIMSTRIDE_ALLOC_ERROR(std::string("ArrayShape"),
		                      std::string("Cannot allocate memory for dimstrides buffer!"));

ArrayShape::ArrayShape(){
    _rank = 0;
    _dimstrides = NULL;
    _shape = NULL;
    _size = 0;
}

ArrayShape::ArrayShape(const unsigned int r,const unsigned int *s){
    unsigned int i;
    _rank = r;
    _shape = NULL;
    _dimstrides = NULL;
    
    //allocate memory for the shape pointer
    _shape = new unsigned int[r];
    if (_shape == NULL) throw SHAPE_ALLOC_ERROR;
    _dimstrides = new unsigned int[r];
    if (_dimstrides == NULL){
    	if(_shape!= NULL) delete [] _shape;
    	throw DIMSTRIDE_ALLOC_ERROR;
    }
    for(i=0;i<r;i++) _shape[i] = s[i];
    
    //compute the dimension  strides
    _compute_dimstrides();
    
    //compute the total size of the array
    _compute_size();
    
}

ArrayShape::ArrayShape(const ArrayShape &s){
    unsigned int i;
    
    _rank = s._rank;
    _shape = new unsigned int[_rank];
    if(_shape==NULL) throw SHAPE_ALLOC_ERROR;
    _dimstrides = new unsigned int [_rank];
    if(_dimstrides == NULL){
    	if(_shape != NULL) delete [] _shape;
    	throw DIMSTRIDE_ALLOC_ERROR;
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
    int i;
    
    //compute the dimension  strides
    for(i=_rank-1;i>=0;i--){
        if(((unsigned int)i)==_rank-1){
            _dimstrides[i] = 1;
            continue;
        }
        _dimstrides[i] = _dimstrides[i+1]*_shape[i+1];
    }
}

void ArrayShape::_compute_size(){
    unsigned int i;
    
    _size = 1;
    for(i=0;i<_rank;i++) _size *= _shape[i];
}

void ArrayShape::setRank(const unsigned int &r){
    unsigned int i;

    
    if(_shape==NULL){
        //the shape points has not been allocated yet
        _shape = new unsigned int[r];
        //throw an exception if memory allocation fails
        if(_shape == NULL) throw SHAPE_ALLOC_ERROR;
        _dimstrides = new unsigned int[r];
        //throw an exception if memory allocation fails
        if(_dimstrides == NULL){
        	if(_shape != NULL) delete [] _shape;
        	throw DIMSTRIDE_ALLOC_ERROR;
        }
        //set the number of elements along each dimension to 1
        //default value
        for(i=0;i<r;i++) _shape[i] = 1;
    }else{
        //the shape pointer is already allocated
        unsigned int *new_shape;
        unsigned int *new_dimstrides;
        new_shape = new unsigned int[r];
        if(new_shape == NULL) throw SHAPE_ALLOC_ERROR;
        new_dimstrides = new unsigned int[r];
        if(new_dimstrides == NULL){
        	if(new_shape != NULL) delete [] new_shape;
        	throw DIMSTRIDE_ALLOC_ERROR;
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

void ArrayShape::setDimensions(const unsigned int *s){
    //here the only thing we have to take care is, that the new 
    //shape is not smaller then the old one - that is up to the 
    //programmer
    unsigned int i;
    
    for(i=0;i<_rank;i++) _shape[i] = s[i];
    
    //new size and new stride values must be computed
    _compute_dimstrides();
    _compute_size();
}

void ArrayShape::setDimension(const unsigned int &i,const unsigned int &d){
	if(i>=_rank){
		IndexError e;
		e.setSource("ArrayShape::setDimension");
		e.setDescription("The dimension index must not be equal or exceed the rank of the shape object!");
		throw e;
	}

	_shape[i] = d;

	//like for setDimensions - strides and array size must be adopted
	_compute_dimstrides();
	_compute_size();
}

const unsigned int *ArrayShape::getDimensions() const{
    return _shape;
}

unsigned int ArrayShape::getDimension(const unsigned int &i) const{
	if(i>=_rank){
		IndexError e;
		e.setSource("ArrayShape::setDimension");
		e.setDescription("The dimension index must not be equal or exceed the rank of the shape object!");
		throw e;
	}

	return _shape[i];
}

unsigned int ArrayShape::getOffset(const unsigned int *index){
    unsigned int i;
    unsigned int offset = 0;
    
    for(i=0;i<_rank;i++){
        offset += index[i]*_dimstrides[i];
    }
    return offset;
}
ArrayShape &ArrayShape::operator=(const ArrayShape &a){
    unsigned int i;
    
    //avoid assigning the object to itself
    if(this != &a){
        _rank = a._rank;
        if(_shape != NULL) delete [] _shape;
        if(_dimstrides != NULL) delete [] _dimstrides;
        
        _shape = new unsigned int[_rank];
        if(_shape==NULL) throw SHAPE_ALLOC_ERROR;
        _dimstrides = new unsigned int[_rank];
        if(_dimstrides==NULL){
        	if(_shape!= NULL) delete [] _shape;
        	throw DIMSTRIDE_ALLOC_ERROR;
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
    unsigned long i;

    //check the rank of the two shapes
    if(a._rank != b._rank) return true;

    //check the sizes of the two shapes
    if(a._size != b._size) return true;

    //check the shape of the two array shapes
    for(i=0;i<a._rank;i++){
        if(a._shape[i] != b._shape[i]) return true;
    }

    return false;
}

