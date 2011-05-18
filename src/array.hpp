//declaration of a numeric array type as a template

#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include<iostream>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
#include<typeinfo>
#include<boost/shared_ptr.hpp>

#include "buffer.hpp"
#include "arrayshape.hpp"
#include "datavalue.hpp"
#include "exceptions.hpp"
#include "pnitypes.hpp"

template<typename T> class Array;

//binary operators must be defined here since they are implemented as friend operators
template<typename T> Array<T> operator+ (const Array<T>&, const T&);
template<typename T> Array<T> operator+ (const T&, const Array<T>&);
template<typename T> Array<T> operator+ (const Array<T>&, const Array<T>&);
        
template<typename T> Array<T> operator- (const Array<T>&, const T&);
template<typename T> Array<T> operator- (const Array<T>&, const Array<T>&);
template<typename T> Array<T> operator- (const T&, const Array<T>&);
        
template<typename T> Array<T> operator* (const Array<T>&, const T&);
template<typename T> Array<T> operator* (const Array<T>&, const Array<T>&);
template<typename T> Array<T> operator* (const T&, const Array<T>&);
        
template<typename T> Array<T> operator/ (const Array<T>&, const T&);
template<typename T> Array<T> operator/ (const Array<T>&, const Array<T>&);
template<typename T> Array<T> operator/ (const T&, const Array<T>&);

template<typename T> bool operator== (const Array<T> &,const Array<T> &);
template<typename T> bool operator!= (const Array<T> &,const Array<T> &);
template<typename T> std::ostream &operator<< (std::ostream &o,const Array<T> &a);

//! multi-dimensional array class

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

