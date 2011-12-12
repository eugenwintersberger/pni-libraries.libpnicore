/*
 * Declaration of template class TypeInfo
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * type_conversion.cpp
 *
 *  Created on: Dec 10, 2011
 *      Author: Eugen Wintersberger
 */

#include "type_conversion.hpp"
#include "PNITypes.hpp"

namespace pni{
namespace utils{

COMPLEX_CONVERT_TYPE(Float32,Float64);
COMPLEX_CONVERT_TYPE(Float32,Float128);
COMPLEX_CONVERT_TYPE(Float64,Float32);
COMPLEX_CONVERT_TYPE(Float64,Float128);
COMPLEX_CONVERT_TYPE(Float128,Float32);
COMPLEX_CONVERT_TYPE(Float128,Float64);

//end of namespace
}
}

