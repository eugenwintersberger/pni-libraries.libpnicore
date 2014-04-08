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

#include "check_indexes_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(check_indexes_test);

//-----------------------------------------------------------------------------
void check_indexes_test::setUp()
{
    index_1 = {{4}};
    index_2 = {{5,3}};
    index_3 = {{7,3,10}};
}

//-----------------------------------------------------------------------------
void check_indexes_test::tearDown()
{
}

//-----------------------------------------------------------------------------
void check_indexes_test::test_no_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    //check 1D case
    CPPUNIT_ASSERT(check_indexes(vector_type{0},index_1));
    CPPUNIT_ASSERT(check_indexes(vector_type{3},index_1));
    CPPUNIT_ASSERT(!check_indexes(vector_type{4},index_1));
    CPPUNIT_ASSERT(!check_indexes(vector_type{10},index_1));

    // check 2D case
    CPPUNIT_ASSERT(check_indexes(vector_type{2,1},index_2));
    CPPUNIT_ASSERT(check_indexes(vector_type{4,2},index_2));
    CPPUNIT_ASSERT(!check_indexes(vector_type{10,10},index_2));
    CPPUNIT_ASSERT(!check_indexes(vector_type{10,2},index_2));
    CPPUNIT_ASSERT(!check_indexes(vector_type{3,5},index_2));

    // check the 3D case
    CPPUNIT_ASSERT(check_indexes(vector_type{0,0,0},index_3));
    CPPUNIT_ASSERT(!check_indexes(vector_type{7,0,0},index_3));
    CPPUNIT_ASSERT(!check_indexes(vector_type{0,3,0},index_3));
    CPPUNIT_ASSERT(!check_indexes(vector_type{0,0,10},index_3));

    // check different ranks
    CPPUNIT_ASSERT(!check_indexes(vector_type{2},index_3));
    CPPUNIT_ASSERT(!check_indexes(vector_type{3,2},index_1));

}

//-----------------------------------------------------------------------------
void check_indexes_test::test_throw()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //check 1D case
    CPPUNIT_ASSERT_NO_THROW(check_indexes(vector_type{0},index_1,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_NO_THROW(check_indexes(vector_type{3},index_1,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{4},index_1,EXCEPTION_RECORD),
                         index_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{10},index_1,EXCEPTION_RECORD),
                         index_error);

    // check 2D case
    CPPUNIT_ASSERT_NO_THROW(check_indexes(vector_type{2,1},index_2,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_NO_THROW(check_indexes(vector_type{4,2},index_2,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{10,10},index_2,EXCEPTION_RECORD),
                         index_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{10,2},index_2,EXCEPTION_RECORD),
                         index_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{3,5},index_2,EXCEPTION_RECORD),
                         index_error);
    
    // check the 3D case
    CPPUNIT_ASSERT_NO_THROW(check_indexes(vector_type{0,0,0},index_3,EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{7,0,0},index_3,EXCEPTION_RECORD),
                         index_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{0,3,0},index_3,EXCEPTION_RECORD),
                         index_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{0,0,10},index_3,EXCEPTION_RECORD),
                         index_error);

    // check different ranks
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{2},index_3,EXCEPTION_RECORD),
                         shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{3,2},index_1,EXCEPTION_RECORD),
                         shape_mismatch_error);
}

//-----------------------------------------------------------------------------
void check_indexes_test::test_invalid_input()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(check_indexes(vector_type(),vector_type()));
    CPPUNIT_ASSERT_NO_THROW(check_indexes(vector_type(),vector_type(),EXCEPTION_RECORD));
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type(),index_3,EXCEPTION_RECORD),
                         shape_mismatch_error);
    CPPUNIT_ASSERT_THROW(check_indexes(vector_type{2,2},vector_type(),EXCEPTION_RECORD),
                         shape_mismatch_error);
}

