/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Oct 29, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

//program to test random number sequences

#include <vector>
#include <boost/lexical_cast.hpp>

#include <pni/core/types.hpp>
#include <pni/core/configuration.hpp>


#include "data_generator.hpp"

using namespace pni::core;

template<typename T> struct bound_type
{
    typedef T type;
};

template<typename T> struct bound_type<std::complex<T>>
{
    typedef T type;
};

template<> struct bound_type<string>
{
    typedef unsigned long type;
};


template<typename T> void execute(size_t n,string a,string b)
{
    using boost::lexical_cast;
    typedef random_generator<T> random_generator_t;

    random_generator_t generator;

    if((a=="")&&(b=="")) //if both are empty strings 
        generator = random_generator_t();
    else
    {
        //convert user input to the appropriate number type
        auto a_value = lexical_cast<typename bound_type<T>::type>(a);
        auto b_value = lexical_cast<typename bound_type<T>::type>(b);
    
        assert(a_value<b_value);
        generator = random_generator_t(a_value,b_value);
    }

    for(size_t i=0;i<n;++i) std::cout<<generator()<<std::endl;
}


int main(int argc,char **argv)
{
    configuration config;
    config.add_option(config_option<string>("type","t",
                "data type to use","float32"));
    config.add_option(config_option<size_t>("nruns","n",
                "number of random numbers to generate",1));
    config.add_option(config_option<string>("lower-bound","l",
                "lower bound of the distribution",string()));
    config.add_option(config_option<string>("upper-bound","u",
                "upper bound of the distribution",string()));
    
    parse(config,cliargs2vector(argc,argv));
    
    size_t nruns = config.value<size_t>("nruns");
    type_id_t type_id  = type_id_from_str(config.value<string>("type"));
    auto a = config.value<string>("lower-bound");
    auto b = config.value<string>("upper-bound");


    if     (type_id == type_id_t::INT32 ) execute<int32>(nruns,a,b);
    else if(type_id == type_id_t::UINT32) execute<uint32>(nruns,a,b);
    else if(type_id == type_id_t::INT64 ) execute<int64>(nruns,a,b);
    else if(type_id == type_id_t::UINT64)  execute<uint64>(nruns,a,b);
    else if(type_id == type_id_t::FLOAT32) execute<float32>(nruns,a,b);
    else if(type_id == type_id_t::FLOAT64) execute<float64>(nruns,a,b);
    else if(type_id == type_id_t::FLOAT128) execute<float128>(nruns,a,b);
    else if(type_id == type_id_t::COMPLEX32) execute<complex32>(nruns,a,b);
    else if(type_id == type_id_t::COMPLEX64) execute<complex64>(nruns,a,b);
    else if(type_id == type_id_t::COMPLEX128) execute<complex128>(nruns,a,b);
    else if(type_id == type_id_t::STRING) execute<string>(nruns,a,b);
    else
    {
        std::cerr<<"Unknown data type!"<<std::endl;
        return 1;
    }

    return 0;
}
