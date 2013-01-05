/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Mar 11, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/CIndexMap.hpp>

#include <vector>
#include <list>

using namespace pni::core;


template<typename MTYPE>
class IndexMapTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(IndexMapTest<MTYPE>);
        CPPUNIT_TEST(test_offset<std::vector<size_t> >);
        CPPUNIT_TEST(test_offset<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_offset<std::vector<int> >);
        CPPUNIT_TEST(test_offset<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_offset<std::list<size_t> >);
        CPPUNIT_TEST(test_offset<std::list<ssize_t> >);
        CPPUNIT_TEST(test_offset<std::list<int> >);
        CPPUNIT_TEST(test_offset<std::list<unsigned int> >);
        CPPUNIT_TEST(test_index<std::vector<size_t> >);
        CPPUNIT_TEST(test_index<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_index<std::vector<int> >);
        CPPUNIT_TEST(test_index<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_index<std::list<size_t> >);
        CPPUNIT_TEST(test_index<std::list<ssize_t> >);
        CPPUNIT_TEST(test_index<std::list<int> >);
        CPPUNIT_TEST(test_index<std::list<unsigned int> >);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp(){}
        void tearDown() {}
    
        template<typename CTYPE> void test_offset();
        template<typename CTYPE> void test_index();
};

//-----------------------------------------------------------------------------
template<typename MTYPE> 
template<typename CTYPE> void IndexMapTest<MTYPE>::test_offset()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    MTYPE map{2,3};
    CPPUNIT_ASSERT(map.offset(1,2)==5);
    CPPUNIT_ASSERT(map.offset(CTYPE{1,2}) == 5);

    map = MTYPE{5,4};
    CPPUNIT_ASSERT(map.offset(1,2) == 6);
    CPPUNIT_ASSERT(map.offset(CTYPE{1,2}) == 6);

}

//-----------------------------------------------------------------------------
template<typename MTYPE> 
template<typename CTYPE> void IndexMapTest<MTYPE>::test_index()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    MTYPE map{2,3};
    auto i = map.template index<CTYPE>(5);

    CTYPE ic{1,2};
    CPPUNIT_ASSERT(std::equal(ic.begin(),ic.end(),i.begin()));

}
