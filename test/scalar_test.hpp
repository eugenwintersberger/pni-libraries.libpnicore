/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Sep 02, 2011
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <boost/current_function.hpp>
#include <pni/core/Scalar.hpp>

#define DOUBLE_PREC 1.e-3

using namespace pni::core;

template<typename T> class scalar_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(scalar_test<T>);
        CPPUNIT_TEST(test_constructors);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_access_unchecked);
        CPPUNIT_TEST(test_access_checked);
        CPPUNIT_TEST(test_access_iterator);
        CPPUNIT_TEST(test_conversion);
        CPPUNIT_TEST_SUITE_END();
    public:
        typedef Scalar<T> scalar_t;
        void tearDown();
        void setUp();
        
        void test_constructors();
        void test_assignment();
        void test_access_unchecked();
        void test_access_checked();
        void test_access_iterator();
        void test_conversion();

};

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::setUp(){ }

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::tearDown(){ }

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    scalar_t s; 

    CPPUNIT_ASSERT(s.rank() == 0);
    CPPUNIT_ASSERT(s.template shape<shape_t>().size() == 0);
    CPPUNIT_ASSERT(s.size() == 1);

    scalar_t s1 = 100;
    CPPUNIT_ASSERT( s1 == 100);
}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_access_unchecked()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_access_checked()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_access_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_conversion()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}
