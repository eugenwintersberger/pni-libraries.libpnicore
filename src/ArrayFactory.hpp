#ifndef __ARRAYFACTORY_HPP__
#define __ARRAYFACTORY_HPP__

#include "Shape.hpp"
#include "Buffer.hpp"
#include "RefBuffer.hpp"
#include "Array.hpp"

namespace pni{
namespace utils{

    /*!
    \ingroup data_classes
    \brief array factory template

    This is the most general template for an array factory. It provides static
    methods for array creation. The factory assumes that the buffer template is
    capable of allocating memory by itself. If this is not the case a
    specialization of this factory must be provided.

    Factories are necessary for two reasons:

    \li to keep the constructor interface of the Array template simple
    \li to take into account the fact that the constructor interface might
    depend on the Buffer template used  for a particular Array type.

    Using specialization the interface for this factory can be customized for
    each different Buffer and Allocator type. All methods return the instance of
    Array<T,BTYPE,ALLOCATOR> by value. This is perfectly ok as the Array
    template supports moving.
    */
    template<typename T,
             template<typename,typename> class BTYPE=Buffer,
             typename ALLOCATOR=NewAllocator
            >
    class ArrayFactory
    {
        public:
            //=============public types========================================
            typedef Array<T,BTYPE,ALLOCATOR> array_type; //!< array type created by this factory

            //================static member functions==========================
            /*! \brief create a simple array

            Create a simple array from a singe shape object. The function 
            allocates memory and passes it to the array constructor using move
            semantics. 
            \throws MemoryAllocationError if buffer allocation fails
            \param s Shape object
            \return instance of Array<T,BTYPE,ALLOCATOR>
            */
            static Array<T,BTYPE,ALLOCATOR> create(const Shape &s)
            {
                BTYPE<T,ALLOCATOR> buffer(s.size());
                Array<T,BTYPE,ALLOCATOR> a(s,std::move(buffer));
                return a;
            }

            //-----------------------------------------------------------------
            /*! \brief create array from existing buffer

            Create an array using a shape object and an existing buffer. In this
            case the buffer object is copied by the constructor. The original
            buffer remains untouched.
            \throws ShapeMissmatchError if buffer and shape size do not match
            \param s array shape
            \param b buffer object
            \return instance of Array<T,BTYPE,ALLOCATOR>
            */
            static Array<T,BTYPE,ALLOCATOR> create(const Shape &s,const BTYPE<T,ALLOCATOR> &b)
            {
                //throw exception if sizes do not match
                if(s.size() != b.size())
                {
                    std::stringstream ss;
                    ss<<"Buffer size ("<<b.size()<<") and shape size (";
                    ss<<s.size()<<") do not match!";
                    SizeMissmatchError error;
                    error.issuer("Array<T,BTYPE,ALLOCATOR> "
                                 "ArrayFactory<T,BTYPE,ALLOCATOR>::"
                                 "create(const Shape &s,"
                                 "const BTYPE<T,ALLOCATOR> &b)");
                    error.description(ss.str());
                    throw error;
                }

                return Array<T,BTYPE,ALLOCATOR>(s,b);
            }

            //-----------------------------------------------------------------
            /*! \brief create array with initial data

            Create a new array by allocating memory and initialize the array
            with a particular value. After creation all values of the array have
            the same initial value passed by the user
            \throws MemoryAllocationError if Buffer allocation fails
            \param s Shape object
            \param i initial value
            \return instance of Array<T,BTYPE,ALLOCATOR>
            */
            static Array<T,BTYPE,ALLOCATOR> create(const Shape &s,const T &i)
            {
                BTYPE<T,ALLOCATOR> buffer(s.size());
                buffer = i;
                Array<T,BTYPE,ALLOCATOR> a(s,std::move(buffer));

                return a;
            }

            //-----------------------------------------------------------------
            /*! \brief create new array with initial data from container

            Create a new array and initialize it with data from a container. The
            container must be as large as the size of the array otherwise an
            exception will be thrown. 
            \throws SizeMissmatchError if container and array size do not match
            \param s Shape object
            \param i container with initial values
            \return instance of Array<T,BTYPE,ALLOCATOR>
            */
            template<typename CONT = std::vector<T> > static 
            Array<T,BTYPE,ALLOCATOR> create(const Shape &s,const CONT &i)
            {
                if(s.size() != i.size())
                {
                    std::stringstream ss;
                    ss<<"Container size ("<<i.size()<<") does not match Shape ";
                    ss<<" size ("<<s.size()<<")!";
                    SizeMissmatchError error;
                    error.description(ss.str());
                    error.issuer("template<typename T,typename CONT = "
                                 "std::vector<T> > static Array<T,BTYPE, "
                                 "ALLOCATOR> create(const Shape &s,const "
                                 "CONT &i)");
                    throw error;
                }

                BTYPE<T,ALLOCATOR> buffer(i);
                Array<T,BTYPE,ALLOCATOR> a(s,std::move(buffer));
                return a;
            }

            //-----------------------------------------------------------------
            /*! \brief create a new array from a view 

            Use this method to create a new array from an array view object.
            ArrayViews do not provide contiguous memory. It is thus sometimes
            convenient to copy the content of a view to a new memory region. 
            \throws MemoryAllocationError if buffer allocation fails
            \param view array view instance
            \return new instance of Array<T,BTYPE,ALLOCATOR>
            */
            template<template<typename,typename> 
                     class UBUFFER, 
                     typename UALLOCATOR>
            static Array<T,BTYPE,ALLOCATOR> 
            create(const ArrayView<T,Array<T,UBUFFER,UALLOCATOR> > &view)
            {
                BTYPE<T,ALLOCATOR> buffer(view.size());
                Array<T,BTYPE,ALLOCATOR> array(view.shape(),buffer);

                //copy data
                for(size_t i=0;i<array.size();i++) array[i] = view[i];

                return array;
            }
                      

    };

    
    /*! 
    \ingroup data_classes
    \brief special array factory for RefBuffer arrays

    This is a specialization of the ArrayFactory template for the RefBuffer
    buffer template. This is required as RefBuffer has no possibility to
    allocate memory by itself. This most of the static methods present in the
    standard ArrayFactory template cannot be used.
    */
    template<typename T,typename ALLOCATOR> 
        class ArrayFactory<T,RefBuffer,ALLOCATOR>
    {
        public:
            //===================public types==================================
            typedef Array<T,RefBuffer,ALLOCATOR> array_type; //!< array type constructed by this factory

            //================public static member methods=====================
            /*! \brief create RefBuffer array

            Create an array using a raw pointer to data provided by the used. 
            The size of the memory pointed to by ptr must be equals to the size
            of the shape object. The method has no possibility to check this.
            Thus it is entirely in the responsibility of the user to ensure that
            memory allocation is ok.
            \param s shape of the new array
            \param ptr pointer to memory.
            \return new instance of Array<T,RefBuffer,ALLOCATOR>
            */
            static Array<T,RefBuffer,ALLOCATOR> create(const Shape &s,T *ptr)
            {
                RefBuffer<T,ALLOCATOR> buffer(s.size(),ptr);
                Array<T,RefBuffer,ALLOCATOR> a(s,buffer);
                return a;
            }

    };


//end of namespace
}
}

#endif
