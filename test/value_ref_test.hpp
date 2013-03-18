/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jan 11, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>
#include "EqualityCheck.hpp"

#include <pni/core/value_ref.hpp>
#include <functional>

using namespace pni::core;


template<typename T> class value_ref_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(value_ref_test<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_copy_and_move);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_stream);
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        void test_construction();
        void test_copy_and_move();
        void test_assignment();
        void test_stream();
};

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::setUp() { }

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    T a(1),b(2);
    value_ref v1 = std::ref(a);
    value_ref v2 = std::ref(b);

    CPPUNIT_ASSERT(v1.as<T>()==a);
    CPPUNIT_ASSERT(v2.as<T>()==b);

}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_copy_and_move()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    T a(1);
    value_ref v1 = std::ref(a);
    
    value_ref v2(v1);
    CPPUNIT_ASSERT(v1.as<T>() == a);
    CPPUNIT_ASSERT(v2.as<T>() == a);

    value_ref v3(std::move(v2));
    CPPUNIT_ASSERT(v3.as<T>() == v1.as<T>());
    CPPUNIT_ASSERT_THROW(v2.as<T>(),memory_not_allocated_error);
    CPPUNIT_ASSERT_THROW(v3.as<complex128>(),type_error);

}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    T a(1);
    value_ref v1;
    CPPUNIT_ASSERT_THROW(v1.as<T>(),memory_not_allocated_error); 
    //assign a reference
    v1 = std::ref(a);

    //assigning a simple value to the reference 
    v1 = T(2);
    check_equality(a,T(2));

    value_ref v2;
    v2 = v1;
    CPPUNIT_ASSERT(v1.as<T>() == v2.as<T>());

    value_ref v3;
    v3 = std::move(v2);
    CPPUNIT_ASSERT(v3.as<T>() == v1.as<T>());
    CPPUNIT_ASSERT_THROW(v2.as<T>(),memory_not_allocated_error);
}

//-----------------------------------------------------------------------------
template<typename T> void value_ref_test<T>::test_stream()
{
    std::stringstream ss("12343.4");

    T data;
    value_ref v=std::ref(data);
    ss>>v;
    std::cout<<v<<std::endl;
    CPPUNIT_ASSERT(v.type_id() == type_id_t::FLOAT32);
}



