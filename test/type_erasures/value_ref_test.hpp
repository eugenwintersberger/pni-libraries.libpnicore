//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Jan 11, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include "../compare.hpp"
#include "../data_generator.hpp"

#include <pni/core/type_erasures/value_ref.hpp>
#include <functional>

using namespace pni::core;


template<typename T> class value_ref_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(value_ref_test<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_stream);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST_SUITE_END();
        
        typedef random_generator<T> generator_type;
        generator_type generator;
        T value_1;
        T value_2;

    public:
        void setUp();
        void tearDown();

        void test_construction();
        void test_assignment();
        void test_stream();
        void test_comparison();
};

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::setUp() 
{ 
    generator = generator_type(1,10);
    value_1 = generator();
    value_2 = generator();
}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_construction()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value_ref v1(std::ref(value_1));
    value_ref v2(std::ref(value_2));

    compare(v1.as<T>(),value_1);
    compare(v2.as<T>(),value_2);

}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_assignment()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    value_ref v1;
    CPPUNIT_ASSERT_THROW(v1.as<T>(),memory_not_allocated_error); 
    value_ref v2;
    v2 = value_ref(std::ref(value_1));
    //assign a reference
    v1 = value_ref(std::ref(value_1));

    //assigning a simple value to the reference 
    v1 = value_2;
    compare(value_1,value_2);

    v2 = v1;
    CPPUNIT_ASSERT(v1.as<T>() == v2.as<T>());
}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_stream()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    std::stringstream ss("12343.4");

    T data;
    value_ref v(std::ref(data));
    ss>>v;
}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    value_ref v1(std::ref(value_1));
    value_ref v2(std::ref(value_2));

    CPPUNIT_ASSERT((v1!=v2)==(value_1!=value_2));
    CPPUNIT_ASSERT(v1==v1);

}


