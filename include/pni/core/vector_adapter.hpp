/*
 * (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Feb 17, 2014
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

namespace pni{
namespace core{


    template<typename T> class vector_adapter
    {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef const T* const_pointer;
            typedef const T& const_reference;
            typedef size_t size_type;
            typedef pointer iterator;
            typedef const_pointer const_iterator;
        private:
            pointer _data;
            size_type _size; 
        public:
            /*!
            \brief default constructor
            */
            explicit vector_adapter():_data(nullptr),_size(0){}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            */
            explicit vector_adapter(pointer ptr,size_type s):
                _data(ptr),
                _size(s)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief copy constructor

            */
            vector_adapter(const vector_adapter<T> &a):
                _data(a._data),
                _size(a._size)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief move constructor

            */
            vector_adapter(vector_adapter<T> &&a):
                _data(a._data),
                _size(a._size)
            {
                a._data = nullptr;
                a._size = 0;
            }

    };

//end of namespace
}
}