template<typename T> class Array{
    protected:
        boost::shared_ptr<Buffer<T> > _data;   //!< Buffer object holding the data
        boost::shared_ptr<ArrayShape> _shape;  //!< shape object describing the shape of the array
                                               //!< and managing the access to the data
        unsigned int *_index_buffer;  //!< a buffer used to hold index variables.
    public:
        //! default constructor
        Array();
        //! copy constructor
        Array(const Array<T> &);
        //! constructor where rank and dimension are set
        //! In this case a shape object is created and memory allocated.
        //! The shape object as well as the data buffer will be managed
        //! by the resulting Array object.

        //! \param r rank of the array
        //! \param s array with number of elements along each direction
        Array(const unsigned int &r,const unsigned int s[]);
        //! constructor with an array shape pointer

        //! The pointer to an existing ArrayShape object is used to construct
        //! the Array-object.
        //!
        //! \param s - reference to a shape object
        //! \sa Array(const boost::shared_ptr<ArrayShape> &s)
        Array(const ArrayShape &s);
        //! constructor with a smart pointer to an array shape

        //! Since a smart pointer is used the the shape object of the
        //! created Array object will be shared with the array's creator.

        //! \param &s reference to a smart pointer to a shape object
        Array(const boost::shared_ptr<ArrayShape> &s);
        //! constructor where array shape and buffer object are set

        //! The constructor takes pointers to a shape object and a buffer
        //! object. An exception will be raised if their sizes do not match.
        //! To keep ownership the objects will be copied.

        //! \param s pointer to a shape object
        //! \param b pointer to a buffer object
        //! \sa rray(const boost::shared_ptr<ArrayShape> &s,const boost::shared_ptr<Buffer<T> > &b)
        Array(const ArrayShape &s,const Buffer<T> &b);
        //! constructor with smart pointers

        //! This constructor passes smart pointers on the shape and buffer object
        //! to the array. The shape and buffer objects will be shared with the
        //! array's creator.

        //! \param s smart pointer to the array shape object
        //! \param b smart pointer to the buffer object
        Array(const boost::shared_ptr<ArrayShape> &s,const boost::shared_ptr<Buffer<T> > &b);

        //! destructor
        virtual ~Array();
        
        //! set the shape of the array

        //! The size of the shape array and that of the existing array must match
        //! otherwise and exception will be raised. Since a reference to a plain
        //! ArrayShape object is passed the Array object creates a new ArrayShape
        //! instance and copies the content from the existing one.

        //! \param s reference to the existing shape object
        //! \sa void setShape(boost::shared_ptr<ArrayShape> &s)
        virtual void setShape(const ArrayShape &s);
        //! set the shape of the array

        //! The size of the shape array and that of the existing array must match
        //! otherwise and exception will be raised. Here a shared smart pointer
        //! is passed to the method. Thus the calling instance and the array
        //! will share the shape object -  no copy process takes place.

        //! \param s reference to the existing shape object
        //! \sa void setShape(const ArrayShape &s)
        virtual void setShape(boost::shared_ptr<ArrayShape> &s);
        //! obtain the shape of an array

        //! returns a constant reference to the shape object of the array.
        //! The reference is constant to avoid changes of the shape object while
        //! being used by the array.

        //! \return constant reference to the shape object
        virtual const ArrayShape &getShape() const;
        //! obtain the shape of an array

        //! returns a constant reference to the smart pointer holding the
        //! address of the shape object. The fact that the smart pointer
        //! is set constant should prevent users from accidently changing
        //! the shape of the array without informing the array.

        //! \return refrence to the smart pointer object holding the shape object
        virtual const boost::shared_ptr<ArrayShape> &getShape() const;
        //! set the buffer of the array

        //! Manually set the Buffer object of the array. Here a reference to an
        //! existing Buffer object is passed to the method. In this case
        //! the Array object will allocate new memory and copy the content
        //! from the argument Buffer to the newly allocated.
        //! If the size of the Buffer object and the ArrayShape object in the
        //! Array do not match an exception will be raised.
        
        //! \param b reference to a Buffer object
        virtual void setBuffer(const Buffer<T> &b);
        //! set the array buffer

        //! Manually set the Buffer object of an array. A smart pointer is
        //! passed here. Thus the caller and the array share the Buffer
        //! object. The Buffer's size and that of the ArrayShape object
        //! in the array must match otherwise and exception will be raised.

        //! \param b reference to a smart pointer to a Buffer object
        virtual void setBuffer(const boost::shared_ptr<Buffer<T> > &b);
        //! obtain a reference to the array's Buffer

        //! Returns a constant reference to the Buffer object of the
        //! Array. The content of the Buffer can be changed from external
        //! sources. In this case one gets only a reference. This means
        //! that this will lead to undefined behavior in the case that the
        //! Array object which owns the Buffer object is destroyed.

        //! \return reference to the Buffer object
        virtual const Buffer<T> &getBuffer() const;
        //! obtain a smart pointer to the array Buffer

        //! Returns a smart Pointer to the array's Buffer object.
        //! The advantage of this is that in this case the Buffer
        //! will remain in memory even if the Array object is destroyed.

        //! \return reference to the smart pointer holding the Array object
        virtual const boost::shared_ptr<Buffer<T> > &getBuffer() const;


        //! assign a native type to the array

        //! Here a value of a native type will be assigned to the Array.
        //! The value is assigned to all elements of the array. Thus, this
        //! operator can be used for a quick initialization of an array with numbers.
        Array<T> &operator = (const T&);
        //! assignment between two arrays

        //! This operation is only possible if the shapes of the two arrays are equal.
        //! If this is not the case an exception will be raised. The content of the
        //! array on the r.h.s of the operator is copied to the array on the l.h.s.
        //! of the operator. No memory allocation is done - only copying.
        Array<T> &operator = (const Array<T>&);
        
        
        //overloaded simple binary arithmetic operators
        friend Array<T> operator+ <> (const Array<T>&, const T&);
        friend Array<T> operator+ <> (const T&, const Array<T>&);
        friend Array<T> operator+ <> (const Array<T>&, const Array<T>&);
        
        friend Array<T> operator- <> (const Array<T>&, const T&);
        friend Array<T> operator- <> (const Array<T>&, const Array<T>&);
        friend Array<T> operator- <> (const T&, const Array<T>&);
        
        friend Array<T> operator* <> (const Array<T>&, const T&);
        friend Array<T> operator* <> (const Array<T>&, const Array<T>&);
        friend Array<T> operator* <> (const T&, const Array<T>&);
        
        friend Array<T> operator / <> (const Array<T>&, const T&);
        friend Array<T> operator / <> (const Array<T>&, const Array<T>&);
        friend Array<T> operator / <> (const T&, const Array<T>&);
        
        //these operators are important because they are performed
        //in-place - no new array is allocated
        //! addition operator - unary

        //! Adds a single native value of type T to all elements in the Array.
        //! This unary operator performs the operation in-place. No temporary
        //! array will be allocated.
        Array<T> &operator += (const T&);
        //! addition operator - unary

        //! Adds the array on the r.h.s to that on the l.h.s. of the operator.
        //! The operation is performed in-place without the allocation of a
        //! temporary array. The shapes of the tow arrays must match otherwise
        //! a ShapeMissmatchError exception will be raised.
        Array<T> &operator += (const Array<T>&);
        //! subtraction operator - unary

        //! Subtracts a single value of type T on the r.h.s. of the operator
        //! to the array on the l.h.s. The operation is performed in-place without
        //! creation of a temporary array.
        Array<T> &operator -= (const T&);
        //! subtraction operator - unary

        //! Subtracts the  array on the r.h.s. of the operator from that on the
        //! l.h.s. The operation is performed in-place without allocation of a
        //! temporary array. The shapes of the arrays must match otherwise a
        //! ShapeMissmatchError exception will be raised.
        Array<T> &operator -= (const Array<T>&);
        //! multiplication operator - unary

        //! Multiplies the single value of type T on the r.h.s. of the operator
        //! with all elements of the array on the l.h.s. The operation is performed
        //! in-place without allocation of a temporary array.
        Array<T> &operator *= (const T&);
        //! multiplication operator - unary

        //! Element wise multiplication of the array on the r.h.s of the operator
        //! with the array of the l.h.s. The operation is stored in-place without
        //! allocation of a temporary array. The shapes of the arrays must match
        //! otherwise a ShapeMissmatchError exception will be raised.
        Array<T> &operator *= (const Array<T>&);
        //! Division operator - unary

        //! Divide the elements of the array on the l.h.s. of the operator by the
        //! single value of type T on the r.h.s. THe operation is performed in-place
        //! without allocation of a temporary array.
        Array<T> &operator /= (const T&);
        //! Division operator - unary

        //! Element wise division of the array on the l.h.s. with the array on the
        //! r.h.s. The operation is done in-place without allocation of a temporary array.
        //! The arrays must match in shape otherwise a ShapeMissmatchError exception will be raised.
        Array<T> &operator /= (const Array<T>&);
        
        //some functions that are of importance for arrays

        //! compute the sum of all element in the array

        //! Computes the sum of all elements stored in the array.
        //! \return number of type T
        T Sum() const;
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
        void MinMax(T &min,T &max) const;
        //! clip the array data

        //! Set values greater or equal maxth to maxth and those smaller or equal minth
        //! to minth.

        //! \param minth minimum threshold
        //! \param maxth maximum threshold
        void Clip(T minth,T maxth);
        void Clip(T minth,T minval,T maxth,T maxval);
        void MinClip(T threshold);
        void MinClip(T threshold, T value);
        void MaxClip(T threshold);
        void MaxClip(T threshold, T value);
        
        //operators for data access
        T& operator()(unsigned int i,...);
        T& operator[](unsigned int i) { return (*_data)[i];}

        //operators for comparison

        //! equality between arrays

        //! Tow arrays are considered equal if they coincide in shape and data content.
        friend bool operator== <> (const Array<T> &b1,const Array<T> &b2);
        //! inequality between arrays

        //! Tow arrays are considered different if they have different shape or
        //! content.
        friend bool operator!= <> (const Array<T> &b1,const Array<T> &b2);
        friend std::ostream &operator<< <> (std::ostream &o,const Array<T> &a);

        
};


