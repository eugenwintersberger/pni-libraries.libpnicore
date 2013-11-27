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
 *  Created on: Nov 28, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include <algorithm>

#include <pni/core/arrays.hpp>

#include "../data_generator.hpp"
#include "../compare.hpp"

using namespace pni::core;

/*!
\brief darray template test

\tparam STORAGE type
\tparam MAPT index map type
 */
template<typename ATYPE>
class mdarray_unary_arithmetic_test : public CppUnit::TestFixture
{
        typedef typename ATYPE::map_type     index_map_type;
        typedef typename ATYPE::storage_type storage_type;
        typedef typename ATYPE::value_type   value_type;
        
        typedef dynamic_array<value_type>      darray;
        typedef static_array<value_type,2,3,5> sarray;
        typedef fixed_dim_array<value_type,3>  farray;
        
        typedef mdarray_unary_arithmetic_test<ATYPE> test_type;
        CPPUNIT_TEST_SUITE(test_type);
        CPPUNIT_TEST(test_add_scalar);
        CPPUNIT_TEST(test_add_array<darray>);
        CPPUNIT_TEST(test_add_array<sarray>);
        CPPUNIT_TEST(test_add_array<farray>);

        CPPUNIT_TEST(test_sub_scalar);
        CPPUNIT_TEST(test_sub_array<darray>);
        CPPUNIT_TEST(test_sub_array<sarray>);
        CPPUNIT_TEST(test_sub_array<farray>);

        CPPUNIT_TEST(test_mult_scalar);
        CPPUNIT_TEST(test_mult_array<darray>);
        CPPUNIT_TEST(test_mult_array<sarray>);
        CPPUNIT_TEST(test_mult_array<farray>);

        CPPUNIT_TEST(test_div_scalar);
        CPPUNIT_TEST(test_div_array<darray>);
        CPPUNIT_TEST(test_div_array<sarray>);
        CPPUNIT_TEST(test_div_array<farray>);
        CPPUNIT_TEST_SUITE_END();
    private:

        std::vector<value_type> ref_data; //buffer with reference data
        ATYPE array;
        shape_t shape;

        template<typename RTYPE,typename CTYPE> 
        RTYPE create_random_array(const CTYPE &shape)
        {
            auto data = array_factory<RTYPE>::create(shape);
            std::generate(data.begin(),data.end(),
                          random_generator<typename RTYPE::value_type>());

            return data;
        }

    public:
        void setUp();
        void tearDown();
        void test_add_scalar();
        void test_sub_scalar();
        void test_mult_scalar();
        void test_div_scalar();

        //---------------------------------------------------------------------
        template<typename RTYPE> void test_add_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto rhs = create_random_array<RTYPE>(shape);

            array += rhs;

            auto rhs_iter = rhs.begin();
            auto ref_iter = ref_data.begin();
            for(auto v: array) compare(v,(*ref_iter++)+(*rhs_iter++));
        }
        
        //---------------------------------------------------------------------
        template<typename RTYPE> void test_sub_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto rhs = create_random_array<RTYPE>(shape);

            array -= rhs;

            auto rhs_iter = rhs.begin();
            auto ref_iter = ref_data.begin();
            for(auto v: array) compare(v,(*ref_iter++)-(*rhs_iter++));
        }
        
        //---------------------------------------------------------------------
        template<typename RTYPE> void test_mult_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto rhs = create_random_array<RTYPE>(shape);

            array *= rhs;

            auto rhs_iter = rhs.begin();
            auto ref_iter = ref_data.begin();
            for(auto v: array) compare(v,(*ref_iter++)*(*rhs_iter++));
        }
        
        //---------------------------------------------------------------------
        template<typename RTYPE> void test_div_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto rhs = create_random_array<RTYPE>(shape);

            array /= rhs;

            auto rhs_iter = rhs.begin();
            auto ref_iter = ref_data.begin();
            for(auto v: array) compare(v,(*ref_iter++)/(*rhs_iter++));
        }
};

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_unary_arithmetic_test<ATYPE>::setUp()
{
    shape = {2,3,5};
    ref_data = std::vector<value_type>(2*3*5);
    std::generate(ref_data.begin(),ref_data.end(),random_generator<value_type>());
    
    //create the target array
    array = array_factory<ATYPE>::create(shape);
    std::copy(ref_data.begin(),ref_data.end(),array.begin());
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_unary_arithmetic_test<ATYPE>::tearDown() { }

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_unary_arithmetic_test<ATYPE>::test_add_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    array += s;
    auto riter = ref_data.begin();
    for(auto v: array) compare(v,(*riter++) + s);
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_unary_arithmetic_test<ATYPE>::test_sub_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    array -= s;
    auto riter = ref_data.begin();
    for(auto v: array) compare(v,(*riter++) - s);
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_unary_arithmetic_test<ATYPE>::test_mult_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    array *= s;
    auto riter = ref_data.begin();
    for(auto v: array) compare(v,(*riter++) * s);
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_unary_arithmetic_test<ATYPE>::test_div_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    array /= s;
    auto riter = ref_data.begin();
    for(auto v: array) compare(v,(*riter++) / s);
}
