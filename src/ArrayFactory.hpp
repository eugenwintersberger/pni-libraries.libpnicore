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
    template< template<typename,typename ...> class REPTEMP >
    class ArrayFactory
    {
        public:
            //================static member functions==========================
            /*! \brief create a simple array

            Create a simple array from a singe shape object. The function 
            allocates memory and passes it to the array constructor using move
            semantics. 
            \throws MemoryAllocationError if buffer allocation fails
            \param s Shape object
            \return instance of Array<T,BTYPE,ALLOCATOR>
            */
            template<typename T,typename ...OTYPES>
            static Array<T,REPTEMP<T,OTYPES...> > create(const Shape &s)
            {
                typedef typename REPTEMP<T,OTYPES...>::storage_type storage;
                
                //create the storage buffer
                storage buffer(s.size());

                //create the rep type of the array
                REPTEMP<T,OTYPES...> array(s,buffer);

                //return the Array instance
                return Array<T,REPTEMP<T,OTYPES...> >(array);
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
            template<typename T,typename ...OTYPES>
            static Array<T,REPTEMP<T,OTYPES...> > create(const Shape &s,const T &i)
            {
                typedef typename REPTYPE<T,OTYPES...>::storage_type storage;
                storage buffer(s.size());
                buffer = i;
                
                REPTEMP<T,OTYPES...> array(s,buffer);

                return Array<T,REPTEMP<T,OTYPES...> >(array);
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
            template<typename T,typename ...OTYPES>
            template<typename CONT = std::vector<T> > static 
            Array<T,REPTEMP<T,OTYPES...> > create(const Shape &s,const CONT &i)
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

                //create storage for the new array
                typedef typename REPTYPE<T,OTYPES...>::storage_type storage;
                storage buffer(shape.size());

                //copy data from the container to the storage
                size_t index = 0;
                for(storage::value_type &v: buffer)
                {
                    v = i[index];
                    index++;
                }

                //create array implementation
                REPTYPE<T,OTYPES...> array(s,buffer);
                return Array<T,REPTYPE<T,OTYPES...>(array);
            }


    };

    


//end of namespace
}
}

#endif
