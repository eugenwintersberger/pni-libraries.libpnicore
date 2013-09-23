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


#define DYNAMICARRAY_TEST_REGISTRATION(T,BT)\
static CPPUNIT_NS::AutoRegisterSuite< darray_test<T,BT > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

DYNAMICARRAY_TEST_REGISTRATION(uint8,std::vector<uint8>);
DYNAMICARRAY_TEST_REGISTRATION(int8,std::vector<int8>);
DYNAMICARRAY_TEST_REGISTRATION(uint16,std::vector<uint16>);
DYNAMICARRAY_TEST_REGISTRATION(int16,std::vector<int16>);
DYNAMICARRAY_TEST_REGISTRATION(uint32,std::vector<uint32>);
DYNAMICARRAY_TEST_REGISTRATION(int32,std::vector<int32>);
DYNAMICARRAY_TEST_REGISTRATION(uint64,std::vector<uint64>);
DYNAMICARRAY_TEST_REGISTRATION(int64,std::vector<int64>);
DYNAMICARRAY_TEST_REGISTRATION(float32,std::vector<float32>);
DYNAMICARRAY_TEST_REGISTRATION(float64,std::vector<float64>);
DYNAMICARRAY_TEST_REGISTRATION(float128,std::vector<float128>);
DYNAMICARRAY_TEST_REGISTRATION(complex32,std::vector<complex32>);
DYNAMICARRAY_TEST_REGISTRATION(complex64,std::vector<complex64>);
DYNAMICARRAY_TEST_REGISTRATION(complex128,std::vector<complex128>);
//DYNAMICARRAY_TEST_REGISTRATION(bool,std::vector<bool>);
DYNAMICARRAY_TEST_REGISTRATION(string,std::vector<string>);


