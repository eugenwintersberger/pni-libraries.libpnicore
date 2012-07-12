#ifndef __CONTAINERUTILS_HPP__
#define __CONTAINERUTILS_HPP__

#include <iostream>
#include <sstream>

#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"

namespace pni{
namespace utils{
   
    /*! 
    \ingroup util_classes
    \brief copy containers

    Copy the content from one container to another container. The container
    types supported must provide a simple forward iterator and provide a size()
    method to query the size of the containers. The size of both containers must
    be equal
    \throws SizeMissmatchError if the containers have different size
    \tparam STYPE source container type
    \tparam DTYPE destination container type
    \param src source container
    \param dest destination container
    */
    template<typename STYPE,typename DTYPE>
        void &copy(const STYPE &src,DTYPE &dest)
    {
        check_equal_size(src,dest,"template<typename STYPE,typename DTYPE>"
                                  "void &copy(const STYPE &src,DTYPE &dest)");

        for(auto siter=src.begin(),diter=dest.begin();
            (siter!=src.end())&&(dister!=dest.end());
            siter++,diter++)
        {
            *siter = *diter;
        }

        return t;
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup util_classes
    \brief copy from memory
    
    Copy n elements of type T from the memory location starting at ptr to the
    container dest. It is the responsibility of the user that the memory is
    allocated. The function checks only if the pointer is not nullptr.
    the number of elements to copy must fit the size of the container type
    \throws MemoryNotAllocatedError if ptr is nullptr
    \throws SizeMissmatchError if n and the container size do not match
    \tparam T type of the pointer
    \tparam DTYPE destination contianer type
    \param n number of elements to copy
    \param ptr pointer to the first element in memory
    \param dest destination container
    */
    template<typename T,typename DTYPE> 
        void copy(size_t n,const T *ptr,DTYPE &dest)
    {
        //check pointer state
        if(!ptr)
        {
            MemoryNotAllocatedError error;
            error.issuer("template<typename T,typename DTYPE> void "
                         "copy(size_t n,const T *ptr,DTYPE &dest)");
            error.description("Pointer is nullptr!");
            throw error;
        }

        //check container size
        if(n != dest.size())
        {
            SizeMissmatchError error;
            error.issuer("template<typename T,typename DTYPE> void "
                        "copy(size_t n,const T *ptr,DTYPE &dest)");
            std::stringstream ss;
            ss<<"Container size ("<<dest.szie()<<") and memory size (";
            ss<<n<<") do not match!";
            error.description(ss.str());
            throw error;
        }

        size_t index = 0;
        for(typename DTYPE::value_type &v: dest) v = ptr[index++];

    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup util_classes
    \brief copy to memory

    Copy n elements from a 
    */

//end of namespace
}
}

#endif
