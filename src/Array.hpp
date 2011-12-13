/*
 * Declaration of the Array<T> template
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
 * This header file declares the Array<T> template class.
 *
 * Created on: 18.05.2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include<iostream>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
#include<typeinfo>
#include<boost/shared_ptr.hpp>

#include "Buffer.hpp"
#include "Shape.hpp"
#include "Exceptions.hpp"
#include "Types.hpp"
#include "DataObject.hpp"
#include "ArrayObject.hpp"
#include "Index.hpp"
#include "Selection.hpp"

#include "ArrayTrait.hpp"
#include "TypeInfo.hpp"
#include "TypeIDMap.hpp"

namespace pni {
namespace utils {



//! \internal
template<typename T> class Array;

//binary operators must be defined here since they are implemented as friend operators
template<typename T> Array<T> operator+(const Array<T>&, const T&);
template<typename T> Array<T> operator+(const T&, const Array<T>&);
template<typename T> Array<T> operator+(const Array<T>&, const Array<T>&);

template<typename T> Array<T> operator-(const Array<T>&, const T&);
template<typename T> Array<T> operator-(const Array<T>&, const Array<T>&);
template<typename T> Array<T> operator-(const T&, const Array<T>&);

template<typename T> Array<T> operator*(const Array<T>&, const T&);
template<typename T> Array<T> operator*(const Array<T>&, const Array<T>&);
template<typename T> Array<T> operator*(const T&, const Array<T>&);

template<typename T> Array<T> operator/(const Array<T>&, const T&);
template<typename T> Array<T> operator/(const Array<T>&, const Array<T>&);
template<typename T> Array<T> operator/(const T&, const Array<T>&);

template<typename T> bool operator==(const Array<T> &, const Array<T> &);
template<typename T> bool operator!=(const Array<T> &, const Array<T> &);
template<typename T> std::ostream &operator<<(std::ostream &o,
		const Array<T> &a);

//! \ingroup Data-objects
//! \brief template for a multi-dimensional array class

//! This class represents a multidimensional array of data values. It consists of two
//! components: a pointer to an instance of type Buffer and a pointer to an instance
//! of type ArrayShape. From the point of object oriented programming such an array can
//! be considered as a special view on the linear data stream represented by the Buffer
//! object. The ArrayShape and Buffer object of the array are hold by smart pointers
//! which allows sharing of these objects between different arrays or other
//! program instances. How data is handled depends on which constructors are used
//! to create the array and which methods are used to modify data elements of an
//! instance of Array. Usually set and get methods as well as constructors come
//! in two flavors: one where constant references of native objects are passed to them
//! and one where smart pointers are used. In the former case the objects will be
//! recreated by the Array object and their content will be copied.
//! In the later case of the smart pointer versions only the pointers
//! will be changed which allows sharing of data between the Array and external
//! instances of the program using the array. The boost::shared_ptr avoids
//! problems with object ownership and makes it quite simple to implement this
//! behavior.

//! The motivation for the reallocation and copy processes for the reference type
//! methods and constructors is quite simple: one cannot be sure that the
//! instance which created the object or a simple pointer will not destroy the
//! object while still being used in the array. Therefore the copy process is
//! absolutely necessary.

template<typename T> class Array: public ArrayObject {
protected:
	Buffer<T> _data; //!< Buffer object holding the data
public:
	typedef T ElementType;  //!< type of an array element
	typedef boost::shared_ptr<Array<T> > sptr; //!< shared pointer to an Array<T>
	//! default constructor

	//! Neither ArrayShape nor Buffer object will be allocated. Buffer
	//! as well as shape must be handled later using the appropriate
	//! setBuffer(), setShape(), and allocate methods. This constructor
	//! is perfectly applicable in all cases where the type of the array
	//! is known at the time of definition but all other parameters
	//! are obtained later in the code.
	Array();
	//! copy constructor

	//! This constructor is a full copy constructor. A new array is created
	//! and the content of the original array is copied.
	Array(const Array<T> &);
	//! move constructor
	Array(Array<T> &&);
	//! constructor with an array shape pointer

	//! The pointer to an existing ArrayShape object is used to construct
	//! the Array-object.
	//!
	//! \param s - reference to a shape object
	//! \sa Array(const boost::shared_ptr<ArrayShape> &s)
	Array(const Shape &s);
	//! constructor where array shape and buffer object are set

	//! The constructor takes pointers to a shape object and a buffer
	//! object. An exception will be raised if their sizes do not match.
	//! To keep ownership the objects will be copied.

	//! \param s pointer to a shape object
	//! \param b pointer to a buffer object
	Array(const Shape &s, const Buffer<T> &b);

	//! constructor

	//! This constructors sets also name, unit, and description
	//! of the NumericObject base class.
	Array(const Shape &s,const String &n,const String &u,const String &d);
	Array(const Shape &s,const Buffer<T> &b,
		  const String &n,const String &u,const String &d);

	//! destructor
	virtual ~Array();

	virtual TypeID type_id() const;

	//! set the buffer of the array

	//! Manually set the Buffer object of the array. Here a reference to an
	//! existing Buffer object is passed to the method. In this case
	//! the Array object will allocate new memory and copy the content
	//! from the argument Buffer to the newly allocated.
	//! If the size of the Buffer object and the ArrayShape object in the
	//! Array do not match an exception will be raised.

	//! \param b reference to a Buffer object
	virtual void buffer(const BufferObject &b);

	//! obtain a smart pointer to the array Buffer
	virtual const BufferObject &buffer() const;

	//! assign a native type to the array

	//! Here a value of a native type will be assigned to the Array.
	//! The value is assigned to all elements of the array. Thus, this
	//! operator can be used for a quick initialization of an array with numbers.
	Array<T> &operator =(const T&);

	template<typename U> Array<T> &operator=(const U &v);
	//! assignment between two arrays

	//! This operation is only possible if the shapes of the two arrays are equal.
	//! If this is not the case an exception will be raised. The content of the
	//! array on the r.h.s of the operator is copied to the array on the l.h.s.
	//! of the operator. No memory allocation is done - only copying.
	Array<T> &operator =(const Array<T> &a);

	template<typename U> Array<T> &operator=(const Array<U> &a);

	//overloaded simple binary arithmetic operators
	//! binary + operator for arrays

	//! This version of the operator implements Array<T> + T operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator+<> (const Array<T>&, const T&);
	//overloaded simple binary arithmetic operators
	//! binary + operator for arrays

	//! This version of the operator implements T + Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator+<> (const T&, const Array<T>&);
	//overloaded simple binary arithmetic operators
	//! binary + operator for arrays

	//! This version of the operator implements Array<T> + Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator+<> (const Array<T>&, const Array<T>&);

	//! binary - operator for arrays

	//! This version of the operator implements Array<T> - T operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator-<> (const Array<T>&, const T&);
	//! binary - operator for arrays

	//! This version of the operator implements Array<T> - Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator-<> (const Array<T>&, const Array<T>&);
	//! binary - operator for arrays

	//! This version of the operator implements T - Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator-<> (const T&, const Array<T>&);

	//! binary * operator for arrays

	//! This version of the operator implements Array<T> * T operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator*<> (const Array<T>&, const T&);
	//! binary * operator for arrays

	//! This version of the operator implements Array<T> * Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator*<> (const Array<T>&, const Array<T>&);
	//! binary * operator for arrays

	//! This version of the operator implements T * Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator*<> (const T&, const Array<T>&);

	//! binary / operator for arrays

	//! This version of the operator implements Array<T> / T operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator /<> (const Array<T>&, const T&);
	//! binary / operator for arrays

	//! This version of the operator implements Array<T> / Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator /<> (const Array<T>&, const Array<T>&);
	//! binary / operator for arrays

	//! This version of the operator implements T / Array<T> operations.
	//! During the operation a temporary array object is created.
	friend Array<T> operator /<> (const T&, const Array<T>&);

	//these operators are important because they are performed
	//in-place - no new array is allocated
	//! addition operator - unary

	//! Adds a single native value of type T to all elements in the Array.
	//! This unary operator performs the operation in-place. No temporary
	//! array will be allocated.
	Array<T> &operator +=(const T&);
	//! addition operator - unary

	//! Adds the array on the r.h.s to that on the l.h.s. of the operator.
	//! The operation is performed in-place without the allocation of a
	//! temporary array. The shapes of the tow arrays must match otherwise
	//! a ShapeMissmatchError exception will be raised.
	Array<T> &operator +=(const Array<T>&);
	//! subtraction operator - unary

	//! Subtracts a single value of type T on the r.h.s. of the operator
	//! to the array on the l.h.s. The operation is performed in-place without
	//! creation of a temporary array.
	Array<T> &operator -=(const T&);
	//! subtraction operator - unary

	//! Subtracts the  array on the r.h.s. of the operator from that on the
	//! l.h.s. The operation is performed in-place without allocation of a
	//! temporary array. The shapes of the arrays must match otherwise a
	//! ShapeMissmatchError exception will be raised.
	Array<T> &operator -=(const Array<T>&);
	//! multiplication operator - unary

	//! Multiplies the single value of type T on the r.h.s. of the operator
	//! with all elements of the array on the l.h.s. The operation is performed
	//! in-place without allocation of a temporary array.
	Array<T> &operator *=(const T&);
	//! multiplication operator - unary

	//! Element wise multiplication of the array on the r.h.s of the operator
	//! with the array of the l.h.s. The operation is stored in-place without
	//! allocation of a temporary array. The shapes of the arrays must match
	//! otherwise a ShapeMissmatchError exception will be raised.
	Array<T> &operator *=(const Array<T>&);
	//! Division operator - unary

	//! Divide the elements of the array on the l.h.s. of the operator by the
	//! single value of type T on the r.h.s. THe operation is performed in-place
	//! without allocation of a temporary array.
	Array<T> &operator /=(const T&);
	//! Division operator - unary

	//! Element wise division of the array on the l.h.s. with the array on the
	//! r.h.s. The operation is done in-place without allocation of a temporary array.
	//! The arrays must match in shape otherwise a ShapeMissmatchError exception will be raised.
	Array<T> &operator /=(const Array<T>&);

	//some functions that are of importance for arrays

	//! compute the sum of all element in the array

	//! Computes the sum of all elements stored in the array.
	//! \return number of type T
	typename ArrayType<T>::Type Sum() const;
	//! minimum value

	//! returns the minimum element in the array.
	//! \return value of type T
	T Min() const;
	//! maximum value

	//! returns the maximum element in the array
	//! \return value of type T
	T Max() const;
	//! minimum and maximum in the array

	//! returns the minimum and maximum values in the array.
	//! \param min minimum value
	//! \param max maximum value
	void MinMax(T &min, T &max) const;
	//! clip the array data

	//! Set values greater or equal maxth to maxth and those smaller or equal minth
	//! to minth.

	//! \param minth minimum threshold
	//! \param maxth maximum threshold
	void Clip(T minth, T maxth);
	//! clip the array data

	//! Set values smaller or equal to minth to minval and those larger or equal than
	//! maxth to maxval.

	//! \param minth minimum threshold
	//! \param minval value for numbers smaller or equal to minth
	//! \param maxth maximum threshold
	//! \param maxval value for numbers larger or equal to maxth
	void Clip(T minth, T minval, T maxth, T maxval);
	//! clip minimum values

	//! Set value smaller or equal to a threshold value to threshold.

	//! \param threshold threshold value
	void MinClip(T threshold);
	//! clip minimum values

	//! Set values smaller or equal than a threshold value to value
	//! \param threshold threshold value
	//! \param value value to set the numbers to
	void MinClip(T threshold, T value);
	//! clip maximum values

	//! Set values larger or equal than threshold to threshold.
	//! \param threshold threshold value
	void MaxClip(T threshold);
	//! clip maximum values

	//! Set values larger or equal than threshold to value.

	//! \param threshold the threshold value for the clip operation
	//! \param value the value to set the numbers to
	void MaxClip(T threshold, T value);
	//! bracket operator - accessing linear data

	//! Using the []-operator allows to access the data stored in the array
	//! in a linear manner as it is stored by the buffer object.
	T& operator[](const UInt64 &i);
	T operator[](const UInt64 &i) const;
	T& operator()(const Index &i);
	T operator()(const Index &i) const;

	void operator()(const Selection &s,Array<T> &a) const;

	//operators for comparison

	//! equality between arrays

	//! Tow arrays are considered equal if they coincide in shape and data content.
	friend bool operator==<> (const Array<T> &b1, const Array<T> &b2);
	//! inequality between arrays

	//! Tow arrays are considered different if they have different shape or
	//! content.
	friend bool operator!=<> (const Array<T> &b1, const Array<T> &b2);
	//! output operator for console output
	friend std::ostream &operator<<<> (std::ostream &o, const Array<T> &a);

	virtual void allocate();

	virtual bool is_allocated() const{
		return _data.is_allocated();
	}

	virtual void reset(){
		_data.free();
		ArrayObject::reset();
	}

	virtual inline T *ptr(){
		return _data.ptr();
	}

	virtual inline const T* ptr() const {
		return _data.ptr();
	}

	virtual inline void *void_ptr(){
		return _data.void_ptr();
	}

	virtual inline const void *void_ptr() const{
		return _data.void_ptr();
	}

};

//=====================Constructors and destructors=============================
//default constructor
template<typename T> Array<T>::Array():ArrayObject() {
	EXCEPTION_SETUP("template<typename T> Array<T>::Array():ArrayObject()");

	//there is nothing to do in the default constructor
}

//------------------------------------------------------------------------------
//copy constructor - allocate new memory and really copy the data
template<typename T> Array<T>::Array(const Array<T> &a):ArrayObject(a){
	EXCEPTION_SETUP("template<typename T> Array<T>::Array(const Array<T> &a):ArrayObject(a)");

	//set buffer object
	try{
		_data = a._data;
	}catch(MemoryAllocationError &error){
		//raise an exception here if memory allocation failes
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for Buffer instance!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
template<typename T> Array<T>::Array(Array<T> &&a):ArrayObject(std::move(a)){
	_data = std::move(a._data);
}

//------------------------------------------------------------------------------
//construct a new array from a shape object - the recommended way
template<typename T> Array<T>::Array(const Shape &s) :
	ArrayObject(s) {
	EXCEPTION_SETUP("template<typename T> Array<T>::Array(const ArrayShape &s)");

	try{
		_data.allocate(s.size());
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for Buffer object!");
		EXCEPTION_THROW();
	}
}

//------------------------------------------------------------------------------
//implementation of an array constructor
template<typename T> Array<T>::Array(const Shape &s,const String &n,
		             const String &u,const String &d):
		             ArrayObject(s){
	EXCEPTION_SETUP("template<typename T> Array<T>::Array(const ArrayShape &s,"
					"const String &n,const String &u,const String &d)");

	try{
		_data.allocate(s.size());
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for Buffer object!");
		EXCEPTION_THROW();
	}

	//set additional attributes
	this->name(n);
	this->unit(u);
	this->description(d);
}

//-----------------------------------------------------------------------------
//Array construction from a shape and a buffer
template<typename T> Array<T>::Array(const Shape &s, const Buffer<T> &b) :
	ArrayObject(s) {
	EXCEPTION_SETUP("template<typename T> Array<T>::Array(const ArrayShape &s, const Buffer<T> &b):ArrayObject(s)");

	//first we need to check if buffer and shape have matching sizes
	if (s.size() != b.size()) {
		EXCEPTION_INIT(SizeMissmatchError,"Size of shape and buffer objects do not match!");
		EXCEPTION_THROW();
	}

	//creates a new buffer object
	try{
		_data = b;
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for array failed!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
//implementation of an array constructor
template<typename T> Array<T>::Array(const Shape &s, const Buffer<T> &b,
		const String &n,const String &u,const String &d) :
	ArrayObject(s) {
	EXCEPTION_SETUP("template<typename T> Array<T>::Array(const ArrayShape &s, const Buffer<T> &b):ArrayObject(s)");

	//first we need to check if buffer and shape have matching sizes
	if (s.size() != b.size()) {
		EXCEPTION_INIT(SizeMissmatchError,"Size of shape and buffer objects do not match!");
		EXCEPTION_THROW();
	}

	//creates a new buffer object
	try{
		_data = b;
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Memory allocation for array failed!");
		EXCEPTION_THROW();
	}

	//set additional parameters
	this->name(n);
	this->unit(u);
	this->description(d);

}

//------------------------------------------------------------------------------
//destructor for the array object
template<typename T> Array<T>::~Array() {
	_data.free();
}

//==============================================================================================
//Introspection of element type ID

template<typename T> TypeID Array<T>::type_id() const {
	return TypeIDMap<T>::type_id;
}




//===============================output operators==============================
template<typename T> std::ostream &operator<<(std::ostream &o,
		                                      const Array<T> &a){
	o << "Array of shape ("<<a.shape()<<")"<<std::endl;
	return o;
}

//======================Methods for data access and array manipulation=========

template<typename T> void Array<T>::buffer(const BufferObject &b) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::setBuffer(const Buffer<T> &b)");

	if(b.type_id() != this->type_id()){
		EXCEPTION_INIT(TypeError,"Buffer and Array type do not match!");
		EXCEPTION_THROW();
	}

	//if the shape is not set yet (means that its rank is 0) we do not have
	//to care.
	if (this->shape().size()!=0) {
		//if there exists already a shape object we have to check the size
		if (b.size() != this->shape().size()) {
			EXCEPTION_INIT(SizeMissmatchError,"Buffer and array size do not match!");
			EXCEPTION_THROW();
		}
	}

	try{
		_data = (Buffer<T> &)b;
	}catch(MemoryAllocationError &error){
		EXCEPTION_INIT(MemoryAllocationError,"Error allocating memory for the array!");
		EXCEPTION_THROW();
	}


}

template<typename T> const BufferObject &Array<T>::buffer() const {
	return _data;
}

template<typename T> T &Array<T>::operator[](const UInt64 &i){
	EXCEPTION_SETUP("template<typename T> T &Array<T>::operator[](const UInt64 &i)");

	try{
		T &res = _data[i];
		return res;
	}catch(...){
		EXCEPTION_INIT(MemoryAccessError,"Memory access failed!");
		EXCEPTION_THROW();
	}
}

template<typename T> T Array<T>::operator[](const UInt64 &i) const{
	EXCEPTION_SETUP("template<typename T> T Array<T>::operator[](const UInt64 &i)");
	T res = 0;

	try{
		res = _data[i];
	}catch(...){
		EXCEPTION_INIT(MemoryAccessError,"Memory access failed!");
		EXCEPTION_THROW();
	}

	return res;
}


template<typename T> T &Array<T>::operator()(const Index &i){
	EXCEPTION_SETUP("template<typename T> T &Array<T>::operator()(const Index &i)");

	try{
		T &res = _data[this->shape().offset(i)];
		return res;
	}catch(...){
		EXCEPTION_INIT(MemoryAccessError,"Error accessing array data!");
		EXCEPTION_THROW();
	}

}

template<typename T> T Array<T>::operator()(const Index &i) const{
	EXCEPTION_SETUP("template<typename T> T Array<T>::operator()(const Index &i) const");

	try{
		T result = _data[this->shape().offset(i)];
		return result;
	}catch(...){
		EXCEPTION_INIT(MemoryAccessError,"Error accessing array data!");
		EXCEPTION_THROW();
	}

	return 0;
}

template<typename T> void Array<T>::operator()(const Selection &s,Array<T> &a) const {
	EXCEPTION_SETUP("template<typename T> void Array<T>::operator()(const Selection &i,Array<T> &a) const ");

	//loop over the target array
	Index sindex(this->shape().rank());
	Index index (s.getRank());

	//loop over the target array
	UInt64 offset = 0;
	for(UInt64 i=0;i<a.shape().size();i++){
		a[i] = _data[offset];
	}


}


template<typename T> void Array<T>::allocate(){
	if(_data.is_allocated()) _data.free();
	_data.allocate(this->shape().size());
}

//===============================Comparison operators==========================
template<typename T> bool operator==(const Array<T> &b1, const Array<T> &b2) {
	const Shape &as = b1.shape();
	const Shape &bs = b2.shape();
	Buffer<T> &ad = (Buffer<T> &)b1.buffer();
	Buffer<T> &bd = (Buffer<T> &)b2.buffer();

	if ((as == bs) && (ad == bd)) return true;

	return false;
}

template<typename T> bool operator!=(const Array<T> &b1, const Array<T> &b2) {
	if (!(b1 == b2)) {
		return true;
	}
	return false;
}

//==============Methods for in-place array manipulation========================
template<typename T> typename ArrayType<T>::Type Array<T>::Sum() const {
	EXCEPTION_SETUP("template<typename T> typename ArrayType<T>::Type Array<T>::Sum() const");

	UInt64 i;
	typename ArrayType<T>::Type result = 0;

	try{
		for (i = 0; i < this->shape().size(); i++) result += (*this)[i];
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array sum operation!");
		EXCEPTION_THROW();
	}

	return result;

}

template<typename T> T Array<T>::Min() const {
	EXCEPTION_SETUP("template<typename T> T Array<T>::Min() const");

	UInt64 i;
	T result = 0,value = 0;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			value = (*this)[i];

			if (value < result) result = value;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array min operation!");
		EXCEPTION_THROW();
	}

	return result;
}

template<typename T> T Array<T>::Max() const {
	EXCEPTION_SETUP("template<typename T> T Array<T>::Max() const");

	UInt64 i;
	T result = 0,value=0;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			value = (*this)[i];

			if (value > result) result = value;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array max operation!");
		EXCEPTION_THROW();
	}

	return result;
}

template<typename T> void Array<T>::MinMax(T &min, T &max) const {
	EXCEPTION_SETUP("template<typename T> void Array<T>::MinMax(T &min, T &max) const");
	UInt64 i;
	min = 0;
	max = 0;
	T value = 0;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			value = (*this)[i];

			if (value > max) max = value;
			if (value < min) min = value;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array minmax operation!");
		EXCEPTION_THROW();
	}
}

template<typename T> void Array<T>::Clip(T minth, T maxth) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::Clip(T minth, T maxth)");
	UInt64 i;
	T value = 0;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			value = (*this)[i];

			if (value < minth) (*this)[i] = minth;
			if (value > maxth) (*this)[i] = maxth;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array operation!");
		EXCEPTION_THROW();
	}
}

template<typename T> void Array<T>::Clip(T minth, T minval, T maxth, T maxval) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::Clip(T minth, T minval, T maxth, T maxval)");
	UInt64 i;
	T value = 0;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			value = (*this)[i];

			if (value <= minth) (*this)[i] = minval;
			if (value >= maxth) (*this)[i] = maxval;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array operation!");
		EXCEPTION_THROW();
	}
}

template<typename T> void Array<T>::MinClip(T threshold) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::MinClip(T threshold)");
	UInt64 i;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			if ((*this)[i] < threshold) (*this)[i] = threshold;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array operation!");
		EXCEPTION_THROW();
	}
}

template<typename T> void Array<T>::MinClip(T threshold, T value) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::MinClip(T threshold, T value)");
	UInt64 i;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			if ((*this)[i] < threshold) (*this)[i] = value;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array operation!");
		EXCEPTION_THROW();
	}
}

template<typename T> void Array<T>::MaxClip(T threshold) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::MaxClip(T threshold)");
	UInt64 i;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			if ((*this)[i] > threshold)
				(*this)[i] = threshold;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array operation!");
		EXCEPTION_THROW();
	}
}

template<typename T> void Array<T>::MaxClip(T threshold, T value) {
	EXCEPTION_SETUP("template<typename T> void Array<T>::MaxClip(T threshold, T value)");
	UInt64 i;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			if ((*this)[i] > threshold)
				(*this)[i] = value;
		}
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array operation!");
		EXCEPTION_THROW();
	}
}

//==============================Assignment operators===========================

template<typename T> Array<T> &Array<T>::operator =(const T &v) {
	EXCEPTION_SETUP("template<typename T> Array<T> &Array<T>::operator =(const T &v)");
	UInt32 i;

	try{
		for (i = 0; i < this->shape().size(); i++) {
			(*this)[i] = v;
		}
	}catch(...){
		EXCEPTION_INIT(AssignmentError,"Object assignment failed!");
		EXCEPTION_THROW();
	}

	return *this;
}

template<typename T>
template<typename U> Array<T> &Array<T>::operator=(const U &v){
	EXCEPTION_SETUP("template<typename T> template<typename U> Array<T> &Array<T>::operator=(const U &v)");

	try{
		_data = v;
	}catch(...){
		EXCEPTION_INIT(AssignmentError,"Object assignment failed!");
		EXCEPTION_THROW();
	}

	return *this;
}

template<typename T> Array<T> &Array<T>::operator =(const Array<T> &v) {
	EXCEPTION_SETUP("template<typename T> Array<T> &Array<T>::operator =(const Array<T> &v)");

	if(this != &v){
		//check the array shapes
		try{
			this->reset();
			this->shape(v.shape());
			this->buffer(v.buffer());
		}catch(...){
			EXCEPTION_INIT(AssignmentError,"Object assignment failed!");
			EXCEPTION_THROW();
		}
	}


	return *this;
}

template<typename T>
template<typename U> Array<T> &Array<T>::operator=(const Array<U> &v) {
	EXCEPTION_SETUP("template<typename T> template<typename U> Array<T> &Array<T>::operator=(const Array<U> &v)");

	try{
		this->reset();
		this->shape(v.shape());
		_data = (Buffer<U> &)v.getBuffer();
	}catch(...){
		EXCEPTION_INIT(AssignmentError,"Object assignment failed!");
		EXCEPTION_THROW();
	}
}

//==============================binary arithmetic operators====================
template<typename T> Array<T> operator+(const Array<T> &a, const T &b) {
	EXCEPTION_SETUP("template<typename T> Array<T> operator+(const Array<T> &a, const T &b)");
	Array<T> tmp(a.getShape());
	UInt64 i;
	T *tmpbuf = tmp.getBuffer().getPtr();
	T *abuf = tmp.getBuffer().getPtr();

	try{
		for (i = 0; i < a.getShape().getSize(); i++)  tmpbuf[i] = abuf[i] + b;
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array processing!");
		EXCEPTION_THROW();
	}

	return tmp;
}

template<typename T> Array<T> operator+(const T &a, const Array<T> &b) {
	EXCEPTION_SETUP("template<typename T> Array<T> operator+(const T &a, const Array<T> &b)");
	Array<T> tmp;

	try{
		tmp = b + a;
	}catch(...){
		EXCEPTION_INIT(ProcessingError,"Error during array processing!");
		EXCEPTION_THROW();
	}

	return tmp;

}

template<typename T> Array<T> operator+(const Array<T> &a, const Array<T> &b) {
	EXCEPTION_SETUP("template<typename T> Array<T> operator+(const Array<T> &a, const Array<T> &b)");
	UInt64 i;

	if (a.getShape() != b.getShape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
		EXCEPTION_THROW();
	}

	Array<T> tmp(a.getShape());
	T *tmpbuf = tmp.getBuffer().getPtr();
	T *abuf = a.getBuffer().getPtr();
	T *bbuf = b.getBuffer().getPtr();


	for (i = 0; i < a.getShape().getSize(); i++) tmpbuf[i] = abuf[i] + bbuf[i];

	return tmp;
}

template<typename T> Array<T> operator-(const Array<T> &a, const T &b) {
	Array<T> tmp(a.getShape());
	UInt64 i;

	T *tmpbuf = tmp.getBuffer().getPtr();
	T *abuf = a.getBuffer().getPtr();

	for (i = 0; i < a.getShape().getSize(); i++)  tmpbuf[i] = abuf[i] - b;

	return tmp;
}

template<typename T> Array<T> operator-(const T &a, const Array<T> &b) {
	Array<T> tmp(b.getShape());
	UInt64 i;

	T *tmpbuf = b.getBuffer().getPtr();
	T *bbuf = b.getBuffer().getPtr();

	for (i = 0; i < b.getShape().getSize(); i++) tmpbuf[i] = a - bbuf[i];

	return tmp;

}

template<typename T> Array<T> operator-(const Array<T> &a, const Array<T> &b) {
	EXCEPTION_SETUP("template<typename T> Array<T> operator-(const Array<T> &a, const Array<T> &b)");
	unsigned long i;

	if (a.getShape() != b.getShape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
		EXCEPTION_THROW();
	}
	Array<T> tmp(a.getShape());

	T *tmpbuf = tmp.getBuffer().getPtr();
	T *abuf = a.getBuffer().getPtr();
	T *bbuf = b.getBuffer().getPtr();

	for (i = 0; i < a.getShape().getSize(); i++) tmpbuf[i] = abuf[i] - bbuf[i];

	return tmp;
}

template<typename T> Array<T> operator*(const Array<T> &a, const T &b) {
	Array<T> tmp(a.getShape());
	UInt64 i;

	for (i = 0; i < a.getShape().getSize(); i++) tmp[i] = a[i] * b;

	return tmp;
}

template<typename T> Array<T> operator*(const T &a, const Array<T> &b) {
	Array<T> tmp(b.getShape());
	UInt64 i;

	for (i = 0; i < b.getShape().getSize(); i++) tmp[i] = b[i] * a;

	return tmp;

}

template<typename T> Array<T> operator*(const Array<T> &a, const Array<T> &b) {
	EXCEPTION_SETUP("template<typename T> Array<T> operator*(const Array<T> &a, const Array<T> &b)");
	UInt64 i;

	if (a.getShape() != b.getShape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
		EXCEPTION_THROW();
	}
	Array<T> tmp(a.getShape());

	for (i = 0; i < a.getShape().getSize(); i++) tmp[i] = a[i] * b[i];


	return tmp;
}

template<typename T> Array<T> operator/(const Array<T> &a, const T &b) {
	Array<T> tmp(a.getShape());
	UInt64 i;

	for (i = 0; i < a.getShape().getSize(); i++) tmp[i] = a[i] / b;

	return tmp;
}

template<typename T> Array<T> operator/(const T &a, const Array<T> &b) {
	Array<T> tmp(b.getShape());
	UInt64 i;

	for (i = 0; i < b.getShape().getSize(); i++) tmp[i] = a / b[i];

	return tmp;

}

template<typename T> Array<T> operator/(const Array<T> &a, const Array<T> &b) {
	EXCEPTION_SETUP("template<typename T> Array<T> operator/(const Array<T> &a, const Array<T> &b)");
	UInt64 i;

	if (a.getShape() != b.getShape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
		EXCEPTION_THROW();
	}
	Array<T> tmp(a.getShape());

	for (i = 0; i < a.getShape().getSize(); i++) tmp[i] = a[i] / b[i];

	return tmp;
}

//=======================Unary arithmetic operations===========================
template<typename T> Array<T> &Array<T>::operator +=(const T &v) {

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] += v;

	return *this;
}

template<typename T> Array<T> &Array<T>::operator +=(const Array<T> &v) {
	EXCEPTION_SETUP("template<typename T> Array<T> &Array<T>::operator +=(const Array<T> &v)");

	if (this->shape() != v.shape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays on left and right side of += do not match!");
		EXCEPTION_THROW();
	}

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] += v[i];

	return *this;
}

template<typename T> Array<T> &Array<T>::operator -=(const T &v) {

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] -= v;

	return *this;
}

template<typename T> Array<T> &Array<T>::operator -=(const Array<T> &v) {
	EXCEPTION_SETUP("template<typename T> Array<T> &Array<T>::operator -=(const Array<T> &v)");

	if (this->shape() != v.shape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays on left and right side of -= do not match!");
		EXCEPTION_THROW();
	}

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] -= v[i];

	return *this;
}

template<typename T> Array<T> &Array<T>::operator *=(const T &v) {

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] *= v;

	return *this;
}

template<typename T> Array<T> &Array<T>::operator *=(const Array<T> &v) {
	EXCEPTION_SETUP("template<typename T> Array<T> &Array<T>::operator *=(const Array<T> &v)");

	if (this->shape() != v.shape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays on left and right side of *= do not match!");
		EXCEPTION_THROW();
	}

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] *= v[i];

	return *this;
}

template<typename T> Array<T> &Array<T>::operator /=(const T &v) {

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] /= v;

	return *this;
}

template<typename T> Array<T> &Array<T>::operator /=(const Array<T> &v) {
	EXCEPTION_SETUP("template<typename T> Array<T> &Array<T>::operator /=(const Array<T> &v)");

	if (this->shape() != v.shape()) {
		EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays on left and right side of /= do not match!");
		EXCEPTION_THROW();
	}

	for (size_t i = 0; i < this->shape().size(); i++) (*this)[i] /= v[i];

	return *this;
}

//===============================definition of some standard arrays============
typedef Array<Int8> Int8Array;
typedef Array<UInt8> UInt8Array;
typedef Array<Int16> Int16Array;
typedef Array<UInt16> UInt16Array;
typedef Array<Int32> Int32Array;
typedef Array<UInt32> UInt32Array;
typedef Array<Int64> Int64Array;
typedef Array<UInt64> UInt64Array;
typedef Array<Float32> Float32Array;
typedef Array<Float64> Float64Array;
typedef Array<Float128> Float128Array;
typedef Array<Complex32> Complex32Array;
typedef Array<Complex64> Complex64Array;
typedef Array<Complex128> Complex128Array;



}
}

#endif
