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
 * Declaration of the typed Buffer<T> template. This is a descendant of
 * BufferObject as declared in BufferObject.hpp. It implements the interface
 * as suggested by its base class.
 *
 * Created on: Jan 02, 2012
 *     Author: Eugen Wintersberger
 *
 */



#ifndef __RBUFFER_HPP_
#define __RBUFFER_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"
#include "Types.hpp"
#include "TypeIDMap.hpp"
#include "Iterator.hpp"

namespace pni{
namespace utils{

    /*! \ingroup buffer_classes
    \brief reference buffer template

    This buffer template acts as a decorator for already allocated memory
    referenced by a raw pointer. 
    This template is useful in cases where one needs to interact with a library
    which supports only raw pointers. 
    The usage is quite straight forward as shown in this example:
    \code
    UInt32 *ptr = new UInt32[100];

    RBuffer<UInt32> buffer(100,ptr);
    \endcode
    The constructor of RBuffer<T> takes the number of elements and a pointer to
    the allocated memory as arguments. It is up to the user to take care that
    memory remains allocated during the entire lifetime of the instance of
    RBuffer<T>. 
    As the template does not memory management it is also up to the user to free
    the allocated memory when no longer needed.
    \tparam T element type 
    */
    template<typename T> class RBuffer
    {
        private:
            T *_data; //!< pointer to the data block
            size_t _size; //!< number of elements allocated in the buffer
        public:
            //===================public types =================================
            //! type of data stored
            typedef T value_type;             
            //! type of the buffer
            typedef RBuffer<T> buffer_type;
            //! unique pointer type 
            typedef std::unique_ptr<buffer_type> unique_ptr;
            //! shared pointer type
            typedef std::shared_ptr<buffer_type> shared_ptr;
            //! iterator type
            typedef Iterator<buffer_type,0> iterator; 
            //! const iterator type
            typedef Iterator<buffer_type,1> const_iterator; 

            //===================public static member variables================
            //! ID of the element data type
            static const TypeID type_id    = TypeIDMap<value_type>::type_id; 

            //=================constructors and destructors====================
            //! default constructor
            explicit RBuffer():
                _data(nullptr),
                _size(0)
            {}

            //-----------------------------------------------------------------
            //! copy constructor
            RBuffer(const buffer_type &b):_data(b._data),_size(b._size) {}

            //-----------------------------------------------------------------
            //! move constructor
            RBuffer(buffer_type &&b):_data(b._data),_size(b._size)
            {
                b._data = nullptr;
                b._size = 0;
            }

            //-----------------------------------------------------------------
            /*! \brief standard constructor

            This constructor takes the number of elements and a raw pointer to
            the allocated memory region. It is the responsibility of the user to
            ensure that memory is allocated.
            \param n number of elements of type T in the buffer
            \param data pointer to the allocated memory
            */
            explicit RBuffer(size_t n,T *data):
                _data(data),
                _size(n)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~RBuffer() 
            { 
                this->_data = nullptr; 
                this->_size = 0;
            }

            //====================assignment operators=========================
            //! copy assignment operator
            buffer_type &operator=(const buffer_type &b)
            {
                if(&b != this){
                    _data = b._data;
                    _size = b._size;
                }

                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            buffer_type &operator=(buffer_type &&b)
            {
                if(this != &b){
                    _data = b._data;
                    b._data = nullptr;
                    _size = b._size;
                    b._size = 0;
                }

                return *this;
            }

            //====================data access methods==========================
            /*! \brief return data pointer

            Returns a const pointer to the internal pointer member.
            \return pointer to allocated memory
            */
            const value_type* ptr() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief return value at index i

            Return the value stored in the buffer at index i. This method
            performes index checking and throws an exception if i exceeds the
            size of the buffer. In addition an exception is thrown if the
            internal pointer of the template is a nullptr which indicates that
            no memory has been allocated at the first place.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws IndexError if i exceeds buffer size
            \param i buffer index
            \return value at index i
            */
            value_type at(size_t i) const
            {
                check_allocation_state(*this,EXCEPTION_RECORD);
                check_ptr_state(this->_data,EXCEPTION_RECORD);
                check_index(i,this->size(),EXCEPTION_RECORD);

                return this->_data[i];
            }

            //-----------------------------------------------------------------
            /*! \brief return reference to index i

            Returns a reference to the element stored at index i. This method
            performs index checking and throws an exception if i exceeds the
            size of the buffer. If the internal pointer is a nullptr an
            exception will be thrown as the template assumes that no memory has
            been allocated at the first place.
            \throws MemoryNotAllocatedError if buffer not allocated
            \throws IndexError if i exceeds buffer size
            \param i buffer index
            \return reference to element at i
            */
            value_type &at(size_t i)
            {
                check_allocation_state(*this,EXCEPTION_RECORD);
                check_ptr_state(this->_data,EXCEPTION_RECORD);
                check_index(i,this->size(),EXCEPTION_RECORD);

                return this->_data[i];
            }

            //-----------------------------------------------------------------
            /*! \brief return reference to element i

            Return a reference to the value of the buffer stored at index i.
            No index checking is done - use this operator with care. It should
            be used for high performance access only. 
            \param n index of element to fetch
            \return reference to the n-th element in the buffer
            \sa at()
            */
            value_type& operator[](size_t n) { return this->_data[n];}

            //-----------------------------------------------------------------
            /*! \brief return the value of element i

            This operator will be used in expressions where read only access 
            to the data values in the buffer is required. No index checking is
            performed. Invalid indices will thus lead to segmentation faults.
            \param n index of the element to fetch
            \return value of the buffer at position n
            \sa at()
            */
            value_type operator[](size_t n) const { return this->_data[n]; }

            //-----------------------------------------------------------------
            /*! 
            \brief insert a value

            Insert a value at a given position. Familiar to at() but can be used
            in thread-safe wrappers.
            \throws MemoryNotAllocatedError if internal pointer is nullptr
            \throws IndexError if i exceeds buffer size
            \param i index where to insert the value
            \param v value to insert
            */
            void insert(size_t i,const value_type &v)
            {
                try { this->at(i) = v; } 
                EXCEPTION_FORWARD(IndexError)
                EXCEPTION_FORWARD(MemoryNotAllocatedError);
            }


            //-----------------------------------------------------------------
            /*! \brief return number of elements 

            Returns the number of elements allocated by the buffer.
            \return number of elements
            */
            size_t size() const { return this->_size; }
            
            //------------------------------------------------------------------
            /*! \brief get iterator to first element

            Returns an iterator pointing on the first element of the buffer.
            \return iterator to first element
            */
            iterator begin() { return iterator(this,0); }

            //------------------------------------------------------------------
            /*! \brief get iterator to last element

            Returns an iterator pointing to the last+1 element of the buffer.
            The iterator is thus invalid.
            \return iterator to last element
            */
            iterator end() { return iterator(this,this->size()); }

            //------------------------------------------------------------------
            /*! \brief get const iterator to first element

            Returns an const iterator pointing on the first element of the buffer.
            \return const iterator to first element
            */
            const_iterator begin() const { return const_iterator(this,0); }

            //------------------------------------------------------------------
            /*! \brief get const iterator to last element

            Returns an const iterator pointing to the last+1 element of the buffer.
            The iterator is thus invalid.
            \return const iterator to last element
            */
            const_iterator end() const { return const_iterator(this,this->size());}

    };

    //==============comparison operators============================================
    /*! 
    \ingroup buffer_classes
    \brief equality comparison between RBuffer templates

    Compares two instances of RBuffer for equality. Two buffers are considered
    of being equal if they are of same size and the values of their elements
    coincide. To use this operator the two types T and U must be comparable.
    \tparam T type of the first buffer
    \tparam T type of the second buffer
    \param a first buffer - instance of RBuffer<T>
    \param b second buffer - instance of RBuffer<U>
    \return true of equal, else otherwise
    */
    template<typename T,typename U>
    bool operator==(const RBuffer<T> &a,const RBuffer<U> &b){
        if(a.size() != b.size()) return false;
        
        return std::equal(a.begin(),a.end(),b.begin());
    }

    //-----------------------------------------------------------------------------
    /*!
    \ingroup buffer_classes
    \brief in-equality comparison between two RBuffer templates

    Checks two instance of RBuffer for in-equality. In order to use this
    operator the two types T and U must be comparable.
    \tparam T type of first buffer
    \tparam U type of second buffer
    \param a first buffer - instance of RBuffer<T>
    \param b second buffer - instance of RBuffer<U>
    \return true if not-equal, false otherwise
    */
    template<typename T,typename U>
    bool operator!=(const RBuffer<T> &a,const RBuffer<U> &b){
        if(a == b) return false;
        return true;
    }




//end of namespace
}
}
#endif /* BUFFER_HPP_ */
