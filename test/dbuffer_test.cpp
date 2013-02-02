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
#include "dbuffer_test.hpp"


#define BUFFER_TEST_REGISTRATION(VTYPE,ALLOC)\
static CPPUNIT_NS::AutoRegisterSuite< dbuffer_test<VTYPE,ALLOC> >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

BUFFER_TEST_REGISTRATION(int8,new_allocator);
BUFFER_TEST_REGISTRATION(uint8,new_allocator);
BUFFER_TEST_REGISTRATION(int16,new_allocator);
BUFFER_TEST_REGISTRATION(uint16,new_allocator);
BUFFER_TEST_REGISTRATION(int32,new_allocator);
BUFFER_TEST_REGISTRATION(uint32,new_allocator);
BUFFER_TEST_REGISTRATION(int64,new_allocator);
BUFFER_TEST_REGISTRATION(uint64,new_allocator);

BUFFER_TEST_REGISTRATION(float32,new_allocator);
BUFFER_TEST_REGISTRATION(float64,new_allocator);
BUFFER_TEST_REGISTRATION(float128,new_allocator);

BUFFER_TEST_REGISTRATION(complex32,new_allocator);
BUFFER_TEST_REGISTRATION(complex64,new_allocator);
BUFFER_TEST_REGISTRATION(complex128,new_allocator);

BUFFER_TEST_REGISTRATION(binary,new_allocator);
BUFFER_TEST_REGISTRATION(bool,new_allocator);
BUFFER_TEST_REGISTRATION(string,new_allocator);