//===============================Constructors and destructors===================================
//default constructor
template<typename T> Array<T>::Array()
{
	//in the default constructor we set all pointers to NULL
    _data.reset();
    _shape.reset();
    _index_buffer = NULL;
}

//simple constructor using rank and dimensions
template<typename T> Array<T>::Array(const unsigned int &r,const unsigned int s[])
{
	//here all objects are newly generated by the array object
    _shape.reset(new ArrayShape(r,s));
    _data.reset(new Buffer<T>(_shape->getSize()));
    _index_buffer = new unsigned int[_shape->getRank()];
}

//copy constructor - allocate new memory and really copy the data
template<typename T> Array<T>::Array(const Array<T> &a)
{
    unsigned int i;
    //set shape object
    _shape.reset(new ArrayShape(*(a._shape)));
    if(!_shape){
    	//raise an exception here if memory allocation fails
    	MemoryAllocationError e("Array<T>::Array","Cannot allocate memory for ArrayShape instance!");
    	throw e;
    }

    _index_buffer = new unsigned int[_shape->getRank()];

    //set buffer object
    _data.reset(new Buffer<T>(*(a._data)));
    if(!_data){
    	//raise an exception here if memory allocation failes
    	MemoryAllocationError e("Array<T>::Array","Cannot allocate memory for Buffer instance!");
    	throw e;
    }
}

