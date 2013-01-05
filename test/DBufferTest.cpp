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
 *  Created on: Jul 19, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include "DBufferTest.hpp"


#define BUFFER_TEST_REGISTRATION(VTYPE,ALLOC)\
static CPPUNIT_NS::AutoRegisterSuite< DBufferTest<VTYPE,ALLOC> >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

BUFFER_TEST_REGISTRATION(Int8,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt8,NewAllocator);
BUFFER_TEST_REGISTRATION(Int16,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt16,NewAllocator);
BUFFER_TEST_REGISTRATION(Int32,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt32,NewAllocator);
BUFFER_TEST_REGISTRATION(Int64,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt64,NewAllocator);

BUFFER_TEST_REGISTRATION(Float32,NewAllocator);
BUFFER_TEST_REGISTRATION(Float64,NewAllocator);
BUFFER_TEST_REGISTRATION(Float128,NewAllocator);

BUFFER_TEST_REGISTRATION(Complex32,NewAllocator);
BUFFER_TEST_REGISTRATION(Complex64,NewAllocator);
BUFFER_TEST_REGISTRATION(Complex128,NewAllocator);

BUFFER_TEST_REGISTRATION(Binary,NewAllocator);

