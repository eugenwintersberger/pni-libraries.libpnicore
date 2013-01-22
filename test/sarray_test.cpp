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

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "sarray_test.hpp"

using namespace pni::core;

#define STATICARRAY_TEST_REGISTRATION(T)\
static CPPUNIT_NS::AutoRegisterSuite< sarray_test<T> >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

STATICARRAY_TEST_REGISTRATION(UInt8);
STATICARRAY_TEST_REGISTRATION(Int8);
STATICARRAY_TEST_REGISTRATION(UInt16);
STATICARRAY_TEST_REGISTRATION(Int16);
STATICARRAY_TEST_REGISTRATION(UInt32);
STATICARRAY_TEST_REGISTRATION(Int32);
STATICARRAY_TEST_REGISTRATION(UInt64);
STATICARRAY_TEST_REGISTRATION(Int64);

STATICARRAY_TEST_REGISTRATION(Float32);
STATICARRAY_TEST_REGISTRATION(Float64);
STATICARRAY_TEST_REGISTRATION(Float128);

STATICARRAY_TEST_REGISTRATION(Complex32);
STATICARRAY_TEST_REGISTRATION(Complex64);
STATICARRAY_TEST_REGISTRATION(Complex128);

STATICARRAY_TEST_REGISTRATION(String);
STATICARRAY_TEST_REGISTRATION(Bool);


