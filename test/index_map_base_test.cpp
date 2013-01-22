/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 20, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "index_map_base_test.hpp"
#include <list>

CPPUNIT_TEST_SUITE_REGISTRATION(index_map_base_test);


//-----------------------------------------------------------------------------
void index_map_base_test::setUp() {}

//-----------------------------------------------------------------------------
void index_map_base_test::tearDown() {}

//-----------------------------------------------------------------------------
void index_map_base_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //default construction
    IndexMapBase im1;

    CPPUNIT_ASSERT(im1.size()==0);
    CPPUNIT_ASSERT(im1.rank()==0);

    //construction from initializer list
    IndexMapBase im2{1,2,3,4,5};
    CPPUNIT_ASSERT(im2.size()==2*3*4*5);
    CPPUNIT_ASSERT(im2.rank()==5);

    //construction from a container
    std::list<size_t> s{3,2,5,6};
    IndexMapBase im3(s);
    CPPUNIT_ASSERT(im3.size()==3*2*5*6);
    CPPUNIT_ASSERT(im3.rank()==4);

    //copy construction
    IndexMapBase im4(im3);
    CPPUNIT_ASSERT(im4.size() == im3.size());
    CPPUNIT_ASSERT(im4.rank() == im3.rank());
    CPPUNIT_ASSERT(std::equal(im4.shape().begin(),im4.shape().end(),
                              im3.shape().begin()));

    //move construction
    IndexMapBase im5 = std::move(im3);
    CPPUNIT_ASSERT(im3.size() == 0);
    CPPUNIT_ASSERT(im3.rank() == 0);

    CPPUNIT_ASSERT(im4.size() == im5.size());
    CPPUNIT_ASSERT(im4.rank() == im5.rank());
    CPPUNIT_ASSERT(std::equal(im4.shape().begin(),im4.shape().end(),
                              im5.shape().begin()));

}

//-----------------------------------------------------------------------------
void index_map_base_test::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    IndexMapBase im1{2,3,4,5};
    IndexMapBase im2,im3;

    im2 = im1;
    CPPUNIT_ASSERT(im2.rank() == im1.rank());
    CPPUNIT_ASSERT(im2.size() == im1.size());
    CPPUNIT_ASSERT(std::equal(im1.shape().begin(),im1.shape().end(),
                              im2.shape().begin()));

    im3 = std::move(im1);
    CPPUNIT_ASSERT(im1.size() == 0);
    CPPUNIT_ASSERT(im1.rank() == 0);
    CPPUNIT_ASSERT(im3.rank() == im2.rank());
    CPPUNIT_ASSERT(im3.size() == im2.size());
    CPPUNIT_ASSERT(std::equal(im2.shape().begin(),im2.shape().end(),
                              im3.shape().begin()));
}

//-----------------------------------------------------------------------------
void index_map_base_test::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    std::vector<size_t> s{3,2,5,7};
    IndexMapBase im1(s);

    //this is trivial
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),im1.shape().begin()));


}
