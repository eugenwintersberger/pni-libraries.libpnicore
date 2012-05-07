/*
 * Declaration of the Buffer<T> template
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
 * Created on: Apr 11, 2011
 *     Author: Eugen Wintersberger
 *
 */



#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Exceptions.hpp"
#include "Types.hpp"
#include "TypeIDMap.hpp"
#include "NewAllocator.hpp"

namespace pni{
namespace utils{

    /*! \ingroup data_classes
    \brief buffer template

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
    template<typename T,typename Allocator=NewAllocator >class Buffer{
        private:
            T *_data; //!< pointer to the data block
            size_t _size; //!< number of allocated elements

            //some private methods
            void _allocate();
        public:
            //============public types provided by the template================
            typedef std::shared_ptr<Buffer<T,Allocator> > shared_ptr; //!< smart pointer to a typed buffer
            typedef std::unique_ptr<Buffer<T,Allocator> > unique_ptr; //!< unique poitner type to a buffer
            typedef T value_type;  //!< type stored in the buffer
            typedef Allocator allocator_type; //!< allocator type

            //=============public static variables=============================
            static const size_t value_size = sizeof(T); //!< size of the element type
            static const TypeID type_id    = TypeIDMap<T>::type_id; //!< type ID of the element type
           
            //=================constructors and destructor=====================
            //! default constructor
            explicit Buffer();

            //-----------------------------------------------------------------
            /*! \brief copy constructor

            This constructor initializes the new Buffer with the content of the
            old. New memory is allocated for the newly created Buffer<T> object.
            \throws MemoryAllocationError if allocation for the new buffer fails
            */
            Buffer(const Buffer<T,Allocator> &b);

            //-----------------------------------------------------------------
            /*! \brief move constructor

            Unlike the copy constructor no new memory is allocated during the
            construction of the lhs object. However, the rhs buffer will be
            freed. 
            */
            Buffer(Buffer<T,Allocator> &&b);

            //-----------------------------------------------------------------
            /*! \brief constructor with buffer size

            Using this constructor the buffer will automatically allocate 
            memory.
            \throws MemoryAllocationError if allocation on the heap fails
            \param n number of elements of type T in the buffer
            */
            explicit Buffer(size_t n);

            //-----------------------------------------------------------------
            /*! \brief construct with initializer list

            This constructor allows the construction of Buffer<T> objects 
            using an initializer list
            \code
            Buffer<UInt32> buffer = {1,3,5,6,10};
            \endcode
            which in some cases simplifies the code sigificantly. 
            \throws MemoryAllocationError if memory allocation fails
            \param list reference to the initializer list
            */
            Buffer(const std::initializer_list<T> &list);

            //-----------------------------------------------------------------
            /*! \brief initialize object from a vector
            
            Uses a std::vector to initialize the new buffer object.
            \throws MemoryAllocationError if memory allocation fails
            \param vector instance of std::vector<T>
            */
            Buffer(const std::vector<T> &vector);

            //-----------------------------------------------------------------
            //! destructor
            ~Buffer();

            //===================assignment operators==========================
            /*! copy assignment operator

            If the buffer on the rhs of the assignment operator is not allocated
            the rhs buffer object will be freed.
            \throws MemoryAccessError if something goes wring with memory allocation
            \param b Buffer whose content will be assigned to this buffer
            \return reference to a Buffer<T> object
            */
            Buffer<T,Allocator> &operator=(const Buffer<T,Allocator> &b);
            //-----------------------------------------------------------------
            //! move assignment operator
            Buffer<T,Allocator> &operator=(Buffer<T,Allocator> &&b);

            //-----------------------------------------------------------------
            /*! single value assignment operator

            This special form of the assignment operator can be used to 
            assign a single value to all elements of the buffer. Thus, it is 
            quite useful for initializing a buffer object.
            \throws MemoryAccessError if buffer is not allocated
            \param v value which to assign to all buffer elements
            \return reference to a buffer object
            */
            Buffer<T,Allocator> &operator=(const T &v);

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
            \throws MemoryAccessError if buffer is not allocated
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
            T& operator[](size_t n) { return _data[n]; }

