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
//=============================================================================
//
//  Created on: Jan 8, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include "dim_algorithm_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(dim_algorithm_test);


//-----------------------------------------------------------------------------
void dim_algorithm_test::setUp() 
{ 
    layout1 = layout_type({2,2,3},{1,1,1},{1,1,0});
    layout2 = layout_type({4,2,1},{1,4,2},{0,1,3});
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::tearDown() { }

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_span()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(span(layout1) == 12);
    CPPUNIT_ASSERT(span(layout2) == 4*(2+3)*(1));
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_size()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(size(layout1) == 12);
    CPPUNIT_ASSERT(size(layout2) == 8);
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_rank()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(rank(layout1) == 3);
    CPPUNIT_ASSERT(rank(layout2) == 3);
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_effective_rank()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(effective_rank(layout1) == 3);
    CPPUNIT_ASSERT(effective_rank(layout2) == 2);
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_is_compact()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(is_compact(layout1));
    CPPUNIT_ASSERT(!is_compact(layout2));
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_effective_shape()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s1 = effective_shape<vector_type>(layout1);
    auto s2 = effective_shape<vector_type>(layout2);

    CPPUNIT_ASSERT(s1.size() == 3);
    CPPUNIT_ASSERT(s1[0] == 2);
    CPPUNIT_ASSERT(s1[1] == 2);
    CPPUNIT_ASSERT(s1[2] == 3);

    CPPUNIT_ASSERT(s2.size() == 2);
    CPPUNIT_ASSERT(s2[0] == 4);
    CPPUNIT_ASSERT(s2[1] == 2);

}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_shape()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    auto s1 = shape<vector_type>(layout1);
    auto s2 = shape<vector_type>(layout2);
    
    CPPUNIT_ASSERT(s1.size() == 3);
    CPPUNIT_ASSERT(s1[0] == 2);
    CPPUNIT_ASSERT(s1[1] == 2);
    CPPUNIT_ASSERT(s1[2] == 3);
    
    CPPUNIT_ASSERT(s2.size() == 3);
    CPPUNIT_ASSERT(s2[0] == 4);
    CPPUNIT_ASSERT(s2[1] == 2);
    CPPUNIT_ASSERT(s2[2] == 1);
}

//-----------------------------------------------------------------------------
void dim_algorithm_test::test_expand_index()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_type i1{1,1,0};
    vector_type e1(3);

    expand_index(layout1,i1,e1);
    CPPUNIT_ASSERT(e1[0] == 2);
    CPPUNIT_ASSERT(e1[1] == 2);
    CPPUNIT_ASSERT(e1[2] == 0);

    e1 = vector_type(2);
    CPPUNIT_ASSERT_THROW(expand_index(layout1,i1,e1),shape_mismatch_error);
    i1 = vector_type(2);
    CPPUNIT_ASSERT_THROW(expand_index(layout1,i1,e1),shape_mismatch_error);
}