//construct a new array from a shape object - the recommended way
template<typename T> Array<T>::Array(const ArrayShape &s){
	MemoryAllocationError e("Array<T>::Array()");

    _shape.reset(new ArrayShape(s));
    if(!_shape){
    	e.setDescription("Cannot allocate memory for ArrayShape object!");
    	throw e;
    }

    _data.reset(new Buffer<T>(s.getSize()));
    if(!_data){
    	e.setDescription("Cannot allocate memory for Buffer object!");
    	throw e;
    }

    _index_buffer = new unsigned int[_shape->getRank()];
    if(_index_buffer == NULL){
    	e.setDescription("Cannot allocate memory for index buffer!");
    	throw e;
    }
}


template<typename T> Array<T>::Array(const boost::shared_ptr<ArrayShape> &s){
	_shape = s; //the shape is now shared with the array creator (will increment reference counter)

	MemoryAllocationError e("Array<T>::Array");
	_data.reset(new Buffer<T>(_shape->getSize()));
	if(!_data){
		e.setDescription("Cannot allocate memory for Buffer object!");
		throw e;
	}

	_index_buffer = new unsigned int[_shape->getRank()];
	if(_index_buffer == NULL){
		e.setDescription("Cannot allocate memory for index buffer!");
		throw e;
	}
}

template<typename T> Array<T>::Array(const ArrayShape &s,const Buffer<T> &b){
	//first we need to check if buffer and shape have matching sizes
	if(s.getSize()!=b.getSize()){
		SizeMissmatchError e("Array<T>::Array()","Size of shape and buffer objects do not match!");
		throw e;
	}

	MemoryAllocationError e("Array<T>::Array()");

	_shape.reset(new ArrayShape(s));
	if(!_shape){
		e.setDescription("Cannot allocate memory for ArrayShape object!");
		throw e;
	}

	_data.reset(new Buffer<T>(b));
	if(!_data){
		e.setDescription("Cannot allocate memory for Buffer object!");
		throw e;
	}

	_index_buffer = new unsigned int[_shape->getRank()];
	if(_index_buffer == NULL){
		e.setDescription("Cannot allocate memory for index buffer!");
		throw e;
	}
}

template<typename T> Array<T>::Array(const boost::shared_ptr<ArrayShape> &s,const boost::shared_ptr<Buffer<T> > &b){
	//nee to check if sizes of shape and buffer object match
	if(s->getSize()!=b->getSize()){
		SizeMissmatchError e("Array<T>::Array()","Size of shape and buffer objects do not match!");
		throw e;
	}

	//share pointers
	_data = b;
	_shape = s;

	//allocate memory for the index buffer
	_index_buffer = new unsigned int[_shape->getRank()];
	if(_index_buffer == NULL){
		MemoryAllocationError e("Array<T>::Array()","Cannot allocate memory for index buffer!");
		throw e;
	}

}

//destructor for the array object
template<typename T>Array<T>::~Array(){
	if(_index_buffer!=NULL) delete [] _index_buffer;
	_shape.reset();
	_data.reset();
}



