/*! \example example_array4.cpp

Using selections and numerics
*/

#include <iostream>
#include <vector>
#include <pni/utils/Types.hpp>
#include <pni/utils/DArray.hpp>
#include <pni/utils/SArray.hpp>
#include <pni/utils/NumArray.hpp>
#include <pni/utils/Slice.hpp>

using namespace pni::utils;

//some usefull type definitions
typedef std::vector<size_t> shape_t; //container to describe array shapes
typedef std::vector<size_t> index_t; //index type
typedef DArray<Float32> F32Array;    //an array type for Float32 values
typedef NumArray<F32Array> Frame;    //a numeric frame
typedef SArray<Float32,3> F32Vector; //a static 3-vector type
typedef NumArray<F32Vector> Vector;  //a numeric 3-vector



std::ostream &operator<<(std::ostream &o,const Frame &a)
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

std::ostream &operator<<(std::ostream &o,const Vector &v)
{
    o<<"( ";
    for(auto c: v) o<<c<<" ";
    o<<")";
    return o;
}



int main(int argc,char **argv)
{
    shape_t shape{10,3};
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    Frame a(shape); 

    //initialize the array with 0
    std::fill(a.begin(),a.end(),0);

    //using a selection to set the values of each vector
    for(size_t i=0;i<shape[0];i++)
    {
        Vector v(a(Slice(i),Slice(0,3)));
        v +=
            Vector(Vector::storage_type{Float32(i+0.1),Float32(i+0.2),Float32(i+0.3)});
    }

    //plotting some output
    std::cout<<a<<std::endl;

    //do some conversion
    for(size_t i=0;i<shape[0];i++)
    {
        Vector v(Vector::storage_type(a(Slice(i),Slice(0,3))));
        std::cout<<"vector = "<<v<<std::endl;
    }        


    return 0;
}

