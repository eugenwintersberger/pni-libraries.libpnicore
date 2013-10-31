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
 *  Created on: Oct 28, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size_t.hpp>
#include <pni/core/mdarray.hpp>

using namespace pni::core;

//---------------------a dynamic array type------------------------------------
/*!
\brief a dynamic array type

Usage
\code
typedef dyn_array<float64> array_type;
\endcode

\tparam T element type
*/
template<typename T> 
using dyn_array = mdarray<std::vector<T>,dynamic_cindex_map>;

//------------an array type with fixed number of dimensions--------------------
/*!
\brief a fixed dimension array type

This is the array type most probably used the most. You have to fix the number
of dimensions at compile time

\code
typedef fix_array<uint32,2> image_type;
\endcode

alternatively one could us it with an additional template alias to define a more
versatile image type

\code
template<typename T> using image_type = fix_array<T,2>;
\endcode

\tparam T element type
\tparam NDIMS number of dimensions
*/
template<typename T,size_t NDIMS> 
using fix_array = mdarray<std::vector<T>,fixed_dim_cindex_map<NDIMS> >;

//--------------------------a static array type--------------------------------
/*!
\brief a static array type

The number of dimensions as well as the number of elements along each dimension
must be fixed at compile time. This is a particularly useful type for small
objects  as they are allocated on the stack rather than on the heap. 

\code
typedef static_array<float64,3> vector3_type;
typedef static_array<float64,3,3> matrix3_type;
\endcode

\tparam T element type
\tparam DIMS number of elements along each dimension
*/
template<typename T,size_t... DIMS>
using static_array = mdarray<std::array<T,
                             boost::mpl::times<
                                 boost::mpl::size_t<1>,
                                 boost::mpl::size_t<DIMS>...
                             >::value
                             >,
                             static_cindex_map<DIMS...>>;
