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
#include <iterator>
#include <stdexcept>

namespace pni{
namespace core{


    /*!
    \brief vector_adapter

    */
    template<typename T> class vector_adapter
    {
        public:
            typedef T value_type;
            typedef void allocator_type;
            typedef size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef T& reference;
            typedef const T& const_reference;
            typedef T* pointer;
            typedef const T* const_pointer;
            typedef pointer iterator;
            typedef const_pointer const_iterator;
            typedef std::reverse_iterator<iterator> reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
            
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

            //===============assignment operators==============================
            /*!
            \brief copy assignment operator

            */
            vector_adapter<T> &operator=(const vector_adapter<T> &o)
            {
                if(this == &o) return *this;

                _data = o._data;
                _size = o._size;
                return *this;
            }

            //-----------------------------------------------------------------
            /*!
            \brief move assignment operator

            */
            vector_adapter<T> &operator=(vector_adapter<T> &&o)
            {
                if(this == &o) return *this;

                _data = o._data;
                _size = o._size;

                o._data = nullptr;
                o._size = 0;
            }

            //=============element access======================================
            reference at(size_type pos)
            {
                if(pos>=size())
                    throw std::out_of_range();

                return _data[pos];
            }

            //-----------------------------------------------------------------
            const_reference at(size_type pos) const
            {
                if(pos>=size())
                    throw std::out_of_range();

                return _data[pos];
            }

            //-----------------------------------------------------------------
            reference operator[](size_type pos) { return _data[pos]; }

            //-----------------------------------------------------------------
            const_reference operator[](size_type pos) const 
            { 
                return _data[pos]; 
            }

            //-----------------------------------------------------------------
            reference front() { return _data[0]; }

            //-----------------------------------------------------------------
            const_reference front() const { return _data[0]; }

            //-----------------------------------------------------------------
            reference back() { return _data[size()-1]; }

            //-----------------------------------------------------------------
            const_reference back() const { return _data[size()-1]; }

            //-----------------------------------------------------------------
            pointer data() { return _data; }

            //-----------------------------------------------------------------
            const_pointer data() const { return _data; }

           
            //-----------------------------------------------------------------
            /*!
            \brief get number of elements
            */
            size_type size() const
            {
                return _size;
            }

            //-----------------------------------------------------------------
            bool empty() const
            {
                return _data == nullptr;
            }

            //-----------------------------------------------------------------
            size_type capacity() const
            {
                return size();
            }

            //=================iterators=======================================
            iterator begin() { return &_data[0]; }

            //-----------------------------------------------------------------
            iterator end() { return &_data[size()]; }

            //-----------------------------------------------------------------
            const_iterator begin() const { return &_data[0]; }

            //-----------------------------------------------------------------
            const_iterator end() const { return &_data[size()]; }

            //-----------------------------------------------------------------
            reverse_iterator rbegin() 
            { 
                return reverse_iterator(end());  
            }

            //-----------------------------------------------------------------
            reverse_iterator rend() 
            {
                return reverse_iterator(begin()); 
            }

            //-----------------------------------------------------------------
            const_reverse_iterator rbegin() const 
            {
                return const_reverse_iterator(end()); 
            }

            //-----------------------------------------------------------------
            const_reverse_iterator rend() const 
            {
                return const_reverse_iterator(begin()); 
            }


    };

//end of namespace
}
}
