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
#include "Types.hpp"
#include "Index.hpp"
#include "NumericObject.hpp"

#include "ArrayTrait.hpp"
#include "TypeInfo.hpp"
#include "TypeIDMap.hpp"
#include "type_conversion.hpp"

namespace pni {
namespace utils {

#define ARRAYTMPDEF \
    template< \
        typename T,\
        template<typename,typename> class BType,\
        typename Allocator\
        >
#define ARRAYTMP Array<T,BType,Allocator>

    //! \internal
    ARRAYTMPDEF class Array;

    //binary operators must be defined here since they are implemented as 
    //friend operators
    ARRAYTMPDEF ARRAYTMP operator+(const ARRAYTMP&, const T&);
    ARRAYTMPDEF ARRAYTMP operator+(const T&, const ARRAYTMP&);
    ARRAYTMPDEF ARRAYTMP operator+(const ARRAYTMP&, const ARRAYTMP&);

    ARRAYTMPDEF ARRAYTMP operator-(const ARRAYTMP&, const T&);
    ARRAYTMPDEF ARRAYTMP operator-(const T&, const ARRAYTMP&);
    ARRAYTMPDEF ARRAYTMP operator-(const ARRAYTMP&, const ARRAYTMP&);

    ARRAYTMPDEF ARRAYTMP operator*(const ARRAYTMP&, const T&);
    ARRAYTMPDEF ARRAYTMP operator*(const T&, const ARRAYTMP&);
    ARRAYTMPDEF ARRAYTMP operator*(const ARRAYTMP&, const ARRAYTMP&);

    ARRAYTMPDEF ARRAYTMP operator/(const ARRAYTMP&, const T&);
    ARRAYTMPDEF ARRAYTMP operator/(const T&, const ARRAYTMP&);
    ARRAYTMPDEF ARRAYTMP operator/(const ARRAYTMP&, const ARRAYTMP&);

    ARRAYTMPDEF bool operator==(const ARRAYTMP &, const ARRAYTMP &);
    ARRAYTMPDEF bool operator!=(const ARRAYTMP &, const ARRAYTMP &);
    ARRAYTMPDEF std::ostream &operator<<(std::ostream &o, const ARRAYTMP &a);

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

    template<typename T,
             template<typename,typename> class BType,
             typename Allocator=NewAllocator>
    class Array: public NumericObject 
    {
        private:
            Shape _shape;   //!< shape of the array holding thed ata
            BType<T,Allocator> _data; //!< Buffer object holding the data

            //==================private methods================================
            /*! \brief throws if array is not allocated
            
            A static class method that throws an exception if the array is not 
            allocated.
            \throws MemoryAccessError if array is not allocated
            \param a reference to an array
            */
            static void _throw_if_not_allocated(const Array<T,BType,Allocator> &a);
        public:
            //================public types=====================================
            typedef Allocator allocator_type; //!< allocator type
            typedef T value_type;  //!< type of an array element
            typedef BType<T,Allocator> buffer_type; //!< type of the buffer object
            typedef std::shared_ptr<ARRAYTMP > shared_ptr; //!< shared pointer to an Array<T>
            typedef std::unique_ptr<ARRAYTMP > unique_ptr; //!< unique pointer type
            
            //==================public members=================================
            static const TypeID type_id = TypeIDMap<T>::type_id;
            static const size_t value_size = sizeof(T);

            //=================constructors and destructor=====================
            /*! \brief default constructor

            Neither ArrayShape nor Buffer object will be allocated. Buffer
            as well as shape must be handled later using the appropriate
            buffer(), shape(), and allocate methods. This constructor
            is perfectly applicable in all cases where the type of the array
            is known at the time of definition but all other parameters
            are obtained later in the code.
            */
            Array();

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            This constructor is a full copy constructor. A new array is created
            and the content of the original array is copied.
            */
            Array(const ARRAYTMP &);

