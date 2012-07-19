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
 * Created on: Apr 11, 2011
 *     Author: Eugen Wintersberger
 *
 */



#ifndef __DBUFFER_HPP__
#define __DBUFFER_HPP__

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Exceptions.hpp"
#include "Types.hpp"
#include "TypeIDMap.hpp"
#include "NewAllocator.hpp"
#include "Iterator.hpp"
#include "ExceptionUtils.hpp"

namespace pni{
namespace utils{

    /*! \ingroup data_classes
    \brief dynamic buffer template

    The Buffer template can be considered as a kind of guard object for
    pointers. It manages a particular portion of allocated memory. Once the
    object is destroyed (its destructor is called) the memory will be freed.
    Thus, the Buffer template should help to avoid memory leaks. 

    Although its interface looks a bit like a container class, the Buffer<T>
    template is not. It is rather really a replacement for a pointer to a
    portion of memory. It provides access to the pointer it holds via its ptr()
    and void_ptr() methods. Although this violates the object oriented paradigm
    of encapsulation, this is necessary in particular if one wants to use
    libraries which need access to such low level pointers. However, the class
    has still full controll over of the allocated memory.

    Due to the fact that access to the stored pointer is granted, this template
    is not thread safe. It would not make too much sense as the protection by a
    mutex could easily be cancled by passing the pointer held by the object
    around to other routines.
    */
    template<typename T,typename Allocator=NewAllocator >class DBuffer
    {
        private:
            T *_data; //!< pointer to the data block
            size_t _size; //!< number of allocated elements

            /*! \brief allocate memory

            Private method used to allocate memory. The method throws an
            exception if allocation fails.
            \throws MemoryAllocationError if allocation fails.
            */ 
            void _allocate();
           
        public:
            //============public types provided by the template================
            //! type stored in the buffer
            typedef T value_type;
            //! buffer type
            typedef DBuffer<T,Allocator> buffer_type;
            //! smart pointer to a typed buffer
            typedef std::shared_ptr<buffer_type> shared_ptr;
            //! unique poitner type to a buffer
            typedef std::unique_ptr<buffer_type> unique_ptr;
            //! allocator type
            typedef Allocator allocator_type;
            //! iterator type
            typedef Iterator<buffer_type,0 > iterator;        
            //! const iterator type
            typedef Iterator<buffer_type,1 > const_iterator; 

            //=============public static variables=============================
            //! type ID of the element type
            static const TypeID type_id    = TypeIDMap<value_type>::type_id; 
           
            //=================constructors and destructor=====================
            //! default constructor
            explicit DBuffer():_data(nullptr),_size(0) {}

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            This constructor initializes the new Buffer with the content of the
            old. New memory is allocated for the newly created Buffer<T> object.
            \throws MemoryAllocationError if allocation for the new buffer fails
            \param b reference to the original buffer
            */
            DBuffer(const buffer_type &b):
                _data(Allocator::template allocate<T>(b.size())),
                _size(b.size())
            {
                //copy data
                std::copy(b.begin(),b.end(),(*this).begin());
            }

            //-----------------------------------------------------------------
            /*! \brief move constructor

            Unlike the copy constructor no new memory is allocated during the
            construction of the lhs object. However, the rhs buffer will be
            freed. 
            */
            DBuffer(buffer_type &&b):_data(b._data),_size(b._size) 
            {
                b._data = nullptr;
                b._size = 0;
            }

            //-----------------------------------------------------------------
            /*! \brief constructor with buffer size

            Using this constructor the buffer will automatically allocate 
            memory.
            \throws MemoryAllocationError if allocation on the heap fails
            \param n number of elements of type T in the buffer
            */
            explicit DBuffer(size_t n):
                _data(Allocator::template allocate<value_type>(n)),
                _size(n)
            {}

            //-----------------------------------------------------------------
            /*! \brief construct with initializer list

            This constructor allows the construction of DynamicBuffer<T> objects 
            using an initializer list \code
            DBuffer<UInt32> buffer = {1,3,5,6,10};
            \endcode
            which in some cases simplifies the code sigificantly. 
            \throws MemoryAllocationError if memory allocation fails
            \param list reference to the initializer list
            */
            explicit DBuffer(const std::initializer_list<value_type> &list):
                _data(Allocator::template allocate<value_type>(list.size())),
                _size(list.size())
            
            {
                std::copy(list.begin(),list.end(),this->begin());
            }
            
            //-----------------------------------------------------------------
            //! destructor
            ~DBuffer() { this->free(); }

            //===================assignment operators==========================
            /*! copy assignment operator

            If the buffer on the rhs of the assignment operator is not allocated
            the rhs buffer object will be freed.
            \throws MemoryAccessError if something goes wring with memory allocation
            \param b Buffer whose content will be assigned to this buffer
            \return reference to a buffer_type object
            */
            buffer_type &operator=(const buffer_type &b)
            {
                if(this == &b) return *this;
                
                //allocate new memory only if the original buffer is allocated
                if(b.size())
                {
                    this->allocate(b.size());
                    for(size_t i=0;i<this->size();i++) (*this)[i] = b[i];
                }
                else
                {
                    //if the orignal buffer is not allocated we only need to free
                    //memory
                    this->free();
                }

                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            buffer_type &operator=(buffer_type &&b)
            {
                if(this == &b) return *this;

                this->free();
                this->_data = b._data;
                b._data = nullptr;
                this->_size = b._size;
                b._size = 0;

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
            /*! \brief get value at index i

            Returns the data value at index i of the buffer. 
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws IndexError if i exceeds the size of the buffer
            \param i buffer index
            \return value at index i
            */
            value_type at(size_t i) const
            {
                check_index(i,this->size(),"value_type at(size_t i) const");
                check_allocation_state(*this,"value_type at(size_t i) const");
                check_ptr_state(this->_data,"value_type at(size_t i) const");

                return this->_data[i];
            }

            //-----------------------------------------------------------------
            /*! \brief get value at index i

            Returns a reference to the element in the buffer at index i.
            \throws MemoryNotAllocatedError if buffer is not allocated
            \throws IndexError if i exceeds the size of the buffer
            \param i buffer index
            \return reference to the element at index i
            */
            value_type &at(size_t i)
            {
                check_index(i,this->size(),"value_type &at(size_t i) const");
                check_allocation_state(*this,"value_type &at(size_t i) const");
                check_ptr_state(this->_data,"value_type &at(size_t i) const");

                return this->_data[i];
            }

            //-----------------------------------------------------------------
            /*! 
            \brief insert value

            Insert value at index i.
            \throws MemoryNotAllocatedError if buffer not allocated
            \throws IndexError if i exceeds the size of the buffer
            \param i index where to insert data
            \param value the value to insert
            */
            void insert(size_t i,const value_type &value)
            {
                check_index(i,this->size(),"void insert(size_t i,const "
                                           "value_type &value)");
                check_allocation_state(*this,"void insert(size_t i,const "
                                             "value_type &value)");
                check_ptr_state(this->_data,"void insert(size_t i,const "
                                                   "value_type &value)");

                this->_data[i] = value;
            }

            //-----------------------------------------------------------------
            /*! [] operator for read and write access

            Returns a reference to the element at index i of the buffer. Unlike
            at() this operator performs no checks for index overflows or on the
            allocation state of the buffer. Thus, use it with care. 
            \param n index of element to fetch
            \return reference to the n-th element in the buffer
            */
            value_type& operator[](size_t n) { return _data[n]; }

            //-----------------------------------------------------------------
            /*! [] operator for read only access

            This operator will be used in expressions where read only access to 
            the data values in the buffer is required. No checks are performed
            for the allocation state of the buffer or index overflows.
            \param n index of the element to fetch
            \return value of the buffer at position n
            */
            value_type operator[](size_t n) const { return _data[n]; }

            //-----------------------------------------------------------------
            /*! \brief allocates memory

            Method allocates memory for size elements of type T. If the buffer
            is already allocated the original memory will be freed and new
            memory requested from ths OS. 
            \throws MemoryAllocationError if things go wrong
            \param size number of elements for which to allocate memory
            */
            void allocate(size_t size)
            {
                //free memory if necessary
                if(this->size()) this->free();
               
                //allocate new memory
                _data = Allocator::template allocate<T>(size);

                //set the size member variable
                _size = size;
            }

            //-----------------------------------------------------------------
            //! \brief free buffer memory
            void free()
            {
                Allocator::template free(_data);
                this->_data = nullptr;
                _size = 0;
            }


            //-----------------------------------------------------------------
            /*! \brief get number of elements

            Returns the number of elements stored in the buffer.
            \return number of elements
            */
            size_t size() const { return _size; }

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

            Returns an const iterator pointing to the last element of the buffer.
            \return const iterator to last element
            */
            const_iterator end() const 
            {
                return const_iterator(this,this->size());
            }

    };


    //==============comparison operators========================================
    template<typename T,typename TAlloc,typename U,typename UAlloc>
    bool operator==(const DBuffer<T,TAlloc> &a,const DBuffer<U,UAlloc> &b)
    {
        if(a.size() != b.size()) return false;

        if((a.size()) && (b.size()))
        {
            for(size_t i=0;i<a.size();i++)
                if(a[i] != b[i]) return false;
        }

        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename Allocator> 
        bool operator==(const DBuffer<T,Allocator> &a,const DBuffer<T,Allocator> &b)
    {
        if(a.size() != b.size()) return false;

        if((a.size()) && (b.size()))
        {
            for(size_t i=0;i<a.size();i++)
                if(a[i] != b[i]) return false;
        }

        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename TAlloc,typename U,typename UAlloc>
    bool operator!=(const DBuffer<T,TAlloc> &a,const DBuffer<U,UAlloc> &b)
    {
        if(a == b) return false;
        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename Alloc> 
        bool operator!=(const DBuffer<T,Alloc> &a,const DBuffer<T,Alloc> &b)
    {
        if(a == b) return false;
        return true;
    }


//end of namespace
}
}
#endif /* BUFFER_HPP_ */
