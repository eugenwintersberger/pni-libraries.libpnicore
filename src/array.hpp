//declaration of a numeric array type as a template

#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include<iostream>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
#include<typeinfo>

#include "buffer.hpp"
#include "arrayshape.hpp"
#include "datavalue.hpp"
#include "exceptions.hpp"

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
//! object. The data buffer as well as the array shape object are owned by the array object
//! and will therefore be destroyed if it goes out of scope.

template<typename T> class Array:public DataValue{
    protected:
		bool _allocated;              //!< is true if the Buffer belongs to the array instance
		                              //!< in other words: the buffer was allocated by the array instance
        Buffer<T> *_data;             //!< Buffer object holding the data
        ArrayShape *_shape;           //!< shape object describing the shape of the array
                                      //!< and managing the access to the data
        unsigned int *_index_buffer;  //!< a buffer used to hold index variables.
    public:
        //! default constructor
        Array();
        //! copy constructor
        Array(const Array<T> &);
        //! constructor where rank and dimension are set

        //! \param r rank of the array
        //! \param s array with number of elements along each direction
        Array(const unsigned int &r,const unsigned int s[]);
        //! constructor where the array shape object is set

        //! In this case the content of the shape object passed to the constructor
        //! will be copied to the one created by the constructor. By using
        //! this constructor buffer memory will be allocated according to the
        //! array size provided by the shape object.
        Array(const ArrayShape &s);
        //! constructor where array shape and buffer object are set

        //! The constructor takes a reference to a shape object and a buffer
        //! object. An exception will be raised if their sizes do not match.
        //! Additionally the content of the buffer passed to the constructor
        //! will be copied to the internal buffer of the array object.

        //! \param s reference to a shape object
        //! \param b reference to a buffer object
        Array(const ArrayShape &s,const Buffer<T> &b);
        //! destructor
        virtual ~Array();
        
        //! set the shape of the array

        //! The new shape must not lead to more entries
        virtual void setShape(ArrayShape &s);
        virtual const ArrayShape &getShape() const;
        
        virtual void setBuffer(const Buffer<T> &b) { *_data = b;}
        virtual Buffer<T> *getBuffer() { return _data;}
        virtual const Buffer<T> *getBuffer() const { return _data;}
        virtual void allocate();


        //overloaded assignment operators
        Array<T> &operator = (const T&);
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
        Array<T> &operator += (const T&);
        Array<T> &operator += (const Array<T>&);
        Array<T> &operator -= (const T&);
        Array<T> &operator -= (const Array<T>&);
        Array<T> &operator *= (const T&);
        Array<T> &operator *= (const Array<T>&);
        Array<T> &operator /= (const T&);
        Array<T> &operator /= (const Array<T>&);
        
        //some functions that are of importance for arrays

        T Sum() const;
        T Min() const;
        T Max() const;
        void MinMax(T &min,T &max) const;
        void Clip(T minth,T maxth);
        void MinClip(T threshold);
        void MinClip(T threshold, T value);
        void MaxClip(T threshold);
        void MaxClip(T threshold, T value);
        
        //operators for data access
        T& operator()(unsigned int i,...);
        T& operator[](unsigned int i) { return (*_data)[i];}

        //operators for comparison
        friend bool operator== <> (const Array<T> &b1,const Array<T> &b2);
        friend bool operator!= <> (const Array<T> &b1,const Array<T> &b2);
        friend std::ostream &operator<< <> (std::ostream &o,const Array<T> &a);

        
};

template<typename T> std::ostream &operator<< (std::ostream &o,const Array<T> &a){
	o<<"Array of shape (";
	for(unsigned int i=0;i<a._shape->getRank();i++){
		o<<(*a._shape)[i];
		if(i<a._shape->getRank()-1) o<<", ";
	}
	o<<") "<<typeid(a).name();
	return o;
}

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

template<typename T> void Array<T>::setShape(ArrayShape &s){
	*_shape = s;
	_data->resize(s.getSize());
}

