/*! \example example_buffer1.cpp

This example shows the basic of the DBuffer template
*/
#include <iostream>
#include <pni/core/dbuffer.hpp>
#include <pni/core/types.hpp>

using namespace pni::core;

int main(int argc,char **argv)
{
    //-----------------buffer creation an allocation---------------------------
    //allocation at creation
    dbuffer<uint8> buffer(100); 

    //defer memory allocation
    dbuffer<int32> bint32;  //create buffer
    bint32.allocate(1014);   //allocate memory

    //---------------------initializing buffers--------------------------------
    //using the std::fill function
    std::fill(bint32.begin(),bint32.end(),10);

    //at creation using an initializer list
    dbuffer<float32> bfloat32({1.2,-23.123,90934.123}); 

    //-----------------------checking the state of a buffer--------------------
    //check if allocated
    if(bfloat32.size()) std::cout<<"buffer is allocated!"<<std::endl;

    //check size
    std::cout<<bfloat32.size()<<std::endl;

    //---------STL compatability and iterators----------------------------------
    //read access
#ifdef NOFOREACH
    for(auto iter = bint32.begin();iter!=bint32.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: bint32) 
    {
#endif
        std::cout<<v<<std::endl;
    }

    //write access
#ifdef NOFOREACH
    for(auto iter = bint32.begin();iter!=bint32.end();++iter)
    {
        dbuffer<int32>::value_type &v = *iter;
#else
    for(dbuffer<int32>::value_type &v: bint32)
    {
#endif
        v = 1;
    }
    
    return 0;
}
