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
    \brief ref. buffer template

    This template is a concrete implementation of the BufferObject base class.
    Unlike the Buffer<T> template this object can be used to provide a buffer
    interface to memory allocated by other instances. Hence it is quite useful
    to connect to third party libraries.
    As the class is not responsible  for memory allocation it also frees no 
    memory. Thus memory management is entirely in the hand of third party
    instances.
    Such a reference buffer can either be initialized from a raw pointer, an
    instance of Buffer<T>, or from a different RefBuffer object.
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

            Returns a typed const pointer to the allocated memory. The 
            pointer must not be used to modify data values.
            \return pointer to allocated memory
            */
            const value_type* ptr() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief return value at index i

            Return the value stored in the buffer at index i. This method
            performe index checking and throws an exception if i exceeds the
            size of the buffer.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws IndexError if i exceeds buffer size
            \param i buffer index
            \return value at index i
            */
            value_type at(size_t i) const
            {
                check_allocation_state(*this,"value_type at(size_t i) const");
                check_ptr_state(this->_data,"value_type at(size_t i) const");
                check_index(i,this->size(),"value_type at(size_t i) const");

                return this->_data[i];
            }

            //-----------------------------------------------------------------
            /*! \brief return reference to index i

            Returns a reference to the element stored at index i. This method
            performs index checking and throws an exception if i exceeds the
            size of the buffer.
            \throws MemoryNotAllocatedError if buffer not allocated
            \throws IndexError if i exceeds buffer size
            \param i buffer index
            \return reference to element at i
            */
            value_type &at(size_t i)
            {
                check_allocation_state(*this,"value_type &at(size_t i)");
                check_ptr_state(this->_data,"value_type &at(size_t i)");
                check_index(i,this->size(),"value_type &at(size_t i)");

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
            performend. Invalid indices will thus lead to segmentation faults.
            \param n index of the element to fetch
            \return value of the buffer at position n
            \sa at()
            */
            value_type operator[](size_t n) const { return this->_data[n]; }

            //-----------------------------------------------------------------
            /*! 
            \brief insert a value

            Insert a value at a given position. Similiar to at() but can be used
            in thread-safe wrappers.
            \throws SizeMissmatchError if i exceeds buffer size
            \param i index where to insert the value
            \param v value to insert
            */
            void insert(size_t i,const value_type &v)
            {
                this->at(i) = v;
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
    template<typename T,typename U>
    bool operator==(const RBuffer<T> &a,const RBuffer<U> &b){
        if(a.size() != b.size()) return false;

        if((a.size()) && (b.size()))
        {
            for(size_t i=0;i<a.size();i++)
                if(a[i] != b[i]) return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------------
    template<typename T,typename U>
    bool operator!=(const RBuffer<T> &a,const RBuffer<U> &b){
        if(a == b) return false;
        return true;
    }




//end of namespace
}
}
#endif /* BUFFER_HPP_ */
