/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <algorithm>
#include <boost/current_function.hpp>

#include "EqualityCheck.hpp"
#include <pni/core/DArray.hpp>
#include <pni/core/Scalar.hpp>
#include <pni/core/NumArray.hpp>

using namespace pni::core;

/*!
 Do testing only for DArray - all array types provide the same interface and
 thus can be considered as equivalent. However, we have to check ArrayView
 wether or not it works.
 */
template<typename T> class AddOperatorTest: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(AddOperatorTest<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST(test_operator);
        CPPUNIT_TEST_SUITE_END();
    private:
        //==========private types==============================================
        typedef DArray<T> atype;
        typedef NumArray<atype> na_type;
        typedef Scalar<T> s_type;
        typedef std::vector<size_t> shape_t;


        //===================private memebers==================================
        na_type a1;
        na_type a2;
        shape_t shape;

    public:
        void setUp();
        void tearDown();
        
        void test_construction();
        void test_access();
        void test_iterator();
        void test_operator();

};

//-----------------------------------------------------------------------------
template<typename T> void AddOperatorTest<T>::setUp()
{
    shape = shape_t(3);
    shape[0] = 2; shape[1] = 3; shape[2] = 4;
    a1 = std::move(na_type(shape));
    a2 = std::move(na_type(shape));
    
    std::fill(a1.begin(),a1.end(),T(100));
    std::fill(a2.begin(),a2.end(),T(5));
}

//-----------------------------------------------------------------------------
template<typename T> void AddOperatorTest<T>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename T> void AddOperatorTest<T>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    Add<na_type,na_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    s_type s(10);
    Add<na_type,s_type> op2(a1,s);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    Add<s_type,s_type> op3(s,s);
    CPPUNIT_ASSERT(s.size() == op3.size());

}

//-----------------------------------------------------------------------------
template<typename T> void AddOperatorTest<T>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    Add<na_type,na_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++)
        check_equality(op1[i],T(105));

    s_type s(10);
    Add<na_type,s_type> op2(a1,s);

    for(size_t i=0;i<op2.size();i++)
        check_equality(op2[i],T(110));
}

//-----------------------------------------------------------------------------
template<typename T> void AddOperatorTest<T>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    Add<na_type,na_type> op1(a1,a2);
#ifdef NOFOREACH
    for(auto iter = op1.begin();iter!=op1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op1) 
    {
#endif 
        check_equality(v,T(105));
    }

    s_type s(10);
    Add<na_type,s_type> op2(a1,s);
#ifdef NOFOREACH
    for(auto iter = op2.begin();iter!=op2.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op2) 
    {
#endif 
        check_equality(v,T(110));
    }
}

//-----------------------------------------------------------------------------
template<typename T> void AddOperatorTest<T>::test_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    na_type r = atype(shape);
    r = a1+a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(105));
    }

    r = a1+10;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(110));
    }

    r = 95 + a1;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(195));
    }

    //put it all together

    r = a1 + 10 + a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(115));
    }

}
