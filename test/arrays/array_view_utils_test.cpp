//!
//! (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//!  Created on: Apr 6, 2014
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!/
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/current_function.hpp>

#include "array_view_utils_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_view_utils_test);

void array_view_utils_test::setUp()
{
}

//-----------------------------------------------------------------------------
void array_view_utils_test::tearDown()
{
}

//-----------------------------------------------------------------------------
void array_view_utils_test::test_is_index_type()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_index_type<int>::value);
    CPPUNIT_ASSERT(!is_index_type<std::vector<size_t>>::value);
    CPPUNIT_ASSERT(is_index_type<slice>::value);
    CPPUNIT_ASSERT(is_index_type<size_t>::value);
    CPPUNIT_ASSERT(!is_index_type<float64>::value);
}

//-----------------------------------------------------------------------------
void array_view_utils_test::test_is_index_types()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef is_index_types<int,slice,size_t> type_1;
    CPPUNIT_ASSERT(type_1::value);

    typedef is_index_types<int,float32> type_2;
    CPPUNIT_ASSERT(!type_2::value);

    typedef is_index_types<size_t> type_3;
    CPPUNIT_ASSERT(type_3::value);

    typedef is_index_types<std::vector<size_t>> type_4;
    CPPUNIT_ASSERT(!type_4::value);
}








