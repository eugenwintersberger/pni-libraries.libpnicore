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
BufferObject::BufferObject(){
	_size = 0;
	_elem_size = 0;
	_compute_total_size();
}

BufferObject::BufferObject(const BufferObject &b){
	EXCEPTION_SETUP("BufferObject::BufferObject(const BufferObject &b)");

	_size = b._size;
	_elem_size = b._elem_size;
	_compute_total_size();
}

BufferObject::BufferObject(UInt64 n,UInt64 es){
	EXCEPTION_SETUP("BufferObject::BufferObject(UInt64 n,UInt64 es)");
	//initialize member variables
	_size = n;
	_elem_size = es;
	_compute_total_size();
}

BufferObject::~BufferObject(){
	_size = 0;
	_elem_size = 0;
	_tot_size = 0;
}

//==================Methods to influence Buffer size============================
void BufferObject::setElementSize(UInt64 es){
	_elem_size = es;
	_compute_total_size();
}

UInt64 BufferObject::getElementSize() const{
	return _elem_size;
}

void BufferObject::setSize(UInt64 s){
	EXCEPTION_SETUP("void BufferObject::setSize(UInt64 s)");
	//raise an exception if you try to alter the size of an already
	//allocated buffer
	if(isAllocated()){
		EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - free buffer before changing its size!");
		EXCEPTION_THROW();
	}
	_size = s;
	_compute_total_size();
}

UInt64 BufferObject::getSize() const{
	return _size;
}

void BufferObject::allocate(){
	EXCEPTION_SETUP("void BufferObject::allocate()");
	//must be overloaded
}

void BufferObject::allocate(const UInt64 &size,const UInt64 &esize){
	EXCEPTION_SETUP("void BufferObject::allocate(const UInt64 size,const UInt64 esize)");
	if(!isAllocated()){
		setElementSize(esize);
		setSize(size);
		try{
			allocate();
		}catch(...){
			EXCEPTION_INIT(MemoryAllocationError,"Error allocating buffer memory!");
			EXCEPTION_THROW();
		}
	}else{
		//raise an exception here
		EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - free buffer prior to new allocation!");
		EXCEPTION_THROW();
	}
}

void BufferObject::allocate(const UInt64 &size){
	EXCEPTION_SETUP("void BufferObject::allocate(const UInt64 size)");
	if(!isAllocated()){
		setSize(size);
		try{
			allocate();
		}catch(...){
			EXCEPTION_INIT(MemoryAllocationError,"Error allocating buffer memory!");
			EXCEPTION_THROW();
		}
	}else{
		EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - free buffer prior to new allocation!");
		EXCEPTION_THROW();
	}

}

bool BufferObject::isAllocated() const{
	return false;
}

void BufferObject::free(){
}

void *BufferObject::getVoidPtr(){
	return NULL;
}

const void *BufferObject::getVoidPtr() const{
	return NULL;
}


//end of namespace
}
}
