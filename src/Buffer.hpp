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
#include <boost/shared_array.hpp>
#include "Exceptions.hpp"
#include "PNITypes.hpp"
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
	//! constructor with buffer size

	//! Using this constructor the buffer will automatically allocate memory.
	//! \throws MemoryAllocationError if allocation on the heap fails
	//! \param n number of elements of type T in the buffer
	Buffer(UInt64 n);
	//! destructor
	virtual ~Buffer();

	//! assignment operator

	//! The content of the buffer on the lhs is set to that of the lhs.
	//! If necessary memory is reallocated.
	//! \throws MemoryAccessError if something goes wring with memory allocation
	//! \param b Buffer whose content will be assigned to this buffer
	//! \return reference to a Buffer<T> object
	Buffer<T> &operator=(const Buffer<T> &b);
	//! assignment operator

	//! Assignment operator for buffers with different types. Like the
	//!
	//! \throws TypeError if the two types cannot be assigned
	//! \throws RangeError if the values on the rhs exceed the limits of type T
	//! \throws MemoryAccessError if the buffer on the lhs is not allocated
	//! \throws SizeMissmatchError if sizes do not match
	//! \throws MemoryAllocationError if memory allocation fails
	//! \param b Buffer whose content will be assigned to this buffer
	//! \return reference to a Buffer<T> object
	template<typename U> Buffer<T> &operator=(const Buffer<U> &b);
	//! assignment operator

	//! This special form of the assignment operator can be used to assign
	//! a single value to all elements of the buffer. Thus, it is quite useful
	//! for initializing a buffer object.
	//! \param v value which to assign to all buffer elements
	//! \return reference to a buffer object
	Buffer<T> &operator=(const T &v);
	//! assignment operator

	//!
	template<typename U> Buffer<T> &operator=(const U &v);
	//! return data pointer

	//! Returns a typed const pointer to the allocated memory. The pointer must
	//! not be used to modify data values.
	//! \return pointer to allocated memory
	const T* getPtr() const;
	//! return data pointer

	//! Returns a typed pointer to the allocated memory. The pointer can be
	//! used for altering the buffer content.
	//! \return pointer to allocated memory
	T* getPtr();

	//! [] operator for read and write access

	//! This operator will be used in expressions where the buffer access stands
	//! on the left side of an assignment operation. In other words - when data should
	//! be written to the buffer.
	//! \throws IndexError if n is larger than the number of elements in the buffer
	//! \param n index of element to fetch
	//! \return reference to the n-th element in the buffer
	T& operator[](UInt64 n);
	//! [] operator for read only access

	//! This operator will be used in expressions where read only access to the
	//! data values in the buffer is required.
	//! \throws IndexError if n is larger than the number of elements in the buffer
	//! \param n index of the element to fetch
	//! \return value of the buffer at position n
	T operator[](UInt64 n) const;

	//! allocate memory

	//! Allocate memory on the heap. This method throws a MemoryAllocationError
	//! it it will be called on an already allocated buffer. An allocated buffer
	//! must be explicitly freed before this method can be reinvoked.
	//! Furthermore, this exception will be thrown if the number of
	//! elements is not set by calling the setSize() method.
	//! \throws MemoryAllocationError in cases of errors.
	//! \see allocate(const UInt64 &size)
	//! \see free()
	virtual void allocate();
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
	virtual bool isAllocated() const;
	//! frees memory

	//! This function frees the memory allocated by the buffer. It must be
	//! invoked before calling allocate() on an already allocated buffer.
	//! If the buffer is not allocated this method does nothing.
	virtual void free();
	//! read/write void pointer

	//! Returns a pointer of type void * on the allocated memory.
	//! \return pointer to allocated memory
	virtual void *getVoidPtr();
	//! read only void pointer

	//! Returns a read only void pointer to the allocated memory.
	//! \return pointer to allocated memory
	virtual const void *getVoidPtr() const;

};

//! @}

template<typename T> Buffer<T>::Buffer():BufferObject(){
	setElementSize((UInt64)sizeof(T));
	_data = NULL;
}

template<typename T> Buffer<T>::Buffer(UInt64 n):BufferObject(n,sizeof(T)){
	EXCEPTION_SETUP("template<typename T> Buffer<T>::Buffer(UInt64 n):BufferObject(n,sizeof(T))");

	_data = NULL;

	try{
		allocate();
	}catch(...){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Buffer failed!");
		EXCEPTION_THROW();
	}
}

