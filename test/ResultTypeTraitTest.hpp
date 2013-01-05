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
 *  Created on: Jul 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <boost/current_function.hpp>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include <pni/core/ResultTypeTrait.hpp>
#include <pni/core/type_conversion.hpp>
#include "EqualityCheck.hpp"

template<typename T>
class ResultTypeTraitTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(ResultTypeTraitTest);
//        CPPUNIT_TEST(test_add<UInt8>);
//        CPPUNIT_TEST(test_add<Int8>);
//        CPPUNIT_TEST(test_add<UInt16>);
//        CPPUNIT_TEST(test_add<Int16>);
//        CPPUNIT_TEST(test_add<UInt32>);
//        CPPUNIT_TEST(test_add<Int32>);
//        CPPUNIT_TEST(test_add<UInt64>);
//        CPPUNIT_TEST(test_add<Int64>);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();

        template<typename U> void test_add();
};


//-----------------------------------------------------------------------------
template<typename T> void ResultTypeTraitTest<T>::setUp() { }

//-----------------------------------------------------------------------------
template<typename T> void ResultTypeTraitTest<T>::tearDown()
{}


//-----------------------------------------------------------------------------
template<typename T> 
template<typename U> void ResultTypeTraitTest<T>::test_add()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename ResultTypeTrait<T,U>::add_type result_type;

    //now - if we add these two numbers the result should not be convineant for
    //neither data type
    T a = TypeInfo<T>::max()-1;
    U b = TypeInfo<U>::max()-1;

    //now if these two numbers are added the result should overflow
    result_type t;
    t = a + b;
    std::cout<<"a + b = "<<a<<" + "<<b<<" = "<<t<<std::endl;
    check_equality(t,result_type(result_type(a)+result_type(b))); 

    CPPUNIT_ASSERT_THROW(convert_type<T>(t),RangeError);
    CPPUNIT_ASSERT_THROW(convert_type<U>(t),RangeError);
}
