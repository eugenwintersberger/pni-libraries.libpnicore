/*
 * Implementation of class BufferObject
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
 * BufferObject is the base class for all buffers and thus defines their
 * interfaces.
 *
 * Created on: Jun 3, 2011
 *     Author: Eugen Wintersberger
 *
 */


#include "BufferObject.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{
//======================some private methods====================================
void BufferObject::_compute_total_size(){
	_tot_size = _size*_elem_size;
}


//================Constructors and destructors==================================
//implementation of the default constructor
BufferObject::BufferObject(){
	_size = 0;
	_elem_size = 0;
	_compute_total_size();
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
BufferObject::BufferObject(const BufferObject &b){
	EXCEPTION_SETUP("BufferObject::BufferObject(const BufferObject &b)");

	_size = b._size;
	_elem_size = b._elem_size;
	_compute_total_size();
}

//------------------------------------------------------------------------------
//implementation of the move constructor
BufferObject::BufferObject(BufferObject &&o){
	_size = o._size;
	o._size = 0;
	_elem_size = o._elem_size;
	o._elem_size = 0;
	_compute_total_size();
	o._compute_total_size();
}

//------------------------------------------------------------------------------
//implementation of a constructor
BufferObject::BufferObject(size_t n,size_t es){
	EXCEPTION_SETUP("BufferObject::BufferObject(UInt64 n,UInt64 es)");
	//initialize member variables
	_size = n;
	_elem_size = es;
	_compute_total_size();
}

//------------------------------------------------------------------------------
//implementation of the destructor
BufferObject::~BufferObject(){
	_size = 0;
	_elem_size = 0;
	_tot_size = 0;
}

//===============Implementation of assignment operators=========================
//implementation of the copy assignment operator
BufferObject &BufferObject::operator=(const BufferObject &o){
	if(this != &o){
		_size = o._size;
		_elem_size = o._elem_size;
		_tot_size = o._tot_size;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment operator
BufferObject &BufferObject::operator=(BufferObject &&o){
	if(this != &o){
		_size = o._size;
		o._size = 0;
		_elem_size = o._elem_size;
		o._elem_size = 0;
		_tot_size = o._tot_size;
		o._tot_size = 0;
	}

	return *this;
}

//==================Methods to influence Buffer size============================
void BufferObject::setElementSize(size_t es){
	DEPRECATION_WARNING("void BufferObject::setElementSize(size_t es)",
						"void BufferObject::element_size(size_t es)");
	element_size(es);
}

void BufferObject::element_size(size_t es){
	_elem_size = es;
	_compute_total_size();
}

size_t BufferObject::getElementSize() const{
	DEPRECATION_WARNING("size_t BufferObject::getElementSize() const",
						"size_t BufferObject::element_size() const");

	return element_size();
}

size_t BufferObject::element_size() const{
	return _elem_size;
}

void BufferObject::setSize(size_t s){
	DEPRECATION_WARNING("void BufferObject::setSize(UInt64 s)",
						"void BufferObject::size(size_t s)");
	size(s);
}

void BufferObject::size(size_t s){
	EXCEPTION_SETUP("void BufferObject::size(size_t s)");
	//raise an exception if you try to alter the size of an already
	//allocated buffer
	if(is_allocated()){
		EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - "
					   "free buffer before changing its size!");
		EXCEPTION_THROW();
	}
	_size = s;
	_compute_total_size();
}

size_t BufferObject::getSize() const{
	DEPRECATION_WARNING("size_t BufferObject::getSize() const",
						"size_t BufferObject::size() const");
	return size();
}

size_t BufferObject::size() const {
	return _size;
}

//=====================Methods for memory allocation============================
void BufferObject::allocate(){
	EXCEPTION_SETUP("void BufferObject::allocate()");
	//must be overloaded
}

void BufferObject::allocate(const size_t &s,const size_t &esize){
	EXCEPTION_SETUP("void BufferObject::allocate"
					"(const UInt64 size,const UInt64 esize)");
	if(!is_allocated()){
		element_size(esize);
		size(s);
		try{
			allocate();
		}catch(...){
			EXCEPTION_INIT(MemoryAllocationError,"Error allocating buffer memory!");
			EXCEPTION_THROW();
		}
	}else{
		//raise an exception here
		EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - "
					  "free buffer prior to new allocation!");
		EXCEPTION_THROW();
	}
}

void BufferObject::allocate(const size_t &s){
	EXCEPTION_SETUP("void BufferObject::allocate(const UInt64 size)");
	if(!is_allocated()){
		size(s);
		try{
			allocate();
		}catch(...){
			EXCEPTION_INIT(MemoryAllocationError,"Error allocating buffer memory!");
			EXCEPTION_THROW();
		}
	}else{
		EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - "
					   "free buffer prior to new allocation!");
		EXCEPTION_THROW();
	}

}

bool BufferObject::isAllocated() const{
	DEPRECATION_WARNING("bool BufferObject::isAllocated() const",
						"bool BufferObject::is_allocated() const");
	return is_allocated();
}

bool BufferObject::is_allocated() const {
	return false;
}

void BufferObject::free(){
}

//====================Methods for accessing memory=============================
void *BufferObject::getVoidPtr(){
	DEPRECATION_WARNING("void *BufferObject::getVoidPtr()",
						"void *BufferObject::void_ptr()");
	return void_ptr();
}

void *BufferObject::void_ptr() {
	return nullptr;
}

const void *BufferObject::getVoidPtr() const{
	DEPRECATION_WARNING("const void *BufferObject::getVoidPtr() const",
						"const void *BufferObject::void_ptr() const");
	return void_ptr();
}

const void *BufferObject::void_ptr() const {
	return nullptr;
}


//end of namespace
}
}