//===============================output operators===============================================
template<typename T> std::ostream &operator<< (std::ostream &o,const Array<T> &a){
	o<<"Array of shape (";
	for(unsigned int i=0;i<a._shape->getRank();i++){
		o<<(*a._shape)[i];
		if(i<a._shape->getRank()-1) o<<", ";
	}
	o<<") "<<typeid(a).name();
	return o;
}

//======================Methods for data access and array manipulation==========================
template<typename T> void Array<T>::setShape(const ArrayShape &s){
	if(s.getSize()!=_data->getSize()){
		//raise an exception if the size of the new shape object
		//and the buffer object do not fit.
		SizeMissmatchError e("Array<T>::setShape","shape and array size do not match!");
		throw e;
	}
	//create a new shape object
	_shape.reset(new ArrayShape(s));

	if(_index_buffer != NULL) delete [] _index_buffer;

	_index_buffer = new unsigned int[_shape->getRank()];
	if(_index_buffer == NULL){
		MemoryAllocationError e("Array<T>::setShape()","Cannot allocate memory for index buffer!");
		throw e;
	}
}

template<typename T> void Array<T>::setShape(boost::shared_ptr<ArrayShape> &s){
	if(s->getSize()!=_data->getSize()){
		//raise and exception if the size of the new shape object
		//and the buffer object do not match
		SizeMissmatchError e("Array<T>::setShape","shape and array size do not match!");
		throw e;
	}

	_shape = s;

	if(_index_buffer != NULL) delete [] _index_buffer;
	_index_buffer = new unsigned int[_shape->getRank()];
	if(_index_buffer == NULL){
		MemoryAllocationError e("Array<T>::setShape()","Cannot allocate memory for index buffer!");
		throw e;
	}
}

template<typename T> const ArrayShape &Array<T>::getShape() const{
	return *_shape;
}

template<typename T> const boost::shared_ptr<ArrayShape> &Array<T>::getShape() const{
	return _shape;
}

template<typename T> void Array<T>::setBuffer(const Buffer<T> &b) {
    if(b.getSize()!=_shape->getSize()){
    	//raise an exception
    	SizeMissmatchError e("Array<T>::setBuffer","Buffser and array size do not match!");
    	throw e;
    }
    _data.reset(new Buffer<T>(b));

}

template<typename T> void Array<T>::setBuffer(const boost::shared_ptr<Buffer<T> > &b){
	if(b->getSize()!=_shape->getSize()){
		//raise exception if sizes do not match
		SizeMissmatchError e("Array<T>::setBuffer()","Buffer and array size do not match!");
		throw e;
	}
	_data = b;
}

template<typename T> const Buffer<T> &getBuffer() const {
	return *_data;
}

template<typename T> const boost::shared_ptr<Buffer<T> > &Array<T>::getBuffer() const {
	return _data;
}

template<typename T> T& Array<T>::operator()(unsigned int i,...){
	unsigned int j;
	va_list vl;

	va_start(vl,i);

	for(j=0;j<_shape->getRank();j++){
		if(j==0){
			_index_buffer[j] = i;
			continue;
		}
		_index_buffer[j] = va_arg(vl,unsigned int);
	}
	va_end(vl);

	return (*_data)[_shape->getOffset(_index_buffer)];
}

//===============================Comparison operators===========================================
template<typename T> bool operator== (const Array<T> &b1,const Array<T> &b2){
	if((b1._shape==b2._shape)&&(b1._data==b2._data)){
		return true;
	}
	return false;
}

template<typename T> bool operator!= (const Array<T> &b1,const Array<T> &b2){
	if((b1._shape!=b2._shape)&&(b1._data!=b2._data)){
		return true;
	}
	return false;
}

//==============Methods for in-place array manipulation===========================================
template<typename T> T Array<T>::Sum() const{
    unsigned long i;
    T result = 0;
    Buffer<T> &d = *_data;

    for(i=0;i<_shape->getSize();i++) result += d[i];

    return result;

}


template<typename T> T Array<T>::Min() const{
    unsigned long i;
    T result = 0;
    Buffer<T> &d = *_data;

    for(i=0;i<_shape->getSize();i++){
        if(d[i] < result) result = d[i];
    }

    return result;
}