            //-----------------------------------------------------------------
            /*! [] operator for read only access

            This operator will be used in expressions where read only access to 
            the data values in the buffer is required. No checks are performed
            for the allocation state of the buffer or index overflows.
            \param n index of the element to fetch
            \return value of the buffer at position n
            */
            T operator[](size_t n) const { return _data[n]; }

            //-----------------------------------------------------------------
            /*! \brief allocates memory

            Method allocates memory for size elements of type T. If the buffer
            is already allocated the original memory will be freed and new
            memory requested from ths OS. 
            \throws MemoryAllocationError if things go wrong
            \param size number of elements for which to allocate memory
            */
            void allocate(size_t size);

            //-----------------------------------------------------------------
            /*! \brief check allocation status

            Returns true if the buffer is allocated and false otherwise.
            \return true if allocated
            */
            bool is_allocated() const 
            { 
                if(_data) return true;
                return false; 
            }

            //-----------------------------------------------------------------
            //! \brief free buffer memory
            void free();

            //-----------------------------------------------------------------
            /*! \brief total memory consumption

            This method returns the total size of memory in Bytes allocated for
            this buffer. 
            \return total allocate memory in bytes.
            */
            size_t mem_size() const 
            {
                return sizeof(T)*this->size();
            }

            //-----------------------------------------------------------------
            /*! \brief get number of elements

            Returns the number of elements stored in the buffer.
            \return number of elements
            */
            size_t size() const 
            {
                return _size;
            }

    };

    //=================Implementation of constructors and destructors===========
    //implementation of the default constructor
    template<typename T,typename Allocator> 
        Buffer<T,Allocator>::Buffer():
            _data(nullptr),
            _size(0)
    { }

    //--------------------------------------------------------------------------
    //implementation of the standard constructor
    template<typename T,typename Allocator> 
        Buffer<T,Allocator>::Buffer(size_t n):
            _data(Allocator::template allocate<T>(n)),
            _size(n)
    {}

    //--------------------------------------------------------------------------
    //implementation using an initializer list
    template<typename T,typename Allocator> 
        Buffer<T,Allocator>::Buffer(const std::initializer_list<T> &list):
            _data(Allocator::template allocate<T>(list.size())),
            _size(list.size())
        
