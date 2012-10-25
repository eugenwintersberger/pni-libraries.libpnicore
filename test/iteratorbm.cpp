//iterator benchmark

#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include "Iterator.hpp"
#include "DBuffer.hpp"

#include "benchmark/Benchmark.hpp"
#include "benchmark/BenchmarkResult.hpp"
#include "benchmark/ChronoTimer.hpp"
#include "benchmark/ClockTimer.hpp"

#include "benchmark/LinearIOPointerBenchmark.hpp"
#include "benchmark/LinearIODBufferIterator.hpp"

using namespace pni::utils;



template<typename CLKT> void run_benchmark(size_t N,const String clock_name)
{
    typedef LinearIOPointerBenchmark<double> ptr_bmark_t;
    typedef LinearIODBufferIterator<DBuffer<double> > dbuffer_bmark_t;
    
    std::cout<<"Results for timer: "<<clock_name<<std::endl;

    Benchmark::function_t bmfunction;

    //=========================benchmark pointer IO=============================
    ptr_bmark_t ptr_bmark(N);
    Benchmark bm_ptr_write,bm_ptr_read;

    //------------------------run pointer write benchmark-----------------------
    bmfunction = std::bind(&ptr_bmark_t::write_data,ptr_bmark);
    bm_ptr_write.run<CLKT>(1,bmfunction);
    BenchmarkResult ptr_write_result = average(bm_ptr_write);

    //------------------------run pointer read benchmark------------------------
    bmfunction = std::bind(&ptr_bmark_t::read_data,ptr_bmark);
    bm_ptr_read.run<CLKT>(1,bmfunction);
    BenchmarkResult ptr_read_result = average(bm_ptr_read);

    //===========================benchmark iterator IO=========================
    dbuffer_bmark_t buffer_bmark(N);
    Benchmark bm_iter_write,bm_iter_read;

    //------------------------run iterator write benchmark---------------------
    bmfunction = std::bind(&dbuffer_bmark_t::write_data,buffer_bmark);
    bm_iter_write.run<CLKT>(1,bmfunction);
    BenchmarkResult iter_write_result = average(bm_iter_write);

    //-------------------------run iterator read benchmark---------------------
    bmfunction = std::bind(&dbuffer_bmark_t::read_data,buffer_bmark);
    bm_iter_read.run<CLKT>(1,bmfunction);
    BenchmarkResult iter_read_result = average(bm_iter_read);

    //===========================output results================================

    std::cout<<"Pointer write result:  "<<ptr_write_result<<std::endl;
    std::cout<<"Iterator write result: "<<iter_write_result<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Pointer read result:   "<<ptr_read_result<<std::endl;
    std::cout<<"Iterator read result:  "<<iter_read_result<<std::endl;
}


typedef ChronoTimer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

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
        
    
    run_benchmark<bmtimer_t>(N,"ChronoTimer");
    run_benchmark<ClockTimer>(N,"ClockTimer");


    return 0;
}