template<typename T> T Array<T>::Max() const{
    unsigned long i;
    T result = 0;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i] > result) result = (*_data)[i];
    }
    return result;
}

template<typename T> void Array<T>::MinMax(T &min,T &max) const{
    unsigned long i;
    min = 0;
    max = 0;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i] > max) max = (*_data)[i];
        if((*_data)[i] < min) min = (*_data)[i];
    }
}

template<typename T> void Array<T>::Clip(T minth,T maxth){
    unsigned long i;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i]<minth) (*_data)[i] = minth;
        if((*_data)[i]>maxth) (*_data)[i] = maxth;
    }
}

template<typename T> void Array<T>::MinClip(T threshold){
    unsigned long i;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i]<threshold) (*_data)[i] = threshold;
    }
}

template<typename T> void Array<T>::MinClip(T threshold, T value){
    unsigned long i;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i]<threshold) (*_data)[i] = value;
    }
}

template<typename T> void Array<T>::MaxClip(T threshold){
    unsigned long i;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i]>threshold) (*_data)[i] = threshold;
    }
}

template<typename T> void Array<T>::MaxClip(T threshold, T value){
    unsigned long i;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i]>threshold) (*_data)[i] = value;
    }
}

//==============================Assignment operators=======================================

template<typename T> Array<T> &Array<T>::operator = (const T &v){
    unsigned int i;
    Buffer<T> &d = *_data;
    
    for(i=0;i<_shape->getSize();i++){
        d[i] = v;
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator = (const Array<T> &v){
    unsigned int i;
    Buffer<T> &dout = *_data;
    Buffer<T> &din = *(v._data);
    
    if(this != &v){
        //arrays of different shape cannot be assigned to each other
        if(*_shape != *(v._shape)){
            //raise a exception for shape mismatch
        	ShapeMissmatchError e("Array<T>::operator=","Array shapes do not match!");
        	throw e;
        }
        
        //copy from one array to the other
        for(i=0;i<_shape->getSize();i++) dout[i] = din[i];
    }
    
    return *this;
}


//==============================binary arithmetic operators===============================
template<typename T> Array<T> operator+(const Array<T> &a, const T &b){
    Array<T> tmp = a;
    unsigned long i;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] + b;
    }
    return tmp;
}

template<typename T> Array<T> operator+(const T &a, const Array<T> &b){
    Array<T> tmp = b;
    unsigned long i;
    
    for(i=0;i<b._shape->getSize();i++){
        (*tmp._data)[i] = (*b._data)[i] + a;
    }
    
    return tmp;
    
}

template<typename T> Array<T> operator+(const Array<T> &a, const Array<T> &b){
    unsigned long i;
    
    if(a._shape != b._shape){
        ShapeMissmatchError error;
        error.setSource("Array<T> operator+(const Array<T> &a, const Array<T> &b)");
        error.setDescription("shapes of arrays a and b do not match!");
        throw(error);
    }
    Array<T> tmp = a;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] + (*b._data)[i];
    }
    
    return tmp;
}

template<typename T> Array<T> operator-(const Array<T> &a, const T &b){
    Array<T> tmp = a;
    unsigned long i;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] - b;
    }
    return tmp;
}

template<typename T> Array<T> operator-(const T &a, const Array<T> &b){
    Array<T> tmp = b;
    unsigned long i;
    
    for(i=0;i<b._shape->getSize();i++){
        (*tmp._data)[i] = (*b._data)[i] - a;
    }
    
    return tmp;
    
}

template<typename T> Array<T> operator-(const Array<T> &a, const Array<T> &b){
    unsigned long i;
    
    if(a._shape != b._shape){
        ShapeMissmatchError error;
        error.setSource("Array<T> operator-(const Array<T> &a, const Array<T> &b)");
        error.setDescription("shapes of arrays a and b do not match!");
        throw(error);
    }
    Array<T> tmp = a;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] - (*b._data)[i];
    }
    
    return tmp;
}

