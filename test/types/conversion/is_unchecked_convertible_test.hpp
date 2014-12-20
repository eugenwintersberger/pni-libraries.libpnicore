//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Dec 18, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types/type_conversion.hpp>

using namespace pni::core;

class is_unchecked_convertible_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(is_unchecked_convertible_test);
        CPPUNIT_TEST(test_uint8);
        CPPUNIT_TEST(test_uint16);
        CPPUNIT_TEST(test_uint32);
        CPPUNIT_TEST(test_uint64);
        CPPUNIT_TEST(test_int8);
        CPPUNIT_TEST(test_int16);
        CPPUNIT_TEST(test_int32);
        CPPUNIT_TEST(test_int64);
        CPPUNIT_TEST(test_float32);
        CPPUNIT_TEST(test_float64);
        CPPUNIT_TEST(test_float128);
        CPPUNIT_TEST(test_complex32);
        CPPUNIT_TEST(test_complex64);
        CPPUNIT_TEST(test_complex128);
        CPPUNIT_TEST_SUITE_END();

        //--------------------------------------------------------------------
        void always_fails(type_id_t source_tid);

        //--------------------------------------------------------------------
        void uint_always_fails(type_id_t source_tid);

        //--------------------------------------------------------------------
        void int_always_fails(type_id_t source_tid);

        //--------------------------------------------------------------------
        void float_always_fails(type_id_t source_tid);
        
        //--------------------------------------------------------------------
        void float_always_pass(type_id_t source_tid);

        //--------------------------------------------------------------------
        void complex_always_pass(type_id_t source_tid);
    public:
        void setUp();
        void tearDown();
        void test_uint8();
        void test_uint16();
        void test_uint32();
        void test_uint64();
        void test_int8();
        void test_int16();
        void test_int32();
        void test_int64();
        void test_float32();
        void test_float64();
        void test_float128();
        void test_complex32();
        void test_complex64();
        void test_complex128();

};
