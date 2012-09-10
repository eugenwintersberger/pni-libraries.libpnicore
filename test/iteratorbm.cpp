//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
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
    clock_t start,stop;
    double ptr_read,ptr_write,iter_read,iter_write;

    double *ptr = new double[N];

    //writing to memory
    start = clock();
    for(size_t i=0;i<N;i++) ptr[i] = double(i);
    stop = clock();
    ptr_write = ((double)(stop-start))/CLOCKS_PER_SEC;
    std::cout<<"pointer write: "<<ptr_write<<std::endl;

    //reading from memory
    double sum = 0;
    start = clock();
    for(size_t i=0;i<N;i++) sum += ptr[i];
    stop = clock();
    ptr_read = ((double)(stop-start))/CLOCKS_PER_SEC;
    std::cout<<"pointer read: "<<ptr_read<<std::endl;
    std::cout<<sum<<std::endl;

    if(ptr) delete [] ptr;

    DBuffer<double> b(N);
    //writing to memory
    start = clock();
    size_t index = 0;
    for(auto iter = b.begin();iter!=b.end();++iter) *iter = double(index++);
    stop = clock();
    iter_write = ((double)(stop-start))/CLOCKS_PER_SEC;
    std::cout<<"iterator write: "<<iter_write<<std::endl;

    //reading from memory
    sum = 0; index = 0;
    start = clock();
    for(auto iter = b.begin();iter!=b.end();++iter) sum += *iter;
    stop = clock();
    iter_read = ((double)(stop-start))/CLOCKS_PER_SEC;
    std::cout<<"iterator read: "<<iter_read<<std::endl;
    std::cout<<sum<<std::endl;

    //compute speedup
    std::cout<<"iterator/pointer write: "<<iter_write/ptr_write<<std::endl;
    std::cout<<"iterator/pointer read:  "<<iter_read/ptr_read<<std::endl;

    return 0;
}


