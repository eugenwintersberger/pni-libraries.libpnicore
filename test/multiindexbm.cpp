//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/utils/Iterator.hpp>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/DArray.hpp>
#include <pni/utils/Array.hpp>

#include <pni/utils/benchmark/BenchmarkRunner.hpp>
#include <pni/utils/benchmark/BenchmarkResult.hpp>
#include <pni/utils/benchmark/ChronoTimer.hpp>
#include <pni/utils/benchmark/ClockTimer.hpp>

#include "benchmark/MultiIndexIOPointer.hpp"
#include "benchmark/MultiIndexIOArray.hpp"

#include <utility>
using namespace pni::utils;

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark)
{
    std::cout<<bmark.name()<<std::endl;
    //create benchmark functions from the benchmark object
    BenchmarkRunner::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    BenchmarkRunner write_bm,read_bm;
    write_bm.run<CLKT>(nruns,write_func);
    read_bm.run<CLKT>(nruns,read_func);

    String write_unit = write_bm.begin()->unit();
    String read_unit = read_bm.begin()->unit();
    std::cout<<"write ("<<write_unit<<")\tread ("<<read_unit<<")"<<std::endl;
    for(auto wit=write_bm.begin(),rit=read_bm.begin();
        wit!=write_bm.end() && rit != read_bm.end();
        ++wit,++rit)
    {
        std::cout<<wit->time()<<"\t"<<rit->time()<<std::endl;
    }
    std::cout<<std::endl;

    BenchmarkResult write_result = average(write_bm);
    BenchmarkResult read_result  = average(read_bm);

    std::cout<<"Average values: "<<std::endl;
    std::cout<<write_result.time()<<"\t"<<read_result.time()<<std::endl;

}


typedef ChronoTimer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

int main(int argc,char **argv)
{
    typedef DArray<double,DBuffer<double> > darray_t; //DArray type
    typedef SArray<double,100,100> sarray_t;
    typedef NumArray<darray_t> ndarray_t;             //numerical array type
    typedef MultiIndexIOArray<darray_t> darray_bm_t;  //darray multiindex benchmark type
    typedef MultiIndexIOArray<ndarray_t> narray_bm_t; //ndarray multiindex benchmark type
    typedef MultiIndexIOArray<sarray_t> sarray_bm_t;
    typedef MultiIndexIOPointer<double> ptr_bm_t;     //pointer muldiindex benchmark type

    //---------------read user arguments--------------------------------------
    if(argc<5) 
    {
        std::cerr<<"Usage: multiindexbm <type> <nruns> <nx> <ny>"<<std::endl;
        return 1;
    }

    String type(argv[1]);
    size_t nruns = atoi(argv[2]);
    size_t nx = atoi(argv[3]);
    size_t ny = atoi(argv[4]);
    std::cout<<"Array size: "<<nx<<" "<<ny<<std::endl;
    std::cout<<"allocating "<<nx*ny*sizeof(double)/1024/1024<<" MByte of memory!";
    std::cout<<std::endl;

    //-----------------------------run benchmarks------------------------------ 
    if(type=="ptr") run_benchmark<bmtimer_t>(nruns,ptr_bm_t(nx,ny));
    else if(type == "darray")
        run_benchmark<bmtimer_t>(nruns,darray_bm_t(darray_t(shape_t{nx,ny})));
    else if(type == "ndarray")
        run_benchmark<bmtimer_t>(nruns,narray_bm_t(ndarray_t(shape_t{nx,ny})));
    else if(type == "sarray")
        run_benchmark<bmtimer_t>(nruns,sarray_bm_t(sarray_t()));
    else
        std::cerr<<"Unknown benchmark type"<<std::endl;


    return 0;
}


