#ifndef __ARRAYREP_HPP__
#define __ARRAYREP_HPP__

#include "Array.hpp"
#include "ArrayView.hpp"

namespace pni{
namespace utils{
    
    template<typename ATYPE> ArrayRep
    {
        private:
            ATYPE &_object;
        public:
            ArrayRep() = delete;

            template<template<typename,typename> class BTYPE,
                     typename ALLOCATOR>
            ArrayRep(Array<T,BTYPE,ALLOCATOR> &a):_object(a) {}

    
    };


//end of namespace
}
}
#endif
