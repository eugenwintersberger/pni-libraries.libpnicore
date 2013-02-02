/*
 * Declaration of class template Scalar<T>
 *
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
 * Scalar<T> represents a scalar numeric value of a particular type along
 * with basic arithmetic operations.
 *
 * Created on: Jun 9, 2011
 *     Author: Eugen Wintersberger
 *
 */
#pragma once

#include <iostream>

#include "types.hpp"
#include "type_id_map.hpp"
#include "sbuffer.hpp"
#include "array_view.hpp"

namespace pni {
namespace core {


    /*! 
    \ingroup numeric_array_classes
    \brief Scalar template for scalar values

    This template is used in expression tempaltes. Its purpose is to give scalar
    values an array like interface.

    \tparam T scalar type of the data stored.
    */
    template<typename T> class scalar
    {
        private:
            //! static buffer holding the data value
            sbuffer<T,1> _data; 
        public:
            //================public data types================================
            //! native data type of the scalar
            typedef T value_type;
            //! type of the scalar itself
            typedef scalar<T> array_type;
            //! storage type
            typedef sbuffer<T,1> storage_type;
            //! shared pointer typ
            typedef std::shared_ptr<array_type> shared_ptr;
            //! unique pointer type
            typedef std::unique_ptr<array_type> unique_ptr; 
            //! iterator
            typedef typename storage_type::iterator iterator;
            //! const iterator
            typedef typename storage_type::const_iterator const_iterator;
            //! view type
            typedef array_view<array_type> view_type;
            
            //===============public members====================================
            //! type ID of the data type held by the scalar
            static const type_id_t type_id = type_id_map<T>::type_id;

            //====================constructors and destructor==================
            //! default constructor
            scalar():_data() {}

            //-----------------------------------------------------------------
            //! copy constructor
            scalar(const array_type &s):_data(s._data) {}
            
            //-----------------------------------------------------------------
            //! constructor from a scalar value
            scalar(const value_type &r):_data({r}) {}

            //-----------------------------------------------------------------

            //-----------------------------------------------------------------
            //! destructor
            ~scalar() {}

            //=================assignment operators============================
            /*! 
            \brief assignment from T value

            Assigns a value of type T to the scalar.
            \param v value to assign
            */
            array_type &operator=(const value_type &v)
            {
                this->_data[0] = v;
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief assignment from Scalar<T>

            This is the most trivial case. An object of type Scalar<T> is 
            assigned to an other object of type Scalar<T>.
            \param v value of Scalar<T> to assign
            */
            array_type &operator=(const array_type &v)
            {
                if(this == &v) return *this;
                this->_data = v._data;
                return *this;
            }

            //=======================conversion operator========================
            operator T() const
            {
                return this->_data[0];
            }


            //===================linear access operators========================
            /*!
            \brief get data

            Return the single data value independent of what value of i is
            given.
            \return value of the scalar
            */
            T operator[](size_t i) const { return this->_data[0]; }

            //-----------------------------------------------------------------
            /*!
            \brief get reference to data
            
            Return a reference to the data stored in the scalar. No matter what
            value of i is passed to this operator - it will always return the
            same reference.
            \param i index
            \return reference to the scalar data
            */
            T &operator[](size_t i) { return this->_data[0]; }

            //-----------------------------------------------------------------
            /*! 
            \brief get data value

            Return the value of the data stored in the instance no matter of the
            value of the index.
            \param i index
            \return data value
            */
            T at(size_t i) const { return this->_data[0]; }

            //-----------------------------------------------------------------
            /*! 
            \brief get data reference

            Return a reference to the data stored in the scalar no matter what
            index is passed to the method.
            \param i index
            \return reference to data
            */
            T &at(size_t i) { return this->_data[0]; }

            //-----------------------------------------------------------------
            /*! 
            \brief set data value

            Method to set a data value. The index does not matter. 
            \param i index
            \param v value
            */
            void insert(size_t i,const T &v) { this->_data[0] = v; }
            
            //-----------------------------------------------------------------
            /*! 
            \brief get reference to the storage object

            Return a const reference to the static buffer that holds the scalar
            data. 
            \return reference to buffer object
            */
            const storage_type &storage() const { return this->_data; }

            //==================methods for multidim data access===============
            /*! 
            \brief get reference to the data

            Returns the reference to the data value no matter how many or what
            indices are passed.
            \tparam ITYPES index types
            \param indices multidimensional index
            \return reference to data
            */
            template<typename ...ITYPES> T &operator()(ITYPES ...indices)
            {
                return this->_data[0];
            }

            //-----------------------------------------------------------------
            /*!
            \brief get value of data

            Return the value of the scalar. The number of indices or their type
            do not matter.
            \tparam ITYPES index types
            \param indices multidimensional index
            \return data value
            */
            template<typename ...ITYPES> T operator()(ITYPES ...indices) const
            {
                return this->_data[0];
            }

            //-----------------------------------------------------------------
            /*!
            \brief get reference to data

            Return a reference to the data. The multidimensional index is passed
            by a container. The number of indices or their value are ignored. 
            \tparam CTYPE container template
            \tparam OTS template arguments for the container template
            \param c container with indices
            \return reference to the data
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                T &operator()(const CTYPE<OTS...> &c)
            {
                return this->_data[0];
            }

            //-----------------------------------------------------------------
            /*!
            \brief get data value
            
            Return the data value. The multidimensional index is passed by a
            container. The number of indices or their value are ignored.
            \tparam CTYPE container template
            \tparam OTS template arguments of the container template

            \param c container with indices
            \return data value
            */
            template<template<typename ...> class CTYPE,typename ...OTS>
                T operator()(const CTYPE<OTS...> &c) const
            {
                return this->_data[0];
            }


            //===================inquery methods===============================
            /*!
            \brief get size

            For a scalar object this method always returns 1. This is due to the
            fact that one needs to allocate only one block of memory of
            sizeof(T) bytes to hold the scalar data.
            \return 1
            */
            size_t size() const { return 1; }

            //-----------------------------------------------------------------
            /*!
            \brief get rank

            Return the number of dimensions of the scalar. This is always 0.
            \return 0
            */
            size_t rank() const { return 0; }

            //------------------------------------------------------------------
            /*! 
            \brief get shape

            Returns the shape of the scalar - this is a container with a single
            value 1.
            \return container with 1
            */
            template<typename CTYPE> CTYPE shape() const
            {
                return CTYPE();
            }

            //------------------------------------------------------------------
            //! get iterator to first element
            iterator begin() 
            { 
                return this->_data.begin(); 
            }

            //------------------------------------------------------------------
            //! get iterator to last+1 element
            iterator end() 
            { 
                return this->_data.end();
            }

            //------------------------------------------------------------------
            //! get const iterator to first element
            const_iterator begin() const 
            { 
                return this->_data.begin(); 
            }

            //------------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const 
            { 
                return this->_data.end();
            }

    };

    /*!
    \brief stream output operator

    Write content to output stream.
    \param os output stream
    \param s scalar value
    \return reference to output stream
    */
    template<typename T>
    std::ostream &operator<<(std::ostream &os,const scalar<T> &s)
    {
        T value = s[0]; 
        os<<value;
        return os;
    }

    //-------------------------------------------------------------------------
    /*!
    \brief input strema data

    Read content from input stream
    \param is input stream
    \param s scalar 
    \return reference to input stream
    */
    template<typename T>
    std::istream &operator>>(std::istream &is,scalar<T> &s)
    {
        T value;
        is>>value;
        s = value;
        return is;
    }

//end of namespace
}
}
