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

#include "fixed_rank_dim_layout_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(fixed_rank_dim_layout_test);


//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::setUp() { }

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::tearDown() { }

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_default_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    layout2_type layout; 
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_construction_lvalue()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    index3_type o = {10,2,1},c = {20,100,40},s = {1,1,5};

    layout3_type layout(c,s,o);

    CPPUNIT_ASSERT(check_rank(layout,3));
    //the originals have not been consumed
    CPPUNIT_ASSERT(o.size() == 3);
    CPPUNIT_ASSERT(c.size() == 3);
    CPPUNIT_ASSERT(s.size() == 3);
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_construction_rvalue()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    index3_type o{10,2,1},c{20,100,40},s{1,1,5};

    layout3_type layout(std::move(c),
                        std::move(s),
                        std::move(o));
    
    CPPUNIT_ASSERT(check_rank(layout,3));
   
    //the parameters are now gone
    CPPUNIT_ASSERT(o.size() == 3);
    CPPUNIT_ASSERT(s.size() == 3);
    CPPUNIT_ASSERT(c.size() == 3);
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_construction_init_list()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    layout2_type layout({100,3},{1,1},{10,2});
    
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_move_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    layout2_type layout({100,3},{1,1},{10,2});
    layout2_type layout_2 =std::move(layout);
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_copy_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    layout2_type layout({100,3},{1,1},{10,2});
    layout2_type layout_2 =layout;
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,2));

}
//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_copy_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    layout2_type layout({100,3},{1,1},{10,2});
    layout2_type layout_2;

    CPPUNIT_ASSERT(check_rank(layout_2,2));

    //do copy assignment
    layout_2 = layout;
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_move_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    layout2_type layout({100,3},{1,1},{10,2});
    layout2_type layout_2;

    CPPUNIT_ASSERT(check_rank(layout_2,2));

    //do copy assignment
    layout_2 = std::move(layout);
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_counts_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    index3_type o{10,2,1},c{20,100,40},s{1,1,5};

    layout3_type layout(c,s,o);

    CPPUNIT_ASSERT(std::equal(layout.counts().begin(),
                              layout.counts().end(),
                              c.begin()));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_offset_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    index3_type o{10,2,1},c{20,100,40},s{1,1,5};

    layout3_type layout(c,s,o);

    CPPUNIT_ASSERT(std::equal(layout.offset().begin(),
                              layout.offset().end(),
                              o.begin()));
}

//-----------------------------------------------------------------------------
void fixed_rank_dim_layout_test::test_stride_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    index3_type o{10,2,1},c{20,100,40},s{1,1,5};

    layout3_type layout(c,s,o);

    CPPUNIT_ASSERT(std::equal(layout.stride().begin(),
                              layout.stride().end(),
                              s.begin()));
}
