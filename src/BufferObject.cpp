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


//================Constructors and destructors==================================
//implementation of the default constructor
BufferObject::BufferObject():_size(0){
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
BufferObject::BufferObject(const BufferObject &b):_size(b._size){
}

//------------------------------------------------------------------------------
//implementation of the move constructor
BufferObject::BufferObject(BufferObject &&o){
	_size = o._size;
	o._size = 0;
}

//------------------------------------------------------------------------------
//implementation of the protected standard constructor
BufferObject::BufferObject(size_t n):_size(n){
}

//------------------------------------------------------------------------------
//implementation of the destructor
BufferObject::~BufferObject(){
	_size = 0;
}

//===============Implementation of assignment operators=========================
//implementation of the copy assignment operator
BufferObject &BufferObject::operator=(const BufferObject &o){
	if(this != &o){
		_size = o._size;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment operator
BufferObject &BufferObject::operator=(BufferObject &&o){

	//for BufferObject the only thing we have to case about is the size
	//of the buffer in number of elements.
	if(this != &o){
		_size = o._size;
		o._size = 0;
	}

	return *this;
}

//==================Methods to influence Buffer size============================
//protected set size method
void BufferObject::size(size_t s){
	_size = s;
}

//------------------------------------------------------------------------------
//implementation of public get size
size_t BufferObject::size() const {
	return _size;
}



//end of namespace
}
}
