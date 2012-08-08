/*! \example example_array4.cpp

Using selections and numerics
*/

#include <iostream>
#include <vector>
#include <pni/utils/Array.hpp>

using namespace pni::utils;

typedef NF32DArray Frame;

#ifdef NOTMPALIAS
typedef NumArray<SArray<Float32,3> > Vector;
#else
typedef NF32SArray<3> Vector;
#endif


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
#ifdef NOFOREACH
    for(auto iter=v.begin();iter!=v.end();++iter)
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
    Frame a(shape); 

    //initialize the array with 0
    std::fill(a.begin(),a.end(),1);

    //using a selection to set the values of each vector
    for(size_t i=0;i<shape[0];i++)
        a(i,Slice(0,3)) += i+0.1*i;

    //plotting some output
    std::cout<<a<<std::endl;
    for(size_t i=0;i<shape[0];i++)
    {
        Vector v(a(i,Slice(0,3)));
        std::cout<<"vector = "<<v<<std::endl;
    }

    Vector v1(std::vector<Float32>({1.,2.,3.}));
    std::cout<<"v1 = "<<v1<<std::endl;
    Vector v2{std::vector<Float32>{4,5,6}};
    std::cout<<"v2 = "<<v2<<std::endl;

    //Vector v{std::vector<Float32>{4,5,6}};
    return 0;
}

