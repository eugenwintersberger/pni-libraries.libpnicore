/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 12, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <iostream>
#include <chrono>
#include <ratio>
#include <ctime>
#include <pni/core/container_iterator.hpp>
#include <pni/core/dbuffer.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/arrays.hpp>

#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/clock_timer.hpp>

#include "benchmark/linear_io_pointer_benchmark.hpp"
#include "benchmark/linear_io_container_iterator.hpp"

using namespace pni::core;

template<typename CLKT,typename BMARKT> 
void run_benchmark(size_t nruns,const BMARKT &bmark)
{
    std::cout<<"Benchmark: "<<bmark.name()<<std::endl;
    std::cout<<"Timer: "<<CLKT::name<<std::endl;

    //create benchmark functions from the benchmark object
    benchmark_runner::function_t write_func,read_func;
    write_func = std::bind(&BMARKT::write_data,bmark);
    read_func  = std::bind(&BMARKT::read_data,bmark);

    benchmark_runner write_bm,read_bm;
    write_bm.run<CLKT>(nruns,write_func);
    read_bm.run<CLKT>(nruns,read_func);

    benchmark_result write_result = average(write_bm);
    benchmark_result read_result  = average(read_bm);

    std::cout<<"Write result: "<<write_result<<std::endl;
    std::cout<<"Read result:  "<<read_result<<std::endl;
    std::cout<<std::endl;
}


typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

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
    
    typedef linear_io_container_iterator<dbuffer<double> > dbuffer_bm_t;
    typedef linear_io_container_iterator<darray<double,dbuffer<double> > > darray_bm_t;
    typedef linear_io_container_iterator<numarray<
                                               darray<double,dbuffer<double> > 
                                              > 
                                     >  narray_bm_t;
    typedef linear_io_pointer_benchmark<double> ptr_bm_t;
   

    run_benchmark<bmtimer_t>(1,ptr_bm_t(N));
    //run_benchmark<ClockTimer>(1,ptr_bm_t(N));

    run_benchmark<bmtimer_t>(1,dbuffer_bm_t(dbuffer<double>(N)));
    run_benchmark<bmtimer_t>(1,darray_bm_t(darray<double,dbuffer<double> >(shape_t{2,N/2})));
    run_benchmark<bmtimer_t>(1,narray_bm_t(
                numarray<darray<double,dbuffer<double> > >(shape_t{2,N/2})));
    //run_benchmark<ClockTimer>(1,dbuffer_bm_t(DBuffer<double>(N)));


    return 0;
}


