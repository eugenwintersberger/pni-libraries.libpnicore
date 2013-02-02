/*! \example example_buffer2.cpp

Accessing data from a Buffer<T> template
*/

#include <iostream>
#include <pni/core/dbuffer.hpp>
#include <pni/core/types.hpp>

using namespace pni::core;

int main(int argc,char **argv)
{
    dbuffer<float32> buffer(1234);

    //access data without index check
    std::cout<<buffer[10]<<std::endl;
    buffer[100] = 45.23;

    //access data with index check
    std::cout<<buffer.at(10)<<std::endl;
    buffer.at(100) = 567.2334;

    //access to raw pointers
    float32 *ptr = const_cast<float32*>(buffer.ptr());

    return 0;
}