            //-----------------------------------------------------------------
            //! move constructor
            Array(ARRAYTMP &&);
            
            //-----------------------------------------------------------------
            /*! \brief constructor with an array shape pointer

            The pointer to an existing ArrayShape object is used to construct
            the Array-object.
            
            \param s - reference to a shape object
            */
            Array(const Shape &s);

            //-----------------------------------------------------------------
            /*! \brief constructor where array shape and buffer object are set

            The constructor takes pointers to a shape object and a buffer
            object. An exception will be raised if their sizes do not match.
            To keep ownership the objects will be copied.

            \param s pointer to a shape object
            \param b pointer to a buffer object
            */
            Array(const Shape &s, const BType<T,Allocator> &b);

            //-----------------------------------------------------------------
            //! constructor

            //! This constructors sets also name, unit, and description
            //! of the NumericObject base class.
            Array(const Shape &s,const String &n,const String &u,const String &d);
            Array(const Shape &s,const BType<T,Allocator> &b,
                  const String &n,const String &u,const String &d);

            //! destructor
            ~Array();

            //===================assignment operators==========================
            //! assign a native type to the array

            //! Here a value of a native type will be assigned to the Array.
            //! The value is assigned to all elements of the array. Thus, this
            //! operator can be used for a quick initialization of an array with numbers.
            ARRAYTMP &operator =(const T&);

            //-----------------------------------------------------------------
            template<typename U> ARRAYTMP &operator=(const U &v);

            //-----------------------------------------------------------------
            //! assignment between two arrays

            //! This operation is only possible if the shapes of the two arrays are equal.
            //! If this is not the case an exception will be raised. The content of the
            //! array on the r.h.s of the operator is copied to the array on the l.h.s.
            //! of the operator. No memory allocation is done - only copying.
            ARRAYTMP &operator =(const ARRAYTMP &a);

            //-----------------------------------------------------------------
            //! move assignemnt operator
            ARRAYTMP &operator =(ARRAYTMP &&a);

            //-----------------------------------------------------------------
            template<typename U> Array<T,BType,Allocator> &
                operator=(const Array<U,BType,Allocator> &a);


            //================public methods===================================
            /*! \brief set array shape

            Use this method to set the shape of the array. This is typically
            used if the array was created by the default constructor. If the
            buffer holding the arrays data is already allocated this method
            causes a reshape of the array. In order to succeed the size of the
            shape must correpsond with the size of the allocated buffer. If the
            sizes do not match an excpetion will be thrown.

            The second possibility is that the arrays buffer is not allocated
            (as it would be the case when the array was created using the
            defautl constructor). In this case this method allocated memory.
            \throws SizeMissmatchError if allocated buffer and shape size do not
            match
            \throws MemoryAllocationError if array buffer allocation fails
            \param s shape of the array
            */
            void shape(const Shape &s);

            //-----------------------------------------------------------------
            /*! \brief get array shape

            Return a constant reference to the array shape. 
            \return array shape const reference
            */
            const Shape &shape() const
            {
                return _shape;
            }

            //-----------------------------------------------------------------
            /*! \brief copy buffer to array

            Copies the content of buffer b to the arrays buffer. If the buffer
            holing the array data is not allocated new memory will be allocated
            for it and the content of b is copied to the array buffer. 

            If the array buffer is, however, already allocated the sizes of b
            and the array buffer must match in order to copy the data from b to
            the array buffer. If this is not the case an exception will be
            thrown.
            \throws SizeMissmatchError if size of b and array buffer size do not
            match
            \throws MemoryAllocationError if array buffer allocation fails
            \param b reference to a Buffer object
            */
            void buffer(const BType<T,Allocator> &b);

            //-----------------------------------------------------------------
            /*! \brief move buffer to array

            The content of buffer b will be moved to the arrays buffer avoiding
            unnecessary memory allocation. If the buffer of the array is already
            allocated the sizes of b and the array buffer must match. Otherwise
            an exception will b thrown
            \throws SizeMissmatchError if size of b and the array buffer do not
            match
            \param b r-value reference to the original buffer
            */
            void buffer(BType<T,Allocator> &&b);

