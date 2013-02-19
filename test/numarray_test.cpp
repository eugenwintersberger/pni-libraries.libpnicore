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
 *  Created on: Jul 23, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <pni/core/math/mt_inplace_arithmetics.hpp>

#include "numarray_test.hpp"

using namespace pni::core;

#define NUMARRAY_TEST_REGISTRATION(ATYPE,VTYPE,IPAT,MT)\
static CPPUNIT_NS::AutoRegisterSuite< numarray_test<ATYPE<VTYPE>,IPAT,MT > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

NUMARRAY_TEST_REGISTRATION(darray,uint8,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,int8,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,uint16,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,int16,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,uint32,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,int32,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,uint64,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,int64,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,float32,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,float64,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,float128,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,complex32,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,complex64,inplace_arithmetics,false);
NUMARRAY_TEST_REGISTRATION(darray,complex128,inplace_arithmetics,false);

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