    {
        size_t index = 0;
#ifdef NOFOREACH
        for(auto iter = list.begin();iter!=list.end();iter++){
            const T &value = *iter;
#else        
        for(const T &value: list){
#endif
            _data[index] = value;
            index++;
        }
    }

    //--------------------------------------------------------------------------
    //implementation using an initializer list
    template<typename T,typename Allocator> 
        Buffer<T,Allocator>::Buffer(const std::vector<T> &vector):
            _data(Allocator::template allocate<T>(vector.size())),
            _size(vector.size())
         
    {
        //once memory allocation was successfull we can use the values 
        //from the initializer list to fill the buffer
        size_t index = 0;
#ifdef NOFOREACH
        for(auto iter = vector.begin();iter!=vector.end();iter++){
            const T &value = *iter;
#else        
        for(const T &value: vector){
#endif
            _data[index] = value;
            index++;
        }
    }

    //--------------------------------------------------------------------------
    //implementation of the copy constructor
    template<typename T,typename Allocator> 
        Buffer<T,Allocator>::Buffer(const Buffer<T,Allocator> &b):
            _data(Allocator::template allocate<T>(b.size())),
            _size(b.size())
    
    {
        //copy data
        if(this->size())
            for(size_t i=0;i<this->size();i++) (*this)[i] = b[i];
    }

    //--------------------------------------------------------------------------
    //implementation of the move constructor
    template<typename T,typename Allocator> 
        Buffer<T,Allocator>::Buffer(Buffer<T,Allocator> &&b):
            _data(b._data),
            _size(b._size)
    {
        b._data = nullptr;
        b._size = 0;
    }

    //--------------------------------------------------------------------------
    //implementation of the destructor
    template<typename T,typename Allocator> Buffer<T,Allocator>::~Buffer(){
        this->free(); 
    }

    //==============methods for data allocation ================================

    //--------------------------------------------------------------------------
    //implementation of free
    template<typename T,typename Allocator> void Buffer<T,Allocator>::free()
    {
        Allocator::template free(_data);
        this->_data = nullptr;
        _size = 0;
    }

    //--------------------------------------------------------------------------
    //implementation of allocate
    template<typename T,typename Allocator> 
        void Buffer<T,Allocator>::allocate(size_t s)
    {
        //free memory if necessary
        if(this->is_allocated()) this->free();
       
        //allocate new memory
        _data = Allocator::template allocate<T>(s);

        //set the size member variable
        _size = s;
    }



    //===================assignment operators===================================
    //implementation of copy assignment
    template<typename T,typename Allocator> 
        Buffer<T,Allocator> &Buffer<T,Allocator>::
        operator=(const Buffer<T,Allocator> &b)
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

    //--------------------------------------------------------------------------
    //implementation of the move assignment
    template<typename T,typename Allocator> 
        Buffer<T,Allocator> &Buffer<T,Allocator>::
        operator=(Buffer<T,Allocator> &&b)
    {
        if(this == &b) return *this;

        this->free();
        this->_data = b._data;
        b._data = nullptr;
        this->_size = b._size;
        b._size = 0;

        return *this;
    }

    //--------------------------------------------------------------------------
    //implementation of single value assignment
    template<typename T,typename Allocator> 
        Buffer<T,Allocator> &Buffer<T,Allocator>::operator=(const T &d)
    {
        EXCEPTION_SETUP("template<typename T,typename Allocator>"
                        "Buffer<T,Allocator> &Buffer<T,Allocator>::"
                        "operator=(const T &d)");

        if(!this->is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,
                    "Cannot assign data to an unallocated buffer!");
            EXCEPTION_THROW();
        }

        //we do not need to check the size here because if the buffer is 
        //allocated the size is necessarily not zero
        for(size_t i=0;i<this->size();i++) (*this)[i] = d;

        return *this;
    }

    //===============Methods for data access====================================
    template<typename T,typename Allocator> 
        T Buffer<T,Allocator>::at(size_t i) const {
        EXCEPTION_SETUP("template<typename T,typename Allocator> "
                        "T Buffer<T,Allocator>::at(size_t i) const");

        if(!this->is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated");
            EXCEPTION_THROW();
        }

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

        if(!this->is_allocated()){
            EXCEPTION_INIT(MemoryAccessError,"Buffer not allocated");
            EXCEPTION_THROW();
        }

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
    template<typename T,typename TAlloc,typename U,typename UAlloc>
    bool operator==(const Buffer<T,TAlloc> &a,const Buffer<U,UAlloc> &b){
        if(a.size() != b.size()) return false;

        if(a.is_allocated()!=b.is_allocated()) return false;

        if(a.is_allocated() && b.is_allocated()){
            for(size_t i=0;i<a.size();i++){
                if(a[i] != b[i]) return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename Allocator> 
        bool operator==(const Buffer<T,Allocator> &a,const Buffer<T,Allocator> &b)
    {
        if(a.size() != b.size()) return false;

        if(a.is_allocated()!=b.is_allocated()) return false;

        if(a.is_allocated() && b.is_allocated()){
            for(size_t i=0;i<a.size();i++){
                if(a[i] != b[i]) return false;
            }
        }

        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename TAlloc,typename U,typename UAlloc>
    bool operator!=(const Buffer<T,TAlloc> &a,const Buffer<U,UAlloc> &b)
    {
        if(a == b) return false;
        return true;
    }

    //--------------------------------------------------------------------------
    template<typename T,typename Alloc> 
        bool operator!=(const Buffer<T,Alloc> &a,const Buffer<T,Alloc> &b)
    {
        if(a == b) return false;
        return true;
    }


//end of namespace
}
}
#endif /* BUFFER_HPP_ */
