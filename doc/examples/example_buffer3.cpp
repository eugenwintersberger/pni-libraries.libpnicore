/*! \example example_buffer3.cpp

Using the RefBuffer template.
*/

#include <iostream>
#include <pni/core/rbuffer.hpp>
#include <pni/core/types.hpp>

using namespace pni::core;

int main(int argc,char **argv)
{
    size_t N=1024;
    float32 *data = new float32[N];

    //create a new reference buffer
    rbuffer<float32> buffer(N,data);

    //now buffer can be used like a Buffer<T> object.

    delete [] data;
    return 0;
}
