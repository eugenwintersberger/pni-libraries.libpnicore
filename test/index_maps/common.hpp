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
 *  This file contains declarations and definitions common to all index map and
 *  index policy related tests.
 *
 *  Created on: Oct 25, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <vector>
#include <list>
#include <array>
#include <functional>
#include <algorithm>
#include <pni/core/index_map/index_map.hpp>
#include <pni/core/index_map/static_index_map.hpp>

using namespace pni::core;


//---------------------assemble some special containers------------------------
//define some dynamic containers
typedef std::vector<size_t> vector_t; //a vector for index maps
typedef std::list<size_t>   list_t;   //a list for index shapes
//a new array template for static storage of index data
template<size_t N> using array_t = std::array<size_t,N>;


//------------------declare some types for test setup--------------------------
/*!
\brief test parameters 

This type solves the problem that class templates cann only take a single
variadic template set (which we would like to use for the index for the test). 

\tparam DIMS number of elements along each dimension
*/
template<size_t... DIMS> struct test_params
{
    //! a static index type
    typedef std::array<size_t,sizeof...(DIMS)> index_t;
    //! the shape of the index map
    constexpr static index_t shape{{DIMS...}};
    //! the rank of the index map
    constexpr static size_t rank = sizeof...(DIMS);
};

template<size_t... DIMS> 
constexpr typename test_params<DIMS...>::index_t test_params<DIMS...>::shape;
template<size_t... DIMS>
constexpr size_t test_params<DIMS...>::rank; 
