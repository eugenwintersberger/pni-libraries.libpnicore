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

namespace pni{
namespace utils{

//! \addtogroup Data-objects
//! @{

//! BufferObject - base class for data buffers

//! BufferObject is the base class for the Buffer<T> template.
//! This class can be used for polymorphic operations for accessing
//! instances of Buffer<T> objects of unknown data type.
class BufferObject{
protected:
	UInt64 _size;       //!< number of elements in the buffer
	UInt64 _elem_size;  //!< size of a single element
public:
	typedef boost::shared_ptr<BufferObject> sptr;  //!< smart pointer to a BufferObject
	//! default constructor
	BufferObject();
	//! copy constructor
	BufferObject(const BufferObject &b);
	//! constructor

	//! Constructor for a BufferObject that initializes the number of elements
	//! in the buffer and the element size (in bytes).
	//! \param n number of elements in the buffer
	//! \param es element size
	BufferObject(UInt64 n,UInt64 es);
	//! destructor
	virtual ~BufferObject();

	//! assignment operator
	BufferObject &operator=(const BufferObject &o);

	//! return the number of elements in the buffer
	virtual UInt64 getSize(){return _size;}
	//! return the total amount of memory allocated by the buffer
	virtual UInt64 getMemSize(){return _size*_elem_size;}

	//! resize an allready allocated buffer

	//! This method must be allocated by the concrete implementation
	//! of a buffer class - in other words by the child class.
	//! \param n new number of elements in the buffer
	virtual void resize(UInt64 n){}
	//! initial memory allocation

	//! Use this method to allocate memory the first time after
	//! creating a buffer object. This method must be implemented
	//! by child classes of DataBuffer.
	//! \param n number of elements in the buffer
	virtual void allocate(UInt64 n){}

	//! return a void pointer to the allocated memory
	virtual void *getVoidPtr(){ return NULL; }
};

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
	T* _data;            //!< pointer to the data held by the buffer
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
	Buffer(unsigned long n);
	//! destructor
	virtual ~Buffer();

	//! resize the buffer

	//! Reallocate memory to store n elements of type T in the Buffer. The
	//! operation does not alter or reset the content of the buffer. If the
	//! new size of the buffer is larger then the original one the last data value
	//! from the original content will be copied to the newly allocated additional
	//! positions. If the  new size is smaller then the original one, data whose
	//! position would exceed the new size is discarded.
	//! One should to keep in mind that resizing a buffer always requires new
	//! memory allocation and along with this a copy process of original data
	//! to the new memory locations. Therefore this operation should be handled with care.
	//! \param n number of elements for which memory should be allocated
	virtual void resize(unsigned long n);
	//! allocate memory in the buffer

	//! This method can be called if the buffer was created by the default
	//! constructor. An exception will be thrown if the internal data buffer
	//! is already allocated. If the buffer is already allocated use the
	//! resize method in order to change the amount of memory allocated by the buffer.
	//! \param n number of elements in the buffer for which data should be allocated
	virtual void allocate(unsigned long n);
	//! get the size of the buffer

	//! \return number of elements of type T in the buffer
	virtual unsigned long getSize() const {return _size;}
	//! get memory consumption of the buffer

	//! \return number of bytes occupied by the buffer data
	virtual unsigned long getMemSize() const { return (unsigned long)(sizeof(T)*_size);}

	//! return a pointer to the data

	//! \return pointer to the memory allocated by the buffer
	const T* getPtr() const { return _data; }
	//! return a pointer to the data

	//! \return pointer to the memory allocated by the buffer
	T* getPtr() { return _data;}

	//! return a void pointer to the allocate data
	virtual void *getVoidPtr(){ return (void *)_data;}

	//! [] operator for read and write access

	//! This operator will be used in expressions where the buffer access stands
	//! on the left side of an assignment operation. In other words - when data should
	//! be written to the buffer.
	T& operator[](unsigned long n);
	//! [] operator for read only access

	//! This operator will be used in expressions where read only access to the
	//! data values in the buffer is required.
	T operator[](unsigned long n) const;
	//! overloaded assigment operator

	//! the buffer is initialized with the content of an other buffer.
	//! If the size of the two buffers matches data is only copied. Otherwise
	//! memory will be reallocated in order to match the size of buffer b.
	Buffer &operator=(const Buffer<T> &b);
	//! initialization by a single value

	//! The assignment operator (=) can be used to set all values of the buffer to a
	//! single value v.
	Buffer &operator=(const T &v);

	//! == equality operator

