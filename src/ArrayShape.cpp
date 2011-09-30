/*
 * Implementation of class ArrayShape
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * The ArrayShape object describes the shape of an array object. It provides
 * methods for computing the linear offset from a given index vector and
 * methods for computing such an index starting from a linear offset.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

#include<iostream>
#include<string>

#include "ArrayShape.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{

//===========================private methods====================================
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

void ArrayShape::_allocate(UInt32 n){
	EXCEPTION_SETUP("void ArrayShape::_allocate(UInt32 n)");

	//free memory if allocated
	_free();

	_shape = new UInt32[n];
	if(_shape == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Shape buffer allocation failed!");
		EXCEPTION_THROW();
	}

	_dimstrides = new UInt32[n];
	if(_dimstrides == NULL){
		_free();
		EXCEPTION_INIT(MemoryAllocationError,"Stride buffer allocation failed!");
		EXCEPTION_THROW();
	}
}

void ArrayShape::_free(){
	if(_shape != NULL){
		delete [] _shape;
		_shape = NULL;
	}

	if(_dimstrides != NULL){
		delete [] _dimstrides;
		_dimstrides = NULL;
	}
}

void ArrayShape::_init(){
	_rank = 0;
	_size = 0;
	_shape = NULL;
	_dimstrides = NULL;
}

//===================constructors and destructors===============================
ArrayShape::ArrayShape(){
    _init();
}

ArrayShape::ArrayShape(const UInt32 &r){
	EXCEPTION_SETUP("ArrayShape::ArrayShape(const UInt32 &r)");

	//initialize member variables
	_init();

	//set the rank
	_rank = r;

	//allocate memory if neccessary
	if(_rank != 0){

		try{
			_allocate(_rank);
		}catch(MemoryAllocationError &error){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for ArrayObject failed!");
			EXCEPTION_THROW();
		}

		//initialize buffers
		for(UInt32 i=0;i<_rank;i++){
			_shape[i] = 0;
			_dimstrides[i] = 0;
		}

		//do not need to compute dimstrides and size because they are all
		//zero at this stage
	}

}

ArrayShape::ArrayShape(const ArrayShape &s){
	EXCEPTION_SETUP("ArrayShape::ArrayShape(const ArrayShape &s)");

	//initialize variables
	_init();

	//set the rank to its new value
	_rank = s._rank;

    if(_rank != 0){
    	//need to allocate memory only if rank != 0
		try{
			_allocate(_rank);
		}catch(MemoryAllocationError &error){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for ArrayObject failed!");
			EXCEPTION_THROW();
		}
		//if memory allocation was successful data must be copied
		_size = s._size; //copy size

		//copy shape and stride information
		for(UInt32 i=0;i<_rank;i++){
			_shape[i] = s._shape[i];
			_dimstrides[i] = s._dimstrides[i];
		}
    }
}

ArrayShape::~ArrayShape(){
    //free all occupied memory
    _free();
    _init();
}

//==============methods to access and manipulate the rank of a shape============

void ArrayShape::setRank(const UInt32 &r){
	EXCEPTION_SETUP("void ArrayShape::setRank(const UInt32 &r)");

	//need to do here only something if the new rank differs from the old one
	if((_rank != r)&&(r !=0 )){
		//if the new rank is not zero but different from the original one
		//we have to allocate memory
		_free();      //free all memory
		_init();      //reset everything to default
		_rank = r;    //set then rank;

		//allocate memory
		try{
			_allocate(_rank);
		}catch(MemoryAllocationError &error){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for ArrayObject failed!");
			EXCEPTION_THROW();
		}

		//initialize buffers
		for(UInt32 i=0;i<_rank;i++){
			_dimstrides[i] = 0;
			_shape[i] = 0;
		}
		_size = 0;

	}else if(r == 0){
		//if the new rank is zero we simply have to deallocate everything
		_free();
		_init();
	}else{
		//if the new rank is equal to the original one we simply need to
		//initialize the buffers
		for(UInt32 i=0;i<_rank;i++){
			_dimstrides[i] = 0;
			_shape[i] = 0;
		}
		_size = 0;
	}
}

unsigned int ArrayShape::getRank() const{
    return _rank;
}

//============methods to access and manipulate dimensions=======================

void ArrayShape::setDimension(const UInt32 &i,const UInt32 &d){
	EXCEPTION_SETUP("void ArrayShape::setDimension(const UInt32 &i,const UInt32 &d)");

	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Dimension index exceeded the rank of the shape object!");
		EXCEPTION_THROW();
	}

	_shape[i] = d;

	//like for setDimensions - strides and array size must be adopted
	_compute_dimstrides();
	_compute_size();
}

UInt32 ArrayShape::getDimension(const UInt32 &i) const{
	EXCEPTION_SETUP("UInt32 ArrayShape::getDimension(const UInt32 &i) const");
	if(i>=_rank){
		EXCEPTION_INIT(IndexError,"Dimension index exceeded the rank of the shape object!");
		EXCEPTION_THROW();
	}

	return _shape[i];
}

//===========Methods concerning offset and index handling=======================

UInt64 ArrayShape::getOffset(const Index &i) const {
	EXCEPTION_SETUP("UInt64 ArrayShape::getOffset(const Index &i)");
	UInt64 offset = 0;
	UInt64 index = 0;

	if(getSize()==0){
		EXCEPTION_INIT(MemoryAccessError,"ArrayShape object is not allocated (rank == 0)!");
		EXCEPTION_THROW();
	}

	if(i.getRank() == 0){
		EXCEPTION_INIT(MemoryAccessError,"Index object is not allocated (rank = 0)!");
		EXCEPTION_THROW();
	}

	if(i.getRank() != getRank()){
		EXCEPTION_INIT(ShapeMissmatchError,"ArrayShape and Index rank do not match!");
		EXCEPTION_THROW();
	}

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

void ArrayShape::getIndex(const UInt64 &offset,Index &i) const {
	EXCEPTION_SETUP("void ArrayShape::getIndex(const UInt64 &offset,Index &i) const");

	if(getSize()==0){
		EXCEPTION_INIT(MemoryAccessError,"ArrayShape object is not allocated (rank == 0)!");
		EXCEPTION_THROW();
	}

	if(i.getRank() == 0){
		EXCEPTION_INIT(MemoryAccessError,"Index object is not allocated (rank == 0)!")
	}

	if(i.getRank() != getRank()){
		EXCEPTION_INIT(ShapeMissmatchError,"ArrayShape and Index have different rank!");
		EXCEPTION_THROW();
	}

	if(offset>=getSize()){
		EXCEPTION_INIT(MemoryAccessError,"Offset is larger than size!");
		EXCEPTION_THROW();
	}

	UInt64 o,t;
	o = offset;
	for(UInt32 d = 0;d<getRank();d++){
		t = o%_dimstrides[d];
		i[d] = (o-t)/_dimstrides[d];
		o = t;
	}
}

//========================operators============================================

ArrayShape &ArrayShape::operator=(const ArrayShape &a){
	EXCEPTION_SETUP("ArrayShape &ArrayShape::operator=(const ArrayShape &a)");
    
    //avoid assigning the object to itself
    if(this != &a){

    	if((_rank != a._rank) && (a.getRank() != 0)){
    		//if the rank of the rhs differs from that on the lhs and is not zero
    		_free();
    		_init();

    		_rank = a._rank;  //set the new rank
    		try{
    			_allocate(_rank);
    		}catch(MemoryAllocationError &error){
    			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for ArrayObject failed!");
    			EXCEPTION_THROW();
    		}

    		//now we have to copy data
    		for(UInt32 i=0;i<_rank;i++){
    			_shape[i] = a._shape[i];
    			_dimstrides[i] = a._dimstrides[i];
    		}
    		_size = a._size;
    	}else if(a._rank == 0){
    		_free();
    		_init();
    	}else{
    		//rank of the shape on the lhs is equal to that on the rhs
    		for(UInt32 i=0;i<_rank;i++){
    			_shape[i] = a._shape[i];
    			_dimstrides[i] = a._dimstrides[i];
    		}
    		_size = a._size;
    	}
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

const UInt32 ArrayShape::operator[](UInt64 i) const{
	EXCEPTION_SETUP("const UInt32 ArrayShape::operator[](UInt64 i) const");
	UInt32 v = 0;

	try{
		v = getDimension(i);
	}catch(IndexError &error){
		EXCEPTION_INIT(IndexError,"Dimension index out of bounds!");
		EXCEPTION_THROW();
	}

	return v;
}

//end of namespace
}
}

