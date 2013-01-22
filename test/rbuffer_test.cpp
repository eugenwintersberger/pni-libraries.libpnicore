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
#include "rbuffer_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<UInt16>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<UInt32>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<UInt64>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Float128>);

CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Complex128>);

CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Binary>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<Bool>);
CPPUNIT_TEST_SUITE_REGISTRATION(rbuffer_test<String>);
