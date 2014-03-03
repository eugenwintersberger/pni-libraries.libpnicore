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
 *  Created on: May 15, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/current_function.hpp>

#include "slice_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(slice_test);


//===========implementation of private test functions==========================
void slice_test::_construct(size_t start,size_t stop)
{
    slice s(start,stop);
}

void slice_test::_construct(size_t start,size_t stop,size_t stride)
{
    slice s(start,stop,stride);
}

//-----------------------------------------------------------------------------
void slice_test::setUp() { }

//-----------------------------------------------------------------------------
void slice_test::tearDown() { }

//-----------------------------------------------------------------------------
void slice_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT_THROW(_construct(1,0),range_error);
    CPPUNIT_ASSERT_THROW(_construct(1,1),range_error);
    CPPUNIT_ASSERT_THROW(_construct(1,10,100),range_error);
   
    //test construction without stride
    size_t f=1,l=10;
    slice s(f,l);
    CPPUNIT_ASSERT(s.first() == f);
    CPPUNIT_ASSERT(s.last() == l);
    CPPUNIT_ASSERT(s.stride() == 1);

    //test construction with stride
    size_t stride = 2;
    slice s1(f,l,stride);
    CPPUNIT_ASSERT(s1.first() == f);
    CPPUNIT_ASSERT(s1.last() == l);
    CPPUNIT_ASSERT(s1.stride() == stride);

    //test copy construction
    slice s2(s1);
    CPPUNIT_ASSERT(s2.first() == s1.first());
    CPPUNIT_ASSERT(s2.last()  == s1.last());
    CPPUNIT_ASSERT(s2.stride() == s1.stride());

}

//-----------------------------------------------------------------------------
void slice_test::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    size_t f=20,l=100,stride=13;
    slice s(f,l,stride);

    slice s1(f,l);

    CPPUNIT_ASSERT_NO_THROW(s1 = s);
    CPPUNIT_ASSERT(s1.first() == s.first());
    CPPUNIT_ASSERT(s1.last() == s.last());
    CPPUNIT_ASSERT(s1.stride() == s.stride());

}

//-----------------------------------------------------------------------------
void slice_test::test_functions()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    size_t f=20,l=100,stride=13;
    slice s(f,l,stride);

    CPPUNIT_ASSERT(size(s) == 7);
    CPPUNIT_ASSERT(span(s) == 80);

    slice s1(1,3,2);
    CPPUNIT_ASSERT(size(s1) == 1);
    CPPUNIT_ASSERT(span(s1) == 2);
}