template<typename T> Buffer<T>::Buffer(const Buffer<T> &b):BufferObject(b){
	EXCEPTION_SETUP("template<typename T> Buffer<T>::Buffer(const Buffer<T> &b):BufferObject(b)");

	_data = NULL;

	if(b.isAllocated()){
		try{
			allocate();
		}catch(...){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for Buffer failed!");
			EXCEPTION_THROW();
		}

		//if there is some data  - copy it
		if(getSize()!=0) for(UInt64 i=0;i<getSize();i++) (*this)[i] = b[i];
	}

}

template<typename T> Buffer<T>::~Buffer(){
	free();
}

//==============methods for data allocation ===================================
template<typename T> bool Buffer<T>::isAllocated() const {
	if(_data != NULL) return true;
	return false;
}

template<typename T> void Buffer<T>::free(){
	EXCEPTION_SETUP("template<typename T> void Buffer<T>::free()");
	if(isAllocated()) delete [] _data;
	_data = NULL;
}

template<typename T> void Buffer<T>::allocate(){
	EXCEPTION_SETUP("template<typename T> void Buffer<T>::allocate()");

	//if the size of the buffer is zero we do not need to allocate the something
	if(getSize()!=0){

		if(isAllocated()){
			EXCEPTION_INIT(MemoryAllocationError,"Buffer is already allocated - free buffer prior to new allocation!");
			EXCEPTION_THROW();
		}

		_data = new T[getSize()];
		if(_data == NULL){
			EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate buffer memory!");
			EXCEPTION_THROW();
		}
	}else{
		EXCEPTION_INIT(MemoryAllocationError,"Buffer size not set!");
		EXCEPTION_THROW();
	}
}


template<typename T> void Buffer<T>::allocate(const UInt64 &size){
	EXCEPTION_SETUP("void BufferObject::allocate(const UInt64 size)");
	if(!isAllocated()){
		//the allocate method checks if the size is zero and does allocation
		//if appropriate
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

//====================methods to access the data pointer========================
template<typename T> void *Buffer<T>::getVoidPtr(){
	return (void *)_data;
}

template<typename T> const void *Buffer<T>::getVoidPtr() const {
	return (void *)_data;
}

template<typename T> T *Buffer<T>::getPtr(){
	return _data;
}

template<typename T> const T *Buffer<T>::getPtr() const {
	return _data;
}


//===================assignment operators=======================================

template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b){
	EXCEPTION_SETUP("template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b)");

	if(&b != this){
		if(!b.isAllocated()){
			//if the rhs is not allocated we simply need to free memory
			//and copy the size
			if(isAllocated()) free();
			setSize(b.getSize());
		}else{
			//if the rhs is allocated we need to copy data
			if(getSize() != b.getSize()){
				//if the two buffers differ in size we need to allocate new memory
				if(isAllocated()) free();
				setSize(b.getSize());
				try{
					allocate();
				}catch(MemoryAllocationError &error){
					EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for buffer failed!");
					EXCEPTION_THROW();
				}
			}else{
				//what can happen now is that the buffers had the same size
				//but this buffer was not allocated yet
				if(!isAllocated()){
					try{
						allocate();
					}catch(MemoryAllocationError &error){
						EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for buffer failed!");
						EXCEPTION_THROW();
					}
				}
			}

			//copy data
			for(UInt64 i=0;i<getSize();i++) (*this)[i] = b[i];
		}
	}

	return *this;
}

template<typename T>
template<typename U> Buffer<T> &Buffer<T>::operator=(const Buffer<U> &b){
	EXCEPTION_SETUP("template<typename T> template<typename U> Buffer<T> &Buffer<T>::operator=(const Buffer<U> &b)");

	//check for type compatability
	if(!TypeCompat<T,U>::isAssignable){
		EXCEPTION_INIT(TypeError,"Cannot assign buffers - incompatible types!");
		EXCEPTION_THROW();
	}

	if(!b.isAllocated()){
		//if the rhs is not allocated we simply need to free memory
		//and copy the size
		if(isAllocated()) free();
		setSize(b.getSize());
	}else{
		//if the rhs is allocated we need to copy data
		if(getSize() != b.getSize()){
			//if the two buffers differ in size we need to allocate new memory
			if(isAllocated()) free();
			setSize(b.getSize());
			try{
				allocate();
			}catch(MemoryAllocationError &error){
				EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for buffer failed!");
				EXCEPTION_THROW();
			}
		}else{
			//what can happen now is that the buffers had the same size
			//but this buffer was not allocated yet
			if(!isAllocated()){
				try{
					allocate();
				}catch(MemoryAllocationError &error){
					EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for buffer failed!");
					EXCEPTION_THROW();
				}
			}
		}
		//copy data - we have to do a range check during copy
		for(UInt64 i=0; i<getSize();i++){
			U value = b[i];
			if(!TypeRange<T>::checkRange(value)){
				EXCEPTION_INIT(RangeError,"Cannot assign buffers - value exceeds lhs type bounds!");
				EXCEPTION_THROW();
			}
			(*this)[i] = (T)value;
		}
	}



	return *this;
}

template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d){
	EXCEPTION_SETUP("template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d)");
	Buffer<T> &b = *this;

	if(!isAllocated()){
		EXCEPTION_INIT(MemoryAccessError,"Cannot assign data to an unallocated buffer!");
		EXCEPTION_THROW();
	}

	//we do not need to check the size here because if the buffer is allocated
	//the size is necessarily not zero
	for(UInt64 i=0;i<b.getSize();i++) b[i] = d;


	return *this;
}

