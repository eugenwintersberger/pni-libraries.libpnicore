//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Apr 7, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <vector>
#include <list>

#include "check_equal_size_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(check_equal_size_test);

//-----------------------------------------------------------------------------
void check_equal_size_test::setUp()
{
    
}

//-----------------------------------------------------------------------------
void check_equal_size_test::tearDown()
{
}

//-----------------------------------------------------------------------------
void check_equal_size_test::test_no_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    std_vector = vector_type(10);

    CPPUNIT_ASSERT(check_equal_size(std_vector,std_array));
    CPPUNIT_ASSERT(check_equal_size(std_vector,sarray_1));

    fdarray_1 = fixed_dim_array<size_t,2>::create(shape_t{4,10});
    CPPUNIT_ASSERT(!check_equal_size(fdarray_1,std_vector));
    CPPUNIT_ASSERT(!check_equal_size(fdarray_1,sarray_1));

}

//-----------------------------------------------------------------------------
void check_equal_size_test::test_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std_vector = vector_type(100);

    CPPUNIT_ASSERT_THROW(check_equal_size(std_vector,std_array,EXCEPTION_RECORD)
                         ,size_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_equal_size(sarray_1,std_vector,EXCEPTION_RECORD),
                         size_mismatch_error);
}

