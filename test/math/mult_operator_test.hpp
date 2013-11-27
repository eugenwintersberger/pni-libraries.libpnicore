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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <algorithm>

#include "array_factory.hpp"

#include "EqualityCheck.hpp"

using namespace pni::core;

/*!
 Do testing only for DArray - all array types provide the same interface and
 thus can be considered as equivalent. However, we have to check ArrayView
 wether or not it works.
 */
template<typename ATYPE> class mult_operator_test: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(mult_operator_test<ATYPE>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST(test_operator);
        CPPUNIT_TEST_SUITE_END();
    private:
        //==========private types==============================================
        typedef numarray<ATYPE> na_type;
        typedef typename ATYPE::value_type value_type;
        typedef scalar<value_type> s_type;

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
template<typename ATYPE> void mult_operator_test<ATYPE>::setUp()
{
    shape = shape_t({2,3,4});
    a1 = na_type(array_factory<ATYPE>::create(shape));
    a2 = na_type(array_factory<ATYPE>::create(shape));
    
    std::fill(a1.begin(),a1.end(),value_type(10));
    std::fill(a2.begin(),a2.end(),value_type(2));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    mult<na_type,na_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    s_type s(10);
    mult<na_type,s_type> op2(a1,s);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    mult<s_type,s_type> op3(s,s);
    CPPUNIT_ASSERT(s.size() == op3.size());

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    mult<na_type,na_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++)
        check_equality(op1[i],value_type(20));

    s_type s(10);
    mult<na_type,s_type> op2(a1,s);

    for(size_t i=0;i<op2.size();i++)
        check_equality(op2[i],value_type(100));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    mult<na_type,na_type> op1(a1,a2);
#ifdef NOFOREACH
    for(auto iter = op1.begin();iter!=op1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op1) 
    {
#endif
        check_equality(v,value_type(20));
    }

    s_type s(10);
    mult<na_type,s_type> op2(a1,s);
#ifdef NOFOREACH
    for(auto iter = op2.begin();iter!=op2.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op2) 
    {
#endif
        check_equality(v,value_type(100));
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    na_type r = array_factory<ATYPE>::create(shape);
    r = a1*a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,value_type(20));
    }

    r = a1*10;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,value_type(100));
    }

    r = 5*a1;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,value_type(50));
    }

    //put it all together

    r = a1 * 2 * a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,value_type(40));
    }

}