template<typename T> Array<T> operator*(const Array<T> &a, const T &b){
    Array<T> tmp = a;
    unsigned long i;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] * b;
    }
    return tmp;
}

template<typename T> Array<T> operator*(const T &a, const Array<T> &b){
    Array<T> tmp = b;
    unsigned long i;
    
    for(i=0;i<b._shape->getSize();i++){
        (*tmp._data)[i] = (*b._data)[i] * a;
    }
    
    return tmp;
    
}

template<typename T> Array<T> operator*(const Array<T> &a, const Array<T> &b){
    unsigned long i;
    
    if(a._shape != b._shape){
        ShapeMissmatchError error;
        error.setSource("Array<T> operator*(const Array<T> &a, const Array<T> &b)");
        error.setDescription("shapes of arrays a and b do not match!");
        throw(error);
    }
    Array<T> tmp = a;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] * (*b._data)[i];
    }
    
    return tmp;
}

template<typename T> Array<T> operator/(const Array<T> &a, const T &b){
    Array<T> tmp = a;
    unsigned long i;
    
    for(i=0;i<a._shape->getSize();i++){
        (*tmp._data)[i] = (*a._data)[i] / b;
    }
    return tmp;
}

template<typename T> Array<T> operator/(const T &a, const Array<T> &b){
    Array<T> tmp = b;
    unsigned long i;
    
    for(i=0;i<b._shape->getSize();i++){
        (*tmp._data)[i] = (*b._data)[i] / a;
    }
    
    return tmp;
    
}

template<typename T> Array<T> operator/(const Array<T> &a, const Array<T> &b){
    unsigned long i;
    
    if(a._shape != b._shape){
        ShapeMissmatchError error;
        error.setSource("Array<T> operator/(const Array<T> &a, const Array<T> &b)");
        error.setDescription("shapes of arrays a and b do not match!");
        throw(error);
    }
    Array<T> tmp = a;
    
    for(i=0;i<a._shape->getSize();i++){
        (*(tmp._data))[i] = (*(a._data))[i] / (*(b._data))[i];
    }
    
    return tmp;
}

//=======================Unary arithmetic operations=========================================
template<typename T> Array<T> &Array<T>::operator += (const T &v){
    unsigned long i;
    Buffer<T> &d = *(this->_data);
    
    for(i=0;i<this->_shape->getSize();i++) d[i] += v;
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator += (const Array<T> &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    Buffer<T> &drhs = *(v._data);
    
    if(*(this->_shape) != *(v._shape)){
        ShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator += (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of += do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] += drhs[i];
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator -= (const T &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] -= v;
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator -= (const Array<T> &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    Buffer<T> &drhs = *(v._data);
    
    if(*(this->_shape) != *(v._shape)){
        ShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator -= (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of -= do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] -= drhs[i];
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator *= (const T &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] *= v;
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator *= (const Array<T> &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    Buffer<T> &drhs = *(v._data);
    
    if(*(this->_shape) != *(v._shape)){
        ShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator *= (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of *= do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] *= drhs[i];
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator /= (const T &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] /= v;
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator /= (const Array<T> &v){
    unsigned long i;
    Buffer<T> &dlhs = *(this->_data);
    Buffer<T> &drhs = *(v._data);
    
    if(*(this->_shape) != *(v._shape)){
        ShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator /= (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of /= do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++) dlhs[i] *= drhs[i];
    
    return *this;
}

//===============================definition of some standard arrays===============================
typedef Array<Int8>       Int8Array;
typedef Array<UInt8>      UInt8Array;
typedef Array<Int16>      Int16Array;
typedef Array<UInt16>     UInt16Array;
typedef Array<Int32>      Int32Array;
typedef Array<UInt32>     UInt32Array;
typedef Array<Int64>      Int64Array;
typedef Array<UInt64>     UInt64Array;
typedef Array<Float32>    Float32Array;
typedef Array<Float64>    Float64Array;
typedef Array<Float128>   Float128Array;
typedef Array<Complex32>  Complex32Array;
typedef Array<Complex64>  Complex64Array;
typedef Array<Complex128> Complex128Array;

#endif
