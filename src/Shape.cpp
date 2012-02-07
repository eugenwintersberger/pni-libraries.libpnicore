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

#include "Shape.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{

//===========================private methods====================================
void Shape::_compute_dimstrides()
{
    ssize_t i; //we need here a signed value

    //compute the dimension  strides
    for(i=rank()-1;i>=0;i--){
        if(i==(ssize_t)rank()-1){
            _dimstrides[(size_t)i] = 1;
            continue;
        }
        _dimstrides[(size_t)i] = _dimstrides[(size_t)i+1]*_shape[(size_t)i+1];
    }
}

void Shape::_compute_size(){
    _size = 1;
    for(size_t i=0;i<rank();i++) _size *= _shape[i];
}

//===================constructors and destructors===============================
//implementation of the default constructor
Shape::Shape(){
    _size = 0;
}

//------------------------------------------------------------------------------
//implementation of the standard constructor
Shape::Shape(const size_t &r)
    :_dimstrides(r),
     _shape(r)
{
	EXCEPTION_SETUP("ArrayShape::ArrayShape(const UInt32 &r)");

	//initialize member variables
	_size = 0;
    _dimstrides = 0;
    _shape = 0;
}

//------------------------------------------------------------------------------
//implementation of the constructor with initializer list
Shape::Shape(std::initializer_list<size_t> list)
    :_dimstrides(list.size()),
     _shape(list)
{
    EXCEPTION_SETUP("Shape::Shape(std::initializer_list<size_t> list)");

    _size = 0;
    _dimstrides = 0;

    _compute_size();
    _compute_dimstrides();
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
Shape::Shape(const Shape &s){
	EXCEPTION_SETUP("ArrayShape::ArrayShape(const ArrayShape &s)");

	//initialize variables
	_size = 0;

	_dimstrides = s._dimstrides;
	_shape = s._shape;

	_compute_size();
	_compute_dimstrides();
}

//------------------------------------------------------------------------------
//implementation of the move constructor
Shape::Shape(Shape &&o){
	_size = o._size;
	o._size = 0;

	_shape = std::move(o._shape);
	_dimstrides = std::move(o._dimstrides);
}

//------------------------------------------------------------------------------
//implementation of the destructor
Shape::~Shape(){
	_size = 0;
	_dimstrides.free();
	_shape.free();
}

//==============methods to access and manipulate the rank of a shape============

void Shape::rank(const size_t &r){
	EXCEPTION_SETUP("void ArrayShape::setRank(const UInt32 &r)");

	if(r!=0){
		_dimstrides.allocate(r);
		_shape.allocate(r);

		for(size_t i=0;i<r;i++){
			_shape[i] = 0;
			_dimstrides[i] = 0;
		}
	}else{
		_dimstrides.free();
		_shape.free();
	}
	_size = 0;
}

size_t Shape::rank() const{
    return _shape.size();
}

//============methods to access and manipulate dimensions=======================
//implementation of set dimension
void Shape::dim(const size_t &i,const size_t &d){
	EXCEPTION_SETUP("void ArrayShape::setDimension(const UInt32 &i,const UInt32 &d)");

	_shape[i] = d;

	//like for setDimensions - strides and array size must be adopted
	_compute_dimstrides();
	_compute_size();
}

//-------------------------------------------------------------------------------
//implementation of the set dimension by initializer list
void Shape::dim(std::initializer_list<size_t> list){
    EXCEPTION_SETUP("void Shape::dim(std::initializer_list<size_t> list)");

    if(list.size() != rank()){
        EXCEPTION_INIT(SizeMissmatchError,
                "Initializer list size does not match rank of Shape!");
        EXCEPTION_THROW();
    }
    
    size_t cntr = 0;
    for(const size_t &i: list){
        _shape[cntr] = i;
        cntr++;
    }
}

//-----------------------------------------------------------------------------
//implementation of get dimension
size_t Shape::dim(const size_t &i) const{
	EXCEPTION_SETUP("UInt32 ArrayShape::getDimension(const UInt32 &i) const");

	return _shape[i];
}

//===========Methods concerning offset and index handling=======================
//implementation of offset calculation
size_t Shape::offset(const Index &i) const {
	EXCEPTION_SETUP("UInt64 ArrayShape::getOffset(const Index &i)");
	size_t offset = 0;
	size_t index = 0;

	if(!_shape.is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"ArrayShape object is not allocated (rank == 0)!");
		EXCEPTION_THROW();
	}

	if(i.rank() == 0){
		EXCEPTION_INIT(MemoryAccessError,"Index object is not allocated (rank = 0)!");
		EXCEPTION_THROW();
	}

	if(i.rank() != rank()){
		EXCEPTION_INIT(ShapeMissmatchError,"ArrayShape and Index rank do not match!");
		EXCEPTION_THROW();
	}

	for(size_t d=0;d<rank();d++){
		index = i[d];
		if(index >= dim(d)){
			EXCEPTION_INIT(IndexError,"Index out of bounds!");
			EXCEPTION_THROW();
		}
		offset += index*_dimstrides[d];
	}
	return offset;
}

