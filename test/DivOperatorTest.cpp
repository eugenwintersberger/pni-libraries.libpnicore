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
 *  Created on: Jul 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include "DivOperatorTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<UInt32>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<UInt64>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(DivOperatorTest<Complex128>);



