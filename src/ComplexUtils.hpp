/*
 * Declaration of utilities for complex numbers
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
 *
 * A couple of utility operators and function for complex numbers.
 *
 * Created on: Sep 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

#pragma once

#include "Types.hpp"
#include "TypeInfo.hpp"

using namespace pni::utils;

namespace pni{
namespace utils{

template<typename C,typename O> C __convert(const O &v){
	if(TypeInfo<O>::is_complex){
		return C(v.real(),v.imag());
	}

	return C(v);
};

bool operator==(const Complex32 &a,const Complex64 &b);
bool operator==(const Complex32 &a,const Complex128 &b);

bool operator==(const Complex64 &a,const Complex32 &b);
bool operator==(const Complex64 &a,const Complex128 &b);

bool operator==(const Complex128 &a,const Complex32 &b);
bool operator==(const Complex128 &a,const Complex64 &b);


bool operator!=(const Complex32 &a,const Complex64 &b);
bool operator!=(const Complex32 &a,const Complex128 &b);

bool operator!=(const Complex64 &a,const Complex32 &b);
bool operator!=(const Complex64 &a,const Complex128 &b);

bool operator!=(const Complex128 &a,const Complex32 &b);
bool operator!=(const Complex128 &a,const Complex64 &b);

//end of namespace
}
}