	//! Two buffers are considered equal if their size and content matches.
	friend bool operator== <> (const Buffer<T> &b1,const Buffer<T> &b2);
	//! != inequality operator

	//! The inverse of the == operator.
	friend bool operator!= <> (const Buffer<T> &b1,const Buffer<T> &b2);

};

template<typename T> Buffer<T>::Buffer():BufferObject(){
	_data = NULL;
	_elem_size = sizeof(T);
}

template<typename T> Buffer<T>::Buffer(unsigned long n):BufferObject(n,sizeof(T)){
	_data = new T[n];
	if(_data ==NULL){
		//if memory allocation fails - throw an MemoryAllocationException
		MemoryAllocationError e(std::string("Buffer<T>"),
								std::string("Cannot allocate Buffer memory in constructor!"));
		throw e;
	}
}

template<typename T> Buffer<T>::Buffer(const Buffer<T> &b):BufferObject(b){
	_data = new T[b._size];
	if(_data == NULL){
		//if memory allocation fails - throw an MemoryAllocationException
		MemoryAllocationError e(std::string("Buffer<T>"),
		     					std::string("Cannot allocate Buffer memory in constructor!"));
		throw e;
	}

	//copy data from the original buffer to the new one
	for(unsigned long i=0;i<_size;i++) _data[i] = b._data[i];
}

template<typename T> Buffer<T>::~Buffer(){
	if(_data!=NULL) delete _data;
}

template<typename T> void Buffer<T>::resize(unsigned long n){
	unsigned long i;
	unsigned long nmax;

	//check here if the buffer has already allocated memory
	if(_data != NULL){
		//if data has been already allocated - acquire new
		//heap memory from the system and raise an exception if this fails
		T *_new_data = new T[n];
		if(_new_data == NULL){
			//if memory allocation fails - throw an MemoryAllocationException
				MemoryAllocationError e(std::string("Buffer<T>"),
										std::string("Cannot allocate Buffer memory in constructor!"));
				throw e;
		}

		//if the size of the new buffer is larger then the first
		//elements up to _n values correspond to the original data
		//otherwise the content of the original buffer exceeding the
		//size of the new one will be discarded.
		if(n>_size){
			nmax = _size;
		}else{
			nmax = n;
		}

		for(i=0;i<nmax;i++){
			_new_data[i] = _data[i];
		}

		//finally we can free the old buffer
		delete [] _data;
		_data = _new_data;
		_size = n;

	}else{
		//in this case the buffer was not allocated - we can simple
		//call the allocate() method
		allocate(n);
	}
}

template<typename T> void Buffer<T>::allocate(unsigned long n){
	//allcoate memory for the buffer
	if(_data == NULL){
		_data = new T[n];
		_size = n;
	}
}

template<typename T> Buffer<T> &Buffer<T>::operator=(const Buffer<T> &b){
	unsigned long i;
	if(&b != this){
		//resize the buffer to match the size of the buffer to copy
		resize(b._size);

		//copy the data
		for(i=0;i<_size;i++) _data[i] = b._data[i];
	}

	return *this;
}

template<typename T> Buffer<T> &Buffer<T>::operator=(const T &d){
	unsigned long i;
	if(_data!=NULL){
		for(i=0;i<_size;i++) _data[i] = d;
	}

	return *this;
}

template<typename T> bool operator==(const Buffer<T> &b1,const Buffer<T> &b2){
	unsigned long i;

	if(b1._size!=b2._size) return false;

	for(i=0;i<b1._size;i++){
		if(b1._data[i]!=b2._data[i]) return false;
	}

	return true;
}

template<typename T> bool operator!=(const Buffer<T> &b1,const Buffer<T> &b2){
	unsigned long i;

	if(b1._size!=b2._size) return true;

	for(i=0;i<b1._size;i++){
		if(b1._data[i]!=b2._data[i]) return true;
	}

	return false;
}

template<typename T> T& Buffer<T>::operator[](unsigned long n){
	if(n>=_size){
		IndexError e;
		e.setSource("Buffer<T>::operator[]");
		e.setDescription("Index must not be larger or equal the size of the buffer!");
		throw e;
	}

	return _data[n];
}

template<typename T> T Buffer<T>::operator[](unsigned long n) const {
	if(n>=_size){
		IndexError e;
		e.setSource("Buffer<T>::operator[]");
		e.setDescription("Index must not be larger or equal the size of the buffer!");
		throw e;
	}
	return _data[n];
}


//! @}
//end of namespace
}
}
#endif /* BUFFER_HPP_ */
