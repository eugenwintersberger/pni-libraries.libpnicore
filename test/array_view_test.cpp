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

//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<SArray<UInt16,NX,NY> >);

#define SARRAY_VIEW_TEST_REG(T,NX,NY)\
static CPPUNIT_NS::AutoRegisterSuite< array_view_test<SArray<T,NX,NY> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

SARRAY_VIEW_TEST_REG(UInt8,NX,NY);
SARRAY_VIEW_TEST_REG(Int8,NX,NY);
SARRAY_VIEW_TEST_REG(UInt16,NX,NY);
SARRAY_VIEW_TEST_REG(Int16,NX,NY);
SARRAY_VIEW_TEST_REG(UInt32,NX,NY);
SARRAY_VIEW_TEST_REG(Int32,NX,NY);
SARRAY_VIEW_TEST_REG(UInt64,NX,NY);
SARRAY_VIEW_TEST_REG(Int64,NX,NY);
SARRAY_VIEW_TEST_REG(Float32,NX,NY);
SARRAY_VIEW_TEST_REG(Float64,NX,NY);
SARRAY_VIEW_TEST_REG(Float128,NX,NY);
SARRAY_VIEW_TEST_REG(Complex32,NX,NY);
SARRAY_VIEW_TEST_REG(Complex64,NX,NY);
SARRAY_VIEW_TEST_REG(Complex128,NX,NY);
SARRAY_VIEW_TEST_REG(String,NX,NY);
SARRAY_VIEW_TEST_REG(Bool,NX,NY);








