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


CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<uint8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<int8> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<uint16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<int16> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<uint32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<int32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<uint64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<int64> >);

CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<float32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<float64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<float128> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<complex32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<complex64> >);
CPPUNIT_TEST_SUITE_REGISTRATION(mult_operator_test<darray<complex128> >);


#define SARRAY_MULT_TEST_REG(T,NX,NY,NZ)\
static CPPUNIT_NS::AutoRegisterSuite< mult_operator_test<sarray<T,NX,NY,NZ> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

SARRAY_MULT_TEST_REG(uint8,2,3,4);
SARRAY_MULT_TEST_REG(int8,2,3,4);
SARRAY_MULT_TEST_REG(uint16,2,3,4);
SARRAY_MULT_TEST_REG(int16,2,3,4);
SARRAY_MULT_TEST_REG(uint32,2,3,4);
SARRAY_MULT_TEST_REG(int32,2,3,4);
SARRAY_MULT_TEST_REG(uint64,2,3,4);
SARRAY_MULT_TEST_REG(int64,2,3,4);

SARRAY_MULT_TEST_REG(float32,2,3,4);
SARRAY_MULT_TEST_REG(float64,2,3,4);
SARRAY_MULT_TEST_REG(float128,2,3,4);

SARRAY_MULT_TEST_REG(complex32,2,3,4);
SARRAY_MULT_TEST_REG(complex64,2,3,4);
SARRAY_MULT_TEST_REG(complex128,2,3,4);

