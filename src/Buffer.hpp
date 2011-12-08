/*
 * Declaration of the Buffer<T> template
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
 * Declaration of the typed Buffer<T> template. This is a descendant of
 * BufferObject as declared in BufferObject.hpp. It implements the interface
 * as suggested by its base class.
 *
 * Created on: Apr 11, 2011
 *     Author: Eugen Wintersberger
 *
 */



#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <boost/shared_array.hpp>
#include "Exceptions.hpp"
#include "PNITypes.hpp"
#include "PNITypeInfo.hpp"
#include "BufferObject.hpp"
#include "TypeInfo.hpp"
#include "TypeCompat.hpp"
#include "TypeRange.hpp"

namespace pni{
namespace utils{

//! \addtogroup Data-objects
//! @{

//! \brief buffer template

//! This template is a concrete implementation of the BufferObject base class.
//! It uses the new allocator to request memory from the system.
//! Along with the methods provided by the BufferObject base class this
//! template implements a couple of operators that are quite useful.
//! You can assign Buffers of different type T with each other.
//! In general the assignment from the buffer on the rhs to the buffer on the
//! lhs of the operator is straight forward. The full state of the buffer is
//! assigned to the lhs. So if the buffer on the rhs is not allocated
//! memory eventually hold by the buffer of the lhs will be freed to
//! bring the lhs to the same state as the rhs.
template<typename T>class Buffer:public BufferObject{
private:
	T *_data; //!< pointer to the data block

	//some private methods
	void _allocate();
public:
	typedef boost::shared_ptr<Buffer<T> > sptr; //!< smart pointer to a typed buffer
	//! default constructor

	//! If this constructor is used no memory will be allocated. For that purpose
	//! use the allocate method.
	Buffer();
	//! copy constructor

	//! The buffer is initialized by an already existing buffer. All data will be
	//! copied to the storage of the new created buffer object.
	Buffer(const Buffer<T> &b);
	//! move constructor
	Buffer(Buffer<T> &&b);
	//! constructor with buffer size

	//! Using this constructor the buffer will automatically allocate memory.
	//! \throws MemoryAllocationError if allocation on the heap fails
	//! \param n number of elements of type T in the buffer
	Buffer(size_t n);
	//! destructor
	virtual ~Buffer();

	//! copy assignment operator

	//! The content of the buffer on the lhs is set to that of the lhs.
	//! If necessary memory is reallocated.
	//! \throws MemoryAccessError if something goes wring with memory allocation
	//! \param b Buffer whose content will be assigned to this buffer
	//! \return reference to a Buffer<T> object
	Buffer<T> &operator=(const Buffer<T> &b);
	//! move assignment operator
	Buffer<T> &operator=(Buffer<T> &&b);
	//! assignment operator

	//! This special form of the assignment operator can be used to assign
	//! a single value to all elements of the buffer. Thus, it is quite useful
	//! for initializing a buffer object.
	//! \param v value which to assign to all buffer elements
	//! \return reference to a buffer object
	Buffer<T> &operator=(const T &v);
	//! return data pointer

	//! Returns a typed const pointer to the allocated memory. The pointer must
	//! not be used to modify data values.
	//! \return pointer to allocated memory
	const T* ptr() const;
	//! return data pointer

	//! Returns a typed pointer to the allocated memory. The pointer can be
	//! used for altering the buffer content.
	//! \return pointer to allocated memory
	T *ptr();

	//! read/write void pointer

	//! Returns a pointer of type void * on the allocated memory.
	//! \return pointer to allocated memory
	virtual void *void_ptr();
	//! read only void pointer

	//! Returns a read only void pointer to the allocated memory.
	//! \return pointer to allocated memory
	virtual const void *void_ptr() const;

	//! [] operator for read and write access

	//! This operator will be used in expressions where the buffer access stands
	//! on the left side of an assignment operation. In other words - when data should
	//! be written to the buffer.
	//! \throws IndexError if n is larger than the number of elements in the buffer
	//! \param n index of element to fetch
	//! \return reference to the n-th element in the buffer
	T& operator[](size_t n);
	//! [] operator for read only access

	//! This operator will be used in expressions where read only access to the
	//! data values in the buffer is required.
	//! \throws IndexError if n is larger than the number of elements in the buffer
	//! \param n index of the element to fetch
	//! \return value of the buffer at position n
	T operator[](size_t n) const;
	//! allocate memory

	//! Unlike allocate() this method takes the number of elements as an
	//! argument. Thus the number of elements to allocate must not be set
	//! prior to the invocation of this method. However, like allocate()
	//! an exception will be thrown if the buffer is already allocated.
	//! \param size number of elements to allocate
	virtual void allocate(const UInt64 &size);
	//! buffer status

	//! Returns true if the buffer is allocated. False otherwise.
	//! \return true if allocated, false otherwise
	virtual bool is_allocated() const;
	//! frees memory

	//! This function frees the memory allocated by the buffer. It must be
	//! invoked before calling allocate() on an already allocated buffer.
	//! If the buffer is not allocated this method does nothing.
	virtual void free();

	virtual size_t element_size() const {
		return sizeof(T);
	}

	virtual size_t mem_size() const {
		return sizeof(T)*this->size();
	}

	virtual PNITypeID type_id() const {
		return PNITypeInfo<T>::TypeID;
	}


};

//! @}

//=================Implementation of constructors and destructors===============
//implementation of the default constructor
template<typename T> Buffer<T>::Buffer():BufferObject(){
	_data = nullptr;
}

//------------------------------------------------------------------------------
//implementation of the standard constructor
template<typename T> Buffer<T>::Buffer(size_t n):BufferObject(n){
	EXCEPTION_SETUP("template<typename T> Buffer<T>::Buffer(size_t n)");

	_data = nullptr;

	//we try to allocate memory only if the size is not zero - otherwise
	//an exception will be raised.
	if(this->size()!=0){
		try{
			this->allocate(this->size());
		}catch(...){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Buffer failed!");
			EXCEPTION_THROW();
		}
	}
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
template<typename T> Buffer<T>::Buffer(const Buffer<T> &b):BufferObject(b){
	EXCEPTION_SETUP("template<typename T> Buffer<T>::Buffer(const Buffer<T> &b)");

	_data = nullptr;

	//allocate memory only if necessary
	if(this->size()){
		//allocate
		this->allocate(this->size());
		//copy data
		for(size_t i=0;i<this->size();i++) (*this)[i] = b[i];
	}
}

//------------------------------------------------------------------------------
//implementation of the move constructor
template<typename T> Buffer<T>::Buffer(Buffer<T> &&b):BufferObject(std::move(b)){
	_data = b._data;
	b._data = nullptr;
}

//------------------------------------------------------------------------------
//implementation of the destructor
template<typename T> Buffer<T>::~Buffer(){
	free();
}

//==============methods for data allocation ===================================
//implementation of is_allocated
template<typename T> bool Buffer<T>::is_allocated() const {
	if(_data) return true;
	return false;
}

//-----------------------------------------------------------------------------
//implementation of free
template<typename T> void Buffer<T>::free(){
	EXCEPTION_SETUP("template<typename T> void Buffer<T>::free()");
	if(this->is_allocated()) delete [] _data;
	_data = nullptr;
	this->size(0);
}

//------------------------------------------------------------------------------
//implementation of allocate
template<typename T> void Buffer<T>::allocate(const size_t &s){
	EXCEPTION_SETUP("void BufferObject::allocate(const size_t s)");

	//free memory if necessary
	if(is_allocated()) this->free();

	if(s==0){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory os size 0!");
		EXCEPTION_THROW();
	}

	//set the new size of the buffer
	this->size(s);

	_data = new T[this->size()];
	if(!_data){
		EXCEPTION_INIT(MemoryAllocationError,"Error allocating buffer memory!");
		EXCEPTION_THROW();
	}
}

//====================methods to access the data pointer========================
template<typename T> void *Buffer<T>::void_ptr(){
	return (void *)_data;
}

template<typename T> const void *Buffer<T>::void_ptr() const {
	return (void *)_data;
}

template<typename T> T *Buffer<T>::ptr(){
	return _data;
}

template<typename T> const T *Buffer<T>::ptr() const {
	return _data;
}


//===================assignment operators=======================================
//implementation of copy assignment
template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b){
	EXCEPTION_SETUP("template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b)");

	if(&b != this){
		//free this buffer if it is allocated
		this->free();
		//now assign all parameters from the original buffer to the new one
		(BufferObject &)(*this) = (BufferObject &)b;
		//call allocate (which will do nothing if there is nothing to allocate)

		if(this->size()){
			this->allocate(this->size());

			for(size_t i=0;i<this->size();i++) (*this)[i] = b[i];
		}
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment
template<typename T> Buffer<T> &Buffer<T>::operator=(Buffer<T> &&b){
	if(this != &b){
		(BufferObject &)(*this) = std::move((BufferObject &)b);

		_data = b._data;
		b._data = nullptr;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of single value assignment
template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d){
	EXCEPTION_SETUP("template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d)");
	Buffer<T> &b = *this;

	if(!this->is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"Cannot assign data to an unallocated buffer!");
		EXCEPTION_THROW();
	}

	//we do not need to check the size here because if the buffer is allocated
	//the size is necessarily not zero
	for(size_t i=0;i<b.size();i++) b[i] = d;


	return *this;
}

//======================operators for data access===============================
//implementation of read write access
template<typename T> T& Buffer<T>::operator[](size_t n){
	EXCEPTION_SETUP("template<typename T> T& Buffer<T>::operator[](size_t n)");

	if(!this->is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
		EXCEPTION_THROW();
	}

	if(n>=this->size()){
		std::ostringstream sstr;
		sstr<<"Index ("<<n<<") must not be larger or equal the size ("<<this->size()<<")of the buffer!";
		EXCEPTION_INIT(IndexError,sstr.str());
		EXCEPTION_THROW();
	}

	return _data[n];
}

//------------------------------------------------------------------------------
//implementation of read only access
template<typename T> T Buffer<T>::operator[](size_t n) const {
	EXCEPTION_SETUP("template<typename T> T Buffer<T>::operator[](size_t n) const");

	if(!this->is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
		EXCEPTION_THROW();
	}

	if(n>=this->size()){
		std::ostringstream sstr;
		sstr<<"Index ("<<n<<") must not be larger or equal the size ("<<this->size()<<")of the buffer!";
		EXCEPTION_INIT(IndexError,sstr.str());
		EXCEPTION_THROW();
	}
	return _data[n];
}

//==============comparison operators============================================
template<typename T,typename U>
bool operator==(const Buffer<T> &a,const Buffer<U> &b){
	if(a.size() != b.size()) return false;

	if(a.is_allocated()!=b.is_allocated()) return false;

	if(a.is_allocated() && b.is_allocated()){
		for(size_t i=0;i<a.size();i++){
			if(a[i] != b[i]) return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
template<typename T> bool operator==(const Buffer<T> &a,const Buffer<T> &b){
	if(a.size() != b.size()) return false;

	if(a.is_allocated()!=b.is_allocated()) return false;

	if(a.is_allocated() && b.is_allocated()){
		for(size_t i=0;i<a.size();i++){
			if(a[i] != b[i]) return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
template<typename T,typename U>
bool operator!=(const Buffer<T> &a,const Buffer<U> &b){
	if(a == b) return false;
	return true;
}

//-----------------------------------------------------------------------------
template<typename T> bool operator!=(const Buffer<T> &a,const Buffer<T> &b){
	if(a == b) return false;
	return true;
}


//end of namespace
}
}
#endif /* BUFFER_HPP_ */
