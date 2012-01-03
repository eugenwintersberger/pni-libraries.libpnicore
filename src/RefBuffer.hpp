/*
 * Declaration of the RefBuffer<T> template
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
 * Created on: Jan 02, 2012
 *     Author: Eugen Wintersberger
 *
 */



#ifndef __REFBUFFER_HPP_
#define __REFBUFFER_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <boost/shared_array.hpp>
#include "Exceptions.hpp"
#include "Types.hpp"
#include "BufferObject.hpp"
#include "Buffer.hpp"
#include "TypeIDMap.hpp"

namespace pni{
namespace utils{

//! \ingroup data_classes
//! \brief ref. buffer template

//! This template is a concrete implementation of the BufferObject base class.
//! Unlike the Buffer<T> template this object can be used to provide a buffer
//! interface to memory allocated by other instances. Hence it is quite useful
//! to connect to third party libraries.
//! As the class is not responsible  for memory allocation it also frees no 
//! memory. Thus memory management is entirely in the hand of third party
//! instances.
//! Such a reference buffer can either be initialized from a raw pointer, an
//! instance of Buffer<T>, or from a different RefBuffer object.
template<typename T>class RefBuffer:public BufferObject{
private:
	T *_data; //!< pointer to the data block

public:
	typedef boost::shared_ptr<RefBuffer<T> > sptr; //!< smart pointer to a typed buffer
    //-----------------constructors and destructors----------------------------
	//! default constructor
	RefBuffer();
	//! copy constructor

	//! The buffer is initialized by an already existing reference buffer. 
	RefBuffer(const RefBuffer<T> &b);

    //! copy constructor

    //! A reference buffer can also be initialized by a Buffer<T> object. 
    RefBuffer(const Buffer<T> &b);
	//! move constructor
	RefBuffer(RefBuffer<T> &&b);
	//! constructor with buffer size

	//! Using this constructor the buffer will automatically allocate memory.
	//! \throws MemoryAllocationError if allocation on the heap fails
	//! \param n number of elements of type T in the buffer
	RefBuffer(size_t n,T *data);
	//! destructor
	virtual ~RefBuffer();

    //---------------assignment operators---------------------------------------
	//! copy assignment operator

	//! \return reference to a Buffer<T> object
	RefBuffer<T> &operator=(const RefBuffer<T> &b);
	//! move assignment operator
	RefBuffer<T> &operator=(RefBuffer<T> &&b);
    //! copy assignment operator from Buffer<T>

    //! The reference buffer holds a reference to the data which was allocated 
    //! by the b. 
    RefBuffer<T> &operator=(const Buffer<T> &b);
	//! single value assignment operator

	//! This special form of the assignment operator can be used to assign
	//! a single value to all elements of the buffer. Thus, it is quite useful
	//! for initializing a buffer object.
	//! \param v value which to assign to all buffer elements
	//! \return reference to a buffer object
	RefBuffer<T> &operator=(const T &v);

    //---------------data access methods---------------------------------------
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

	virtual void *void_ptr();

	virtual const void *void_ptr() const;

	virtual T get(size_t i) const;
	virtual void set(size_t i,const T &o);

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

    //! allocate memory - does nothing

    //! For a RefBuffer this method has no effect.
	virtual void allocate(const size_t &size);
    
    //! check if buffer is allocated

    //! The behavior of this method varies slightly from the original
    //! definition. As a RefBuffer has no influence on the allocation 
    //! of memory this method returns true if the pointer it referes 
    //! to is not a nullptr. 
    //! \return true if pointer is not nullptr, false otherwise
	virtual bool is_allocated() const;

    //! free memory - does nothing

    //! In the case of a RefBuffer this method does not free memory 
    //! but resets the internal data pointer to nullptr.
	virtual void free();

	virtual size_t element_size() const {
		return sizeof(T);
	}

	virtual size_t mem_size() const {
		return sizeof(T)*this->size();
	}

	virtual TypeID type_id() const {
		return TypeIDMap<T>::type_id;
	}


};

//=================Implementation of constructors and destructors===============
//implementation of the default constructor
template<typename T> RefBuffer<T>::RefBuffer():BufferObject(){
	_data = nullptr;
}

//------------------------------------------------------------------------------
//implementation of the copy from RefBuffer constructor
template<typename T> RefBuffer<T>::RefBuffer(const RefBuffer<T>& o)
:BufferObject(o)
{
    _data = o._data;
}

//------------------------------------------------------------------------------
//implementation of the copy constructor
template<typename T> RefBuffer<T>::RefBuffer(const Buffer<T> &b):BufferObject(b){
	_data = b.ptr();
}

//------------------------------------------------------------------------------
//implementation of the move constructor
template<typename T> RefBuffer<T>::RefBuffer(RefBuffer<T> &&b)
    :BufferObject(std::move(b)){
	_data = b._data;
	b._data = nullptr;
}

//------------------------------------------------------------------------------
//implementation of the standard constructor
template<typename T> RefBuffer<T>::RefBuffer(size_t n,T *data):BufferObject(n){
	_data = data;
}

//------------------------------------------------------------------------------
//implementation of the destructor
template<typename T> RefBuffer<T>::~RefBuffer(){
	free();
}

//===================assignment operators=======================================
//implementation of copy assignment
template<typename T> RefBuffer<T> &RefBuffer<T>::operator=(const RefBuffer<T> &b){
    
	if(&b != this){
		//now assign all parameters from the original buffer to the new one
		(BufferObject &)(*this) = (BufferObject &)b;
		//call allocate (which will do nothing if there is nothing to allocate)
        
        _data = b._data;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment
template<typename T> RefBuffer<T> &RefBuffer<T>::operator=(RefBuffer<T> &&b){
	if(this != &b){
		(BufferObject &)(*this) = std::move((BufferObject &)b);

		_data = b._data;
		b._data = nullptr;
	}

	return *this;
}

//-----------------------------------------------------------------------------
//copy assignment from Buffer<T> template
template<typename T> RefBuffer<T> &RefBuffer<T>::operator=(const Buffer<T> &b){
   (BufferObject &)(*this) = (BufferObject &)(b);

   _data = b.ptr();
    
   return *this;
}

//------------------------------------------------------------------------------
//implementation of single value assignment
template<typename T> RefBuffer<T> &RefBuffer<T>::operator=(const T &d){
	EXCEPTION_SETUP("template<typename T> RefBuffer<T> &RefBuffer<T>::operator=(const T &d)");

	if(!_data){
		EXCEPTION_INIT(MemoryAccessError,"Cannot assign data to an unallocated buffer!");
		EXCEPTION_THROW();
	}

	//we do not need to check the size here because if the buffer is allocated
	//the size is necessarily not zero
	for(size_t i=0;i<this->size();i++) (*this)[i] = d;


	return *this;
}
//==============methods for data allocation ===================================
//implementation of is_allocated
template<typename T> bool RefBuffer<T>::is_allocated() const {
	if(_data) return true;
	return false;
}

//-----------------------------------------------------------------------------
//implementation of free
template<typename T> void RefBuffer<T>::free(){
    _data = nullptr;
}

//------------------------------------------------------------------------------
//implementation of allocate
template<typename T> void RefBuffer<T>::allocate(const size_t &s){
}

//====================methods to access the data pointer========================
template<typename T> void *RefBuffer<T>::void_ptr(){
	return (void *)_data;
}

//------------------------------------------------------------------------------
template<typename T> const void *RefBuffer<T>::void_ptr() const {
	return (void *)_data;
}

//------------------------------------------------------------------------------
template<typename T> T *RefBuffer<T>::ptr(){
	return _data;
}

//------------------------------------------------------------------------------
template<typename T> const T *RefBuffer<T>::ptr() const {
	return _data;
}



//===============Methods for data access========================================
template<typename T> T RefBuffer<T>::get(size_t i) const {
	EXCEPTION_SETUP("template<typename T> T get(size_t i) const");

	if(!this->is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated");
		EXCEPTION_THROW();
	}

	if(i>=this->size()){
		std::ostringstream sstr;
		sstr<<"Index ("<<i<<") must not be larger or equal the size ("<<this->size()<<")of the buffer!";
		EXCEPTION_INIT(IndexError,sstr.str());
		EXCEPTION_THROW();
	}

	return _data[i];
}

//------------------------------------------------------------------------------
template<typename T> void RefBuffer<T>::set(size_t i,const T &o){
	EXCEPTION_SETUP("template<typename T> void Buffer<T>::set(size_t i,const T &o)");

	if(!this->is_allocated()){
		EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
		EXCEPTION_THROW();
	}

	if(i>=this->size()){
		std::ostringstream sstr;
		sstr<<"Index ("<<i<<") must not be larger or equal the size ("<<this->size()<<")of the buffer!";
		EXCEPTION_INIT(IndexError,sstr.str());
		EXCEPTION_THROW();
	}

	_data[i] = o;
}

//======================operators for data access===============================
//implementation of read write access
template<typename T> T& RefBuffer<T>::operator[](size_t n){
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
template<typename T> T RefBuffer<T>::operator[](size_t n) const {
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
bool operator==(const RefBuffer<T> &a,const RefBuffer<U> &b){
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
bool operator!=(const RefBuffer<T> &a,const RefBuffer<U> &b){
	if(a == b) return false;
	return true;
}




//end of namespace
}
}
#endif /* BUFFER_HPP_ */
