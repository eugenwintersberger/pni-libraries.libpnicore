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
//  Created on: Feb 28, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include "static_dim_layout.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(static_dim_layout_test);


//-----------------------------------------------------------------------------
void static_dim_layout_test::setUp() { }

//-----------------------------------------------------------------------------
void static_dim_layout_test::tearDown() { }

//-----------------------------------------------------------------------------
void static_dim_layout_test::test_counts_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    index3_type o = {0,0,0},c = {2,3,4},s = {1,1,1};

    layout3_type layout;

    CPPUNIT_ASSERT(std::equal(layout.counts().begin(),
                              layout.counts().end(),
                              c.begin()));
}

//-----------------------------------------------------------------------------
void static_dim_layout_test::test_offset_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    index3_type o = {0,0,0},c = {2,3,4},s = {1,1,1};

    layout3_type layout;

    CPPUNIT_ASSERT(std::equal(layout.offset().begin(),
                              layout.offset().end(),
                              o.begin()));
}

//-----------------------------------------------------------------------------
void static_dim_layout_test::test_stride_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    index3_type o = {0,0,0},c = {2,3,4},s = {1,1,1};

    layout3_type layout;

    CPPUNIT_ASSERT(std::equal(layout.stride().begin(),
                              layout.stride().end(),
                              s.begin()));
}
