/*! \example example_array3.cpp

Using selections
*/

#include <iostream>
#include <vector>
#include <pni/core/Types.hpp>
#include <pni/core/DArray.hpp>
#include <pni/core/SArray.hpp>
#include <pni/core/Slice.hpp>

using namespace pni::core;

//some usefull type definitions
typedef std::vector<size_t> shape_t; //container to describe array shapes
typedef std::vector<size_t> index_t; //index type
typedef DArray<Float32> F32Array;    //an array type for Float32 values
typedef SArray<Float32,3> F32Vector; //a static 3-vector type



std::ostream &operator<<(std::ostream &o,const F32Array &a)
{
    auto shape = a.shape<shape_t>();
    for(size_t i=0;i<shape[0];i++)
    {
        o<<"| ";
        for(size_t j=0;j<shape[1];j++) o<<a(i,j)<<" ";

        std::cout<<"|"<<std::endl;
    }
    return o;
}

std::ostream &operator<<(std::ostream &o,const F32Vector &v)
{
    o<<"( ";
#ifdef NOFOREACH
    for(auto iter = v.begin();iter!=v.end();++iter)
    {
        auto c = *iter;
#else
    for(auto c: v) 
    {
#endif
        o<<c<<" ";
    }
    o<<")";
    return o;
}



int main(int argc,char **argv)
{
    shape_t shape({10,3});
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    F32Array a(shape); 

    //initialize the array with 0
    std::fill(a.begin(),a.end(),0);

    //using a selection to set the values of each vector
    for(size_t i=0;i<shape[0];i++)
    {
        auto view = a(Slice(i),Slice(0,3));
        view(0) = Float32(i)+0.1;
        view(1) = Float32(i)+0.2;
        view(2) = Float32(i)+0.3;
    }

    //plotting some output
    std::cout<<a<<std::endl;

    //do some conversion
    for(size_t i=0;i<shape[0];i++)
    {
        F32Vector v(a(Slice(i),Slice(0,3)));
        std::cout<<"vector = "<<v<<std::endl;
    }        


    return 0;
}

