//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Oct 29, 2015 
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/arrays.hpp>
#include <pni/core/types.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>
#include <cstddef>

typedef boost::mpl::list<pni::core::dynamic_array<pni::core::uint8>,
                         pni::core::dynamic_array<pni::core::uint16>,
                         pni::core::dynamic_array<pni::core::uint32>,
                         pni::core::dynamic_array<pni::core::uint64>,
                         pni::core::dynamic_array<pni::core::int8>,
                         pni::core::dynamic_array<pni::core::int16>,
                         pni::core::dynamic_array<pni::core::int32>,
                         pni::core::dynamic_array<pni::core::int64>,
                         pni::core::dynamic_array<pni::core::float32>,
                         pni::core::dynamic_array<pni::core::float64>,
                         pni::core::dynamic_array<pni::core::float128>,
                         pni::core::dynamic_array<pni::core::complex32>,
                         pni::core::dynamic_array<pni::core::complex64>,
                         pni::core::dynamic_array<pni::core::complex128>>
                         numeric_dynamic_arrays;

typedef boost::mpl::list<pni::core::dynamic_array<pni::core::string>,
                         pni::core::dynamic_array<pni::core::bool_t>>
                         nonnumeric_dynamic_arrays;

typedef boost::mpl::joint_view<numeric_dynamic_arrays,
                               nonnumeric_dynamic_arrays>
                               all_dynamic_arrays;

template<size_t NDIMS>
using numeric_fixed_dim_arrays = 
        boost::mpl::list<pni::core::fixed_dim_array<pni::core::uint8,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::uint16,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::uint32,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::uint64,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::int8,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::int16,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::int32,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::int64,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::float32,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::float64,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::float128,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::complex32,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::complex64,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::complex128,NDIMS>>;
                         

template<size_t NDIMS>
using nonnumeric_fixed_dim_arrays = 
        boost::mpl::list<pni::core::fixed_dim_array<pni::core::string,NDIMS>,
                         pni::core::fixed_dim_array<pni::core::bool_t,NDIMS>>;

template<size_t NDIMS>
using all_fixed_dim_arrays = 
        boost::mpl::joint_view<numeric_fixed_dim_arrays<NDIMS>,
                               nonnumeric_fixed_dim_arrays<NDIMS>>;

template<size_t... DIMS>
using numeric_static_arrays = 
        boost::mpl::list<pni::core::static_array<pni::core::uint8,DIMS... >,
                         pni::core::static_array<pni::core::uint16,DIMS... >,
                         pni::core::static_array<pni::core::uint32,DIMS... >,
                         pni::core::static_array<pni::core::uint64,DIMS... >,
                         pni::core::static_array<pni::core::int8,DIMS... >,
                         pni::core::static_array<pni::core::int16,DIMS... >,
                         pni::core::static_array<pni::core::int32,DIMS... >,
                         pni::core::static_array<pni::core::int64,DIMS... >,
                         pni::core::static_array<pni::core::float32,DIMS... >,
                         pni::core::static_array<pni::core::float64,DIMS... >,
                         pni::core::static_array<pni::core::float128,DIMS... >,
                         pni::core::static_array<pni::core::complex32,DIMS... >,
                         pni::core::static_array<pni::core::complex64,DIMS... >,
                         pni::core::static_array<pni::core::complex128,DIMS...>>;

template<size_t... DIMS>
using nonnumeric_static_arrays = 
        boost::mpl::list<pni::core::static_array<pni::core::string,DIMS... >,
                         pni::core::static_array<pni::core::bool_t,DIMS... >>;

template<size_t... DIMS>
using all_static_arrays = 
        boost::mpl::joint_view<numeric_static_arrays<DIMS...>,
                               nonnumeric_static_arrays<DIMS...>>;
                         
