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
 *  Created on: Jul 31, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/current_function.hpp>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <list>

#include "static_cindex_map_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(static_cindex_map_test);

//------------------------------------------------------------------------------
void static_cindex_map_test::setUp(){ }

//------------------------------------------------------------------------------
void static_cindex_map_test::tearDown(){ }

//------------------------------------------------------------------------------
void static_cindex_map_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    static_cindex_map<3,4,5> s1;
    CPPUNIT_ASSERT(s1.size() == 3*4*5);
    CPPUNIT_ASSERT(s1.rank() == 3);
    
    auto shape = s1.shape<std::vector<size_t> >();
    CPPUNIT_ASSERT(shape[0] == 3);
    CPPUNIT_ASSERT(shape[1] == 4);
    CPPUNIT_ASSERT(shape[2] == 5);

}

//------------------------------------------------------------------------------
void static_cindex_map_test::test_offset()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    static_cindex_map<3,4> s1;

    size_t offset = 0;
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(2,1));
    CPPUNIT_ASSERT(offset == 9);
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(std::vector<size_t>{2,1}));
    CPPUNIT_ASSERT(offset == 9);
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(std::list<size_t>{2,1}));
    CPPUNIT_ASSERT(offset == 9);

    //test exceptions for offset computation
    CPPUNIT_ASSERT_THROW(s1.offset(std::list<size_t>{10,1}),index_error);
    CPPUNIT_ASSERT_THROW(s1.offset(std::list<size_t>{1,2,3,4}),shape_missmatch_error);

    static_cindex_map<2,3,5> s2;
    CPPUNIT_ASSERT(s2.offset(0,1,3) == 8);
    CPPUNIT_ASSERT(s2.offset(0,1,3) == 8);
}

//------------------------------------------------------------------------------
void static_cindex_map_test::test_index()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    static_cindex_map<3,4> s1;
    static_cindex_map<2,3,5> s2;

	CPPUNIT_ASSERT(s1.offset(2,1)==9);
    auto index = s1.index<std::vector<size_t> >(9);
    CPPUNIT_ASSERT(index[0] == 2);
    CPPUNIT_ASSERT(index[1] == 1);

	CPPUNIT_ASSERT(s2.offset(0,1,3)==8);
    auto list = s2.index<std::vector<size_t> >(8);
    CPPUNIT_ASSERT(list.at(1) == 1);
    CPPUNIT_ASSERT(list.at(2) == 3);
    CPPUNIT_ASSERT(list.at(0) == 0);

    std::vector<size_t> index1(2);
    std::list<size_t> index2(3);
    CPPUNIT_ASSERT_NO_THROW(s1.index(9,index1));
    CPPUNIT_ASSERT_NO_THROW(s2.index(8,index2));
    CPPUNIT_ASSERT_THROW(s1.index(9,index2),shape_missmatch_error);
    CPPUNIT_ASSERT_THROW(s2.index(8,index1),shape_missmatch_error);

    CPPUNIT_ASSERT_THROW(s1.index(900,index1),size_missmatch_error);
    CPPUNIT_ASSERT_THROW(s2.index(800,index2),size_missmatch_error);
}

