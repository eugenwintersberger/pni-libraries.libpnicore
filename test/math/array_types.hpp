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
//  Created on: Nov 27, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/joint_view.hpp>


typedef boost::mpl::list<
                         pni::core::dynamic_array<pni::core::int8>,
                         pni::core::dynamic_array<pni::core::int16>,
                         pni::core::dynamic_array<pni::core::int32>,
                         pni::core::dynamic_array<pni::core::int64>,
                         pni::core::dynamic_array<pni::core::uint8>,
                         pni::core::dynamic_array<pni::core::uint16>,
                         pni::core::dynamic_array<pni::core::uint32>,
                         pni::core::dynamic_array<pni::core::uint64>,
                         pni::core::dynamic_array<pni::core::float32>,
                         pni::core::dynamic_array<pni::core::float64>,
                         pni::core::dynamic_array<pni::core::float128>,
                         pni::core::dynamic_array<pni::core::complex32>,
                         pni::core::dynamic_array<pni::core::complex64>,
                         pni::core::dynamic_array<pni::core::complex128>
                        > dyn_array_types;

typedef boost::mpl::list<
                         pni::core::fixed_dim_array<pni::core::int8,3>,
                         pni::core::fixed_dim_array<pni::core::int16,3>,
                         pni::core::fixed_dim_array<pni::core::int32,3>,
                         pni::core::fixed_dim_array<pni::core::int64,3>,
                         pni::core::fixed_dim_array<pni::core::uint8,3>,
                         pni::core::fixed_dim_array<pni::core::uint16,3>,
                         pni::core::fixed_dim_array<pni::core::uint32,3>,
                         pni::core::fixed_dim_array<pni::core::uint64,3>,
                         pni::core::fixed_dim_array<pni::core::float32,3>,
                         pni::core::fixed_dim_array<pni::core::float64,3>,
                         pni::core::fixed_dim_array<pni::core::float128,3>,
                         pni::core::fixed_dim_array<pni::core::complex32,3>,
                         pni::core::fixed_dim_array<pni::core::complex64,3>,
                         pni::core::fixed_dim_array<pni::core::complex128,3>
                        > fixed_dim_array_types;

typedef boost::mpl::list<
                         pni::core::static_array<pni::core::int8,2,3,4>,
                         pni::core::static_array<pni::core::int16,2,3,4>,
                         pni::core::static_array<pni::core::int32,2,3,4>,
                         pni::core::static_array<pni::core::int64,2,3,4>,
                         pni::core::static_array<pni::core::uint8,2,3,4>,
                         pni::core::static_array<pni::core::uint16,2,3,4>,
                         pni::core::static_array<pni::core::uint32,2,3,4>,
                         pni::core::static_array<pni::core::uint64,2,3,4>,
                         pni::core::static_array<pni::core::float32,2,3,4>,
                         pni::core::static_array<pni::core::float64,2,3,4>,
                         pni::core::static_array<pni::core::float128,2,3,4>,
                         pni::core::static_array<pni::core::complex32,2,3,4>,
                         pni::core::static_array<pni::core::complex64,2,3,4>,
                         pni::core::static_array<pni::core::complex128,2,3,4>
                        > static_array_types;

typedef boost::mpl::joint_view<
                               boost::mpl::joint_view<dyn_array_types,
                                                      fixed_dim_array_types>,
                               static_array_types> all_array_types;

