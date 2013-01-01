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
 *  Created on: Dec 28, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/math/mt_inplace_arithmetics.hpp>
#include <pni/utils/config/configuration.hpp>
#include <pni/utils/config/config_parser.hpp>


#include <pni/utils/benchmark/BenchmarkRunner.hpp>
#include <pni/utils/benchmark/BenchmarkResult.hpp>
#include <pni/utils/benchmark/ChronoTimer.hpp>
#include <pni/utils/benchmark/ClockTimer.hpp>

#include "benchmark/inplace_arithmetic_benchmark.hpp"

using namespace pni::utils;

typedef ChronoTimer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

//-----------------------------------------------------------------------------
template<typename ATYPE> void run_inplace_benchmark(size_t nruns,ATYPE &&a)
{
    //define benchmark type
    typedef inplace_arithmetic_benchmark<ATYPE> bm_t; 

    BenchmarkRunner::function_t add_func,mult_func,div_func,sub_func;
    bm_t benchmark(std::move(a));

    //define benchmark functions
    add_func = std::bind(&bm_t::add,benchmark,100);
    sub_func = std::bind(&bm_t::sub,benchmark,10);
    div_func = std::bind(&bm_t::div,benchmark,10);
    mult_func = std::bind(&bm_t::mult,benchmark,1.23);
    
    //run benchmarks
    BenchmarkRunner add_bm,mult_bm,div_bm,sub_bm;

    add_bm.run<bmtimer_t>(nruns,add_func);
    sub_bm.run<bmtimer_t>(nruns,sub_func);
    div_bm.run<bmtimer_t>(nruns,div_func);
    mult_bm.run<bmtimer_t>(nruns,mult_func);
    
    //print benchmark results 
    BenchmarkResult result;
    result = average(add_bm);
    std::cout<<"Inplace add:\t"<<result<<std::endl;
    result = average(sub_bm);
    std::cout<<"Inplace sub:\t"<<result<<std::endl;
    result = average(div_bm);
    std::cout<<"Inplace div:\t"<<result<<std::endl;
    result = average(mult_bm);
    std::cout<<"Inplace mult:\t"<<result<<std::endl;

}

//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    //program configuration 
    configuration conf;

    conf.add_option(config_option<size_t>("nx","x",
                "channels along first dimension",1024));
    conf.add_option(config_option<size_t>("ny","y",
                "channels along second dimension",1024));
    conf.add_option(config_option<size_t>("nruns","r",
                "number of benchmark runs",1));
    
    parse(conf,argc,argv);

    //type definitions
    typedef NumArray<DArray<Float64> > nf64array;
    typedef NumArray<DArray<Float64>,mt_inplace_arithmetics> nf64array_mt;

    {
        nf64array a_st{conf.value<size_t>("nx"),
                       conf.value<size_t>("ny")};
        std::cout<<"Single threaded benchmark:"<<std::endl;
        run_inplace_benchmark(conf.value<size_t>("nruns"),std::move(a_st));
    }

    {
        //allocate memory
        nf64array_mt a_mt{conf.value<size_t>("nx"),
                       conf.value<size_t>("ny")};
        std::cout<<"Multithreaded benchmark:"<<std::endl;
        run_inplace_benchmark(conf.value<size_t>("nruns"),std::move(a_mt));
    }

    return 0;
}
