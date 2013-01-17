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
 *  Created on: Jan 17, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <sstream>
#include <vector>
#include <pni/core/Types.hpp>
#include "RandomDistributions.hpp"

template<typename T> class data_factory
{
    public:
        template<template<typename ...> class CT,typename ...OTS>
        static  void create(size_t n,CT<T,OTS...> &c)
        {
            c = RandomDistribution::uniform<CT<T,OTS...> >(n);
        }
};

template<> class data_factory<String>
{
    public:
        template<template<typename ...> class CT,typename ...OTS>
        static void create(size_t n,CT<String,OTS...> &c)
        {
           typedef std::vector<int> vec_t;

           //create first integer random numbers
           vec_t buffer = RandomDistribution::uniform<vec_t>(n);

           c = CT<String,OTS...>(n);
           vec_t::const_iterator biter = buffer.begin();
           for(auto iter=c.begin();iter!=c.end();++iter)
           {
               std::stringstream ss;
               ss<<*biter++;
               *iter = ss.str();
           }

        }
};


