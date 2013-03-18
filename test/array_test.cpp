/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jan 12, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/arrays.hpp>
#include <pni/core/scalar.hpp>
#include "array_test.hpp"

typedef sarray<uint32,3,2> sarray_t;
typedef numarray<darray<float64> > narray_t;
typedef scalar<int64> scalar_t;

CPPUNIT_TEST_SUITE_REGISTRATION(array_test<darray<float32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<darray<string> >);
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<sarray_t> );
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<narray_t> );
CPPUNIT_TEST_SUITE_REGISTRATION(array_test<scalar_t>);

//-------------------------------------------------------------
void create_object(darray<string> &o)
{
    o = darray<string>(shape_t{2});
    o[0] = "hello"; o[1] = "world";
}
