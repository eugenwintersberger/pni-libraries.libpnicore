//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/core/container_iterator.hpp>
#include <pni/core/dbuffer.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/arrays.hpp>

#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/clock_timer.hpp>

#include "benchmark/multiindex_io_pointer.hpp"
#include "benchmark/multiindex_io_array.hpp"

#include <utility>
using namespace pni::core;

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark)
{
    std::cout<<bmark.name()<<std::endl;
    //create benchmark functions from the benchmark object
    benchmark_runner::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    benchmark_runner write_bm,read_bm;
    write_bm.run<CLKT>(nruns,write_func);
    read_bm.run<CLKT>(nruns,read_func);

    string write_unit = write_bm.begin()->unit();
    string read_unit = read_bm.begin()->unit();
    std::cout<<"write ("<<write_unit<<")\tread ("<<read_unit<<")"<<std::endl;
    for(auto wit=write_bm.begin(),rit=read_bm.begin();
        wit!=write_bm.end() && rit != read_bm.end();
        ++wit,++rit)
    {
        std::cout<<wit->time()<<"\t"<<rit->time()<<std::endl;
    }
    std::cout<<std::endl;

    benchmark_result write_result = average(write_bm);
    benchmark_result read_result  = average(read_bm);

    std::cout<<"Average values: "<<std::endl;
    std::cout<<"write\tread"<<std::endl;
    std::cout<<write_result.time()<<"\t"<<read_result.time()<<std::endl;

}


typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

int main(int argc,char **argv)
{
    typedef darray<double,dbuffer<double> > darray_t; //DArray type
    typedef sarray<double,100,100> sarray_t;
    typedef numarray<darray_t> ndarray_t;             //numerical array type
    typedef multiindex_io_array<darray_t> darray_bm_t;  //darray multiindex benchmark type
    typedef multiindex_io_array<ndarray_t> narray_bm_t; //ndarray multiindex benchmark type
    typedef multiindex_io_array<sarray_t> sarray_bm_t;
    typedef multiindex_io_pointer<double> ptr_bm_t;     //pointer muldiindex benchmark type

    //---------------read user arguments--------------------------------------
    if(argc<5) 
    {
        std::cerr<<"Usage: multiindexbm <type> <nruns> <nx> <ny>"<<std::endl;
        return 1;
    }

    string type(argv[1]);
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


