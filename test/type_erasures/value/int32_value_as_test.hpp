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
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>
#include "../../compare.hpp"
#include "../../data_generator.hpp"

#include <pni/core/type_erasures/value.hpp>
#include <functional>

using namespace pni::core;


class int32_value_as_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(int32_value_as_test);
        CPPUNIT_TEST(test_as_uint8);
        CPPUNIT_TEST(test_as_uint16);
        CPPUNIT_TEST(test_as_uint32);
        CPPUNIT_TEST(test_as_uint64);
        CPPUNIT_TEST(test_as_int8);
        CPPUNIT_TEST(test_as_int16);
        CPPUNIT_TEST(test_as_int32);
        CPPUNIT_TEST(test_as_int64);
        CPPUNIT_TEST(test_as_float32);
        CPPUNIT_TEST(test_as_float64);
        CPPUNIT_TEST(test_as_float128);
        CPPUNIT_TEST(test_as_complex32);
        CPPUNIT_TEST(test_as_complex64);
        CPPUNIT_TEST(test_as_complex128);
        CPPUNIT_TEST(test_as_string);
        CPPUNIT_TEST(test_as_bool);
        CPPUNIT_TEST(test_as_binary);
        CPPUNIT_TEST_SUITE_END();
   
        typedef int32 value_type;
        typedef random_generator<value_type> generator_type;
        generator_type generator;
        value_type value_1;
        value v;

    public:
        void setUp();
        void tearDown();

        //test default construction
        void test_as_uint8();
        void test_as_uint16();
        void test_as_uint32();
        void test_as_uint64();
        void test_as_int8();
        void test_as_int16();
        void test_as_int32();
        void test_as_int64();
        void test_as_float32();
        void test_as_float64();
        void test_as_float128();
        void test_as_complex32();
        void test_as_complex64();
        void test_as_complex128();
        void test_as_string();
        void test_as_bool();
        void test_as_binary();
};

