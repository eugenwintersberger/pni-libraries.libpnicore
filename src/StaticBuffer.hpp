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



#ifndef __STATICBUFFER_HPP__
#define __STATICBUFFER_HPP__

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Exceptions.hpp"
#include "Types.hpp"
#include "TypeIDMap.hpp"
#include "NewAllocator.hpp"
#include "Iterator.hpp"

namespace pni{
namespace utils{

    /*! \ingroup data_classes
    \brief static buffer template
    
    This template implements a static buffer. Such objects occupy a fixed size
    in memory which cannot be altered. 
    */
    template<typename T,size_t N >class StaticBuffer
    {
        private:
            T _data[N]; //!< pointer to the data block
        public:
            //============public types provided by the template================
            typedef std::shared_ptr<StaticBuffer<T,N> > shared_ptr; //!< smart pointer to a typed buffer
            typedef std::unique_ptr<StaticBuffer<T,N> > unique_ptr; //!< unique poitner type to a buffer
            typedef T value_type;  //!< type stored in the buffer
            typedef Iterator<StaticBuffer<T,N>,0 > iterator;        //!< iterator type
            typedef Iterator<StaticBuffer<T,N>,1 > const_iterator; //!< const iterator type

            //=============public static variables=============================
            static const size_t value_size = sizeof(T); //!< size of the element type
            static const TypeID type_id    = TypeIDMap<T>::type_id; //!< type ID of the element type
           
            //=================constructors and destructor=====================
            //! default constructor
            explicit StaticBuffer(){}

            //-----------------------------------------------------------------
            //! \brief copy constructor
            StaticBuffer(const StaticBuffer<T,N> &b)
            {
                //copy data
                for(size_t i=0;i<this->size();i++) (*this)[i] = b[i];
            }

            //-----------------------------------------------------------------
            /*! \brief constructor from raw pointer
          
            Fill the content of a fixed size buffer from a raw pointer. The user
            is responsible that the pointer points to a sufficiently large
            memory region. The data is copied to the buffer so the original
            pointer can be deleted safely afterwards.
            The constructor throws an exception if the pointer is a NULL
            pointer.
            \code 
            double *data = new double[1024];
            ....
            //data is copied to a buffer
            StaticBuffer<double,1024> buffer(data);

            //you can savely free the original pointer
            delte [] data;
            \endcode
            \param ptr pointer to raw data
            */
            explicit StaticBuffer(const T *ptr)
            {
                if(ptr)
                {
                    //copy data
                    for(size_t i=0;i<this->size();i++) (*this)[i] = ptr[i];
                }
                else
                {
                    MemoryAccessError error;
                    error.issuer("explicit StaticBuffer(const T *ptr)");
                    error.description("Pointer is a nullptr!");
                    throw error;
                }
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
            StaticBuffer(const std::initializer_list<T> &list)
            {
                if(list.size()!=N)
                {
                    SizeMissmatchError error;
                    error.issuer("StaticBuffer(const std::initializer_list"
                                 "<T> &list)");
                    std::stringstream ss;
                    ss<<"List size ("<<list.size()<<") does not match ";
                    ss<<" buffer size ("<<N<<")!";
                    error.description(ss.str());
                    throw error;
                }

                for(size_t i=0;i<N;i++) (*this)[i] = list[i];
            }

            //-----------------------------------------------------------------
            /*! \brief construct buffer from an iterable container
           
            Any iterable container can be used to fill the a buffer. The data
            will be copied from the container to the newly allocated buffer
            object. An exception is thrown if the size of the container does not
            match the size of the buffer.
            \throws SizeMissmatchError if memory allocation fails
            \param container instance of a container type
            */
            template<typename T,template<typename,typename ...> class CONT,
                     typename ...OPTS>
            explicit StaticBuffer(const CONT<T,OPTS...> &container)
            {
                if(list.size()!=N)
                {
                    SizeMissmatchError error;
                    error.issuer("template<typename T,template<typename,"
                                 "typename ...> class CONT,typename ...OPTS>"
                                 "explicit StaticBuffer(const CONT<T,OPTS...> "
                                 "&container)");
                    std::stringstream ss;
                    ss<<"Container size ("<<container.size()<<") does not match ";
                    ss<<" buffer size ("<<N<<")!";
                    error.description(ss.str());
                    throw error;
                }

                size_t index = 0;
                for(auto v: container) (*this)[index++] = v;
            }

            //-----------------------------------------------------------------
            //! destructor
            ~StaticBuffer() {} 

            //===================assignment operators==========================
            //! copy assignment operator
            StaticBuffer<T,N> &operator=(const StaticBuffer<T,N> &b)
            {
                if(this == &b) return *this;
                for(size_t i=0;i<N;i++) (*this)[i] = b[i];
                return *this;
            }

            //-----------------------------------------------------------------
            /*! single value assignment operator

            All values in the buffer will be set to v. 
            \param v value to set the buffer to
            */
            StaticBuffer<T,N> &operator=(const T &v)
            {
                for(T &b: *this) b = v;
                return *this;
            }

            //==============public methods for data access=====================
            /*! \brief return data pointer

            Returns a typed const pointer to the allocated memory. The pointer 
            must not be used to modify data values.
            \return pointer to allocated memory
            */
            const T* ptr() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! return data pointer

            Returns a typed pointer to the allocated memory. The pointer can be
            used for altering the buffer content.
            \return pointer to allocated memory
            */
            T *ptr() { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief return a non-const pointer to the allocate memory

            Returns a non-const pointer to the memory region belonging to a
            Buffer<T> object.
            \return return read/write pointer to data
            */
            void *void_ptr() { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief get const void pointer

            Return a const void pointer to the first element of the buffers
            data.
            \return const void pointer
            */
            const void *void_ptr() const { return this->_data; }

            //-----------------------------------------------------------------
            /*! \brief get value at index i

            Returns the data value at index i of the buffer. 
            \throws IndexError if i exceeds the size of the buffer
            \param i buffer index
            \return value at index i
            */
            T at(size_t i) const;

            //-----------------------------------------------------------------
            /*! \brief get value at index i

            Returns a reference to the element in the buffer at index i.
            \throws MemoryAccessError if buffer is not allocated
            \throws IndexError if i exceeds the size of the buffer
            \param i buffer index
            \return reference to the element at index i
            */
            T &at(size_t i);

            //-----------------------------------------------------------------
            /*! [] operator for read and write access

            Returns a reference to the element at index i of the buffer. Unlike
            at() this operator performs no checks for index overflows or on the
            allocation state of the buffer. Thus, use it with care. 
            \param n index of element to fetch
            \return reference to the n-th element in the buffer
            */
            T& operator[](size_t n) { return this->_data[n]; }

            //-----------------------------------------------------------------
            /*! [] operator for read only access

            This operator will be used in expressions where read only access to 
            the data values in the buffer is required. No checks are performed
            for the allocation state of the buffer or index overflows.
            \param n index of the element to fetch
            \return value of the buffer at position n
            */
            T operator[](size_t n) const { return this->_data[n]; }

            //-----------------------------------------------------------------
            /*! \brief total memory consumption

            This method returns the total size of memory in Bytes allocated for
            this buffer. 
            \return total allocate memory in bytes.
            */
            size_t mem_size() const { return sizeof(T)*this->size(); }

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
            StaticBuffer<T,N>::iterator begin()
            {
                return StaticBuffer<T,N>::iterator(this,0);
            }

            //------------------------------------------------------------------
            /*! \brief get iterator to last element

            Returns an iterator pointing to the last element of the buffer.
            \return iterator to last element
            */
            StaticBuffer<T,N>::iterator end()
            {
                return StaticBuffer<T,N>::iterator(this,this->size());
            }

            //------------------------------------------------------------------
            /*! \brief get const iterator to first element

            Returns an const iterator pointing on the first element of the buffer.
            \return const iterator to first element
            */
            StaticBuffer<T,N>::const_iterator begin() const
            {
                return StaticBuffer<T,N>::const_iterator(this,0);
            }

            //------------------------------------------------------------------
            /*! \brief get const iterator to last element

            Returns an const iterator pointing to the last element of the buffer.
            \return const iterator to last element
            */
            StaticBuffer<T,N>::const_iterator end() const
            {
                return StaticBuffer<T,N>::const_iterator(this,this->size());
            }


    };

    //===============Methods for data access====================================
    template<typename T,typename Allocator> 
        T Buffer<T,Allocator>::at(size_t i) const 
    {
        EXCEPTION_SETUP("template<typename T,typename Allocator> "
                        "T Buffer<T,Allocator>::at(size_t i) const");

        if(i>=this->size()){
            std::ostringstream sstr;
            sstr<<"Index ("<<i<<") must not be larger or equal the size ";
            sstr<<"("<<this->size()<<")of the buffer!";
            EXCEPTION_INIT(IndexError,sstr.str());
            EXCEPTION_THROW();
        }

        return _data[i];
    }

    //===============Methods for data access====================================
    template<typename T,typename Allocator> T &Buffer<T,Allocator>::at(size_t i)
    {
        EXCEPTION_SETUP("template<typename T,typename Allocator> "
                        "T Buffer<T,Allocator>::at(size_t i) const");


        if(i>=this->size()){
            std::ostringstream sstr;
            sstr<<"Index ("<<i<<") must not be larger or equal the size ";
            sstr<<"("<<this->size()<<")of the buffer!";
            EXCEPTION_INIT(IndexError,sstr.str());
            EXCEPTION_THROW();
        }

        return _data[i];
    }


    //==============comparison operators========================================
    template<typename T,typename U,size_t N>
    bool operator==(const StaticBuffer<T,N> &a,const StaticBuffer<U,N> &b){

        for(size_t i=0;i<a.size();i++)
            if(a[i] != b[i]) return false;

        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename U,size_t N>
    bool operator!=(const StaticBuffer<T,N> &a,const StaticBuffer<U,N> &b)
    {
        if(a == b) return false;
        return true;
    }



//end of namespace
}
}
#endif 
