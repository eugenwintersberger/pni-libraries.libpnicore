#ifndef __BUFFERHELPER_HPP__
#define __BUFFERHELPER_HPP__

#include "Buffer.hpp"
#include "RefBuffer.hpp"
#include "NewAllocator.hpp"

using namespace pni::utils;

template<typename T,typename Allocator>
    void allocate_buffer(Buffer<T,Allocator> &b,size_t n)
{
    b =  Buffer<T,Allocator>(n);
}


//-------------------------------------------------------------------------
template<typename T,typename Allocator>
    void allocate_buffer(RefBuffer<T,Allocator> &b,size_t n)
{
    b = RefBuffer<T,Allocator>(n,new T[n]);
}
#endif
