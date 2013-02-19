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

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/math/mt_inplace_arithmetics.hpp>
#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>


#include <pni/core/benchmark/benchmark_runner.hpp>
#include <pni/core/benchmark/benchmark_result.hpp>
#include <pni/core/benchmark/chrono_timer.hpp>
#include <pni/core/benchmark/clock_timer.hpp>

#include "benchmark/inplace_arithmetic_benchmark.hpp"
#include "benchmark/inplace_arithmetic_benchmark_ptr.hpp"
#include "benchmark/binary_arithmetic_benchmark.hpp"
#include "benchmark/binary_arithmetic_benchmark_ptr.hpp"

using namespace pni::core;

typedef chrono_timer<std::chrono::high_resolution_clock,std::chrono::nanoseconds> bmtimer_t;

template<typename ATYPE,bool use_ptr_flag> struct inplace_benchmark_type;
template<typename ATYPE> struct inplace_benchmark_type<ATYPE,true>
{
    typedef inplace_arithmetic_benchmark_ptr<ATYPE> benchmark_type;
};

template<typename ATYPE> struct inplace_benchmark_type<ATYPE,false>
{
    typedef inplace_arithmetic_benchmark<ATYPE> benchmark_type;
};

//-----------------------------------------------------------------------------
template<typename ATYPE,bool use_ptr_flag> struct binary_benchmark_type;
template<typename ATYPE> struct binary_benchmark_type<ATYPE,true>
{
    typedef binary_arithmetic_benchmark_ptr<ATYPE> benchmark_type;
};

template<typename ATYPE> struct binary_benchmark_type<ATYPE,false>
{
    typedef binary_arithmetic_benchmark<ATYPE> benchmark_type;
};

