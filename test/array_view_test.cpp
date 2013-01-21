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
 *  Created on: May 14, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/current_function.hpp>

#include <pni/core/DArray.hpp>
#include <pni/core/DBuffer.hpp>
#include <pni/core/ArrayOperations.hpp>

#include "array_view_test.hpp"

using namespace pni::core;

typedef SArray<UInt16,NX,NY> sarray_type;

CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<UInt8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Int8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<UInt16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Int16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<UInt32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Int32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<UInt64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Int64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Float32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Float64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Float128> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Complex32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Complex64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Complex128> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<String> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<DArray<Bool> >);

CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<sarray_type>);







