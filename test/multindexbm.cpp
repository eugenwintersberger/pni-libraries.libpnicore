//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/utils/Iterator.hpp>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/DArray.hpp>
#include <pni/utils/Array.hpp>

#include "benchmark/BenchmarkRunner.hpp"
#include "benchmark/BenchmarkResult.hpp"
#include "benchmark/ChronoTimer.hpp"
#include "benchmark/ClockTimer.hpp"

#include "benchmark/MultiIndexIOPointer.hpp"
#include "benchmark/MultiIndexIOArray.hpp"

using namespace pni::utils;

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark)
{
    std::cout<<"Benchmark: "<<bmark.name()<<std::endl;
    std::cout<<"Timer: "<<CLKT::name<<std::endl;

    //create benchmark functions from the benchmark object
    BenchmarkRunner::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    BenchmarkRunner write_bm,read_bm;
    write_bm.run<CLKT>(nruns,write_func);
    read_bm.run<CLKT>(nruns,read_func);

    BenchmarkResult write_result = average(write_bm);
    BenchmarkResult read_result  = average(read_bm);

    std::cout<<"Write result: "<<write_result<<std::endl;
    std::cout<<"Read result:  "<<read_result<<std::endl;
    std::cout<<std::endl;
}


typedef ChronoTimer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

int main(int argc,char **argv)
{
    typedef DArray<double,DBuffer<double> > darray_t; //DArray type
    typedef NumArray<darray_t> ndarray_t;             //numerical array type
    typedef MultiIndexIOArray<darray_t> darray_bm_t;  //darray multiindex benchmark type
    typedef MultiIndexIOArray<ndarray_t> narray_bm_t; //ndarray multiindex benchmark type
    typedef MultiIndexIOPointer<double> ptr_bm_t;     //pointer muldiindex benchmark type

    //---------------read user arguments--------------------------------------
    if(argc<3) 
    {
        std::cerr<<"Usage: multiindexbm <nx> <ny>"<<std::endl;
        return 1;
    }

    size_t nx = atoi(argv[1]);
    size_t ny = atoi(argv[2]);
    std::cout<<"Array size: "<<nx<<" "<<ny<<std::endl;
    std::cout<<"allocating "<<nx*ny*sizeof(double)/1024/1024<<" MByte of memory!";
    std::cout<<std::endl;

    //-----------------------------run benchmarks------------------------------ 
    run_benchmark<bmtimer_t>(1,ptr_bm_t(nx,ny));
    run_benchmark<bmtimer_t>(1,darray_bm_t(darray_t(shape_t{nx,ny})));
    run_benchmark<bmtimer_t>(1,narray_bm_t(ndarray_t(shape_t{nx,ny})));

    return 0;
}