            /*! \brief obtain buffer reference

            Return a const reference to the arrays buffer object.
            \return buffer reference
            */
            const BType<T,Allocator> &buffer() const
            {
                return _data;
            }

            size_t size() const { return this->_shape.size(); }

            //==================Uniary arithmetic operators====================
            //these operators are important because they are performed
            //in-place - no new array is allocated

            /*! \brief unary scalar addition 

            Adds a single native value of type T to all elements in the Array.
            This unary operator performs the operation in-place. No temporary
            array will be allocated.
            \param v scalar to add
            */
            ARRAYTMP &operator +=(const T&v)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] +=v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary array addition

            Adds the array on the r.h.s to that on the l.h.s. of the operator.
            The operation is performed in-place without the allocation of a
            temporary array. 
            \throws ShapeMissmatchError if array shapes do not match
            \param 
            */
            ARRAYTMP &operator +=(const ARRAYTMP &a)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] += a[i];
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary scalar subtraction 

            Subtracts a single value of type T on the r.h.s. of the operator
            to the array on the l.h.s. The operation is performed in-place without
            creation of a temporary array.
            */
            ARRAYTMP &operator -=(const T&v)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] -= v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary array subtraction

            Subtracts the  array on the r.h.s. of the operator from that on the
            l.h.s. The operation is performed in-place without allocation of a
            temporary array. The shapes of the arrays must match otherwise a
            ShapeMissmatchError exception will be raised.
            */
            ARRAYTMP &operator -=(const ARRAYTMP&a)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] -=a[i];
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary scalar multiplication

            Multiplies the single value of type T on the r.h.s. of the operator
            with all elements of the array on the l.h.s. The operation is performed
            in-place without allocation of a temporary array.
            */
            ARRAYTMP &operator *=(const T&v)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] *= v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary array multiplication 

            Element wise multiplication of the array on the r.h.s of the operator
            with the array of the l.h.s. The operation is stored in-place without
            allocation of a temporary array. The shapes of the arrays must match
            otherwise a ShapeMissmatchError exception will be raised.
            */
            ARRAYTMP & operator *=(const ARRAYTMP &a)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] *= a[i];
                return *this;
            }
            
            //-----------------------------------------------------------------
            /*! \brief unary scalar division 

            Divide the elements of the array on the l.h.s. of the operator by the
            single value of type T on the r.h.s. THe operation is performed in-place
            without allocation of a temporary array.
            */
            ARRAYTMP &operator /=(const T&v)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] /= v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary array division

            Element wise division of the array on the l.h.s. with the array on the
            r.h.s. The operation is done in-place without allocation of a temporary array.
            The arrays must match in shape otherwise a ShapeMissmatchError exception will be raised.
            */
            ARRAYTMP & operator /=(const ARRAYTMP &a)
            {
                for(size_t i=0;i<this->size();i++) (*this)[i] /=a[i];
                return *this;
            }


            //================Binary arithemtic operators======================
            //overloaded simple binary arithmetic operators
            //! binary + operator for arrays

            //! This version of the operator implements Array<T> + T operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator+<> (const ARRAYTMP&, const T&);
            //overloaded simple binary arithmetic operators
            //! binary + operator for arrays

            //! This version of the operator implements T + Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator+<> (const T&, const ARRAYTMP&);
            //overloaded simple binary arithmetic operators
            //! binary + operator for arrays

            //! This version of the operator implements Array<T> + Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator+<> (const ARRAYTMP&, const ARRAYTMP&);

            //! binary - operator for arrays

            //! This version of the operator implements Array<T> - T operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator-<> (const ARRAYTMP&, const T&);
            //! binary - operator for arrays

            //! This version of the operator implements Array<T> - Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator-<> (const ARRAYTMP&, const ARRAYTMP&);
            //! binary - operator for arrays

            //! This version of the operator implements T - Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator-<> (const T&, const ARRAYTMP&);

            //! binary * operator for arrays

            //! This version of the operator implements Array<T> * T operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator*<> (const ARRAYTMP&, const T&);
            //! binary * operator for arrays

            //! This version of the operator implements Array<T> * Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator*<> (const ARRAYTMP&, const ARRAYTMP&);
            //! binary * operator for arrays

            //! This version of the operator implements T * Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator*<> (const T&, const ARRAYTMP&);

            //! binary / operator for arrays

            //! This version of the operator implements Array<T> / T operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator /<> (const ARRAYTMP&, const T&);
            //! binary / operator for arrays

            //! This version of the operator implements Array<T> / Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator /<> (const ARRAYTMP&, const ARRAYTMP&);
            //! binary / operator for arrays

            //! This version of the operator implements T / Array<T> operations.
            //! During the operation a temporary array object is created.
            friend ARRAYTMP operator /<> (const T&, const ARRAYTMP&);


            //========methods for array data inquery===========================
            //some functions that are of importance for arrays

            //! compute the sum of all element in the array

            //! Computes the sum of all elements stored in the array.
            //! \return number of type T
            typename ArrayType<T>::Type sum() const;

            //-----------------------------------------------------------------
            //! minimum value

            //! returns the minimum element in the array.
            //! \return value of type T
            T min() const;

            //-----------------------------------------------------------------
            //! maximum value

            //! returns the maximum element in the array
            //! \return value of type T
            T max() const;

            //-----------------------------------------------------------------
            //! minimum and maximum in the array

            //! returns the minimum and maximum values in the array.
            //! \param min minimum value
            //! \param max maximum value
            void min_max(T &min, T &max) const;

            //-----------------------------------------------------------------
            //! clip the array data

            //! Set values greater or equal maxth to maxth and those smaller or equal minth
            //! to minth.

            //! \param minth minimum threshold
            //! \param maxth maximum threshold
            void clip(T minth, T maxth);

            //-----------------------------------------------------------------
            //! clip the array data

            //! Set values smaller or equal to minth to minval and those larger or equal than
            //! maxth to maxval.

            //! \param minth minimum threshold
            //! \param minval value for numbers smaller or equal to minth
            //! \param maxth maximum threshold
            //! \param maxval value for numbers larger or equal to maxth
            void clip(T minth, T minval, T maxth, T maxval);

            //-----------------------------------------------------------------
            //! clip minimum values

            //! Set value smaller or equal to a threshold value to threshold.

            //! \param threshold threshold value
            void min_clip(T threshold);

            //-----------------------------------------------------------------
            //! clip minimum values

            //! Set values smaller or equal than a threshold value to value
            //! \param threshold threshold value
            //! \param value value to set the numbers to
            void min_clip(T threshold, T value);

            //-----------------------------------------------------------------
            //! clip maximum values

            //! Set values larger or equal than threshold to threshold.
            //! \param threshold threshold value
            void max_clip(T threshold);

            //-----------------------------------------------------------------
            //! clip maximum values

            //! Set values larger or equal than threshold to value.

            //! \param threshold the threshold value for the clip operation
            //! \param value the value to set the numbers to
            void max_clip(T threshold, T value);

            //=============operators and methods to access array data==========
            //! bracket operator - accessing linear data

            //! Using the []-operator allows to access the data stored in the array
            //! in a linear manner as it is stored by the buffer object.
            T& operator[](const size_t &i) { return this->_data[i]; }
            T operator[](const size_t &i) const { return this->_data[i]; }

            //-----------------------------------------------------------------
            /*! \brief access with multidimensional index

            Returns the data at a position described by the multidimensional
            index i. This method performs no range checking.
            \param i multidimensional index 
            \return reference to the element at position i
            */
            T& operator()(const Index &i) 
            { 
                return this->_data[this->_shape.offset(i)];
            }

            //-----------------------------------------------------------------
            T operator()(const Index &i) const
            {
                return this->_data[this->_shape.offset(i)];
            }


            //=====================comparison operators========================
            //operators for comparison

            //! equality between arrays

            //! Tow arrays are considered equal if they coincide in shape and data content.
            friend bool operator==<> (const ARRAYTMP &b1, const ARRAYTMP &b2);
            //! inequality between arrays

            //! Tow arrays are considered different if they have different shape or
            //! content.
            friend bool operator!=<> (const ARRAYTMP &b1, const ARRAYTMP &b2);
            //! output operator for console output
            friend std::ostream &operator<<<> (std::ostream &o, const ARRAYTMP &a);


            bool is_allocated() const{
                return _data.is_allocated();
            }


            T *ptr(){ return _data.ptr(); }

            const T* ptr() const { return _data.ptr(); }

            void *void_ptr(){ return _data.void_ptr(); }

            const void *void_ptr() const{ return _data.void_ptr(); }

    };

    //=====================Constructors and destructors=========================
    //default constructor
    ARRAYTMPDEF ARRAYTMP::Array():
        NumericObject(),
        _shape(),
        _data()
    {}

    //--------------------------------------------------------------------------
    //copy constructor - allocate new memory and really copy the data
    ARRAYTMPDEF ARRAYTMP::Array(const ARRAYTMP &a):
        NumericObject(),
        _shape(a._shape()),
        _data(a._data())
    { }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP::Array(ARRAYTMP &&a):
        NumericObject(std::move(a)),
        _shape(std::move(a._shape)),
        _data(std::move(a._data))
    { }

    //--------------------------------------------------------------------------
    //construct a new array from a shape object - the recommended way
    ARRAYTMPDEF ARRAYTMP::Array(const Shape &s): 
        NumericObject(),
        _shape(s),
        _data(s.size())
    { }

    //--------------------------------------------------------------------------
    //implementation of an array constructor
    ARRAYTMPDEF ARRAYTMP::Array(const Shape &s,const String &n,const String &u,
        const String &d):
        NumericObject(n,u,d),
        _shape(s),
        _data(s.size())
    { }

    //--------------------------------------------------------------------------
    //Array construction from a shape and a buffer
    ARRAYTMPDEF ARRAYTMP::Array(const Shape &s, const BType<T,Allocator> &b):
        NumericObject(),
        _shape(s)
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType>::Array(const ArrayShape &s, "
                        "const BType<T> &b):ArrayObject(s)");

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

    //--------------------------------------------------------------------------
    //implementation of an array constructor
    ARRAYTMPDEF ARRAYTMP::Array(const Shape &s, const BType<T,Allocator> &b,
            const String &n,const String &u,const String &d) : 
        NumericObject(n,u,d),
        _shape(s)
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType>::Array(const Shape &s, const BType<T> &b,"
                        "const String &n, const String &u,const String &d):ArrayObject(s)");

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

    //--------------------------------------------------------------------------
    //destructor for the array object
    ARRAYTMPDEF ARRAYTMP::~Array() 
    {
        _data.free();
    }



    //===============================output operators==============================
    ARRAYTMPDEF std::ostream &operator<<(std::ostream &o,const ARRAYTMP &a)
    {
        o << "Array of shape ("<<a.shape()<<")"<<std::endl;
        return o;
    }

    //======================Methods for data access and array manipulation======
    ARRAYTMPDEF void ARRAYTMP::shape(const Shape &s)
    {
        EXCEPTION_SETUP("template<typename T,template<typename> class BType,"
                "typename Allocator> void Array<T,BType,Allocator>::shape"
                "(const Shape &s)");

        if(this->_data.is_allocated())
        {
            if(this->_data.size() != s.size())
            {
                std::stringstream ss;
                ss<<"Size of shape ("<<s.size()<<") and allocate buffer (";
                ss<<this->_data.size()<<") do not match!";
                EXCEPTION_INIT(SizeMissmatchError,ss.str());
                EXCEPTION_THROW();
            }
        }
        else
        {
            this->_data.allocate(s.size());
        }
       
        //finally we can set the shape
        this->_shape = s;
    }

    //-------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::buffer(const BType<T,Allocator> &b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class "
                "BType,typename Allocator> void Array<T,BType,Allocator>::"
                "buffer(const BType<T,Allocator> &b)");


        if(this->_data.is_allocated())
        {
            if(this->_data.size() != b.size())
            {
                std::stringstream ss;
                ss<<"Size of new buffer ("<<b.size()<<") does not match";
                ss<<"the original array buffer size ("<<this->_data.size();
                ss<<")!";
                EXCEPTION_INIT(SizeMissmatchError,ss.str());
                EXCEPTION_THROW();
            }
        }
        
        this->_data = b;
    }

    //-------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::buffer(BType<T,Allocator> &&b) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class "
                "BType,typename Allocator> void Array<T,BType,Allocator>::"
                "buffer(BType<T,Allocator> &&b)");


        if(this->_data.is_allocated())
        {
            if(this->_data.size() != b.size())
            {
                std::stringstream ss;
                ss<<"Size of new buffer ("<<b.size()<<") does not match";
                ss<<"the original array buffer size ("<<this->_data.size();
                ss<<")!";
                EXCEPTION_INIT(SizeMissmatchError,ss.str());
                EXCEPTION_THROW();
            }
        }
        
        this->_data = std::move(b);
    }



    //===============================Comparison operators=======================
    ARRAYTMPDEF bool operator==(const ARRAYTMP &b1, const ARRAYTMP &b2) 
    {
        const Shape &as = b1.shape();
        const Shape &bs = b2.shape();
        const BType<T,Allocator> &ad = b1.buffer();
        const BType<T,Allocator> &bd = b2.buffer();

        if ((as == bs) && (ad == bd)) return true;

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

    //==============Methods for in-place array manipulation=====================
    ARRAYTMPDEF typename ArrayType<T>::Type ARRAYTMP::sum() const 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "typename ArrayType<T>::Type Array<T,BType>"
                        "::Sum() const");

        typename ArrayType<T>::Type result = 0;

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
                result += (*this)[i];
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array sum operation!");
            EXCEPTION_THROW();
        }

        return result;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF T ARRAYTMP::min() const 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "T Array<T,BType>::Min() const");

        T result = 0,value = 0;

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
            {
                value = (*this)[i];
                if (value < result) result = value;
            }
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array min operation!");
            EXCEPTION_THROW();
        }

        return result;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF T ARRAYTMP::max() const 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "T Array<T,BType>::Max() const");

        T result = 0,value=0;

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
            {
                value = (*this)[i];
                if (value > result) result = value;
            }
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array max operation!");
            EXCEPTION_THROW();
        }

        return result;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::min_max(T &min, T &max) const 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::MinMax(T &min, T &max) const");
        min = 0;
        max = 0;
        T value = 0;

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
            {
                value = (*this)[i];

                if (value > max) max = value;
                if (value < min) min = value;
            }
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array minmax operation!");
            EXCEPTION_THROW();
        }
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::clip(T minth, T maxth) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::Clip(T minth, T maxth)");
        T value = 0;

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
            {
                value = (*this)[i];

                if (value < minth) (*this)[i] = minth;
                if (value > maxth) (*this)[i] = maxth;
            }
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array operation!");
            EXCEPTION_THROW();
        }
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::clip(T minth, T minval, T maxth, T maxval) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::Clip(T minth, T minval, T maxth,"
                        "T maxval)");
        T value = 0;

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
            {
                value = (*this)[i];

                if (value <= minth) (*this)[i] = minval;
                if (value >= maxth) (*this)[i] = maxval;
            }
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array operation!");
            EXCEPTION_THROW();
        }
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::min_clip(T threshold) {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::MinClip(T threshold)");

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
                if ((*this)[i] < threshold) (*this)[i] = threshold;
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array operation!");
            EXCEPTION_THROW();
        }
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::min_clip(T threshold, T value) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::MinClip(T threshold, T value)");

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
                if ((*this)[i] < threshold) (*this)[i] = value;
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array operation!");
            EXCEPTION_THROW();
        }
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::max_clip(T threshold) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::MaxClip(T threshold)");

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
                if ((*this)[i] > threshold) (*this)[i] = threshold;
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array operation!");
            EXCEPTION_THROW();
        }
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF void ARRAYTMP::max_clip(T threshold, T value) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "void Array<T,BType>::MaxClip(T threshold, T value)");

        try{
            for (size_t i = 0; i < this->shape().size(); i++) 
                if ((*this)[i] > threshold) (*this)[i] = value;
        }catch(...){
            EXCEPTION_INIT(ProcessingError,"Error during array operation!");
            EXCEPTION_THROW();
        }
    }

    //==============================Assignment operators=======================
    ARRAYTMPDEF ARRAYTMP &ARRAYTMP::operator =(const T &v)
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType,"
                "typename Allocator> Array<T,BType,Allocator> &Array<T,"
                "BType,Allocator>::operator =(const T &v)");

        if(!this->is_allocated())
        {
            EXCEPTION_INIT(MemoryAccessError,"Array buffer not allocated!");
            EXCEPTION_THROW();
        }

        for (size_t i = 0; i < this->shape().size(); i++)  (*this)[i] = v;

        return *this;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF template<typename U> ARRAYTMP &ARRAYTMP:: operator=(const U &v)
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType,"
                "typename Allocator> template<typename U> Array<T,BType,"
                "Allocator> &Array<T,BType,Allocator>::operator=(const U &v)");

        if(!this->is_allocated())
        {
            EXCEPTION_INIT(MemoryAccessError,"Array buffer not allocated!");
            EXCEPTION_THROW();
        }

        try{
            _data = convert_type<T>(v);
        }catch(...){
            EXCEPTION_INIT(AssignmentError,"Object assignment failed!");
            EXCEPTION_THROW();
        }

        return *this;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP &ARRAYTMP::operator =(const ARRAYTMP &v) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "Array<T,BType> &Array<T,BType>::operator ="
                        "(const Array<T,BType> &v)");

        if(this == &v) return *this;

        this->_data = v._data;
        this->_shape = v._shape;

        return *this;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF ARRAYTMP &ARRAYTMP::operator=(ARRAYTMP &&a)
    {
        if (this == &a) return *this;
        
        this->_data = std::move(a._data);
        this->_shape = std::move(a._shape);

        return *this;
    }

    //--------------------------------------------------------------------------
    ARRAYTMPDEF template<typename U> ARRAYTMP &ARRAYTMP::operator=
        (const Array<U,BType,Allocator> &v) 
    {
        EXCEPTION_SETUP("template<typename T,template <typename> class BType>"
                        "template<typename U> Array<T,BType> &"
                        "Array<T,BType>::operator=(const Array<U,BType> &v)");

        try{
            this->reset();
            this->shape(v.shape());
            this->allocate();
            for(size_t i=0;i<this->size();i++) (*this)[i] = convert_type<T>(v.buffer()[i]);
        }catch(...){
            EXCEPTION_INIT(AssignmentError,"Object assignment failed!");
            EXCEPTION_THROW();
        }
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

        if (a.shape() != b.shape()) {
            EXCEPTION_INIT(ShapeMissmatchError,"shapes of arrays a and b do not match!");
            EXCEPTION_THROW();
        }

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
