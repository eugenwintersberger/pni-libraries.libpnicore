/*
 * BufferObject.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: Eugen Wintersberger
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
	_ptr = NULL;
	_compute_total_size();
}

BufferObject::BufferObject(const BufferObject &b){
	EXCEPTION_SETUP("BufferObject::BufferObject(const BufferObject &b)");

	_ptr = NULL;
	_size = b._size;
	_elem_size = b._elem_size;
	_compute_total_size();

	try{
		allocate();
	}catch(MemoryAllocationError &e){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for data buffer!");
		EXCEPTION_THROW();
	}


	//finally we have to copy the content of the original buffer to the new
	//one
	char *this_ptr = (char *)_ptr;
	char *that_ptr = (char *)b._ptr;
	for(UInt64 i=0;i<_tot_size;i++){
		this_ptr[i] = that_ptr[i];
	}
}

BufferObject::BufferObject(UInt64 n,UInt64 es){
	EXCEPTION_SETUP("BufferObject::BufferObject(UInt64 n,UInt64 es)");
	//initialize member variables
	_size = n;
	_elem_size = es;
	_ptr = NULL;

	try{
		allocate();
	}catch(MemoryAllocationError &e){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for buffer failed!");
		EXCEPTION_THROW();
	}

	_compute_total_size();
	//initialize memory content
	char *this_ptr = (char *)_ptr;
	for(UInt64 i=0;i<_tot_size;i++) this_ptr[i] = 0;
}

BufferObject::~BufferObject(){
	_size = 0;
	_elem_size = 0;
	_tot_size = 0;

	char *this_ptr = (char *)_ptr;
	if(_ptr != NULL) delete [] this_ptr;
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
	_size = s;
	_compute_total_size();
}

UInt64 BufferObject::getSize() const{
	return _size;
}

void BufferObject::allocate(){
	EXCEPTION_SETUP("void BufferObject::allocate()");

	if(_ptr != NULL){
		char *this_ptr = (char *)_ptr;
		delete [] this_ptr;
	}

	_ptr = new char[_tot_size];
	if(_ptr == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for buffer failed!");
		EXCEPTION_THROW();
	}
}

void *BufferObject::getVoidPtr(){
	return _ptr;
}

const void *BufferObject::getVoidPtr() const{
	return _ptr;
}


//====================Operators=================================================
BufferObject &BufferObject::operator=(const BufferObject &o){
	if(this != &o){
		//have two possibilities here
		if(getMemSize() != o.getMemSize()){
			//need to reallocate memory

		}else{
			//only need to copy data
			_size = o._size;
			_elem_size = o._elem_size;
			_compute_total_size();
		}

		//in the end in all cases we need to copy data
		char *this_ptr = (char *)_ptr;
		char *that_ptr = (char *)o._ptr;
		for(UInt64 i=0;i<getMemSize();i++) this_ptr[i] = that_ptr[i];
	}

	return *this;
}

//end of namespace
}
}
