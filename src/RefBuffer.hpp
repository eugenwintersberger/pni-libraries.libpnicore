/*
 * Declaration of the RefBuffer<T> template
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
 * Declaration of the typed Buffer<T> template. This is a descendant of
 * BufferObject as declared in BufferObject.hpp. It implements the interface
 * as suggested by its base class.
 *
 * Created on: Jan 02, 2012
 *     Author: Eugen Wintersberger
 *
 */



#ifndef __REFBUFFER_HPP_
#define __REFBUFFER_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include "Exceptions.hpp"
#include "Types.hpp"
#include "Buffer.hpp"
#include "TypeIDMap.hpp"

namespace pni{
namespace utils{

#define RBUFFTMPDEC template<typename T,typename Allocator>
#define RBUFFTMP RefBuffer<T,Allocator>

    /*! \ingroup data_classes
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
    RBUFFTMPDEC class RefBuffer
    {
        private:
            T *_data; //!< pointer to the data block
            size_t _size; //!< number of elements allocated in the buffer
        public:
            //===================public types =================================
            typedef std::unique_ptr<RBUFFTMP > unique_ptr;
            typedef std::shared_ptr<RBUFFTMP > shared_ptr; //!< smart pointer to a typed buffer
            typedef T value_type;
            typedef Allocator allocator_type;

            //===================public static member variables================
            static const size_t value_size = sizeof(T);
            static const TypeID type_id    = TypeIDMap<T>::type_id;

            //=================constructors and destructors====================
            //! default constructor
            explicit RefBuffer();

            //-----------------------------------------------------------------
            //! copy constructor
            RefBuffer(const RBUFFTMP &b);

            //-----------------------------------------------------------------
            //! copy constructor
            RefBuffer(const Buffer<T,Allocator> &b);

            //-----------------------------------------------------------------
            //! move constructor
            RefBuffer(RBUFFTMP &&b);

            //-----------------------------------------------------------------
            /*! \brief standard constructor

            This constructor takes the number of elements and a raw pointer to
            the allocated memory region. It is the responsibility of the user to
            ensure that memory is allocated.
            \param n number of elements of type T in the buffer
            \param data pointer to the allocated memory
            */
            explicit RefBuffer(size_t n,T *data);
            
            //-----------------------------------------------------------------
            //! destructor
            virtual ~RefBuffer();

            //====================assignment operators=========================
            //! copy assignment operator
            RBUFFTMP &operator=(const RBUFFTMP &b);

            //-----------------------------------------------------------------
            //! move assignment operator
            RBUFFTMP &operator=(RBUFFTMP &&b);

            //-----------------------------------------------------------------
            /*! copy assignment operator from Buffer<T>

            The reference buffer holds a reference to the data which was allocated 
            by the b. 
            */
            RBUFFTMP &operator=(const Buffer<T,Allocator> &b);

            //-----------------------------------------------------------------
            /*! \brief single value assignment operator

            This special form of the assignment operator can be used to assign
            a single value to all elements of the buffer. Thus, it is quite useful
            for initializing a buffer object.
            \param v value which to assign to all buffer elements
            */
            RBUFFTMP &operator=(const T &v);

            //====================data access methods==========================
            //! return data pointer

            //! Returns a typed const pointer to the allocated memory. The pointer must
            //! not be used to modify data values.
            //! \return pointer to allocated memory
            const T* ptr() const { return this->_data; }
            //! return data pointer

            //! Returns a typed pointer to the allocated memory. The pointer can be
            //! used for altering the buffer content.
            //! \return pointer to allocated memory
            T *ptr() { return this->_data; }

            void *void_ptr() { return (void *)this->_data;}

            const void *void_ptr() const { return (const void *)this->_data; }

            T at(size_t i) const;
            T &at(size_t i);

            //! [] operator for read and write access

            //! This operator will be used in expressions where the buffer access stands
            //! on the left side of an assignment operation. In other words - when data should
            //! be written to the buffer.
            //! \param n index of element to fetch
            //! \return reference to the n-th element in the buffer
            T& operator[](size_t n) { return this->_data[n];}
            //! [] operator for read only access

            //! This operator will be used in expressions where read only access to the
            //! data values in the buffer is required.
            //! \param n index of the element to fetch
            //! \return value of the buffer at position n
            T operator[](size_t n) const { return this->_data[n]; }

            //! allocate memory - does nothing

            //! For a RefBuffer this method has no effect.
            void allocate(size_t size) {}
            
            //! check if buffer is allocated

            //! The behavior of this method varies slightly from the original
            //! definition. As a RefBuffer has no influence on the allocation 
            //! of memory this method returns true if the pointer it referes 
            //! to is not a nullptr. 
            //! \return true if pointer is not nullptr, false otherwise
            bool is_allocated() const
            {
                if(this->_data) return true;
                return false;
            }

            //! free memory - does nothing

            //! In the case of a RefBuffer this method does not free memory 
            //! but resets the internal data pointer to nullptr.
            void free() 
            {
                _data = nullptr;
                _size = 0;
            }

