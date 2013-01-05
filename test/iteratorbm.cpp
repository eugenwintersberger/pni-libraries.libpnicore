/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 12, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/core/Iterator.hpp>
#include <pni/core/DBuffer.hpp>
#include <pni/core/DArray.hpp>
#include <pni/core/Array.hpp>

#include <pni/core/benchmark/BenchmarkRunner.hpp>
#include <pni/core/benchmark/BenchmarkResult.hpp>
#include <pni/core/benchmark/ChronoTimer.hpp>
#include <pni/core/benchmark/ClockTimer.hpp>

#include "benchmark/LinearIOPointerBenchmark.hpp"
#include "benchmark/LinearIOContainerIterator.hpp"

using namespace pni::core;

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
    if(argc<2) 
    {
        std::cerr<<"Usage: iterbm <N>"<<std::endl;
        return 1;
    }

    size_t N = atoi(argv[1]);
    std::cout<<"allocating "<<N*sizeof(double)/1024/1024<<" MByte of memory!";
    std::cout<<std::endl;
    
    typedef LinearIOContainerIterator<DBuffer<double> > dbuffer_bm_t;
    typedef LinearIOContainerIterator<DArray<double,DBuffer<double> > > darray_bm_t;
    typedef LinearIOContainerIterator<NumArray<
                                               DArray<double,DBuffer<double> > 
                                              > 
                                     >  narray_bm_t;
    typedef LinearIOPointerBenchmark<double> ptr_bm_t;
   

    run_benchmark<bmtimer_t>(1,ptr_bm_t(N));
    //run_benchmark<ClockTimer>(1,ptr_bm_t(N));

    run_benchmark<bmtimer_t>(1,dbuffer_bm_t(DBuffer<double>(N)));
    run_benchmark<bmtimer_t>(1,darray_bm_t(DArray<double,DBuffer<double> >(shape_t{2,N/2})));
    run_benchmark<bmtimer_t>(1,narray_bm_t(
                NumArray<DArray<double,DBuffer<double> > >(shape_t{2,N/2})));
    //run_benchmark<ClockTimer>(1,dbuffer_bm_t(DBuffer<double>(N)));


    return 0;
}


