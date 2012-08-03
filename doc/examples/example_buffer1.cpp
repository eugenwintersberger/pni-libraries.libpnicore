/*! \example example_buffer1.cpp

This example shows the basic of the DBuffer template
*/
#include <iostream>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::utils;

int main(int argc,char **argv)
{
    //-----------------buffer creation an allocation---------------------------
    //allocation at creation
    DBuffer<UInt8> buffer(100); 

    //defer memory allocation
    DBuffer<Int32> bint32;  //create buffer
    bint32.allocate(1014);   //allocate memory

    //---------------------initializing buffers--------------------------------
    //using the std::fill function
    std::fill(bint32.begin(),bint32.end(),10);

    //at creation using an initializer list
    DBuffer<Float32> bfloat32{1.2,-23.123,90934.123}; 

    //-----------------------checking the state of a buffer--------------------
    //check if allocated
    if(bfloat32.size()) std::cout<<"buffer is allocated!"<<std::endl;

    //check size
    std::cout<<bfloat32.size()<<std::endl;

    //---------STL compatability and iterators----------------------------------
    //read access
    for(auto v: bint32) std::cout<<v<<std::endl;

    //write access
    for(DBuffer<Int32>::value_type &v: bint32)
        v = 1;
    
    return 0;
}
