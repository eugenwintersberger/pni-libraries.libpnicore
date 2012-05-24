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
 * Definition of a dynamic array template.
 *
 * Created on: 24.05.2012
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
#include "policies/InplaceArithmetics.hpp"

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

    template<typename T,typename STORAGE=Buffer<T,NewAllocator> > class DynamicArray
    {
        private:
            Shape _shape;   //!< shape of the array holding thed ata
            STORAGE _data; //!< Buffer object holding the data

            //==================private methods================================
            /*! \brief setup view parameters from variadic template

            Private member function to setup the parameters for an ArrayView
            object from a variadic template. This method is called recursively
            until all slices in the argument list are processed.
            \param offset vector with offset values for the view
            \param stride vector with stride values for the view
            \param shape vector with shape values for the view
            \param s first slice object 
            \param slices residual slice objects
            */
            template<typename ...STypes>
                void _slice_setup(std::vector<size_t> &offset,
                                  std::vector<size_t> &stride,
                                  std::vector<size_t> &shape,
                                  Slice s,
                                  STypes ...slices)
            {
                _add_offset(offset,s);
                _add_stride(stride,s);
                _add_shape(shape,s);
                _slice_setup(offset,stride,shape,slices...);
            }

            //-----------------------------------------------------------------
            //! final version of _slice_setup 
            void _slice_setup(std::vector<size_t> &offset,
                              std::vector<size_t> &stride,
                              std::vector<size_t> &shape)
            {}

            //-----------------------------------------------------------------
            /*! \brief extract offset information 

            Extracts the offset information from a slice information for a
            particular dimension and adds it the offset vector.
            \param offset vector where to store offset values
            \param s slice object
            */
            void _add_offset(std::vector<size_t> &offset,const Slice &s)
            {
                offset.push_back(s.first());
            }

            //-----------------------------------------------------------------
            /*! \brief extract stride information

            Extracts stride information from a Slice object and adds it to the
            stride vector in the argument list.
            \param stride vector holding stride data
            \param s slice object
            */
            void _add_stride(std::vector<size_t> &stride,const Slice &s)
            {
                stride.push_back(s.stride());
            }

            //-----------------------------------------------------------------
            /*! \brief extract shape information

            Extracts shape information from a Slice object and adds it to
            a vector.
            \param shape vector with shape information
            \param s Slice object
            */
            void _add_shape(std::vector<size_t> &shape,const Slice &s)
            {
                shape.push_back(pni::utils::size(s));
            }

        protected:
        public:
            //================public types=====================================
            typedef T value_type;  //!< type of an array element
            typedef STORAGE storage_type; //!< type of the buffer object
            typedef std::shared_ptr<DynamicArray<T,STORAGE> > shared_ptr; //!< shared pointer to an Array<T>
            typedef std::unique_ptr<DynamicArray<T,STORAGE> > unique_ptr; //!< unique pointer type
            typedef ArrayView<DynamicArray<T,STORAGE> > view_type; //!< type for array view
            typedef typename STORAGE::iterator iterator; //!< iterator type
            typedef typename STORAGE::const_iterator const_iterator; //!< const iterator type
            
            //==================public members=================================
            static const TypeID type_id = TypeIDMap<T>::type_id; //!< type ID of the element type
            static const size_t value_size = sizeof(T); //!< size of the element type
            /*! \brief protected constructor

            This protected constructor is used by the ArrayFactory templates. It
            provides move semantics for the buffer passed to the array. Thus the
            array takes ownership over the buffer object. The method assumes
            that the size of the Buffer and the Shape object do match.
            \param s shape of the array
            \param buffer buffer object
            */
            DynamicArray(const Shape &s,STORAGE &&buffer):
                _shape(s),
                _data(std::move(buffer))
            { }

            //=================constructors and destructor=====================
            /*! \brief default constructor

            Neither ArrayShape nor Buffer object will be allocated. Buffer
            as well as shape must be handled later using the appropriate
            buffer(), shape(), and allocate methods. This constructor
            is perfectly applicable in all cases where the type of the array
            is known at the time of definition but all other parameters
            are obtained later in the code.
            */
            DynamicArray():_shape(),_data() {}

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            This constructor is a full copy constructor. A new array is created
            and the content of the original array is copied.
            \throws MemoryAllocationError if memory allocation fails
            */
            DynamicArray(const DynamicArray<T,STORAGE> &a):
                _shape(a._shape),
                _data(a._data)
            { }

            //-----------------------------------------------------------------
            //! move constructor
            DynamicArray(DynamicArray<T,STORAGE> &&a):
                _shape(std::move(a._shape)),
                _data(std::move(a._data))
            { }

            //-----------------------------------------------------------------
            /*! \brief constructor where array shape and buffer object are set

            The constructor takes pointers to a shape object and a buffer
            object. An exception will be raised if their sizes do not match.
            To keep ownership the objects will be copied.

            \throws MemoryAllocationError if memory allocation fails
            \throws SizeMissmatchError if sizes do not match
            \param s shape object
            \param b buffer object
            */
            DynamicArray(const Shape &s, const STORAGE &b):
                _shape(s),
                _data(b)
            {
                check_equal_size(s,b,
                        "DynamicArray(const Shape &s, const BType<T,Allocator> &b))");
            }

            //-----------------------------------------------------------------
            //! destructor
            ~DynamicArray() { _data.free(); }

            //===================assignment operators==========================
            //! assign a native type to the array

            //! Here a value of a native type will be assigned to the Array.
            //! The value is assigned to all elements of the array. Thus, this
            //! operator can be used for a quick initialization of an array with numbers.
            DynamicArray<T,STORAGE> &operator =(const T &v)
            {
                check_allocation_state(this->buffer(),
                                       "ARRAYTMP &operator =(const T&)");
                for(value_type &a: this->_data) a = v;
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
            template<typename U> DynamicArray<T,STORAGE> &operator=(const U &v)
            {
                check_allocation_state(this->buffer(),
                        "template<typename U> ARRAYTMP &operator=(const U &v)");

                for(T &a: this->_data) a = convert_type<T>(v);
                return *this;
            }


            //-----------------------------------------------------------------
            //! copy assignment between two arrays

            //! This operation is only possible if the shapes of the two arrays are equal.
            //! If this is not the case an exception will be raised. The content of the
            //! array on the r.h.s of the operator is copied to the array on the l.h.s.
            //! of the operator. No memory allocation is done - only copying.
            DynamicArray<T,STORAGE> & operator =(const DynamicArray<T,STORAGE> &a)
            {
                if(this == &a) return *this;

                this->_data = a._data;
                this->_shape = a._shape;

                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignemnt operator
            DynamicArray<T,STORAGE> & operator =(DynamicArray<T,STORAGE> &&a)
            {
                if (this == &a) return *this;
                
                this->_data = std::move(a._data);
                this->_shape = std::move(a._shape);

                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief copy assignment from a view

            An exception will be thrown if the shape of the view on the lhs does
            not match the shape of the array on the rhs of the operator.
            \throws ShapeMissmatchError if array and view shape do not match
    
            */
            template<typename U,
                     typename USTORAGE,
                     template<typename,typename> class ATYPE
                    >
            DynamicArray<T,STORAGE> &operator=
            (const ArrayView<ATYPE<U,USTORAGE> > &view)
            {
                check_equal_shape(this->shape(),view.shape(),
                    "template<template<typename,typename> class UBUFFER,"
                    "typename UALLOCATOR>Array<T,BType,Allocator> &operator="
                    "(const ArrayView<T,Array<T,UBUFFER,UALLOCATOR> > &view)");

                for(size_t i=0;i<this->size();i++) 
                    (*this)[i] = convert_type<T>(view[i]);

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
                check_allocation_state(this->buffer(),
                        "void shape(const Shape &s)");
                check_size_equal(this->buffer(),s,
                        "void shape(const Shape &s)");
                this->_shape = s;
            }

            //-----------------------------------------------------------------
            /*! \brief get array shape

            Return a constant reference to the array shape. 
            \return array shape const reference
            */
            const Shape &shape() const { return _shape; }

            //-----------------------------------------------------------------
            /*! \brief obtain buffer reference

            Return a const reference to the arrays buffer object.
            \return buffer reference
            */
            const STORAGE &buffer() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief get size of array

            Returns the total number of elements stored in the array.
            \return total number of elements
            */
            size_t size() const { return this->_shape.size(); }

            //==================Uniary arithmetic operators====================
            //these operators are important because they are performed
            //in-place - no new array is allocated

            /*! \brief unary scalar addition 

            Adds a single native value of type T to all elements in the Array.
            This unary operator performs the operation in-place. No temporary
            array will be allocated.
            \param v rhs argument of the operator
            */
            template<typename U>
            DynamicArray<T,STORAGE> &operator +=(const U &v)
            {
                InplaceArithmetics<T,DynamicArray,STORAGE>::add_inplace(*this,v);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! \brief unary array addition

            Adds the array on the r.h.s to that on the l.h.s. of the operator.
            The operation is performed in-place without the allocation of a
            temporary array. 
            \throws ShapeMissmatchError if array shapes do not match
            \param a rhs argment of the operator
            */
            template<typename U,
                     typename USTORAGE,
                     template<typename,typename> class ATYPE
                    >
            DynamicArray<T,STORAGE> &operator +=(const ATYPE<U,USTORAGE> &a)
            {
                InplaceArithmetics<T,DynamicArray,STORAGE>::add_inplace(*this,a);
                return *this;
            }

            //-----------------------------------------------------------------
            template<typename U,
                     typename USTORAGE,
                     template<typename,typename> class ATYPE
                    >
            DynamicArray<T,STORAGE> &
            operator +=(const ArrayView<ATYPE<U,USTORAGE> > &view)
            {
                InplaceArithmetics<T,DynamicArray,STORAGE>::add_inplace(*this,view);
                return *this;
            }

            //=============operators and methods to access array data==========
            /*! \brief get referece to element i

            Returns a reference to the element at linear index i. No index
            checking is done! Thus use this operator with care.
            \param i linear index 
            \return reference to the element at linear index i
            */
            T& operator[](const size_t &i) { return this->_data[i]; }

            /*! \brief get value at i

            Returns the value of the element at the linar array index i. No
            index checking is done! Thus use this operator with care.
            \param i linear index of the element
            \return value of the element at linear index i
            */
            T operator[](const size_t &i) const { return this->_data[i]; }

            /*! \brief get value at i

            Return a reference to the value at linear index i. This method
            performs index checking. 
            \throws IndexError if i exceeds array size
            \param i linear index of element
            \return reference to the value at i
            */
            T &at(size_t i) { return this->_data.at(i); } 

            /*! \brief get value at i

            Return the value of element i. This method
            performs index checking. 
            \throws IndexError if i exceeds array size
            \param i linear index of element
            \return value at i
            */
            T at(size_t i) const { return this->_data.at(i); } 


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
                return this->_data[this->_shape.offset(c)];
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
                return this->_data[this->_shape.offset(c)];
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
                return this->_data[this->_shape.offset(i,indices...)];
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
                return this->_data[this->_shape.offset(i,indices...)];
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
                DynamicArray<T,STORAGE>::view_type operator()
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
                
                return DynamicArray<T,STORAGE>::view_type(*this,shape,offset,stride);

            }

            //-----------------------------------------------------------------
            /*! \brief iterator to first element

            Returns a non-const iterator to the first element in the array.
            \return iterator to first element
            */
            DynamicArray<T,STORAGE>::iterator begin()
            {
                return this->_data.begin();
            }

            //-----------------------------------------------------------------
            /*! \brief iterator to last element

            Returns a non-const iterator to the last element in the array. 
            \return iterator to last element
            */
            DynamicArray<T,STORAGE>::iterator end()
            {
                return this->_data.end();
            }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to first element

            Returns a const-iterator to the first element in the array.
            \return iterator to first element
            */
            DynamicArray<T,STORAGE>::const_iterator begin() const
            {
                return this->_data.begin();
            }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to last element

            Returns a const-iterator to the last element in the array.
            \return iterator to last element
            */
            DynamicArray<T,STORAGE>::const_iterator end() const
            {
                return this->_data.end();
            }


    };

    //=====================non-member operators================================

    template<typename T,typename STORAGE>
    std::ostream &operator<<(std::ostream &o,const DynamicArray<T,STORAGE> &a)
    {
        o << "Dynamic Array of shape ("<<a.shape()<<")"<<std::endl;
        return o;
    }
   
    //-------------------------------------------------------------------------
    template<typename T,typename STORAGE>
    bool operator==(const DynamicArray<T,STORAGE> &b1, 
                    const DynamicArray<T,STORAGE> &b2) 
    {
        if((b1.shape() == b2.shape()) &&
           (b1.buffer() == b2.buffer())) return true;

        return false;
    }

    //-------------------------------------------------------------------------
    template<typename T,typename STORAGE>
    bool operator!=(const DynamicArray<T,STORAGE> &b1, 
                    const DynamicArray<T,STORAGE> &b2) 
    {
        if (!(b1 == b2)) {
            return true;
        }
        return false;
    }



}
}

#endif
