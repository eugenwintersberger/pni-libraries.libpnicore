/*! \example example_buffer2.cpp

Accessing data from a Buffer<T> template
*/

#include <iostream>
#include <pni/core/DBuffer.hpp>
#include <pni/core/Types.hpp>

using namespace pni::core;

int main(int argc,char **argv)
{
    DBuffer<Float32> buffer(1234);

    //access data without index check
    std::cout<<buffer[10]<<std::endl;
    buffer[100] = 45.23;

    //access data with index check
    std::cout<<buffer.at(10)<<std::endl;
    buffer.at(100) = 567.2334;

    //access to raw pointers
    Float32 *ptr = const_cast<Float32*>(buffer.ptr());

    return 0;
}
