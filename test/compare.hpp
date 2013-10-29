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
 *  Created on: Oct 29, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <type_traits>
#include <complex>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/array.hpp>
#include <pni/core/id_type_map.hpp>

using namespace pni::core;

/*!
\brief compare integers and strings

This template function compares two values which are integers and strings. 
*/
template<typename T> 
void compare(T &&a,T &&b,
             typename std::enable_if<!std::is_floating_point<T>::value,T>::type* =0)
{
    CPPUNIT_ASSERT(a==b);
}


/*!
\brief compare floats

This function compares floating points values.
*/
template<typename T > 
void compare(T &&a,T &&b,
        typename std::enable_if<std::is_floating_point<T>::value,T>::type* =0)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-12);
}

template<typename T>
void compare(std::complex<T> &&a,std::complex<T> &&b)
{
    compare(a.real,b.real);
    compare(a.imag,b.imag);
}


void compare(const value_ref &a,const value_ref &b);
void compare(const value &a,const value &b);

