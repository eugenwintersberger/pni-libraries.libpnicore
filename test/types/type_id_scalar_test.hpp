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
 *  Created on: Sep 30, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <boost/current_function.hpp>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include <limits>
#include <climits>
#include <pni/core/types.hpp>
#include <pni/core/type_utils.hpp>


using namespace pni::core;

#define CPPUNIT_TEST_SCALAR(type,id)                        \
    CPPUNIT_TEST_SUITE_ADD_TEST(                           \
        ( new CPPUNIT_NS::TestCaller<TestFixtureType>(    \
                  context.getTestNameFor("test_type_id<type,type_id_t::id>"),   \
                  &TestFixtureType::test_type_id<type,type_id_t::id>,           \
                  context.makeFixture() ) ) )

class type_id_scalar_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(type_id_scalar_test);

        //----------------testing scalars--------------------------------------
        CPPUNIT_TEST_SCALAR(uint8,UINT8);
        CPPUNIT_TEST_SCALAR(int8,INT8);
        CPPUNIT_TEST_SCALAR(uint16,UINT16);
        CPPUNIT_TEST_SCALAR(int16,INT16);
        CPPUNIT_TEST_SCALAR(uint32,UINT32);
        CPPUNIT_TEST_SCALAR(int32,INT32);
        CPPUNIT_TEST_SCALAR(uint64,UINT64);
        CPPUNIT_TEST_SCALAR(int64,INT64);
        CPPUNIT_TEST_SCALAR(float32,FLOAT32);
        CPPUNIT_TEST_SCALAR(float64,FLOAT64);
        CPPUNIT_TEST_SCALAR(float128,FLOAT128);
        CPPUNIT_TEST_SCALAR(complex32,COMPLEX32);
        CPPUNIT_TEST_SCALAR(complex64,COMPLEX64);
        CPPUNIT_TEST_SCALAR(complex128,COMPLEX128);
        CPPUNIT_TEST_SCALAR(string,STRING);
        CPPUNIT_TEST_SCALAR(binary,BINARY);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp() {}
        void tearDown() {}
        

        template<typename T,type_id_t ID> void test_type_id();


};


//-----------------------------------------------------------------------------
template<typename T,type_id_t ID> void type_id_scalar_test::test_type_id()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    T instance;
    CPPUNIT_ASSERT(type_id(instance)==ID);
}
