/*! \example example_buffer1.cpp

This example shows the basic useage of the Buffer<T> template.
*/

#include <iostream>
#include <pni/utils/Buffer.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

int main(int argc,char **argv)
{
    //---------different was of how to create a buffer------
    Buffer<UInt8> buffer(100); //allocation at creation

    Buffer<Float32> bfloat32{1.2,-23.123,90934.123}; //using initializer lists



}