            virtual size_t mem_size() const {
                return sizeof(T)*this->size();
            }

    };

    //=================Implementation of constructors and destructors===============
    //implementation of the default constructor
    RBUFFTMPDEC RBUFFTMP::RefBuffer():
        _data(nullptr),
        _size(0)
    { }

    //------------------------------------------------------------------------------
    //implementation of the copy from RefBuffer constructor
    RBUFFTMPDEC RBUFFTMP::RefBuffer(const RBUFFTMP& o):
        _data(o._data),
        _size(o._size)
    { }

    //------------------------------------------------------------------------------
    //implementation of the copy constructor
    RBUFFTMPDEC RBUFFTMP::RefBuffer(const Buffer<T,Allocator> &b):
        _data(b.ptr()),
        _size(b.size())
    { }

    //------------------------------------------------------------------------------
    //implementation of the move constructor
    RBUFFTMPDEC RBUFFTMP::RefBuffer(RBUFFTMP &&b):
        _data(std::move(b._data)),
        _size(std::move(b._size))
    {
        b._data = nullptr;
        b._size = 0;
    }

    //------------------------------------------------------------------------------
    //implementation of the standard constructor
    RBUFFTMPDEC RBUFFTMP::RefBuffer(size_t n,T *data):
        _data(data),
        _size(n)
    { }

    //------------------------------------------------------------------------------
    //implementation of the destructor
    RBUFFTMPDEC RBUFFTMP::~RefBuffer()
    {
        free();
    }

    //===================assignment operators=======================================
    //implementation of copy assignment
    RBUFFTMPDEC RBUFFTMP &RBUFFTMP::operator=(const RBUFFTMP &b)
    {
        if(&b != this){
            _data = b._data;
            _size = b._size;
        }

        return *this;
    }

    //------------------------------------------------------------------------------
    //implementation of the move assignment
    RBUFFTMPDEC RBUFFTMP &RBUFFTMP::operator=(RBUFFTMP &&b)
    {
        if(this != &b){
            _data = b._data;
            b._data = nullptr;
            _size = b._sizel;
            b._size = 0;
        }

        return *this;
    }

    //-----------------------------------------------------------------------------
    //copy assignment from Buffer<T> template
    RBUFFTMPDEC RBUFFTMP &RBUFFTMP::operator=(const Buffer<T,Allocator> &b)
    {
        _data = b.ptr();
        _size = b.size();
        
        return *this;
    }

    //------------------------------------------------------------------------------
    //implementation of single value assignment
    RBUFFTMPDEC RBUFFTMP &RBUFFTMP::operator=(const T &d){
        EXCEPTION_SETUP("template<typename T> RefBuffer<T> &RefBuffer<T>::operator=(const T &d)");

        if(!this->is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,"Cannot assign data to an unallocated buffer!");
            EXCEPTION_THROW();
        }

        //we do not need to check the size here because if the buffer is allocated
        //the size is necessarily not zero
        for(size_t i=0;i<this->size();i++) (*this)[i] = d;


        return *this;
    }

    //===============Methods for data access========================================
    RBUFFTMPDEC T RBUFFTMP::at(size_t i) const 
    {
        EXCEPTION_SETUP("RBUFFTMPDEC T RBUFFTMP::at(size_t i) const ");

        if(!this->is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated");
            EXCEPTION_THROW();
        }

        if(i>=this->size()){
            std::ostringstream sstr;
            sstr<<"Index ("<<i<<") must not be larger or equal the size ("<<this->size()<<")of the buffer!";
            EXCEPTION_INIT(IndexError,sstr.str());
            EXCEPTION_THROW();
        }

        return this->_data[i];
    }

    //------------------------------------------------------------------------------
    RBUFFTMPDEC T & RBUFFTMP::at(size_t i)
    {
        EXCEPTION_SETUP("RBUFFTMPDEC T & RBUFFTMP::at(size_t i)");

        if(!this->is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated!");
            EXCEPTION_THROW();
        }

        if(i>=this->size()){
            std::ostringstream sstr;
            sstr<<"Index ("<<i<<") must not be larger or equal the size ("<<this->size()<<")of the buffer!";
            EXCEPTION_INIT(IndexError,sstr.str());
            EXCEPTION_THROW();
        }

        return this->_data[i];
    }


    //==============comparison operators============================================
    template<typename T,typename U,typename Allocator>
    bool operator==(const RefBuffer<T,Allocator> &a,const RefBuffer<U,Allocator> &b){
        if(a.size() != b.size()) return false;

        if(a.is_allocated()!=b.is_allocated()) return false;

        if(a.is_allocated() && b.is_allocated()){
            for(size_t i=0;i<a.size();i++){
                if(a[i] != b[i]) return false;
            }
        }

        return true;
    }




    //-----------------------------------------------------------------------------
    template<typename T,typename U,typename Allocator>
    bool operator!=(const RefBuffer<T,Allocator> &a,const RefBuffer<U,Allocator> &b){
        if(a == b) return false;
        return true;
    }




//end of namespace
}
}
#endif /* BUFFER_HPP_ */
