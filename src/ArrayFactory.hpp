#ifndef __ARRAYFACTORY_HPP__
#define __ARRAYFACTORY_HPP__

#include "Shape.hpp"
#include "Buffer.hpp"
#include "RefBuffer.hpp"
#include "Array.hpp"

namespace pni{
namespace utils{

    template<typename T,
             template<typename,typename> class BTYPE=Buffer,
             typename ALLOCATOR=NewAllocator
            >
    class ArrayFactory
    {
        public:
            //=============public types========================================
            typedef Array<T,BTYPE,ALLOCATOR> array_type;

            //================static member functions==========================
            /*! \brief create a simple array

            Create a simple array from a singe shape object. The function
            allocates memory and passes it to the array constructor using move
            semantics. 
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
            */
            static Array<T,BTYPE,ALLOCATOR> create(const Shape &s,const BTYPE<T,ALLOCATOR> &b)
            {
                return Array<T,BTYPE,ALLOCATOR>(s,b);
            }

            //-----------------------------------------------------------------
            /*! \brief create array with initial data

            Create a new array by allocating memory and initialize the array
            with a particular value. After creation all values of the array have
            the same initial value passed by the user
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

    };

    template<typename T,typename ALLOCATOR> 
        class ArrayFactory<T,RefBuffer,ALLOCATOR>
    {
        public:
            //===================public types==================================
            typedef Array<T,RefBuffer,ALLOCATOR> array_type;

            //================public static member methods=====================
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
