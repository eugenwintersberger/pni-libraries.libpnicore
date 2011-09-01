/*
 * Buffer.hpp
 *
 *  Created on: Apr 11, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <iostream>
#include <string>
#include <boost/shared_array.hpp>
#include "Exceptions.hpp"
#include "PNITypes.hpp"
#include "BufferObject.hpp"

namespace pni{
namespace utils{



template<typename T> class Buffer;
template<typename T> bool operator==(const Buffer<T> &,const Buffer<T> &);
template<typename T> bool operator!=(const Buffer<T> &,const Buffer<T> &);

//! buffer template

//! Class Buffer describes a contiguous region of memory holding
//! data. The class is implemented as a template and can hold all
//! kind of data. Memory is allocated in a way that it is always
//! aligned correctly to optimize access performance.
//! The basic idea of this class is to hide details of memory allocation
//! for a buffer from the user. Until now there is not too much secret in
//! this class. Since we assume actually only numerical values to be
//! stored the compiler should ensure correct memory alignment in any case.
//!
//! Future implementations of this structure may include thread safety using
//! the BOOST threading classes.
template<typename T>class Buffer:public BufferObject{
protected:
public:
	typedef boost::shared_ptr<Buffer<T> > sptr; //smart pointer
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
	Buffer(UInt64 n);
	//! destructor
	virtual ~Buffer();


	//! \return pointer to the memory allocated by the buffer
	const T* getPtr() const { return (T *)_ptr; }
	//! return a pointer to the data

	//! \return pointer to the memory allocated by the buffer
	T* getPtr() { return (T *)_ptr;}

	//! [] operator for read and write access

	//! This operator will be used in expressions where the buffer access stands
	//! on the left side of an assignment operation. In other words - when data should
	//! be written to the buffer.
	T& operator[](UInt64 n);
	//! [] operator for read only access

	//! This operator will be used in expressions where read only access to the
	//! data values in the buffer is required.
	T operator[](UInt64 n) const;
	//! overloaded assigment operator

	//! the buffer is initialized with the content of an other buffer.
	//! If the size of the two buffers matches data is only copied. Otherwise
	//! memory will be reallocated in order to match the size of buffer b.
	Buffer<T> &operator=(const Buffer<T> &b);
	//! initialization by a single value

	//! The assignment operator (=) can be used to set all values of the buffer to a
	//! single value v.
	Buffer<T> &operator=(const T &v);

	//! == equality operator

	//! Two buffers are considered equal if their size and content matches.
	friend bool operator== <> (const Buffer<T> &b1,const Buffer<T> &b2);
	//! != inequality operator

	//! The inverse of the == operator.
	friend bool operator!= <> (const Buffer<T> &b1,const Buffer<T> &b2);

};

template<typename T> Buffer<T>::Buffer():BufferObject(){
	_elem_size = sizeof(T);
}

template<typename T> Buffer<T>::Buffer(UInt64 n):BufferObject(n,sizeof(T)){
}

template<typename T> Buffer<T>::Buffer(const Buffer<T> &b):BufferObject(b){
}

template<typename T> Buffer<T>::~Buffer(){
}



template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b){
	unsigned long i;
	if(&b != this){
		(BufferObject)(*this) = (BufferObject)b;
	}

	return *this;
}

template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d){
	Buffer<T> &b = *this;

	for(UInt64 i=0;i<b.getSize();i++) b[i] = d;

	return *this;
}

template<typename T> bool operator==(const Buffer<T> &b1,const Buffer<T> &b2){
	UInt64 i;

	if(b1.getMemSize()!=b2.getMemSize()) return false;

	for(i=0;i<b1._size;i++){
		if(b1._data[i]!=b2._data[i]) return false;
	}

	return true;
}

template<typename T> bool operator!=(const Buffer<T> &b1,const Buffer<T> &b2){
	UInt64 i;

	if(!(b1==b2)){
		return true;
	}

	return false;
}

template<typename T> T& Buffer<T>::operator[](UInt64 n){
	EXCEPTION_SETUP("template<typename T> T& Buffer<T>::operator[](unsigned long n)");

	if(n>=getSize()){
		EXCEPTION_INIT(IndexError,"Index must not be larger or equal the size of the buffer!");
		EXCEPTION_THROW();
	}

	return ((T *)getVoidPtr())[n];
}

template<typename T> T Buffer<T>::operator[](UInt64 n) const {
	EXCEPTION_SETUP("template<typename T> T Buffer<T>::operator[](unsigned long n) const");

	if(n>=getSize()){
		EXCEPTION_INIT(IndexError,"Index must not be larger or equal the size of the buffer!");
		EXCEPTION_THROW();
	}
	return ((T *)getVoidPtr())[n];
}


//! @}
//end of namespace
}
}
#endif /* BUFFER_HPP_ */
