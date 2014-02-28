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

#include "default_dim_layout_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(default_dim_layout_test);

//-----------------------------------------------------------------------------
bool default_dim_layout_test::check_rank(const default_dim_layout &l,size_t r)
{
    if (l.stride().size() != r) return false;
    if (l.offset().size() != r) return false;
    if (l.counts().size() != r) return false;

    return true;
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::setUp() { }

//-----------------------------------------------------------------------------
void default_dim_layout_test::tearDown() { }

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_default_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    default_dim_layout layout; 
    CPPUNIT_ASSERT(check_rank(layout,0));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_construction_lvalue()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    vector_type o{10,2,1},c{20,100,40},s{1,1,5};

    default_dim_layout layout(c,s,o);

    CPPUNIT_ASSERT(check_rank(layout,3));
    //the originals have not been consumed
    CPPUNIT_ASSERT(o.size() == 3);
    CPPUNIT_ASSERT(c.size() == 3);
    CPPUNIT_ASSERT(s.size() == 3);
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_construction_rvalue()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_type o{10,2,1},c{20,100,40},s{1,1,5};

    default_dim_layout layout(std::move(c),
                              std::move(s),
                              std::move(o));
    
    CPPUNIT_ASSERT(check_rank(layout,3));
   
    //the parameters are now gone
    CPPUNIT_ASSERT(o.size() == 0);
    CPPUNIT_ASSERT(s.size() == 0);
    CPPUNIT_ASSERT(c.size() == 0);
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_construction_init_list()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    default_dim_layout layout({100,3},{1,1},{10,2});
    
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_move_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    default_dim_layout layout({100,3},{1,1},{10,2});
    default_dim_layout layout_2 =std::move(layout);
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,0));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_copy_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    default_dim_layout layout({100,3},{1,1},{10,2});
    default_dim_layout layout_2 =layout;
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,2));

}
//-----------------------------------------------------------------------------
void default_dim_layout_test::test_copy_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    default_dim_layout layout({100,3},{1,1},{10,2});
    default_dim_layout layout_2;

    CPPUNIT_ASSERT(check_rank(layout_2,0));

    //do copy assignment
    layout_2 = layout;
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,2));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_move_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    default_dim_layout layout({100,3},{1,1},{10,2});
    default_dim_layout layout_2;

    CPPUNIT_ASSERT(check_rank(layout_2,0));

    //do copy assignment
    layout_2 = std::move(layout);
    
    CPPUNIT_ASSERT(check_rank(layout_2,2));
    CPPUNIT_ASSERT(check_rank(layout,0));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_counts_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    vector_type o{10,2,1},c{20,100,40},s{1,1,5};

    default_dim_layout layout(c,s,o);

    CPPUNIT_ASSERT(std::equal(layout.counts().begin(),
                              layout.counts().end(),
                              c.begin()));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_offset_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_type o{10,2,1},c{20,100,40},s{1,1,5};

    default_dim_layout layout(c,s,o);

    CPPUNIT_ASSERT(std::equal(layout.offset().begin(),
                              layout.offset().end(),
                              o.begin()));
}

//-----------------------------------------------------------------------------
void default_dim_layout_test::test_stride_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_type o{10,2,1},c{20,100,40},s{1,1,5};

    default_dim_layout layout(c,s,o);

    CPPUNIT_ASSERT(std::equal(layout.stride().begin(),
                              layout.stride().end(),
                              s.begin()));
}