//-----------------------------------------------------------------------------
template<bool use_ptr_flag,typename ATYPE> 
void run_inplace_benchmark(size_t nruns,ATYPE &&a)
{
    //define benchmark type
    typedef typename inplace_benchmark_type<ATYPE,use_ptr_flag>::benchmark_type bm_t; 

    benchmark_runner::function_t add_func,mult_func,div_func,sub_func;
    bm_t benchmark(std::move(a));

    //define benchmark functions
    add_func = std::bind(&bm_t::add,benchmark,100);
    sub_func = std::bind(&bm_t::sub,benchmark,10);
    div_func = std::bind(&bm_t::div,benchmark,10);
    mult_func = std::bind(&bm_t::mult,benchmark,1.23);
    
    //run benchmarks
    benchmark_runner add_bm,mult_bm,div_bm,sub_bm;

    add_bm.run<bmtimer_t>(nruns,add_func);
    sub_bm.run<bmtimer_t>(nruns,sub_func);
    div_bm.run<bmtimer_t>(nruns,div_func);
    mult_bm.run<bmtimer_t>(nruns,mult_func);
    
    //print benchmark results 
    benchmark_result result;
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

template<typename ATYPE> void reset_array(ATYPE &a)
{
    std::fill(a.begin(),a.end(),typename ATYPE::value_type(0));
}

template<bool use_ptr_flag,typename ATYPE> 
void run_binary_benchmark(size_t nruns,ATYPE &a,ATYPE &b,ATYPE &c)
{
    //define benchmark type
    typedef typename binary_benchmark_type<ATYPE,use_ptr_flag>::benchmark_type bm_t; 

    benchmark_runner::function_t add_func,mult_func,div_func,sub_func;
    bm_t benchmark(a);

    //define benchmark functions
    add_func = std::bind(&bm_t::add,benchmark,c,a,b);
    sub_func = std::bind(&bm_t::sub,benchmark,c,a,b);
    div_func = std::bind(&bm_t::div,benchmark,c,a,b);
    mult_func = std::bind(&bm_t::mult,benchmark,c,a,b);
    
    //run benchmarks
    benchmark_runner add_bm,mult_bm,div_bm,sub_bm;

    std::fill(a.begin(),a.end(),typename ATYPE::value_type(10.0));
    std::fill(b.begin(),b.end(),typename ATYPE::value_type(100.0));
    add_bm.run<bmtimer_t>(nruns,add_func);
    std::fill(a.begin(),a.end(),typename ATYPE::value_type(10.0));
    std::fill(b.begin(),b.end(),typename ATYPE::value_type(100.0));
    sub_bm.run<bmtimer_t>(nruns,sub_func);
    std::fill(a.begin(),a.end(),typename ATYPE::value_type(10.0));
    std::fill(b.begin(),b.end(),typename ATYPE::value_type(100.0));
    div_bm.run<bmtimer_t>(nruns,div_func);
    std::fill(a.begin(),a.end(),typename ATYPE::value_type(10.0));
    std::fill(b.begin(),b.end(),typename ATYPE::value_type(100.0));
    mult_bm.run<bmtimer_t>(nruns,mult_func);
    
    //print benchmark results 
    benchmark_result result;
    result = average(add_bm);
    std::cout<<"Binary add:\t"<<result<<std::endl;
    result = average(sub_bm);
    std::cout<<"Binary sub:\t"<<result<<std::endl;
    result = average(div_bm);
    std::cout<<"Binary div:\t"<<result<<std::endl;
    result = average(mult_bm);
    std::cout<<"Binary mult:\t"<<result<<std::endl;

}
//-----------------------------------------------------------------------------
int main(int argc,char **argv)
{
    //program configuration 
    configuration conf;
    
    conf.add_option(config_option<bool>("help","h",
                "show help text",false));
    conf.add_option(config_option<size_t>("nx","x",
                "channels along first dimension",1024));
    conf.add_option(config_option<size_t>("ny","y",
                "channels along second dimension",1024));
    conf.add_option(config_option<size_t>("nruns","r",
                "number of benchmark runs",1));
    conf.add_option(config_option<size_t>("nthreads","n",
                "number of threads to use for arithmetics",1));
    conf.add_option(config_option<bool>("use-ptr","p",
                    "use raw pointer code",false));
    conf.add_option(config_option<bool>("binary","b",
                    "run binary arithmetics",false));
    
    parse(conf,cliargs2vector(argc,argv));

    if(conf.value<bool>("help"))
    {
        std::cerr<<conf<<std::endl;
        return 1;
    }


    //type definitions
    typedef numarray<darray<float64> > nf64array;
    typedef numarray<darray<float64>,mt_inplace_arithmetics,true> nf64array_mt;

    if(conf.value<size_t>("nthreads") == 1)
    {
        nf64array a(shape_t{conf.value<size_t>("nx"),conf.value<size_t>("ny")});

        if(conf.value<bool>("binary"))
        {
            nf64array b(a.shape<shape_t>());
            nf64array c(a.shape<shape_t>());

            if(conf.value<bool>("use-ptr"))
                run_binary_benchmark<true>(conf.value<size_t>("nruns"),a,b,c);
            else
                run_binary_benchmark<false>(conf.value<size_t>("nruns"),a,b,c);
        }
        else
        {
            if(conf.value<bool>("use-ptr"))
                run_inplace_benchmark<true>(conf.value<size_t>("nruns"),std::move(a));
            else
                run_inplace_benchmark<false>(conf.value<size_t>("nruns"),std::move(a));
        }
    }
    else
    {
        if(conf.value<bool>("use-ptr"))
        {
            std::cerr<<"multithreading benchmarks do not support pointers!"<<std::endl;
            return 1;
        }

        //set the number of threads in the library configuration

        //allocate memory
        nf64array_mt array(shape_t{conf.value<size_t>("nx"),
                                   conf.value<size_t>("ny")});
        run_inplace_benchmark<false>(conf.value<size_t>("nruns"),std::move(array));
    }

    return 0;
}
