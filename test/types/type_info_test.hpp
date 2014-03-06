//!
//! (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Oct 01, 2012
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include <boost/current_function.hpp>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include <limits>
#include <climits>
#include <pni/core/types.hpp>


using namespace pni::core;

class type_info_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(type_info_test);
        CPPUNIT_TEST(test_min_max);
        CPPUNIT_TEST(test_signed_integer<int8>);
        CPPUNIT_TEST(test_signed_integer<int16>);
        CPPUNIT_TEST(test_signed_integer<int32>);
        CPPUNIT_TEST(test_signed_integer<int64>);
        CPPUNIT_TEST(test_unsigned_integer<uint8>);
        CPPUNIT_TEST(test_unsigned_integer<uint16>);
        CPPUNIT_TEST(test_unsigned_integer<uint32>);
        CPPUNIT_TEST(test_unsigned_integer<uint64>);
        CPPUNIT_TEST(test_float<float32>);
        CPPUNIT_TEST(test_float<float64>);
        CPPUNIT_TEST(test_float<float128>);
        CPPUNIT_TEST(test_complex<complex32>);
        CPPUNIT_TEST(test_complex<complex64>);
        CPPUNIT_TEST(test_complex<complex128>);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp() {}
        void tearDown() {}
        
        void test_min_max();
        template<typename T> void test_signed_integer();
        template<typename T> void test_unsigned_integer();
        template<typename T> void test_float();
        template<typename T> void test_complex();


};

//-----------------------------------------------------------------------------
template<typename T> void type_info_test::test_signed_integer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef type_info<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(info_t::is_signed);
    CPPUNIT_ASSERT(info_t::is_integer);
    CPPUNIT_ASSERT(!info_t::is_complex);

    CPPUNIT_ASSERT(info_t::is_negative(-1));
    CPPUNIT_ASSERT(!info_t::is_negative(1));
}

//-----------------------------------------------------------------------------
template<typename T> void type_info_test::test_unsigned_integer()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef type_info<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(!info_t::is_signed);
    CPPUNIT_ASSERT(info_t::is_integer);
    CPPUNIT_ASSERT(!info_t::is_complex);
    CPPUNIT_ASSERT(!info_t::is_negative(1));
}

//-----------------------------------------------------------------------------
template<typename T> void type_info_test::test_float()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef type_info<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(info_t::is_signed);
    CPPUNIT_ASSERT(!info_t::is_integer);
    CPPUNIT_ASSERT(!info_t::is_complex);

    CPPUNIT_ASSERT(info_t::is_negative(-1.1232));
    CPPUNIT_ASSERT(!info_t::is_negative(2.342));
}

//-----------------------------------------------------------------------------
template<typename T> void type_info_test::test_complex()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef type_info<T> info_t;

    CPPUNIT_ASSERT(info_t::size == sizeof(T));
    CPPUNIT_ASSERT(!info_t::is_integer);
    CPPUNIT_ASSERT(info_t::is_complex);

}
