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
 *  Created on: May 22, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <random>

#include <pni/utils/TypeInfo.hpp>
#include <pni/utils/Types.hpp>

using namespace pni::utils;


template<typename CT,bool is_int,bool is_complex> class UniformDistribution;

//create integer data uniformly distributed
template<typename CT> class UniformDistribution<CT,true,false> 
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);

#ifndef NOCPPRAND
            std::mt19937_64 engine;
            std::uniform_int_distribution<> 
                dist(TypeInfo<value_type>::min(),TypeInfo<value_type>::max());
#endif

#ifdef NOFOREACH
            for(auto iter=container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
#ifdef NOCPPRAND
                v = value_type(1);
#else
                v = dist(engine);
#endif
            }

            return container;
        }
};

//create floating point uniform distribution
template<typename CT> class UniformDistribution<CT,false,false>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);
#ifndef NOCPPRAND       
            std::mt19937_64 engine;
            std::uniform_real_distribution<> 
                dist(TypeInfo<Float32>::min(),TypeInfo<Float32>::max());
#endif

#ifdef NOFOREACH
            for(auto iter=container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
#ifdef NOCPPRAND
                v = value_type(1);
#else
                v = dist(engine);
#endif
            }

            return container;
        }
};

//create complex uniform distribution
template<typename CT> class UniformDistribution<CT,false,true>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            typedef typename value_type::value_type base_type;
            CT container(n);

#ifndef NOCPPRAND       
            std::mt19937_64 engine;
            std::uniform_real_distribution<>
                dist(TypeInfo<Float32>::min(),
                     TypeInfo<Float32>::max());
#endif

#ifdef NOFOREACH
            for(auto iter = container.begin();iter!=container.end();iter++)
            {
                value_type &v = *iter;
#else
            for(value_type &v: container)
            {
#endif
#ifdef NOCPPRAND
                v = value_type(1,1);
#else
                v = value_type(dist(engine),dist(engine));
#endif
            }

            return container;
        }
};

class RandomDistribution
{
    public:
        template<typename CT> static CT uniform(size_t n)
        {
            return UniformDistribution<CT,
                                       TypeInfo<typename CT::value_type>::is_integer,
                                       TypeInfo<typename CT::value_type>::is_complex>
                                           ::create_data(n);
        }
};
#endif
