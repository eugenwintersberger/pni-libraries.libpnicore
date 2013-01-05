/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Oct 01, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <boost/current_function.hpp>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include <limits>
#include <climits>
#include <pni/core/Types.hpp>
#include <pni/core/TypeInfo.hpp>


using namespace pni::core;

class TypeInfoTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TypeInfoTest);
        CPPUNIT_TEST(test_min_max);
        CPPUNIT_TEST(test_signed_integer<Int8>);
        CPPUNIT_TEST(test_signed_integer<Int16>);
        CPPUNIT_TEST(test_signed_integer<Int32>);
        CPPUNIT_TEST(test_signed_integer<Int64>);
        CPPUNIT_TEST(test_unsigned_integer<UInt8>);
        CPPUNIT_TEST(test_unsigned_integer<UInt16>);
        CPPUNIT_TEST(test_unsigned_integer<UInt32>);
        CPPUNIT_TEST(test_unsigned_integer<UInt64>);
        CPPUNIT_TEST(test_float<Float32>);
        CPPUNIT_TEST(test_float<Float64>);
        CPPUNIT_TEST(test_float<Float128>);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp() {}
        void tearDown() {}
        
        void test_min_max();
        template<typename T> void test_signed_integer();
        template<typename T> void test_unsigned_integer();
        template<typename T> void test_float();


};

//-----------------------------------------------------------------------------
template<typename T> void TypeInfoTest::test_signed_integer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef TypeInfo<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(info_t::is_signed);
    CPPUNIT_ASSERT(info_t::is_integer);
    CPPUNIT_ASSERT(!info_t::is_complex);

    CPPUNIT_ASSERT(info_t::is_negative(-1));
    CPPUNIT_ASSERT(!info_t::is_negative(1));
}

//-----------------------------------------------------------------------------
template<typename T> void TypeInfoTest::test_unsigned_integer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef TypeInfo<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(!info_t::is_signed);
    CPPUNIT_ASSERT(info_t::is_integer);
    CPPUNIT_ASSERT(!info_t::is_complex);
    CPPUNIT_ASSERT(!info_t::is_negative(1));
}

//-----------------------------------------------------------------------------
template<typename T> void TypeInfoTest::test_float()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef TypeInfo<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(info_t::is_signed);
    CPPUNIT_ASSERT(!info_t::is_integer);
    CPPUNIT_ASSERT(!info_t::is_complex);

    CPPUNIT_ASSERT(info_t::is_negative(-1.1232));
    CPPUNIT_ASSERT(!info_t::is_negative(2.342));
}