//------------------------------------------------------------------------------
//compute an offset form an initializer list
size_t Shape::offset(std::initializer_list<size_t> list) const{
    EXCEPTION_SETUP("size_t Shape::"
            "offset(std::initializer_list<size_t> list) const");

	size_t offset = 0;

	if(!_shape.is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"Shape object is not allocated (rank == 0)!");
		EXCEPTION_THROW();
	}


	if(list.size() != rank()){
		EXCEPTION_INIT(ShapeMissmatchError,
                "Shape rank and initializer list size do not match!");
		EXCEPTION_THROW();
	}

    size_t cntr = 0;
    for(const size_t &index: list){
        if(index >= dim(cntr)){
			EXCEPTION_INIT(IndexError,"Index out of bounds!");
			EXCEPTION_THROW();
        }
        offset += index*_dimstrides[cntr];
        cntr++; //increment list counter
    }

	return offset;

}

//------------------------------------------------------------------------------
//implementation of index calculation
void Shape::index(const size_t &offset,Index &i) const {
	EXCEPTION_SETUP("void ArrayShape::getIndex(const UInt64 &offset,Index &i) const");

	if(!_shape.is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"ArrayShape object is not allocated (rank == 0)!");
		EXCEPTION_THROW();
	}

	if(i.rank() == 0){
		EXCEPTION_INIT(MemoryAccessError,"Index object is not allocated (rank == 0)!")
	}

	if(i.rank() != rank()){
		EXCEPTION_INIT(ShapeMissmatchError,"ArrayShape and Index have different rank!");
		EXCEPTION_THROW();
	}

	if(offset>=size()){
		EXCEPTION_INIT(MemoryAccessError,"Offset is larger than size!");
		EXCEPTION_THROW();
	}

	size_t o,t;
	o = offset;
	for(size_t d = 0;d<rank();d++){
		t = o%_dimstrides[d];
		i[d] = (o-t)/_dimstrides[d];
		o = t;
	}
}

//=============Implementation of the assignment operators=======================
//implementation of the copy assignment
Shape &Shape::operator=(const Shape &a){
	EXCEPTION_SETUP("ArrayShape &ArrayShape::operator=(const ArrayShape &a)");

	if(this != &a){
		_size = a._size;
		_dimstrides = a._dimstrides;
		_shape = a._shape;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of move assignment
Shape &Shape::operator=(Shape &&o){
	if(this != &o){
		_size = o._size;
		o._size = 0;
		_dimstrides = std::move(o._dimstrides);
		_shape = std::move(o._shape);
	}

	return *this;
}


//================Implementation of comparison operators========================
//implementation of equality check
bool operator==(const Shape &a,const Shape &b){
    //check the rank of the two shapes
    if(a.rank() != b.rank()) return false;
    
    //check the sizes of the two shapes
    if(a.size() != b.size()) return false;
    
    //check the shape of the two array shapes
    for(size_t i=0;i<a.rank();i++){
        if(a[i] != b[i]) return false;
    }
    
    return true;
}

//------------------------------------------------------------------------------
//implementation if inequality checkc
bool operator!=(const Shape &a,const Shape &b){
    if(a==b){
    	return false;
    }

    return true;
}

//=====================Implementation of output operator========================
std::ostream &operator<<(std::ostream &o,const Shape &s){
	o<<"Rank = "<<s.rank()<<":";
	o<<"( ";
	for(size_t i=0;i<s.rank();i++) o<<s[i]<<" ";
	o<<")";
	return o;
}

//================Implementation of access operators============================
//implementation of read only access
const size_t Shape::operator[](size_t i) const{
	return _shape[i];
}

//end of namespace
}
}

