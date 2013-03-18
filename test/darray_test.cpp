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
 *  Created on: Jul 20, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "darray_test.hpp"

using namespace pni::core;

#define DYNAMICARRAY_TEST_REGISTRATION(T,BT,ALLOC)\
static CPPUNIT_NS::AutoRegisterSuite< darray_test<T,BT<T,ALLOC> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

DYNAMICARRAY_TEST_REGISTRATION(uint8,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(int8,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(uint16,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(int16,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(uint32,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(int32,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(uint64,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(int64,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(float32,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(float64,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(float128,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(complex32,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(complex64,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(complex128,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(bool,dbuffer,new_allocator);
DYNAMICARRAY_TEST_REGISTRATION(string,dbuffer,new_allocator);
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



