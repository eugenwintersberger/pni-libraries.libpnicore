//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Sep 02, 2011
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <boost/current_function.hpp>
#include <pni/core/arrays/scalar.hpp>
#include "../compare.hpp"
#include "../data_generator.hpp"

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

        typedef scalar<T> scalar_type;
        scalar_type s;
        T v;
    public:
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
template<typename T> void scalar_test<T>::setUp()
{ 
    v = random_generator<T>(1,10)();
}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::tearDown(){ }

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //check the default constructed scalar
    CPPUNIT_ASSERT(s.rank() == 0);
    CPPUNIT_ASSERT(s.template shape<shape_t>().size() == 0);
    CPPUNIT_ASSERT(s.size() == 1);

    //standard construction
    scalar_type s1(v);
    compare(T(s1),T(v));

    //copy construction
    scalar_type s2 = s1;
    compare(T(s2),T(s1));
}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    s = v;
    compare(T(s),v);

    scalar_type s2;
    s2 = s;
    compare(T(s2),v);
}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_access_unchecked()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    s = v;
    compare(s[0],v);
    compare(s[1],v);
}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_access_checked()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    s = v;
    compare(s.at(10),v);
    compare(s.at(0),v);
}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_access_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    s = v;
    auto iter = s.begin();
    for(size_t n=0;n<20;++n)
        compare(T(*iter++),v);

}

//-----------------------------------------------------------------------------
template<typename T> void scalar_test<T>::test_conversion()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

}
