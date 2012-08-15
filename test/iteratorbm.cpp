//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include "Iterator.hpp"
#include "DBuffer.hpp"

using namespace pni::utils;

int main(int argc,char **argv)
{
    if(argc<2) 
    {
        std::cerr<<"Usage: iterbm <N>"<<std::endl;
        return 1;
    }

    size_t N = atoi(argv[1]);
    std::cout<<"allocating "<<N*sizeof(double)/1024/1024<<" MByte of memory!";
    std::cout<<std::endl;

    std::chrono::time_point<std::chrono::high_resolution_clock> start,stop;
    typedef std::chrono::duration<double,std::ratio<1,1000000000> > museconds;

    double *ptr = new double[N];
    double sum = 0;

    for(size_t i=0;i<N;i++) ptr[i] = double(i);

    start = std::chrono::high_resolution_clock::now();
    for(size_t i=0;i<N;i++) sum += sin(ptr[i]);

    stop = std::chrono::high_resolution_clock::now();
    double tptr = museconds(stop-start).count();
    std::cout<<"Pointer data access: "<<std::scientific<<tptr<<std::endl;

    if(ptr) delete [] ptr;

    DBuffer<double> b(N);
    sum = 0;
    start = std::chrono::high_resolution_clock::now();
#ifdef NOFOREACH
    for(auto iter = b.begin();iter!=b.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: b) 
    {
#endif
        sum += sin(v);
    }
    stop = std::chrono::high_resolution_clock::now();
    double titer = museconds(stop-start).count();
    std::cout<<"Iterator data access: "<<std::scientific<<titer<<std::endl;

    return 0;
}


