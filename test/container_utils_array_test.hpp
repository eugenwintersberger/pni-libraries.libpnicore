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
 *std::vector<T> along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Nov 07, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/container_utils.hpp>
#include <functional>
#include "data_generator.hpp"
#include "compare.hpp"

using namespace pni::core;

template<typename CTYPE> 
class container_utils_array_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(container_utils_array_test<CTYPE>);
        CPPUNIT_TEST(test_create_from_size);
        CPPUNIT_TEST(test_create_from_range);
        CPPUNIT_TEST(test_create_from_container);
        CPPUNIT_TEST(test_create_from_init_list);
        CPPUNIT_TEST_SUITE_END();

        typedef container_utils<CTYPE> cutils;
        typedef typename CTYPE::value_type value_type;
        typedef random_generator<value_type> generator_type;
        typedef std::vector<value_type> container_type;

        generator_type generator;
        container_type c;

    public:
        void setUp();
        void tearDown();

        void test_create_from_size();
        void test_create_from_range();
        void test_create_from_container();
        void test_create_from_init_list();

};

//-----------------------------------------------------------------------------
template<typename CTYPE>
void container_utils_array_test<CTYPE>::setUp() 
{
    generator = generator_type();
    c = container_type(4);
    std::generate(c.begin(),c.end(),generator);
}

//-----------------------------------------------------------------------------
template<typename CTYPE>
void container_utils_array_test<CTYPE>::tearDown() {}

//-----------------------------------------------------------------------------
template<typename CTYPE>
void container_utils_array_test<CTYPE>::test_create_from_size()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //without initializiation value
    auto c1 = cutils::create(4);
    CPPUNIT_ASSERT(c1.size() == 4);
    for(auto c: c1) compare(c,value_type());

    //with initializiation value
    auto random_value = generator();
    auto c2 = cutils::create(4,random_value);
    for(auto c: c2) compare(c,random_value);

    //check exception
    CPPUNIT_ASSERT_THROW(cutils::create(5),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(cutils::create(3),size_mismatch_error);
}

//-----------------------------------------------------------------------------
template<typename CTYPE>
void container_utils_array_test<CTYPE>::test_create_from_range()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    auto c1 = cutils::create(c.begin(),c.end());
    CPPUNIT_ASSERT(c.size() == c1.size());
    CPPUNIT_ASSERT(std::equal(c1.begin(),c1.end(),c.begin()));

    //check exceptions
    c = container_type(10);
    CPPUNIT_ASSERT_THROW(cutils::create(c.begin(),c.end()),size_mismatch_error);
    c = container_type(3);
    CPPUNIT_ASSERT_THROW(cutils::create(c.begin(),c.end()),size_mismatch_error);
}

//-----------------------------------------------------------------------------
template<typename CTYPE>
void container_utils_array_test<CTYPE>::test_create_from_container()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    auto c1 = cutils::create(c);
    CPPUNIT_ASSERT(c.size() == c1.size());
    CPPUNIT_ASSERT(std::equal(c1.begin(),c1.end(),c.begin()));
    
    c = container_type(10);
    CPPUNIT_ASSERT_THROW(cutils::create(c),size_mismatch_error);
    c = container_type(3);
    CPPUNIT_ASSERT_THROW(cutils::create(c),size_mismatch_error);
}

//-----------------------------------------------------------------------------
template<typename CTYPE>
void container_utils_array_test<CTYPE>::test_create_from_init_list()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    c = container_type{1,2,3,4};
    auto c1 = cutils::create({1,2,3,4});
    CPPUNIT_ASSERT(c1.size() == c.size());
    CPPUNIT_ASSERT(std::equal(c1.begin(),c1.end(),c.begin()));

    CPPUNIT_ASSERT_THROW(cutils::create({1,2}),size_mismatch_error);
    CPPUNIT_ASSERT_THROW(cutils::create({1,2,3,4,5}),size_mismatch_error);
}
