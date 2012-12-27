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
 *  Created on: Jul 23, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <pni/utils/mth_inplace_arithmetics.hpp>

#include "NumArrayTest.hpp"

using namespace pni::utils;

#define NUMARRAY_TEST_REGISTRATION(ATYPE,VTYPE,IPAT)\
static CPPUNIT_NS::AutoRegisterSuite< NumArrayTest<ATYPE<VTYPE>,IPAT > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

NUMARRAY_TEST_REGISTRATION(DArray,UInt8,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Int8,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,UInt16,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Int16,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,UInt32,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Int32,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,UInt64,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Int64,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Float32,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Float64,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Float128,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Complex32,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Complex64,inplace_arithmetics);
NUMARRAY_TEST_REGISTRATION(DArray,Complex128,inplace_arithmetics);

//NUMARRAY_TEST_REGISTRATION(DArray,UInt8,mth_inplace_arithmetics);
/*
ARRAY_TEST_REGISTRATION(UInt8,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int8,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(UInt16,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int16,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(UInt32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(UInt64,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int64,RefBuffer,NewAllocator);

ARRAY_TEST_REGISTRATION(Float32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Float64,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Float128,RefBuffer,NewAllocator);

ARRAY_TEST_REGISTRATION(Complex32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Complex64,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Complex128,RefBuffer,NewAllocator);
*/



