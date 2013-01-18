/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Sep 02, 2011
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<iostream>
#include<typeinfo>

#include<cppunit/extensions/HelperMacros.h>

#include "scalar_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<UInt16>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<UInt32>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<UInt64>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Float128>);

CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(scalar_test<Complex128>);




