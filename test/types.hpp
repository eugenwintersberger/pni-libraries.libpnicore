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
//************************************************************************
//
//  Created on: Oct 27, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/core/types.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<pni::core::uint8,
                         pni::core::uint16,
                         pni::core::uint32,
                         pni::core::uint64,
                         pni::core::int8,
                         pni::core::int16,
                         pni::core::int32,
                         pni::core::int64,
                         pni::core::float32,
                         pni::core::float64,
                         pni::core::float128,
                         pni::core::complex32,
                         pni::core::complex64,
                         pni::core::complex128>
                         numeric_types;

typedef boost::mpl::list<pni::core::bool_t,
                         pni::core::string,
                         pni::core::binary>
                         non_numeric_types;

typedef boost::mpl::joint_view<numeric_types,non_numeric_types>
                              all_types;

