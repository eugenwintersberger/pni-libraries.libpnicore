//!
//! (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Jul 13, 2012
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

#include <list>

#include "array_selection_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_selection_test);

//-----------------------------------------------------------------------------
void array_selection_test::setUp() 
{ 
    m1 = map_type(index_type{10,20});
    m2 = map_type(index_type{10,20,5});
    
    slices_1 = {slice(2,10),slice(2)};
    slices_2 = {slice(2,10),slice(2),slice(1,5,2)};

    sel_1 = array_selection::create(slices_1);
    sel_2 = array_selection::create(slices_2);
}

//-----------------------------------------------------------------------------
void array_selection_test::tearDown() { }

//-----------------------------------------------------------------------------
void array_selection_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //testing default constructor
    array_selection sel1;
    auto sel1_shape = sel1.shape<shape_t>();
    CPPUNIT_ASSERT(sel1.rank() == 0);
    CPPUNIT_ASSERT(sel1.shape<shape_t>() == shape_t());
    CPPUNIT_ASSERT(sel1.size() == 0);

    //testing standard constructor
    index_type s({1,100,100}); 
    index_type o({0,0,0}); 
    index_type str({1,1,1});
    array_selection sel2(s,o,str);
    CPPUNIT_ASSERT(sel2.rank() == 2);
    CPPUNIT_ASSERT(sel2.size() == 100*100);
    auto sel2_shape = sel2.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(s.begin()+1,s.end(),sel2_shape.begin()));

    //check full parameters
    CPPUNIT_ASSERT(std::equal(sel2.full_shape().begin(),
                              sel2.full_shape().end(),
                              s.begin()));
    CPPUNIT_ASSERT(std::equal(sel2.offset().begin(),
                              sel2.offset().end(),
                              o.begin()));
    CPPUNIT_ASSERT(std::equal(sel2.stride().begin(),
                              sel2.stride().end(),
                              str.begin()));

    //! copy constructor
    array_selection sel3(sel2);
    CPPUNIT_ASSERT(sel3.rank() == sel2.rank());
    CPPUNIT_ASSERT(sel3.size() == sel2.size());
    auto sel3_shape = sel3.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(sel3_shape.begin(),sel3_shape.end(),
                              sel2_shape.begin()));

    //! move construction
    array_selection sel4(std::move(sel3));
    CPPUNIT_ASSERT(sel4.rank() == sel2.rank());
    CPPUNIT_ASSERT(sel4.size() == sel2.size());
    auto sel4_shape = sel4.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(sel4_shape.begin(),sel4_shape.end(),sel2_shape.begin()));

    CPPUNIT_ASSERT(sel3.size() == 0);
    CPPUNIT_ASSERT(sel3.rank() == 0);
    CPPUNIT_ASSERT(sel3.shape<index_type>() == index_type());

    //testing the default internal objects
    CPPUNIT_ASSERT(sel_1.rank() == 1);
    auto sel_1_shape = sel_1.shape<index_type>();
    index_type sel_1_shape_ref = {8};
    CPPUNIT_ASSERT(std::equal(sel_1_shape.begin(),sel_1_shape.end(),
                              sel_1_shape_ref.begin()));

    CPPUNIT_ASSERT(sel_2.rank() == 2);
    auto sel_2_shape = sel_2.shape<index_type>();
    index_type sel_2_shape_ref = {8,2};
    
    CPPUNIT_ASSERT(std::equal(sel_2_shape.begin(),sel_2_shape.end(),
                              sel_2_shape_ref.begin()));

}

//------------------------------------------------------------------------------
void array_selection_test::test_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    std::vector<slice> slices{slice(0,10),slice(1,30,2),slice(2)};
    array_selection s = array_selection::create(slices);

    CPPUNIT_ASSERT(s.size() == 10*15);
    CPPUNIT_ASSERT(s.rank() == 2);
    index_type ref_shape{10,15};
    auto ss = s.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(ss.begin(),ss.end(),ref_shape.begin()));

}

//-----------------------------------------------------------------------------
void array_selection_test::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    array_selection sel(index_type({100,1,200}),index_type({1,1,1}),index_type({1,1,2}));
    CPPUNIT_ASSERT(sel.rank() == 2);
    index_type s{100,200};
    auto sel_shape = sel.shape<index_type>();

    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sel_shape.begin()));
    CPPUNIT_ASSERT(sel.size() == 100*200);

    //------------------------test copy assignment------------------------------
    array_selection s1;

    s1 = sel;
    CPPUNIT_ASSERT(s1.rank() == sel.rank());
    CPPUNIT_ASSERT(s1.size() == sel.size());
    auto s1_shape = s1.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(s1_shape.begin(),s1_shape.end(),
                              sel_shape.begin()));

    //-----------------test move assignment------------------------------------
    array_selection s2;
    s2 = std::move(s1);
    CPPUNIT_ASSERT(s2.rank() == sel.rank());
    CPPUNIT_ASSERT(s2.size() == sel.size());
    auto s2_shape  = s2.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(s2_shape.begin(),s2_shape.end(),
                              sel_shape.begin()));

    CPPUNIT_ASSERT(s1.size() == 0);
    CPPUNIT_ASSERT(s1.rank() == 0);
    CPPUNIT_ASSERT(s1.shape<index_type>() == index_type());

}

//-----------------------------------------------------------------------------
void array_selection_test::test_index()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    array_selection sel(index_type({10,20}),index_type({1,2}),index_type({3,2}));
    index_type s{10,20};
    auto sshape = sel.shape<index_type>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sshape.begin()));
    CPPUNIT_ASSERT(sel.rank()==2);
    CPPUNIT_ASSERT(sel.size() == 10*20);
        
    index_type i(sel.rank());
    sel.index(index_type({1,3}),i);
    index_type r{4,8};
    CPPUNIT_ASSERT(std::equal(r.begin(),r.end(),i.begin()));

    array_selection sel2(index_type({10,1,20}),index_type({1,1,2}),index_type({3,1,2}));
    i = index_type(3);
    sel2.index(index_type({1,3}),i);
    r = index_type{4,1,8};
    CPPUNIT_ASSERT(std::equal(r.begin(),r.end(),i.begin()));
}

//-----------------------------------------------------------------------------
void array_selection_test::test_offset()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    index_type index={2};

    CPPUNIT_ASSERT(offset(m1,sel_1,index)==m1.offset(index_type{4,2}));

    index_type index_2 = {2,1};
    CPPUNIT_ASSERT(offset(m2,sel_2,index_2)==
                   m2.offset(index_type{4,2,1+2}));

}

//-----------------------------------------------------------------------------
void array_selection_test::test_start_offset()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
        
    CPPUNIT_ASSERT(start_offset(m1,sel_1)==42);
    CPPUNIT_ASSERT(start_offset(m2,sel_2)==211);
}

//-----------------------------------------------------------------------------
void array_selection_test::test_end_offset()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(last_offset(m1,sel_1) == 182);
    CPPUNIT_ASSERT(last_offset(m2,sel_2) == 913);
}

//-----------------------------------------------------------------------------
void array_selection_test::test_is_contiguous()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!is_contiguous(m1,sel_1));
    CPPUNIT_ASSERT(!is_contiguous(m2,sel_2));

    vslice_type cslices{slice(1),slice(10,19)};
    array_selection cs = array_selection::create(cslices);
    CPPUNIT_ASSERT(is_contiguous(m1,cs));

}

