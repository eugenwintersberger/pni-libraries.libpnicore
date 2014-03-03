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
 *  Created on: Nov 07, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <list>
#include <vector>
#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "container_utils_array_test.hpp"

template<typename T>
using array_type = std::array<T,4>;

template<typename T> 
using array_test = container_utils_array_test<array_type<T>>;


CPPUNIT_TEST_SUITE_REGISTRATION(array_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<complex128>);

