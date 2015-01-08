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
//!  Created on: Jan 7, 2015
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!/

#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>
#include "../../compare.hpp"
#include "../../data_generator.hpp"

#include <pni/core/type_erasures/value.hpp>
#include <functional>

using namespace pni::core;


template<typename T> class value_construction_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(value_construction_test<T>);
        CPPUNIT_TEST(test_default);
        CPPUNIT_TEST(test_from_value);
        CPPUNIT_TEST(test_make_value);
        CPPUNIT_TEST(test_copy);
        CPPUNIT_TEST(test_move);
        CPPUNIT_TEST_SUITE_END();

        typedef random_generator<T> generator_type;
        generator_type generator;
        T value_1;
        T value_2;

    public:
        void setUp();
        void tearDown();

        //test default construction
        void test_default();
        void test_from_value();
        void test_copy();
        void test_move();
        void test_make_value();
};

//-----------------------------------------------------------------------------
template<typename T> 
void value_construction_test<T>::setUp() 
{ 
    generator = generator_type(1,10);
    value_1 = generator();
    value_2 = generator();
}

//-----------------------------------------------------------------------------
template<typename T> 
void value_construction_test<T>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename T> 
void value_construction_test<T>::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    //untyped construction
    value v;
    CPPUNIT_ASSERT(v.type_id() == type_id_t::NONE);
    //there is nothing more we can do here
}

//----------------------------------------------------------------------------
template<typename T>
void value_construction_test<T>::test_make_value()
{
    value v = make_value<T>();
    CPPUNIT_ASSERT(v.type_id() == type_id_map<T>::type_id);
}

//----------------------------------------------------------------------------
template<typename T>
void value_construction_test<T>::test_from_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    value v(value_1);
    CPPUNIT_ASSERT(v.type_id() == type_id_map<T>::type_id);
    compare(v.as<T>(),value_1); 
}


//-----------------------------------------------------------------------------
template<typename T> 
void value_construction_test<T>::test_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value v1(value_1);
    value v2(v1);

    CPPUNIT_ASSERT(v1.type_id() == v2.type_id());
    compare(v1.as<T>(),v2.as<T>());
}

//----------------------------------------------------------------------------
template<typename T>
void value_construction_test<T>::test_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value v1(value_1);
    value v2 = std::move(v1);

    CPPUNIT_ASSERT(v1.type_id()==type_id_t::NONE);
    CPPUNIT_ASSERT(v2.type_id()==type_id_map<T>::type_id);
    compare(value_1,v2.as<T>());
}

