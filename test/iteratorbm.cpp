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

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark)
{
    std::cout<<"Benchmark: "<<bmark.name()<<std::endl;
    std::cout<<"Timer: "<<CLKT::name<<std::endl;

    //create benchmark functions from the benchmark object
    Benchmark::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    Benchmark write_bm,read_bm;
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
    if(argc<2) 
    {
        std::cerr<<"Usage: iterbm <N>"<<std::endl;
        return 1;
    }

    size_t N = atoi(argv[1]);
    std::cout<<"allocating "<<N*sizeof(double)/1024/1024<<" MByte of memory!";
    std::cout<<std::endl;
    
    typedef LinearIODBufferIterator<DBuffer<double> > dbuffer_bm_t;
    typedef LinearIOPointerBenchmark<double> ptr_bm_t;
   

    run_benchmark<bmtimer_t>(1,ptr_bm_t(N));
    run_benchmark<ClockTimer>(1,ptr_bm_t(N));

    run_benchmark<bmtimer_t>(1,dbuffer_bm_t(N));
    run_benchmark<ClockTimer>(1,dbuffer_bm_t(N));


    return 0;
}


