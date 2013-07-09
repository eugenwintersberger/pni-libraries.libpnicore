/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of a dynamic array template.
 *
 * Created on: May 24, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

//#include<memory>
#include<iostream>
#include<utility>
#include<complex>
#include<cstdarg>
#include<cstdio>
//#include<typeinfo>

#include "exception_utils.hpp"
#include "types.hpp"
#include "slice.hpp"
#include "array_view.hpp"
#include "array_view_selector.hpp"
#include "cindex_map.hpp"

//#include "type_info.hpp"
#include "type_id_map.hpp"
#include "type_conversion.hpp"
#include "container_iterator.hpp"

namespace pni {
namespace core {

    /*! 
    \ingroup multidim_array_classes
    \brief template for a multi-dimensional array class

    \tparam T data type of the array
    \tparam STORAGE storage object to use to keep the data
    \tparam IMAP the index map 
    */
    template<typename T,
             typename STORAGE=dbuffer<T,new_allocator>,
             typename IMAP=cindex_map > 
    class darray
    {
        private:
            //! Index map of the array 
            IMAP _imap;  
            //! instance of STORAGE
            STORAGE _data;  

            //==================private methods================================
            /*! 
            \brief get array view

            Returns an instance of ArrayView if one of the indices is a Slice
            type. 
            \param view dummy parameter with the view type to select the proper
            private member function
            \param indices list of indices from which to construct the view
            \return array view object
            */
            template<typename ...ITYPES>
            array_view<darray<T,STORAGE,IMAP> >
                _get_data(array_view<darray<T,STORAGE,IMAP> > &view,ITYPES ...indices)
            {

                std::vector<slice> slices{slice(indices)...};
                array_selection s = array_selection::create(slices);

                return array_view<darray<T,STORAGE,IMAP> >(*this,s);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get element reference

            Returns a reference to the element determined by indices if this
            list does not contain an instance of Slice. 
            \tparam ITYPES index types
            \param v dummy variable to select the proper function template
            \param indices list of index values determining the element to
            return
            \return reference to the element
            */
            template<typename ...ITYPES> T &_get_data(T v,ITYPES ...indices)
            {
                return this->_data[this->_imap.offset(indices...)];
            }

            //-----------------------------------------------------------------
            /*!
            \brief get element value

            Returns the value of the element determined by indices if this
            list does not contain an instance of Slice. 
            \tparam ITYPES index types
            \param v dummy variable to select the proper function template
            \param indices list of index values determining the element to
            return
            \return reference to the element
            */
            template<typename ...ITYPES> T _get_data(T v,ITYPES ...indices)
                const
            {
                return this->_data[this->_imap.offset(indices...)];
            }

            //-----------------------------------------------------------------
            /*!
            \brief get array view 

            Get an array view whose shape is determined by the container c.
            \tparam CTYPE container template
            \tparam OTS template arguments to CTYPE
            \param view dummy variable to determine the function
            \param c container with view parameters
            \return array view
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
            array_view<darray<T,STORAGE,IMAP> >
            _get_data(array_view<darray<T,STORAGE,IMAP> >&view,const CTYPE<OTS...> &c)
            {
                array_selection s = array_selection::create(c);

                return array_view<darray<T,STORAGE,IMAP> >(*this,s);
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get reference to element

            Returns a reference to an array element determined by the values in
            a container.
            \tparam CTYPE container template
            \tparam OTS template arguments of CTYPE
            \param v dummy argument to determine the function
            \param c container with indices
            \return element reference
            */
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
            typedef darray<T,STORAGE> array_type;
            //! type of the buffer object
            typedef STORAGE storage_type;
            //! shared pointer to array_type
            typedef std::shared_ptr<array_type> shared_ptr;
            //! unique pointer to array type
            typedef std::unique_ptr<array_type> unique_ptr; 
            //! type for array view
            typedef array_view<array_type> view_type;
            //! iterator type
            typedef typename STORAGE::iterator iterator;
            //! const iterator type
            typedef typename STORAGE::const_iterator const_iterator; 
            //! map type
            typedef IMAP map_type;
            
            //==================public members=================================
            //! type ID of the element type
            static const type_id_t type_id; 

            //=================constructors and destructor=====================
            /*! \brief default constructor

            Neither ArrayShape nor Buffer object will be allocated. Buffer
            as well as shape must be handled later using the appropriate
            buffer(), shape(), and allocate methods. This constructor
            is perfectly applicable in all cases where the type of the array
            is known at the time of definition but all other parameters
            are obtained later in the code.
            */
            darray():_imap(),_data() {}

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            This constructor is a full copy constructor. A new array is created
            and the content of the original array is copied.
            \throws MemoryAllocationError if memory allocation fails
            \param a array from which to copy
            */
            darray(const array_type &a):_imap(a._imap),_data(a._data) { }

            //-----------------------------------------------------------------
            //! move constructor
            darray(array_type &&a):
                _imap(std::move(a._imap)),
                _data(std::move(a._data))
            { }

            //-----------------------------------------------------------------
            /*! \brief constructor where array shape and buffer object are set

            The constructor takes pointers to a shape object and a buffer
            object. An exception will be raised if their sizes do not match.
            To keep ownership the objects will be copied.

            \throws memory_allocation_error if memory allocation fails
            \throws size_mismatch_error if sizes do not match
            \param s shape object
            \param b buffer object
            */
            template<template<typename...> class CTYPE,typename ...OTS>
            explicit darray(const CTYPE<OTS...> &s, const STORAGE &b):
                _imap(s),
                _data(b)
            {
                check_equal_size(this->_imap,this->_data,EXCEPTION_RECORD);
            }
            
            //-----------------------------------------------------------------
            /*! \brief constructor for moving buffer

            \param s shape of the 
            \param buffer buffer object
            */
            template<template<typename...> class CTYPE,typename ...OTS>
            explicit darray(const CTYPE<OTS...> &s,STORAGE &&buffer):
                _imap(s),
                _data(std::move(buffer))
            { }

            //-----------------------------------------------------------------
            /*! 
            \brief construct an array from a view

            Construct an array from an instance of ArrayView. This is usefull as
            the data represented by an ArrayView instance lies not necessarily
            contiguous in memory. Clearly this constructor triggers a mem-copy
            process.
            \tparam ATYPE array type of the view
            \param a reference to the array view
            */
            template<typename ATYPE> 
            explicit darray(const array_view<ATYPE> &a):
                _imap(a.shape<std::vector<size_t> >()),
                _data(a)
            { }


            //-----------------------------------------------------------------
            /*! \brief construct from shape

            Construct Array from a shape and let the constructor allocate
            memory.
            \throws memory_allocation_error if memory allocation fails
            \param s shape container
            */
            template<template<typename...> class CTYPE,typename ...OTS> 
                explicit darray(const CTYPE<OTS...> &s):
                _imap(s),
                _data(STORAGE(_imap.size()))
            { }


            //-----------------------------------------------------------------
            //! destructor
            ~darray() { }

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

            \throws size_mismatch_error if allocated buffer and shape size do not
            match
            \throws memory_not_allocated_error if no memory is allocated
            \param s shape of the array
            */
            template<typename CTYPE> void shape(const CTYPE &s)
            {
                check_allocation_state(this->storage(),EXCEPTION_RECORD);
                IMAP map(s);
                check_equal_size(this->_imap,map,EXCEPTION_RECORD);
                this->_imap = map;
            }

            //-----------------------------------------------------------------
            /*! \brief get index map

            Returns a const reference to the index map of the array.
            \return reference to index map
            */
            map_type map() const { return this->_imap; }

            //-----------------------------------------------------------------
            /*! \brief get array shape

            Return a constant reference to the array shape. 
            \return array shape const reference
            */
            const dbuffer<size_t> &shape() const 
            { 
                return this->_imap.shape(); 
            }

            //----------------------------------------------------------------
            //! shape to container
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
            const STORAGE &storage() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief get size of array

            Returns the total number of elements stored in the array.
            \return total number of elements
            */
            size_t size() const { return this->_imap.size(); }

            //-----------------------------------------------------------------
            //! get number of dimensions of the array
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
            \throws index_error if i exceeds array size
            \param i linear index of element
            \return reference to the value at i
            */
            value_type &at(size_t i) { return this->_data.at(i); } 

            //-----------------------------------------------------------------
            /*! \brief get value at i

            Return the value of element i. This method
            performs index checking. 
            \throws index_error if i exceeds array size
            \param i linear index of element
            \return value at i
            */
            value_type at(size_t i) const { return this->_data.at(i); } 

            //-----------------------------------------------------------------
            /*!
            \brief insert value at index i

            Insert value at index i. 
            \throws index_error if i exceeds the size of the array
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
            \throws shape_mismatch_error if size of c does not match the rank of
            the array
            \throws index_error if one of the indices exceeds the number of
            elements along its dimension
            \param c multidimensional index 
            \return reference to the element at position i
            */
            template<template<typename ...> class CTYPE,typename ...OTS> 
            typename array_view_selector<array_type,typename CTYPE<OTS...>::value_type>::reftype
            operator()(const CTYPE<OTS...> &c)
            {
                typedef array_view_selector<array_type,typename CTYPE<OTS...>::value_type> selector;
                typedef typename selector::viewtype viewtype;
                typedef typename selector::reftype  viewref;

                viewtype r = viewtype();
                return _get_data(r,c);
            }

            //-----------------------------------------------------------------
            /*! \brief access with multidimensional index using a container

            Returns the data at a position described by the multidimensional
            index i. 
            \throws shape_mismatch_error if size of c does not match the rank of
            the array
            \throws index_error if one of the indices exceeds the number of
            elements along its dimension
            \param c multidimensional index 
            \return value of the element at position i
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
            typename array_view_selector<array_type,typename CTYPE<OTS...>::value_type>::viewtype
            operator()(const CTYPE<OTS...> &c) const
            {
                typedef array_view_selector<array_type,typename CTYPE<OTS...>::value_type> sel;
                typename sel::viewtype result = typename sel::viewtype();

                return _get_data(result,c);
                return result;
            }

            //----------------------------------------------------------------- 
            /*! \brief access with variadic template

            Returns the data at a position described by the multidimensional
            index represented by the argument list of this operator. For
            performance reasons no checking of the indices is done. 
            \param indices array indices
            \return reference to the element at position i
            */
            template<typename ...ITYPES>
                typename array_view_selector<array_type,ITYPES...>::reftype
                operator()(ITYPES ...indices) 
            {
                typedef array_view_selector<array_type,ITYPES...> selector;
                typedef typename selector::viewtype viewtype;
                typedef typename selector::reftype  viewref;

                viewtype r = viewtype();
                return _get_data(r,indices...);
            }

            //-----------------------------------------------------------------
            /*! \brief access with variadic template

            Returns the data at a position described by the multidimensional
            index represented by the argument list of this operator. 
            For performance reasons no checking of the indices is done. 
            \param indices residual indices
            \return value of the element at position i
            */
            template<typename ...ITYPES> 
                typename array_view_selector<array_type,ITYPES...>::viewtype
                operator()(ITYPES ...indices) const
            {
                typedef array_view_selector<array_type,ITYPES...> sel;
                typename sel::viewtype result = typename sel::viewtype();

                return _get_data(result,indices...);
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

    //set data for static member attribute
    template<typename T,typename STORAGE,typename IMAP>
    const type_id_t darray<T,STORAGE,IMAP>::type_id = type_id_map<T>::type_id;
    //=====================non-member operators================================

    /*!
    \brief output operator

    Writes content of a DArray to an output stream. 
    \param o output stream
    \param a array to output
    \return output stream
    */
    template<typename T,typename STORAGE>
    std::ostream &operator<<(std::ostream &o,const darray<T,STORAGE> &a)
    {
        for(auto iter = a.begin();iter!=a.end();++iter)
            o<<*iter<<" ";

        return o;
    }

    //-------------------------------------------------------------------------
    /*!
    \brief input stream operator

    Read data from an input stream. 
    \param is input stream
    \param a array where to store the data
    \return reference to input stream
    */
    template<typename T,typename STORAGE>
    std::istream &operator>>(std::istream &is,darray<T,STORAGE> &a)
    {
        for(auto iter=a.begin();iter!=a.end();++iter)
            is>>*iter;

        return is;
    }
   
    //-------------------------------------------------------------------------
    template<typename T,typename STORAGE>
    bool operator==(const darray<T,STORAGE> &b1, 
                    const darray<T,STORAGE> &b2) 
    {
        if((b1.shape() == b2.shape()) &&
           (b1.storage() == b2.storage())) return true;

        return false;
    }

    //-------------------------------------------------------------------------
    template<typename T,typename STORAGE>
    bool operator!=(const darray<T,STORAGE> &b1, 
                    const darray<T,STORAGE> &b2) 
    {
        if (!(b1 == b2)) {
            return true;
        }
        return false;
    }



}
}
