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

#include "div_operator_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<UInt8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Int8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<UInt16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Int16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<UInt32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Int32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<UInt64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Int64> >);

CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Float32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Float64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Float128> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Complex32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Complex64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(div_operator_test<DArray<Complex128> >);

#define SARRAY_DIV_TEST_REG(T,NX,NY,NZ)\
static CPPUNIT_NS::AutoRegisterSuite< div_operator_test<SArray<T,NX,NY,NZ> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

SARRAY_DIV_TEST_REG(UInt8,2,3,4);
SARRAY_DIV_TEST_REG(Int8,2,3,4);
SARRAY_DIV_TEST_REG(UInt16,2,3,4);
SARRAY_DIV_TEST_REG(Int16,2,3,4);
SARRAY_DIV_TEST_REG(UInt32,2,3,4);
SARRAY_DIV_TEST_REG(Int32,2,3,4);
SARRAY_DIV_TEST_REG(UInt64,2,3,4);
SARRAY_DIV_TEST_REG(Int64,2,3,4);

SARRAY_DIV_TEST_REG(Float32,2,3,4);
SARRAY_DIV_TEST_REG(Float64,2,3,4);
SARRAY_DIV_TEST_REG(Float128,2,3,4);

SARRAY_DIV_TEST_REG(Complex32,2,3,4);
SARRAY_DIV_TEST_REG(Complex64,2,3,4);
SARRAY_DIV_TEST_REG(Complex128,2,3,4);


