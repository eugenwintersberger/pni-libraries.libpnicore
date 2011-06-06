/*
 * BufferObject.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: Eugen Wintersberger
 */

#include "Buffer.hpp"

namespace pni{
namespace utils{



BufferObject::BufferObject(){
	_size = 0;
	_elem_size = 0;
}

BufferObject::BufferObject(const BufferObject &b){
	_size = b._size;
	_elem_size = b._elem_size;
}

BufferObject::BufferObject(unsigned long n,unsigned long es){
	_size = n;
	_elem_size = es;
}

BufferObject::~BufferObject(){
	_size = 0;
	_elem_size = 0;
}

//end of namespace
}
}
