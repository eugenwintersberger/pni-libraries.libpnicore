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
#include "TypeInfo.hpp"

namespace pni{
namespace utils{

//! \addtogroup Data-objects
//! @{

//! \brief buffer template

//! This template acts as a type-safe wrapper for the BufferObject class. It allows
//! typed access to data stored in the BufferObject. The template itself
//! holds no data at all. It simply wraps the access to BufferObject.
template<typename T>class Buffer:public BufferObject{
protected:
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
	Buffer(UInt64 n);
	//! destructor
	virtual ~Buffer();

	//! buffer conversion

	//! This method allows conversion between different types of typed buffers.
	//! The method can be used for instance to convert an existing integer buffer to a float buffer.
	//! This method works only for numeric types defined in PNITypes.hpp.
	//! However, there are several restrictions that you should keep in mind before
	//! using this method
	//! - complex numbers can only be converted to other complex numbers
	//! - the size of the target type must be equal or larger than that of the source
	//! - signed numbers can only be converted to unsigned if the source buffer contains no negative values
	//!
	//! If one of these conditions is not satisfied an exception will be raised.
	//! If necessary the target buffer will be reallocated to fit the size of the source buffer. This
	//! must not be a performance issue in cases where the target buffer has not been initialized yet.
	//! \throws TypeError if condition 1 and to are not meet
	//! \throws RangeError if you try to convert to an unsigned type though the buffer holds negative values
	//! \throws MemoryAllocationError
	template <typename U> void convert(Buffer<U> &b) const;

	//! return data pointer

	//! Returns a typed const pointer to the allocated memory. The pointer must not be used to
	//! modify data values.
	//! \return pointer to allocated memory
	const T* getPtr() const { return (T *)getVoidPtr(); }
	//! return data pointer

	//! Returns a typed pointer to the allocated memory. The pointer can be used for altering the
	//! buffer content.
	//! \return pointer to allocated memory
	T* getPtr() { return (T *)getVoidPtr();}

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
	//! assigment operator

	//! The buffer is initialized with the content of an other buffer.
	//! If the size of the buffers do not match new memory is allocated.
	//! \throws MemoryAllocationError if memory allocation fails
	//! \param b Buffer whose content will be assigned to this buffer
	//! \return reference to a Buffer<T> object
	Buffer<T> &operator=(const Buffer<T> &b);
	//! assignment operator

	//! This special form of the assignment operator can be used to assign
	//! a single value to all elements of the buffer. Thus, it is quite useful
	//! for initializing a buffer object.
	//! \param v value which to assigne to all buffer elements
	//! \return reference to a buffer object
	Buffer<T> &operator=(const T &v);

};

//! @}

template<typename T> Buffer<T>::Buffer():BufferObject(){
	setElementSize((UInt64)sizeof(T));
}

template<typename T> Buffer<T>::Buffer(UInt64 n):BufferObject(n,sizeof(T)){
}

template<typename T> Buffer<T>::Buffer(const Buffer<T> &b):BufferObject(b){
}

template<typename T> Buffer<T>::~Buffer(){
}

template<typename T>
template<typename U> void Buffer<T>::convert(Buffer<U> &b) const{
	EXCEPTION_SETUP("template<typename T> template<typename U> Buffer<U> Buffer<T>::convert() const");
	//check if type conversion is possible
	const Buffer<T> &s = *this;

	//you cannot convert a complex number fo a non-complex number
	if((TypeInfo<T>::is_complex)&&(!TypeInfo<U>::is_complex)){
		EXCEPTION_INIT(TypeError,"You try to convert a complex to a non-complex number!");
		EXCEPTION_THROW();
	}

	//you cannot convert a larger type to a smaller type
	if(TypeInfo<T>::size > TypeInfo<U>::size){
		EXCEPTION_INIT(TypeError,"Sizes of types do not match!");
		EXCEPTION_THROW();
	}

	//check if the target is an integer while the source a float
	if((TypeInfo<U>::is_integer)&&(!TypeInfo<T>::is_integer)){
		EXCEPTION_INIT(TypeError,"You try to convert a float buffer to an integer buffer - does not work");
		EXCEPTION_THROW();
	}

	//check if sign is ok - you cannot convert a buffer of a signed type to an unsigned
	//the other direction always works
	if((!TypeInfo<U>::is_signed)&&(TypeInfo<T>::is_signed)){
		//want to convert a signed type to an unsigned - we have to check if
		//there are negative values in this buffer
		for(UInt64 i = 0; i<getSize();i++){
			if(s[i] < 0){
				EXCEPTION_INIT(RangeError,"You try to convert a signed to an unsigned buffer but the source contains negative numbers!");
				EXCEPTION_THROW();
			}
		}
	}

	//reallocate the target buffer if necessary.
	if(b.getSize()!=getSize()){
		b.free();
		b.setSize(getSize());
		try{
			b.allocate();
		}catch(MemoryAllocationError &error){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation failed during buffer conversion!");
			EXCEPTION_THROW();
		}
	}

	for(UInt64 i=0;i<b.getSize();i++) b[i] = s[i];

}

template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b){
	EXCEPTION_SETUP("template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b)");

	if(&b != this){
		try{
			BufferObject &this_buffer = (BufferObject &)(*this);
			BufferObject &that_buffer = (BufferObject &)(b);
			this_buffer = that_buffer;
		}catch(MemoryAllocationError &error){
			EXCEPTION_INIT(MemoryAllocationError,"Memory allocation failed during buffer assignment!");
			EXCEPTION_THROW();
		}
	}

	return *this;
}

template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d){
	Buffer<T> &b = *this;

	for(UInt64 i=0;i<b.getSize();i++) b[i] = d;

	return *this;
}

template<typename T> T& Buffer<T>::operator[](UInt64 n){
	EXCEPTION_SETUP("template<typename T> T& Buffer<T>::operator[](unsigned long n)");

	if(n>=getSize()){
		EXCEPTION_INIT(IndexError,"Index must not be larger or equal the size of the buffer!");
		EXCEPTION_THROW();
	}

	return (getPtr()[n]);
}

template<typename T> T Buffer<T>::operator[](UInt64 n) const {
	EXCEPTION_SETUP("template<typename T> T Buffer<T>::operator[](unsigned long n) const");

	if(n>=getSize()){
		EXCEPTION_INIT(IndexError,"Index must not be larger or equal the size of the buffer!");
		EXCEPTION_THROW();
	}
	return (getPtr()[n]);
}



//end of namespace
}
}
#endif /* BUFFER_HPP_ */
