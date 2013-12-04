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

#include "mult_operator_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<uint8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<int8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<uint16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<int16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<uint32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<int32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<uint64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<int64> >);

CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<float32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<float64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<float128> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<complex32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<complex64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<dynamic_array<complex128> >);



