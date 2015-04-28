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


template<typename T> class value_ref_assignment_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(value_ref_assignment_test<T>);
        CPPUNIT_TEST(test_copy);
        CPPUNIT_TEST(test_from_value);
        CPPUNIT_TEST(test_from_T);
        CPPUNIT_TEST(test_to_value);
        CPPUNIT_TEST_SUITE_END();
       
        typedef T value_type;
        typedef random_generator<value_type> generator_type;
        generator_type generator;
        value_type value_1;
        value_type value_2;

    public:
        void setUp();
        void tearDown();

        //!
        //! \brief test copy assignment 
        //!
        //! Here we test simple copy assignment. The object to which the
        //! refernece referes to will be changed
        //!
        void test_copy();

        //!
        //! \brief test value assignemnt
        //!
        //! We use an instance of value to change the value of the variable 
        //! to which the reference points to. 
        //!
        void test_from_value();

        //!
        //! \brief test value assignment
        //!
        //! Similar to value but here we use a value of a POD type to alter the 
        //! value of the target variable for the reference.
        //!
        void test_from_T();

        void test_to_value();
};

//-----------------------------------------------------------------------------
template<typename T> 
void value_ref_assignment_test<T>::setUp() 
{ 
    generator = generator_type(1,10);
    value_1 = generator();
    value_2 = generator();
}

//-----------------------------------------------------------------------------
template<typename T> 
void value_ref_assignment_test<T>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename T>
void value_ref_assignment_test<T>::test_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value_ref v1(std::ref(value_1)); 
    value_ref v2(std::ref(value_2));

    v2 = v1; //now v2 referes to the same value - value_1

    compare(v1.as<value_type>(),value_1);
    compare(v2.as<value_type>(),value_1);

    value_1 = generator();

    compare(v1.as<value_type>(),value_1);
    compare(v2.as<value_type>(),value_1);
}


//-----------------------------------------------------------------------------
template<typename T> 
void value_ref_assignment_test<T>::test_from_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    value v(value_1);
    value_ref ref(std::ref(value_2));
    
    ref = v;
    compare(ref.as<T>(),value_1);
}

//-----------------------------------------------------------------------------
template<typename T>
void value_ref_assignment_test<T>::test_from_T()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    value_ref v(std::ref(value_1));
    v = value_2;
    compare(v.as<value_type>(),value_2);
    compare(value_2,value_1);
}

//-----------------------------------------------------------------------------
template<typename T>
void value_ref_assignment_test<T>::test_to_value()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    value_ref v_ref(std::ref(value_1));
    value v = to_value(v_ref);
    
    compare(v.as<value_type>(),v_ref.as<value_type>());
    compare(v.as<value_type>(),value_1);
}

