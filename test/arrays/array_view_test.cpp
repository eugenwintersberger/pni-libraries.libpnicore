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

#include "array_view_test.hpp"



template<typename T> using dyn_array_view_test = array_view_test<dynamic_array<T> >;

CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<uint16>);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<int8> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<uint16> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<int16> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<uint32> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<int32> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<uint64> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<int64> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<float32> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<float64> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<float128> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<complex32> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<complex64> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<complex128> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<string> >);
//CPPUNIT_TEST_SUITE_REGISTRATION(array_view_test<darray<bool> >);


#define SARRAY_VIEW_TEST_REG(T,NX,NY)\
static CPPUNIT_NS::AutoRegisterSuite< array_view_test<sarray<T,NX,NY> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )
//
//SARRAY_VIEW_TEST_REG(uint8,NX,NY);
//SARRAY_VIEW_TEST_REG(int8,NX,NY);
//SARRAY_VIEW_TEST_REG(uint16,NX,NY);
//SARRAY_VIEW_TEST_REG(int16,NX,NY);
//SARRAY_VIEW_TEST_REG(uint32,NX,NY);
//SARRAY_VIEW_TEST_REG(int32,NX,NY);
//SARRAY_VIEW_TEST_REG(uint64,NX,NY);
//SARRAY_VIEW_TEST_REG(int64,NX,NY);
//SARRAY_VIEW_TEST_REG(float32,NX,NY);
//SARRAY_VIEW_TEST_REG(float64,NX,NY);
//SARRAY_VIEW_TEST_REG(float128,NX,NY);
//SARRAY_VIEW_TEST_REG(complex32,NX,NY);
//SARRAY_VIEW_TEST_REG(complex64,NX,NY);
//SARRAY_VIEW_TEST_REG(complex128,NX,NY);
//SARRAY_VIEW_TEST_REG(string,NX,NY);
//SARRAY_VIEW_TEST_REG(bool,NX,NY);








