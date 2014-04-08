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
//  Created on: Apr 8, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <vector>
#include <list>

#include "check_index_in_dim_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(check_index_in_dim_test);

//-----------------------------------------------------------------------------
void check_index_in_dim_test::setUp()
{
    
}

//-----------------------------------------------------------------------------
void check_index_in_dim_test::tearDown()
{
}

//-----------------------------------------------------------------------------
void check_index_in_dim_test::test_no_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(check_index_in_dim(0,100));
    CPPUNIT_ASSERT(check_index_in_dim(10,100));
    CPPUNIT_ASSERT(check_index_in_dim(99,100));
    CPPUNIT_ASSERT(!check_index_in_dim(100,100));
    CPPUNIT_ASSERT(!check_index_in_dim(101,100));

}

//-----------------------------------------------------------------------------
void check_index_in_dim_test::test_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_NO_THROW(check_index_in_dim(0,100,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_NO_THROW(check_index_in_dim(10,100,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_NO_THROW(check_index_in_dim(99,100,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_index_in_dim(100,100,EXCEPTION_RECORD),
                         index_error);
    CPPUNIT_ASSERT_THROW(check_index_in_dim(101,100,EXCEPTION_RECORD),
                         index_error);
}

