/*! \example example_array1.cpp

Basic usage of the DArray template.
*/

#include <vector>
#include <pni/core/types.hpp>
#include <pni/core/darray.hpp>

using namespace pni::core;

//some usefull type definitions
typedef darray<float32> f32array;    //an array type for Float32 values



int main(int argc,char **argv)
{
    shape_t shape({1024,2048});
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    f32array a(shape); 

    //reshaping works only if the new shape describes the same number of
    //elements
    a.shape(shape_t({2048,1024}));
    try
    {
        a.shape(shape_t({1024,1024}));
    }
    catch(size_mismatch_error &e)
    {
        std::cout<<e<<std::endl;
        std::cout<<"Array size is not the same!"<<std::endl;
    }

    //get basic information about an array
    std::cout<<"type_id = "<<f32array::type_id<<std::endl;
    auto s = a.shape<shape_t>();
    std::cout<<"rank = "<<a.rank()<<std::endl;
    std::cout<<"shape = ( ";
#ifdef NOFOREACH
    for(auto iter = s.begin();iter!=s.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: s) 
    {
#endif
        std::cout<<v<<" ";
    }
    std::cout<<")"<<std::endl;

    std::cout<<"total size = "<<a.size()<<std::endl;

    

    return 0;
}

