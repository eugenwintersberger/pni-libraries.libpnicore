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
 * Definition of a static buffer. 
 *
 * Created on: May 24, 2012
 *     Author: Eugen Wintersberger
 *
 */



#ifndef __SBUFFER_HPP__
#define __SBUFFER_HPP__

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Exceptions.hpp"
#include "Types.hpp"
#include "TypeIDMap.hpp"
#include "Iterator.hpp"
#include "ExceptionUtils.hpp"

namespace pni{
namespace utils{

    /*! \ingroup buffer_classes
    \brief static buffer template
    
    This template implements a static buffer. The amount of memory occupied by
    the buffer is determined at compile time and cannot be altered during
    runtime.
    The usage of this template is rather simple
    \code
    SBuffer<Float64,1024> buffer; //creates a buffer for 1024 Float64 values

    //full STL compatible
    for(auto v: buffer) std::cout<<v<<std::endl;

    //linear access without index check
    buffer[100] = 1234.23;

    //linear access with index check
    size_t index; 
    std::cin>>index;
    try{ buffer.at(index) = ...; }
    catch(IndexError &e)
    {
        ...handle error ...
    }

    \endcode
    \tparam T type to be stored in the buffer
    \tparam N number of element of T in the buffer
    */
    template<typename T,size_t N >class SBuffer
    {
        private:
            T _data[N]; //!< pointer to the data block
        public:
            //============public types provided by the template================
            //! type stored in the buffer
            typedef T value_type;  
            //! buffer type
            typedef SBuffer<T,N> buffer_type;
            //! smart pointer to a typed buffer
            typedef std::shared_ptr<buffer_type> shared_ptr;
            //! unique poitner type to a buffer
            typedef std::unique_ptr<buffer_type> unique_ptr;
            //! iterator type
            typedef Iterator<buffer_type,0 > iterator;      
            //! const iterator type
            typedef Iterator<buffer_type,1 > const_iterator; 

            //=============public static variables=============================
            //! type ID of the element type
            static const TypeID type_id    = TypeIDMap<value_type>::type_id; 
           
            //=================constructors and destructor=====================
            //! default constructor
            explicit SBuffer(){}

            //-----------------------------------------------------------------
            //! \brief copy constructor
            explicit SBuffer(const buffer_type &b)
            {
                //copy data
                for(size_t i=0;i<this->size();i++) (*this)[i] = b[i];
            }


            //-----------------------------------------------------------------
            /*! \brief construct with initializer list

            Sets the content of the StaticBuffer from an initializer list. 
            \code
            StaticBuffer<UInt32,5> buffer = {1,3,5,6,10};
            \endcode
            An exception is thrown if the number of elements in the list does
            not match the size of the buffer.
            \throws SizeMissmatchError list size does not match buffer size
            \param list reference to the initializer list
            */
            explicit SBuffer(const std::initializer_list<value_type> &list)
            {
                check_equal_size(*this,list,EXCEPTION_RECORD);
                
                size_t i=0;
#ifdef NOFOREACH
                for(auto iter = list.begin();iter!=list.end();++iter)
                {
                    auto v = *iter;
#else
                for(auto v: list)
                {
#endif
                    (*this)[i] = v;
                }
            }


            //-----------------------------------------------------------------
            //! destructor
            ~SBuffer() {} 

            //===================assignment operators==========================
            //! copy assignment operator
            buffer_type &operator=(const buffer_type &b)
            {
                if(this == &b) return *this;
                std::copy(b.begin(),b.end(),(*this).begin());
                return *this;
            }


            //==============public methods for data access=====================
            /*! \brief return data pointer

            Returns a typed const pointer to the allocated memory. The pointer 
            must not be used to modify data values.
            \return pointer to allocated memory
            */
            const value_type* ptr() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! 
            \brief return data pointer

            Returns a typed pointer to the allocated memory. The pointer can be
            used for altering the buffer content.
            \return pointer to allocated memory
            */
            value_type *ptr() { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief get value at index i

            Returns the data value at index i of the buffer. 
            \throws IndexError if i exceeds the size of the buffer
            \param i buffer index
            \return value at index i
            */
            value_type at(size_t i) const
            {
                check_index(i,this->size(),EXCEPTION_RECORD);
                return _data[i];
            }

            //-----------------------------------------------------------------
            /*! \brief get value at index i

            Returns a reference to the element in the buffer at index i.
            \throws IndexError if i exceeds the size of the buffer
            \param i buffer index
            \return reference to the element at index i
            */
            value_type &at(size_t i)
            {
                check_index(i,this->size(),EXCEPTION_RECORD);
                return _data[i];
            }

            //-----------------------------------------------------------------
            /*! 
            \brief [] operator for read and write access

            Returns a reference to the element at index i of the buffer. Unlike
            at() this operator performs no checks for index overflows or on the
            allocation state of the buffer. Thus, use it with care. 
            \param n index of element to fetch
            \return reference to the n-th element in the buffer
            */
            value_type& operator[](size_t n) { return this->_data[n]; }

            //-----------------------------------------------------------------
            /*! 
            \brief [] operator for read only access

            This operator will be used in expressions where read only access to 
            the data values in the buffer is required. No checks are performed
            for the allocation state of the buffer or index overflows.
            \param n index of the element to fetch
            \return value of the buffer at position n
            */
            value_type operator[](size_t n) const { return this->_data[n]; }

            //-----------------------------------------------------------------
            /*! 
            \brief insert value

            This is quite similar to at(). However, unlike at() it can be used
            in a thread-safe interface.
            \throws IndexError if i exceeds buffer size
            \throws MemoryAllocationError if buffer is not allocated
            \param i index where to insert the value\
            \param v value to insert
            */
            void insert(size_t i,const value_type &v)
            {
                check_index(i,this->size(),EXCEPTION_RECORD);
                (*this)[i] = v;
            }

            //-----------------------------------------------------------------
            /*! \brief get number of elements

            Returns the number of elements stored in the buffer.
            \return number of elements
            */
            size_t size() const { return N; }

            //------------------------------------------------------------------
            /*! \brief get iterator to first element

            Returns an iterator pointing on the first element of the buffer.
            \return iterator to first element
            */
            iterator begin() { return iterator(this,0); }

            //------------------------------------------------------------------
            /*! \brief get iterator to last element

            Returns an iterator pointing to the last element of the buffer.
            \return iterator to last element
            */
            iterator end() { return iterator(this,this->size()); }

            //------------------------------------------------------------------
            /*! \brief get const iterator to first element

            Returns an const iterator pointing on the first element of the buffer.
            \return const iterator to first element
            */
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //------------------------------------------------------------------
            /*! \brief get const iterator to last element

            Returns an const iterator pointing to the last element of the buffer.
            \return const iterator to last element
            */
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }


    };

    //==============comparison operators========================================
    /*!
    \ingroup buffer_classes
    \brief comparison operator for static buffers

    Compares two static buffers and returns true if they are equal. Two buffers
    are considered as equal if they have the same size and if their elements
    have the same value. The size does not need to be checked as it is part of
    the buffer types definition.
    \tparam T data type of the first buffer
    \tparam U data type of the second buffer
    \tparam N size of the buffers
    \param a first buffer
    \param b second buffer
    \return true if buffers are equal, false otherwise
    */
    template<typename T,typename U,size_t N>
    bool operator==(const SBuffer<T,N> &a,const SBuffer<U,N> &b){
        
        for(size_t i=0;i<a.size();i++)
            if(a[i] != b[i]) return false;

        return true;
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup buffer_classes
    \brief in-equality operator for static buffers

    Return true if two static buffers are not equal. This will be the case when
    the content of the two buffers does not share the same values.
    \tparam T data type of the first buffer
    \tparam U data type of the second buffer
    \tparam N size of the two buffers
    \param a first buffer
    \param b second buffer
    \return true if buffers are not equal, false otherwise
    */
    template<typename T,typename U,size_t N>
    bool operator!=(const SBuffer<T,N> &a,const SBuffer<U,N> &b)
    {
        if(a == b) return false;
        return true;
    }



//end of namespace
}
}
#endif 