template<typename T> const ArrayShape &Array<T>::getShape() const{
	return *_shape;
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

template<typename T> Array<T>::Array(){
    _data = NULL;
    _shape = NULL;
    _index_buffer = NULL;
    _allocated = false;
}

template<typename T> Array<T>::Array(const unsigned int &r,const unsigned int s[]){
    _shape = new ArrayShape(r,s);
    _data = new Buffer<T>(_shape->getSize());
    _index_buffer = new unsigned int[_shape->getSize()];
    _allocated = true;
}

//copy constructor
template<typename T> Array<T>::Array(const Array<T> &a){
    unsigned int i;
    _shape = new ArrayShape(*(a._shape));

    _index_buffer = new unsigned int[_shape->getSize()];

    //allocate memory
    _data = new Buffer<T>(a._shape->getSize());
    _allocated = true;

    //copy existing data to the new array
    for(i=0;i<a._shape->getSize();i++) (*_data)[i] = (*(a._data))[i];
}

//construct a new array from a shape object - the recommended way
template<typename T> Array<T>::Array(const ArrayShape &s){
    _shape = new ArrayShape(s);
    _data = new Buffer<T>(s.getSize());
    _index_buffer = new unsigned int[_shape->getSize()];
}


template<typename T>Array<T>::~Array(){
	if(_index_buffer!=NULL) delete [] _index_buffer;
}

template<typename T> T Array<T>::Sum() const{
    unsigned long i;
    T result = 0;

    for(i=0;i<_shape->getSize();i++) result += (*_data)[i];

    return result;

}
template<typename T> T Array<T>::Min() const{
    unsigned long i;
    T result = 0;

    for(i=0;i<_shape->getSize();i++){
        if((*_data)[i] < result) result = (*_data)[i];
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

template<typename T> Array<T> &Array<T>::operator = (const T &v){
    unsigned int i;
    
    for(i=0;i<_shape->getSize();i++){
        (*_data)[i] = v;
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator = (const Array<T> &v){
    unsigned int i;
    
    if(this != &v){
        //arrays of different shape cannot be assigned to each other
        if(_shape != v._shape){
            //raise a exception for shape mismatch
        }
        
        for(i=0;i<_shape->getSize();i++){
            (*_data)[i] = (*v._data)[i];
        }
    }
    
    return *this;
}

//many of the simple operations shown here may can be improved by 
//using vectorization - most probably we would need inline assembler 
//to do this. Byte alignment should be no problem at all.

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
        ArrayShapeMissmatchError error;
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
        ArrayShapeMissmatchError error;
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
        ArrayShapeMissmatchError error;
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
        ArrayShapeMissmatchError error;
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


template<typename T> Array<T> &Array<T>::operator += (const T &v){
    unsigned long i;
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] += v;
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator += (const Array<T> &v){
    unsigned long i;
    
    if(this->_shape != v._shape){
        ArrayShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator += (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of += do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] += (*v._data)[i];
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator -= (const T &v){
    unsigned long i;
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] -= v;
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator -= (const Array<T> &v){
    unsigned long i;
    
    if(this->_shape != v._shape){
        ArrayShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator -= (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of -= do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] -= (*v._data)[i];
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator *= (const T &v){
    unsigned long i;
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] *= v;
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator *= (const Array<T> &v){
    unsigned long i;
    
    if(this->_shape != v._shape){
        ArrayShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator *= (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of *= do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] *= (*v._data)[i];
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator /= (const T &v){
    unsigned long i;
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] /= v;
    }
    
    return *this;
}

template<typename T> Array<T> &Array<T>::operator /= (const Array<T> &v){
    unsigned long i;
    
    if(this->_shape != v._shape){
        ArrayShapeMissmatchError error;
        error.setSource("Array<T> &Array<T>::operator /= (const Array<T> &v)");
        error.setDescription("shapes of arrays on left and right side of /= do not match!");
        throw(error);
    }
    
    for(i=0;i<this->_shape->getSize();i++){
        (*(this->_data))[i] *= (*v._data)[i];
    }
    
    return *this;
}

//define here some standard array tpyes
typedef Array<char> Int8Array;
typedef Array<unsigned char> UInt8Array;
typedef Array<short> Int16Array;
typedef Array<unsigned short> UInt16Array;
typedef Array<int> Int32Array;
typedef Array<unsigned int> UInt32Array;
typedef Array<long> Int64Array;
typedef Array<unsigned long> UInt64Array;
typedef Array<float> Float32Array;
typedef Array<double> Float64Array;
typedef Array<std::complex<float> > Complex32Array;
typedef Array<std::complex<double> > Complex64Array;

#endif
