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

#include "Buffer.hpp"
#include "RefBuffer.hpp"
#include "Shape.hpp"
#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"
#include "Types.hpp"
#include "NumericObject.hpp"
#include "Slice.hpp"
#include "ArrayView.hpp"

#include "ArrayTrait.hpp"
#include "TypeInfo.hpp"
#include "TypeIDMap.hpp"
#include "type_conversion.hpp"
#include "Iterator.hpp"

namespace pni {
namespace utils {




    //! \ingroup data_classes
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
    //! instances of the program using the array. The std::shared_ptr avoids
    //! problems with object ownership and makes it quite simple to implement this
    //! behavior.

    //! The motivation for the reallocation and copy processes for the reference type
    //! methods and constructors is quite simple: one cannot be sure that the
    //! instance which created the object or a simple pointer will not destroy the
    //! object while still being used in the array. Therefore the copy process is
    //! absolutely necessary.

    template<typename T,typename REPTYPE> class Array
    {
        private:
            REPTYPE _array; //!< Buffer object holding the data
        public:
            //================public types=====================================
            typedef T value_type;  //!< type of an array element
            typedef std::shared_ptr<Array<T,REPTYPE> > shared_ptr; //!< shared pointer to an Array<T>
            typedef std::unique_ptr<Array<T,REPTYPE> > unique_ptr; //!< unique pointer type
            typedef ArrayView<Array<T,REPTYPE> > view_type; //!< type for array view
            typedef Iterator<Array<T,REPTYPE>,0> iterator; //!< iterator type
            typedef Iterator<Array<T,REPTYPE>,1> const_iterator; //!< const iterator type
            
            //==================public members=================================
            static const TypeID type_id = TypeIDMap<T>::type_id; //!< type ID of the element type
            static const size_t value_size = sizeof(T); //!< size of the element type

            //=================constructors and destructor=====================
            //! \brief default constructor
            Array():_array() {}

            //-----------------------------------------------------------------
            /*! \brief copy constructor
            
            Copy constructor for the 
            */
            Array(const Array<T,REPTYPE> &a):_array(a) {}

            //-----------------------------------------------------------------
            Array(Array<T,REPTYPE> &&a):_array(std::move(a)) { }

            Array(REPTYPE &&a):_array(std::move(a._array)) {}

            Array(const REPTYPE &a):_array(a) {} 

            //-----------------------------------------------------------------
            //! destructor
            ~Array() {  }

            //===================assignment operators==========================
            //! assign a native type to the array

            //! Here a value of a native type will be assigned to the Array.
            //! The value is assigned to all elements of the array. Thus, this
            //! operator can be used for a quick initialization of an array with numbers.
            Array<T,REPTYPE> &operator =(const T &v)
            {
                this->_array = v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! conversion assignment operator

            Converts a value of type U to T and assigns this value to all
            elements of the array. An exception is thrown if U cannot be
            converted to T.
            \throws TypeError if conversion fails.
            \param v value of type U
            */
            template<typename U> Array<T,REPTYPE> &operator=(const U &v)
            {
                this->_array = convert_type<T>(v);
                return *this;
            }


            //-----------------------------------------------------------------
            //! copy assignment between two arrays

            //! This operation is only possible if the shapes of the two arrays are equal.
            //! If this is not the case an exception will be raised. The content of the
            //! array on the r.h.s of the operator is copied to the array on the l.h.s.
            //! of the operator. No memory allocation is done - only copying.
            Array<T,REPTYPE> &operator =(const Array<T,REPTYPE> &a)
            {
                if(this == &a) return *this;
                this->_array = a._array;
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignemnt operator
            Array<T,REPTYPE> &operator =(Array<T,REPTYPE> &&a)
            {
                if (this == &a) return *this;
                this->_array = std::move(a._array);                
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief copy assignment from a view

            An exception will be thrown if the shape of the view on the lhs does
            not match the shape of the array on the rhs of the operator.
            \throws ShapeMissmatchError if array and view shape do not match
    
            */
            template<typename UREP> Array<T,REPTYPE> &operator= 
                (const ArrayView<Array<T,UREP> > &view)
            {
                check_equal_shape(this->shape(),view.shape(),
                    "template<template<typename,typename> class UBUFFER,"
                    "typename UALLOCATOR>Array<T,BType,Allocator> &operator="
                    "(const ArrayView<T,Array<T,UBUFFER,UALLOCATOR> > &view)");

                for(size_t i=0;i<this->size();i++) (*this)[i] = view[i];
                return *this;
            }


            //================public methods===================================
            /*! \brief set array shape
            
            Use this method to set the shape of the array. This can be used to
            reshape an allready allocated array. However, if the array is not
            allocated (as it is typically the case if it was created using the
            default constructor) an exception will be thrown.  
            The size of the new shape must match the size of the buffer
            associated with the array.

            \throws SizeMissmatchError if allocated buffer and shape size do not
            match
            \throws MemoryNotAllocatedError if no memory is allocated
            \param s shape of the array
            */
            void shape(const Shape &s)
            {
                this->_array.shape(s);
            }

            //-----------------------------------------------------------------
            /*! \brief get array shape

            Return a constant reference to the array shape. 
            \return array shape const reference
            */
            const Shape &shape() const { return this->_array.shape(); }

            //-----------------------------------------------------------------
            /*! \brief obtain buffer reference

            Return a const reference to the arrays buffer object.
            \return buffer reference
            */
            const typename REPTYPE::storage_type &buffer() const 
            { 
                return _array->buffer(); 
            }

            //-----------------------------------------------------------------
            /*! \brief get size of array

            Returns the total number of elements stored in the array.
            \return total number of elements
            */
            size_t size() const { return this->_array.size(); }

            //=============operators and methods to access array data==========
            /*! \brief get referece to element i

            Returns a reference to the element at linear index i. No index
            checking is done! Thus use this operator with care.
            \param i linear index 
            \return reference to the element at linear index i
            */
            T& operator[](const size_t &i) { return this->_array[i]; }

            /*! \brief get value at i

            Returns the value of the element at the linar array index i. No
            index checking is done! Thus use this operator with care.
            \param i linear index of the element
            \return value of the element at linear index i
            */
            T operator[](const size_t &i) const { return this->_array[i]; }

            /*! \brief get value at i

            Return a reference to the value at linear index i. This method
            performs index checking. 
            \throws IndexError if i exceeds array size
            \param i linear index of element
            \return reference to the value at i
            */
            T &at(size_t i) { return this->_array.at(i); } 

            /*! \brief get value at i

            Return the value of element i. This method
            performs index checking. 
            \throws IndexError if i exceeds array size
            \param i linear index of element
            \return value at i
            */
            T at(size_t i) const { return this->_array.at(i); } 


            //-----------------------------------------------------------------
            /*! \brief access with multidimensional index using a container

            Returns the data at a position described by the multidimensional
            index i. 
            \throws ShapeMissmatchError if size of c does not match the rank of
            the array
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimension
            \param c multidimensional index 
            \return reference to the element at position i
            */
            template<template<typename,typename> class CONTAINER,typename IT,typename A> 
                T &operator()(const CONTAINER<IT,A> &c)
            {
                return this->_array(c);
            }

            //-----------------------------------------------------------------
            /*! \brief access with multidimensional index using a container

            Returns the data at a position described by the multidimensional
            index i. 
            \throws ShapeMissmatchError if size of c does not match the rank of
            the array
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimension
            \param c multidimensional index 
            \return value of the element at position i
            */
            template<template<typename,typename> class CONTAINER,typename
                IT,typename A>
                T operator()(const CONTAINER<IT,A> &c) const
            {
                return this->_array(c);
            }

            //----------------------------------------------------------------- 
            /*! \brief access with variadic template

            Returns the data at a position described by the multidimensional
            index represented by the argument list of this operator. 
            \throws ShapeMissmatchError if the number of arguments  does not 
            match the rank of the array
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimension
            \param i first index
            \param indices residual indices
            \return reference to the element at position i
            */
            template<typename ...ITypes> 
                T &operator()(size_t i,ITypes ...indices) 
            {
                return this->_array(i,indices...);
            }

            //-----------------------------------------------------------------
            /*! \brief access with variadic template

            Returns the data at a position described by the multidimensional
            index represented by the argument list of this operator. 
            \throws ShapeMissmatchError if the number of arguments  does not 
            match the rank of the array
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimension
            \param i first index
            \param indices residual indices
            \return value of the element at position i
            */
            template<typename ...ITypes> 
                T operator()(size_t i,ITypes ...indices) const
            {
                return this->_array(indices...);
            }

            //-----------------------------------------------------------------
            /*! \brief create an ArrayView object 

            Creates an ArrayView instance for this array using instances of
            class Slice as arguments to the operator.
            \throws ShapeMissmatchError if the number of arguments does not
            match the rank of the Array.
            \throws ShapeMissmatchError if the number of arguments does not
            match the rank of the array.
            */
            template<typename ...STypes>
                Array<T,BType,Allocator>::view_type operator()
                (const Slice &s,STypes ...slices)
            {
                std::vector<size_t> offset;
                std::vector<size_t> stride;
                std::vector<size_t> shape;
                
                if(((sizeof...(STypes))+1)!=this->_shape.rank())
                {
                    std::stringstream ss;
                    ss<<"Array rank ("<<this->_shape.rank()<<") does not ";
                    ss<<"match number of arguments ("<<((sizeof...(STypes))+1)<<")!";
                    ShapeMissmatchError error;
                    error.description(ss.str());
                    error.issuer(" template<typename ...STypes> Array<T,"
                                 "BType,Allocator>::view_type operator() "
                                 "(const Slice &s,STypes ...slices)");
                    throw error;
                }
                
                _add_offset(offset,s);
                _add_stride(stride,s);
                _add_shape(shape,s);
                _slice_setup(offset,stride,shape,slices...);

                
                
                return Array<T,BType,Allocator>::view_type(*this,shape,offset,stride);

            }

            //-----------------------------------------------------------------
            /*! \brief iterator to first element

            Returns a non-const iterator to the first element in the array.
            \return iterator to first element
            */
            Array<T,REPTYPE>::iterator begin()
            {
                return REPTYPE::iterator(this,0);
            }

            //-----------------------------------------------------------------
            /*! \brief iterator to last element

            Returns a non-const iterator to the last element in the array. 
            \return iterator to last element
            */
            ARRAYTMP::iterator end()
            {
                return ARRAYTMP::iterator(this,this->size());
            }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to first element

            Returns a const-iterator to the first element in the array.
            \return iterator to first element
            */
            ARRAYTMP::const_iterator begin() const
            {
                return ARRAYTMP::const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to last element

            Returns a const-iterator to the last element in the array.
            \return iterator to last element
            */
            ARRAYTMP::const_iterator end() const
            {
                return ARRAYTMP::const_iterator(this,this->size());
            }


            friend class ArrayFactory<T,BType,Allocator>;

    };

    //=====================non-member operators================================

    ARRAYTMPDEF std::ostream &operator<<(std::ostream &o,const ARRAYTMP &a)
    {
        o << "Array of shape ("<<a.shape()<<")"<<std::endl;
        return o;
    }
   
    //-------------------------------------------------------------------------
    ARRAYTMPDEF bool operator==(const ARRAYTMP &b1, const ARRAYTMP &b2) 
    {
        if((b1.shape() == b2.shape()) &&
           (b1.buffer() == b2.buffer())) return true;

        return false;
    }

    //-------------------------------------------------------------------------
    ARRAYTMPDEF bool operator!=(const ARRAYTMP &b1, const ARRAYTMP &b2) 
    {
        if (!(b1 == b2)) {
            return true;
        }
        return false;
    }

    //====================binary addition operators=================================
    ARRAYTMPDEF ARRAYTMP operator+(const ARRAYTMP &a, const T &b) 
    {
        ARRAYTMP tmp(a.shape());
        for (size_t i = 0; i < a.shape().size(); i++)  tmp[i] = a[i] + b;

        return tmp;
    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator+(const T &a, const ARRAYTMP &b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType> operator+(const T &a,"
                        "const Array<T,BType> &b)");
        return b + a;
    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator+(const ARRAYTMP &a, const ARRAYTMP &b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType> operator+(const Array<T,BType> &a,"
                        "const Array<T,BType> &b)");
        
        check_shape_equal(a.shape(),b.shape(),
        "ARRAYTMPDEF ARRAYTMP operator+(const ARRAYTMP &a, const ARRAYTMP &b)");

        Array<T,BType,Allocator> tmp(a.shape());
        for (size_t i = 0; i < a.shape().size(); i++) tmp[i] = a[i] + b[i];

        return tmp;
    }

    //=================Binary subtraction operators=================================
    ARRAYTMPDEF ARRAYTMP operator-(const ARRAYTMP &a, const T &b) 
    {
        ARRAYTMP tmp(a.shape());

        for (size_t i = 0; i < a.shape().size(); i++)  tmp[i] = a[i] - b;

        return tmp;
    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator-(const T &a,const ARRAYTMP &b)
    {
        ARRAYTMP tmp(b.shape());

        for (size_t i = 0; i < b.shape().size(); i++) tmp[i] = a - b[i];

        return tmp;

    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator-(const ARRAYTMP &a, const ARRAYTMP &b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType> operator-(const Array<T,BType> &a,"
                        "const Array<T,BType> &b)");

        if (a.shape() != b.shape()) 
        {
            EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
            EXCEPTION_THROW();
        }

        ARRAYTMP tmp(a.shape());

        for (size_t i = 0; i < a.shape().size(); i++) tmp[i] = a[i] - b[i];

        return tmp;
    }

    //==================Binary multiplication operators=============================
    ARRAYTMPDEF ARRAYTMP operator*(const ARRAYTMP &a, const T &b) 
    {
        ARRAYTMP tmp(a.shape());

        for (size_t i = 0; i < a.shape().size(); i++) tmp[i] = a[i] * b;

        return tmp;
    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator*(const T &a, const ARRAYTMP &b) 
    {
        ARRAYTMP tmp(b.shape());

        for (size_t i = 0; i < b.shape().size(); i++) tmp[i] = b[i] * a;

        return tmp;

    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator*(const ARRAYTMP &a, const ARRAYTMP &b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType> operator*(const Array<T,BType> &a,"
                        "const Array<T,BType> &b)");

        if (a.shape() != b.shape()) {
            EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
            EXCEPTION_THROW();
        }
        ARRAYTMP tmp(a.shape());

        for (size_t i = 0; i < a.shape().size(); i++) tmp[i] = a[i] * b[i];


        return tmp;
    }

    //===================Binary division operators==================================
    ARRAYTMPDEF ARRAYTMP operator/(const ARRAYTMP &a, const T &b) 
    {
        ARRAYTMP tmp(a.shape());

        for (size_t i = 0; i < a.shape().size(); i++) tmp[i] = a[i] / b;

        return tmp;
    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator/(const T &a, const ARRAYTMP &b) 
    {
        ARRAYTMP tmp(b.shape());

        for (size_t i = 0; i < b.shape().size(); i++) tmp[i] = a / b[i];

        return tmp;

    }

    //------------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP operator/(const ARRAYTMP &a, const ARRAYTMP &b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType> operator/(const Array<T,BType> &a,"
                        "const Array<T,BType> &b)");

        if (a.shape() != b.shape()) {
            EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
            EXCEPTION_THROW();
        }
        ARRAYTMP tmp(a.shape());

        for (size_t i = 0; i < a.shape().size(); i++) tmp[i] = a[i] / b[i];

        return tmp;
    }


//===============================definition of some standard arrays============
typedef Array<Int8,Buffer> Int8Array;
typedef Array<UInt8,Buffer> UInt8Array;
typedef Array<Int16,Buffer> Int16Array;
typedef Array<UInt16,Buffer> UInt16Array;
typedef Array<Int32,Buffer> Int32Array;
typedef Array<UInt32,Buffer> UInt32Array;
typedef Array<Int64,Buffer> Int64Array;
typedef Array<UInt64,Buffer> UInt64Array;
typedef Array<Float32,Buffer> Float32Array;
typedef Array<Float64,Buffer> Float64Array;
typedef Array<Float128,Buffer> Float128Array;
typedef Array<Complex32,Buffer> Complex32Array;
typedef Array<Complex64,Buffer> Complex64Array;
typedef Array<Complex128,Buffer> Complex128Array;

typedef Array<Int8,RefBuffer> Int8RefArray;
typedef Array<UInt8,RefBuffer> UInt8RefArray;
typedef Array<Int16,RefBuffer> Int16RefArray;
typedef Array<UInt16,RefBuffer> UInt16RefArray;
typedef Array<Int32,RefBuffer> Int32RefArray;
typedef Array<UInt32,RefBuffer> UInt32RefArray;
typedef Array<Int64,RefBuffer> Int64RefArray;
typedef Array<UInt64,RefBuffer> UInt64RefArray;
typedef Array<Float32,RefBuffer> Float32RefArray;
typedef Array<Float64,RefBuffer> Float64RefArray;
typedef Array<Float128,RefBuffer> Float128RefArray;
}
}

#endif
