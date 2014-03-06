//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Nov 27, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <algorithm>
#include <boost/current_function.hpp>

#include <pni/core/arrays.hpp>
#include "../compare.hpp"
#include "../data_generator.hpp"

using namespace pni::core;

/*! 
 \brief test inplace arithemtics modules

 This test 
 */
template<typename IPT,typename ATYPE>
class inplace_arithmetics_test: public CppUnit::TestFixture 
{
        typedef inplace_arithmetics_test<IPT,ATYPE> test_type;
        CPPUNIT_TEST_SUITE(test_type);
        CPPUNIT_TEST(test_add_scalar);
        CPPUNIT_TEST(test_add_array);
        CPPUNIT_TEST(test_sub_scalar);
        CPPUNIT_TEST(test_sub_array);
        CPPUNIT_TEST(test_div_scalar);
        CPPUNIT_TEST(test_div_array);
        CPPUNIT_TEST(test_mult_scalar);
        CPPUNIT_TEST(test_mult_array);

        CPPUNIT_TEST_SUITE_END();
    private:
        typedef ATYPE array_type;
        typedef typename array_type::value_type value_type;
        typedef std::vector<value_type> vector_type;
          
        typedef array_factory<ATYPE> afactory;
        shape_t shape;
        array_type lhs;
        array_type rhs_array;
        value_type rhs_scalar; 
        vector_type data;

    public:
        void setUp();
        void tearDown();

        void test_add_scalar();
        void test_add_array();
        void test_sub_scalar();
        void test_sub_array();
        void test_div_scalar();
        void test_div_array();
        void test_mult_scalar();
        void test_mult_array();

};

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE> 
void inplace_arithmetics_test<IPT,ATYPE>::setUp()
{
    shape = shape_t({2,3,4});
    lhs = afactory::create(shape);
    rhs_array = afactory::create(shape);
    data = vector_type(lhs.size());
   
    //initialize the LHS array
    std::fill(lhs.begin(),lhs.end(),1);

    //generate random data
    std::generate(data.begin(),data.end(),random_generator<value_type>(1,10));

    //copy data
    std::copy(data.begin(),data.end(),rhs_array.begin());

    //initialize scalar data
    rhs_scalar = random_generator<value_type>(1,10)();
    
}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE> 
void inplace_arithmetics_test<IPT,ATYPE>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_add_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::add(lhs,rhs_scalar);

    for(auto v: lhs)
        compare(v,rhs_scalar+value_type(1));
}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_add_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::add(lhs,rhs_array);

    auto lhs_iter = lhs.begin();
    auto rhs_iter = rhs_array.begin();

    while(lhs_iter != lhs.end())
        compare(*lhs_iter++,(*rhs_iter++)+value_type(1));

}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_sub_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::sub(lhs,rhs_scalar);

    for(auto v: lhs)
        compare(v,value_type(1)-rhs_scalar);
}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_sub_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::sub(lhs,rhs_array);

    auto lhs_iter = lhs.begin();
    auto rhs_iter = rhs_array.begin();

    while(lhs_iter != lhs.end())
        compare(*lhs_iter++,value_type(1)-(*rhs_iter++));

}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_div_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::div(lhs,rhs_scalar);

    for(auto v: lhs)
        compare(v,value_type(1)/rhs_scalar);
}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_div_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::div(lhs,rhs_array);

    auto lhs_iter = lhs.begin();
    auto rhs_iter = rhs_array.begin();

    while(lhs_iter != lhs.end())
        compare(*lhs_iter++,value_type(1)/(*rhs_iter++));

}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_mult_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::mult(lhs,rhs_scalar);

    for(auto v: lhs)
        compare(v,value_type(1)*rhs_scalar);
}

//-----------------------------------------------------------------------------
template<typename IPT,typename ATYPE>
void inplace_arithmetics_test<IPT,ATYPE>::test_mult_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    IPT::mult(lhs,rhs_array);

    auto lhs_iter = lhs.begin();
    auto rhs_iter = rhs_array.begin();

    while(lhs_iter != lhs.end())
        compare(*lhs_iter++,value_type(1)*(*rhs_iter++));

}

