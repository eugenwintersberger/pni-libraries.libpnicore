//!
//! (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Jan 9, 2015
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include "../../compare.hpp"
#include "../../data_generator.hpp"

#include <pni/core/type_erasures/value_ref.hpp>
#include <functional>

using namespace pni::core;


template<typename T> class value_ref_construction_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(value_ref_construction_test<T>);
        CPPUNIT_TEST(test_default);
        CPPUNIT_TEST(test_from_value);
        CPPUNIT_TEST(test_copy);
        CPPUNIT_TEST_SUITE_END();
       
        typedef T value_type;
        typedef random_generator<value_type> generator_type;
        generator_type generator;
        value_type value_1;
        value_type value_2;

    public:
        void setUp();
        void tearDown();

        void test_default();
        void test_from_value();
        void test_copy();
};

//-----------------------------------------------------------------------------
template<typename T> 
void value_ref_construction_test<T>::setUp() 
{ 
    generator = generator_type(1,10);
    value_1 = generator();
    value_2 = generator();
}

//-----------------------------------------------------------------------------
template<typename T> 
void value_ref_construction_test<T>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename T>
void value_ref_construction_test<T>::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value_ref v; //default constructed object

    //all methods called on this object should throw an exception
    CPPUNIT_ASSERT_THROW(v.as<double>(),memory_not_allocated_error);
    CPPUNIT_ASSERT_THROW(v.type_id(),memory_not_allocated_error);
}


//-----------------------------------------------------------------------------
template<typename T> 
void value_ref_construction_test<T>::test_from_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value_ref v1(std::ref(value_1));
    value_ref v2(std::ref(value_2));

    compare(v1.as<value_type>(),value_1);
    compare(v2.as<value_type>(),value_2);

    value_1 = generator();
    value_2 = generator();

    compare(v1.as<value_type>(),value_1);
    compare(v2.as<value_type>(),value_2);
}

//-----------------------------------------------------------------------------
template<typename T>
void value_ref_construction_test<T>::test_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    value_ref v1(std::ref(value_1));
    value_ref v2(v1);
    compare(v1.as<value_type>(),v2.as<value_type>());

    //change value_1
    value_1 = generator();
    compare(v1.as<value_type>(),value_1);
    compare(v2.as<value_type>(),value_1);
}


