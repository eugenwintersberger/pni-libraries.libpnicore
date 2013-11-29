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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <algorithm>
#include <boost/current_function.hpp>

#include <pni/core/arrays.hpp>
#include <pni/core/math/add_op.hpp>
#include "../compare.hpp"
#include "../data_generator.hpp"
#include <pni/core/scalar.hpp>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

using namespace pni::core;

/*
 Do testing only for DArray - all array types provide the same interface and
 thus can be considered as equivalent. However, we have to check ArrayView
 wether or not it works.
 */
template<typename ATYPE> class add_operator_test: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(add_operator_test<ATYPE>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST(test_operator);
        CPPUNIT_TEST_SUITE_END();
    private:
        //==========private types==============================================
        typedef ATYPE array_type;
        typedef typename ATYPE::value_type value_type;
        typedef scalar<value_type> scalar_type;

        //===================private memebers==================================
        array_type a1;
        array_type a2;
        scalar_type s1;
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
template<typename ATYPE> void add_operator_test<ATYPE>::setUp()
{
    shape = shape_t({2,3,4});
    a1 = array_factory<array_type>::create(shape);
    a2 = array_factory<array_type>::create(shape);

    std::generate(a1.begin(),a1.end(),random_generator<value_type>());
    std::generate(a2.begin(),a2.end(),random_generator<value_type>());

    s1 = random_generator<value_type>()();
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void add_operator_test<ATYPE>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename ATYPE> void add_operator_test<ATYPE>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    add_op<array_type,array_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    add_op<array_type,scalar_type> op2(a1,s1);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    add_op<scalar_type,scalar_type> op3(s1,s1);
    CPPUNIT_ASSERT(s1.size() == op3.size());

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void add_operator_test<ATYPE>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    add_op<array_type,array_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++) compare(op1[i],a1[i]+a2[i]);

    add_op<array_type,scalar_type> op2(a1,s1);

    for(size_t i=0;i<op2.size();i++) compare(op2[i],a1[i]+s1[i]);
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void add_operator_test<ATYPE>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    add_op<array_type,array_type> op1(a1,a2);
    auto iter1 = a1.begin();
    auto iter2 = a2.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,op1)
#else
    for(auto v: op1) 
#endif 
        compare(v,(*iter1++)+(*iter2));

    add_op<array_type,scalar_type> op2(a1,s1);
    iter1 = a1.begin();
    auto siter1 = s1.begin();
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,op2)
#else
    for(auto v: op2) 
#endif 
        compare(v,(*iter1++)+(*siter1++));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void add_operator_test<ATYPE>::test_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    auto r = array_factory<ATYPE>::create(shape);
    r = a1+a2;
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif 
        compare(v,value_type(105));

    r = a1+10;
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif 
        compare(v,value_type(110));

    r = 95 + a1;
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif 
        compare(v,value_type(195));

    //put it all together

    r = a1 + 10 + a2;
#ifdef NOFOREACH
    BOOST_FOREACH(auto v,r)
#else
    for(auto v: r) 
#endif 
        compare(v,value_type(115));

}
