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
//  Created on: Oct 16, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <pni/core/types.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>
#include <pni/core/arrays.hpp>


template<typename T> using sarray = pni::core::static_array<T,3,2>;
template<typename T> using farray = pni::core::fixed_dim_array<T,2>;

typedef boost::mpl::list<pni::core::dynamic_array<pni::core::uint8>,
                         pni::core::dynamic_array<pni::core::int8>,
                         pni::core::dynamic_array<pni::core::uint16>,
                         pni::core::dynamic_array<pni::core::int16>,
                         pni::core::dynamic_array<pni::core::uint32>,
                         pni::core::dynamic_array<pni::core::int32>,
                         pni::core::dynamic_array<pni::core::uint64>,
                         pni::core::dynamic_array<pni::core::int64>,
                         pni::core::dynamic_array<pni::core::float32>,
                         pni::core::dynamic_array<pni::core::float64>,
                         pni::core::dynamic_array<pni::core::float128>,
                         pni::core::dynamic_array<pni::core::complex32>,
                         pni::core::dynamic_array<pni::core::complex64>,
                         pni::core::dynamic_array<pni::core::complex128>,
                         pni::core::dynamic_array<pni::core::string>,
                         pni::core::dynamic_array<pni::core::bool_t>
                         > dyn_array_types; 

typedef boost::mpl::list<sarray<pni::core::uint8>,
                         sarray<pni::core::int8>,
                         sarray<pni::core::uint16>,
                         sarray<pni::core::int16>,
                         sarray<pni::core::uint32>,
                         sarray<pni::core::int32>,
                         sarray<pni::core::uint64>,
                         sarray<pni::core::int64>,
                         sarray<pni::core::float32>,
                         sarray<pni::core::float64>,
                         sarray<pni::core::float128>,
                         sarray<pni::core::complex32>,
                         sarray<pni::core::complex64>,
                         sarray<pni::core::complex128>,
                         sarray<pni::core::string>,
                         sarray<pni::core::bool_t>
                        > stat_array_types;

typedef boost::mpl::list<farray<pni::core::uint8>,
                         farray<pni::core::int8>,
                         farray<pni::core::uint16>,
                         farray<pni::core::int16>,
                         farray<pni::core::uint32>,
                         farray<pni::core::int32>,
                         farray<pni::core::uint64>,
                         farray<pni::core::int64>,
                         farray<pni::core::float32>,
                         farray<pni::core::float64>,
                         farray<pni::core::float128>,
                         farray<pni::core::complex32>,
                         farray<pni::core::complex64>,
                         farray<pni::core::complex128>,
                         farray<pni::core::string>,
                         farray<pni::core::bool_t>
                        > fix_array_types;

typedef boost::mpl::joint_view<
                              boost::mpl::joint_view<dyn_array_types,
                                                     stat_array_types>,
                              fix_array_types> all_array_types;
