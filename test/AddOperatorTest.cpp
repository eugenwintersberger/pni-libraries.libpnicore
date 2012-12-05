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
 *  Created on: Jul 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include "AddOperatorTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<UInt32>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<UInt64>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(AddOperatorTest<Complex128>);



