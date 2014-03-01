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