template<typename T>
template<typename U> Buffer<T> &Buffer<T>::operator=(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Buffer<T> &Buffer<T>::operator=(const U &v)");

	if(!isAllocated()){
		EXCEPTION_INIT(MemoryAccessError,"Cannot assign data to an unallocated buffer!");
		EXCEPTION_THROW();
	}

	//check for assignment compatability
	if(!TypeCompat<T,U>::isAssignable){
		EXCEPTION_INIT(TypeError,"Types are incompatible for assignment!");
		EXCEPTION_THROW();
	}

	//check for range
	if(!TypeRange<T>::checkRange(v)){
		EXCEPTION_INIT(RangeError,"Value exceeds type bounds!");
		EXCEPTION_THROW();
	}

	//now everything is fine can do assignment - like above we do not
	//need to check the size of the buffer, it must be different from zero
	for(UInt64 i=0; i<getSize();i++) _data[i] = (T)v;


	return *this;
}

//======================operators for data access===============================
template<typename T> T& Buffer<T>::operator[](UInt64 n){
	EXCEPTION_SETUP("template<typename T> T& Buffer<T>::operator[](unsigned long n)");

	if(!isAllocated()){
		EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
		EXCEPTION_THROW();
	}

	if(n>=getSize()){
		EXCEPTION_INIT(IndexError,"Index must not be larger or equal the size of the buffer!");
		EXCEPTION_THROW();
	}

	return _data[n];
}

template<typename T> T Buffer<T>::operator[](UInt64 n) const {
	EXCEPTION_SETUP("template<typename T> T Buffer<T>::operator[](unsigned long n) const");

	if(!isAllocated()){
		EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
		EXCEPTION_THROW();
	}

	if(n>=getSize()){
		EXCEPTION_INIT(IndexError,"Index must not be larger or equal the size of the buffer!");
		EXCEPTION_THROW();
	}
	return _data[n];
}

//==============comparison operators============================================
template<typename T,typename U>
bool operator==(const Buffer<T> &a,const Buffer<U> &b){
	if(a.getSize() != b.getSize()) return false;

	if(a.isAllocated()!=b.isAllocated()) return false;

	if(a.isAllocated() && b.isAllocated()){
		for(UInt64 i=0;i<a.getSize();i++){
			if(a[i] != b[i]) return false;
		}
	}

	return true;
}

template<typename T> bool operator==(const Buffer<T> &a,const Buffer<T> &b){
	if(a.getSize() != b.getSize()) return false;

	if(a.isAllocated()!=b.isAllocated()) return false;

	if(a.isAllocated() && b.isAllocated()){
		for(UInt64 i=0;i<a.getSize();i++){
			if(a[i] != b[i]) return false;
		}
	}

	return true;
}

template<typename T,typename U>
bool operator!=(const Buffer<T> &a,const Buffer<U> &b){
	if(a == b) return false;
	return true;
}

template<typename T> bool operator!=(const Buffer<T> &a,const Buffer<T> &b){
	if(a == b) return false;
	return true;
}


//end of namespace
}
}
#endif /* BUFFER_HPP_ */
