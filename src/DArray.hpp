/*
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

#ifndef __DYARRAY_HPP__
#define __DYARRAY_HPP__

#include<iostream>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
#include<typeinfo>

#include "Shape.hpp"
#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"
#include "Types.hpp"
#include "Slice.hpp"
#include "ArrayView.hpp"
#include "ArrayViewSelector.hpp"
#include "CIndexMap.hpp"

#include "ArrayTrait.hpp"
#include "TypeInfo.hpp"
#include "TypeIDMap.hpp"
#include "type_conversion.hpp"
#include "Iterator.hpp"
#include "policies/InplaceArithmetics.hpp"

namespace pni {
namespace utils {

    /*! 
    \ingroup data_classes
    \brief template for a multi-dimensional array class

    \tparam T data type of the array
    \tparam STORAGE storage object to use to keep the data
    \tparam IMAP the index map 
    */
    template<typename T,
             typename STORAGE=DBuffer<T,NewAllocator>,
             typename IMAP=CIndexMap > 
    class DArray
    {
        private:
            //! Index map of the array 
            IMAP _imap;  
            //! instance of STORAGE
            STORAGE _data;  

            //==================private methods================================
            template<typename ...ITYPES>
            ArrayView<DArray<T,STORAGE,IMAP> >
                _get_data(ArrayView<DArray<T,STORAGE,IMAP> > &view,ITYPES ...indices)
            {

                ArraySelection s = 
                    ArraySelection::create(std::vector<Slice>{Slice(indices)...});

                return ArrayView<DArray<T,STORAGE,IMAP> >(*this,s);
            }

            //-----------------------------------------------------------------
            template<typename ...ITYPES> T &_get_data(T v,ITYPES ...indices)
            {
                return this->_data[this->_imap.offset(indices...)];
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            ArrayView<DArray<T,STORAGE,IMAP> >
            _get_data(ArrayView<DArray<T,STORAGE,IMAP> >&view,const CTYPE<OTS...> &c)
            {
                ArraySelection s = ArraySelection::create(c);

                return ArrayView<DArray<T,STORAGE,IMAP> >(*this,s);
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
                T &_get_data(T v,const CTYPE<OTS...> &c)
            {
                return this->_data[this->_imap.offset(c)];
            }

        public:
            //================public types=====================================
            //! arrays element type
            typedef T value_type;  
            //! type of the array
            typedef DArray<T,STORAGE> array_type;
            //! type of the buffer object
            typedef STORAGE storage_type;
            //! shared pointer to array_type
            typedef std::shared_ptr<array_type> shared_ptr;
            //! unique pointer to array type
            typedef std::unique_ptr<array_type> unique_ptr; 
            //! type for array view
            typedef ArrayView<array_type> view_type;
            //! iterator type
            typedef typename STORAGE::iterator iterator;
            //! const iterator type
            typedef typename STORAGE::const_iterator const_iterator; 
            
            //==================public members=================================
            //! type ID of the element type
            static const TypeID type_id = TypeIDMap<value_type>::type_id; 

            //=================constructors and destructor=====================
            /*! \brief default constructor

            Neither ArrayShape nor Buffer object will be allocated. Buffer
            as well as shape must be handled later using the appropriate
            buffer(), shape(), and allocate methods. This constructor
            is perfectly applicable in all cases where the type of the array
            is known at the time of definition but all other parameters
            are obtained later in the code.
            */
            DArray():_imap(),_data() {}

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            This constructor is a full copy constructor. A new array is created
            and the content of the original array is copied.
            \throws MemoryAllocationError if memory allocation fails
            */
            DArray(const array_type &a):_imap(a._imap),_data(a._data) { }

            //-----------------------------------------------------------------
            //! move constructor
            DArray(array_type &&a):
                _imap(std::move(a._imap)),
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
            template<typename CTYPE>
            explicit DArray(const CTYPE &s, const STORAGE &b):
                _imap(s),
                _data(b)
            {
                check_equal_size(s,b,
                        "DArray(const Shape &s, const STORAGE &b))");
            }

            /*! \brief protected constructor

            \param s shape of the 
            \param buffer buffer object
            */
            template<typename CTYPE>
            explicit DArray(const CTYPE &s,STORAGE &&buffer):
                _imap(s),
                _data(std::move(buffer))
            { }
            //-----------------------------------------------------------------
            //! destructor
            ~DArray() { }

            //===================assignment operators==========================
            //! copy assignment operator
            array_type & operator =(const array_type &a)
            {
                if(this == &a) return *this;

                this->_data = a._data;
                this->_imap = a._imap;

                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignemnt operator
            array_type & operator =(array_type &&a)
            {
                if (this == &a) return *this;
                
                this->_data = std::move(a._data);
                this->_imap = std::move(a._imap);

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
            template<typename CTYPE> void shape(const CTYPE &s)
            {
                check_allocation_state(this->buffer(),
                        "void shape(const Shape &s)");
                check_size_equal(this->buffer(),s,
                        "void shape(const Shape &s)");
                this->_imap = IMAP(s);
            }

            //-----------------------------------------------------------------
            /*! \brief get array shape

            Return a constant reference to the array shape. 
            \return array shape const reference
            */
            const DBuffer<size_t> &shape() const 
            { 
                return this->_imap.shape(); 
            }

            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE c(this->_imap.rank());
                std::copy(this->_imap.shape().begin(),
                          this->_imap.shape().end(),
                          c.begin());
                return c;
            }


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
            size_t size() const { return this->_imap.size(); }

            //-----------------------------------------------------------------
            size_t rank() const { return this->_imap.rank(); }

            //=============operators and methods to access array data==========
            /*! \brief get referece to element i

            Returns a reference to the element at linear index i. No index
            checking is done! Thus use this operator with care.
            \param i linear index 
            \return reference to the element at linear index i
            */
            value_type& operator[](size_t i) { return this->_data[i]; }

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Returns the value of the element at the linar array index i. No
            index checking is done! Thus use this operator with care.
            \param i linear index of the element
            \return value of the element at linear index i
            */
            value_type operator[](size_t i) const { return this->_data[i]; }

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Return a reference to the value at linear index i. This method
            performs index checking. 
            \throws IndexError if i exceeds array size
            \param i linear index of element
            \return reference to the value at i
            */
            value_type &at(size_t i) { return this->_data.at(i); } 

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Return the value of element i. This method
            performs index checking. 
            \throws IndexError if i exceeds array size
            \param i linear index of element
            \return value at i
            */
            value_type at(size_t i) const { return this->_data.at(i); } 

            //-----------------------------------------------------------------
            /*!
            \brief insert value at index i

            Insert value at index i. 
            \throws IndexError if i exceeds the size of the array
            \param i linear index of the element
            \param value the value to store at index i
            */
            void insert(size_t i,const value_type &value)
            {
                this->at(i)=value;
            }


            //-----------------------------------------------------------------
            /*! 
            \brief access with multidimensional index using a container

            Returns the data at a position described by the multidimensional
            index i. 
            \throws ShapeMissmatchError if size of c does not match the rank of
            the array
            \throws IndexError if one of the indices exceeds the number of
            elements along its dimension
            \param c multidimensional index 
            \return reference to the element at position i
            */
            template<template<typename ...> class CTYPE,typename ...OTS> 
            typename ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type>::reftype
            operator()(const CTYPE<OTS...> &c)
            {
                typedef ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type> selector;
                typedef typename selector::viewtype viewtype;
                typedef typename selector::reftype  viewref;

                viewtype r = viewtype();
                return _get_data(r,c);
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
            template<template<typename ...> class CTYPE,typename ...OTS>
            typename ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type>::viewtype
            operator()(const CTYPE<OTS...> &c) const
            {
                typedef ArrayViewSelector<array_type,typename CTYPE<OTS...>::value_type> sel;
                typename sel::viewtype result;

                return _get_data(result,c);
                return result;
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
            template<typename ...ITYPES>
                typename ArrayViewSelector<array_type,ITYPES...>::reftype
                operator()(ITYPES ...indices) 
            {
                typedef ArrayViewSelector<array_type,ITYPES...> selector;
                typedef typename selector::viewtype viewtype;
                typedef typename selector::reftype  viewref;

                viewtype r = viewtype();
                return _get_data(r,indices...);
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
            template<typename ...ITYPES> 
                typename ArrayViewSelector<array_type,ITYPES...>::viewtype
                operator()(ITYPES ...indices) const
            {
                typedef ArrayViewSelector<array_type,ITYPES...> sel;
                typename sel::viewtype result;

                return _get_data(result,indices...);
                return result;
            }


            //-----------------------------------------------------------------
            /*! \brief iterator to first element

            Returns a non-const iterator to the first element in the array.
            \return iterator to first element
            */
            iterator begin() { return this->_data.begin(); }

            //-----------------------------------------------------------------
            /*! \brief iterator to last element

            Returns a non-const iterator to the last element in the array. 
            \return iterator to last element
            */
            iterator end() { return this->_data.end(); }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to first element

            Returns a const-iterator to the first element in the array.
            \return iterator to first element
            */
            const_iterator begin() const { return this->_data.begin(); }

            //-----------------------------------------------------------------
            /*! \brief const-iterator to last element

            Returns a const-iterator to the last element in the array.
            \return iterator to last element
            */
            const_iterator end() const { return this->_data.end(); }


    };

    //=====================non-member operators================================

    template<typename T,typename STORAGE>
    std::ostream &operator<<(std::ostream &o,const DArray<T,STORAGE> &a)
    {
        o << "Dynamic Array of shape ("<<a.shape()<<")"<<std::endl;
        return o;
    }
   
    //-------------------------------------------------------------------------
    template<typename T,typename STORAGE>
    bool operator==(const DArray<T,STORAGE> &b1, 
                    const DArray<T,STORAGE> &b2) 
    {
        if((b1.shape() == b2.shape()) &&
           (b1.buffer() == b2.buffer())) return true;

        return false;
    }

    //-------------------------------------------------------------------------
    template<typename T,typename STORAGE>
    bool operator!=(const DArray<T,STORAGE> &b1, 
                    const DArray<T,STORAGE> &b2) 
    {
        if (!(b1 == b2)) {
            return true;
        }
        return false;
    }



}
}

#endif
