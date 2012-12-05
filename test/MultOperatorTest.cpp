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

#include "MultOperatorTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<UInt32>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<UInt64>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(MultOperatorTest<Complex128>);



