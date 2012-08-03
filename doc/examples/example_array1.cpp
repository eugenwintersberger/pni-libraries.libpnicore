/*! \example example_array1.cpp

Basic usage of the DArray template.
*/

#include <vector>
#include <pni/utils/Types.hpp>
#include <pni/utils/DArray.hpp>

using namespace pni::utils;

//some usefull type definitions
typedef std::vector<size_t> shape_t; //container to describe array shapes
typedef DArray<Float32> F32Array;    //an array type for Float32 values


int main(int argc,char **argv)
{
    shape_t shape{1024,2048};
    //simpel construction from shape - memory allocation is done bye 
    //the array constructor
    F32Array a(shape); 

    //reshaping works only if the new shape describes the same number of
    //elements
    a.shape(shape_t{2048,1024});
    try
    {
        a.shape(shape_t{1024,1024});
    }
    catch(SizeMissmatchError &e)
    {
        std::cout<<e<<std::endl;
        std::cout<<"Array size is not the same!"<<std::endl;
    }
    

    return 0;
}

