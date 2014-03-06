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
//!  Created on: Jul 25, 2012
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <algorithm>

#include <pni/core/arrays.hpp>
#include <pni/core/arrays/array_arithmetic.hpp>
#include "../compare.hpp"
#include "../data_generator.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

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
        CPPUNIT_TEST(test_operator_on_view);
        CPPUNIT_TEST_SUITE_END();
    private:
        //==========private types==============================================
        typedef ATYPE array_type;
        typedef typename ATYPE::value_type value_type;
        typedef scalar<value_type> scalar_type;
        //===================private memebers==================================
        array_type a1,a2;
        scalar_type s1;
        shape_t shape;

    public:
        void setUp();
        void tearDown();
        
        void test_construction();
        void test_access();
        void test_iterator();
        void test_operator();
        void test_operator_on_view();
};

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::setUp()
{
    shape = shape_t({2,3,4});
    a1 = array_factory<array_type>::create(shape);
    a2 = array_factory<array_type>::create(shape);

    std::generate(a1.begin(),a1.end(),random_generator<value_type>(1,10));
    std::generate(a2.begin(),a2.end(),random_generator<value_type>(1,10));
    
    s1 = random_generator<value_type>(1,10)();
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    mult_op<array_type,array_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    mult_op<array_type,scalar_type> op2(a1,s1);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    mult_op<scalar_type,array_type> op3(s1,a1);
    CPPUNIT_ASSERT(op3.size() == a1.size());
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    mult_op<array_type,array_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++) compare(op1[i],a1[i]*a2[i]);

    mult_op<array_type,scalar_type> op2(a1,s1);

    for(size_t i=0;i<op2.size();i++) compare(op2[i],a1[i]*s1[i]);
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    mult_op<array_type,array_type> op1(a1,a2);
    auto iter1 = a1.begin();
    auto iter2 = a2.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,op1)
#else
    for(auto v: op1) 
#endif
        compare(v,(*iter1++)*(*iter2++));

    mult_op<array_type,scalar_type> op2(a1,s1);
    iter1 = a1.begin();
    auto siter = s1.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,op2)
#else
    for(auto v: op2) 
#endif
        compare(v,(*iter1++)*(*siter++));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array_type r(a1*a2);
    auto iter1 = a1.begin();
    auto iter2 = a2.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif
        compare(v,(*iter1++)*(*iter2++));

    r = a1*value_type(10);
    iter1 = a1.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif
        compare(v,(*iter1++)*value_type(10));

    r = value_type(5)*a1;
    iter1 = a1.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif
        compare(v,value_type(5)*(*iter1++));

    //put it all together

    r = a1 * value_type(2) * a2;
    iter1 = a1.begin();
    iter2 = a2.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif
        compare(v,(*iter1++)*value_type(2)*(*iter2++));

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void mult_operator_test<ATYPE>::test_operator_on_view()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef dynamic_array<value_type> result_type;
    auto v1 = a1(0,slice(0,3),slice(0,4));
    auto v2 = a2(0,slice(0,3),slice(0,4));
    result_type r(v1 * v2);
    auto iter1 = v1.begin();
    auto iter2 = v2.begin();
    auto riter = r.begin();

    for(;riter!=r.end();++riter)
        compare(*riter,*iter1++ * *iter2++);

    r = v1*value_type(10);
    riter = r.begin();
    iter1 = v1.begin();
    for(;riter!=r.end();++riter)
        compare(*riter,*iter1++ * value_type(10));

    r = value_type(95) * v1;
    riter = r.begin();
    iter1 = v1.begin();
    for(;riter!=r.end();++riter)
        compare(*riter,value_type(95)*(*iter1++));

    //put it all together
    r = v1 * value_type(10) * v2;
    riter = r.begin();
    iter1 = v1.begin();
    iter2 = v2.begin();
    for(;riter!=r.end();++riter)
        compare(*riter,*iter1++ * value_type(10) * *iter2++);
}
