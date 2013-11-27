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
class array_view_unary_arithmetic_test : public CppUnit::TestFixture
{
        typedef typename ATYPE::map_type     index_map_type;
        typedef typename ATYPE::storage_type storage_type;
        typedef typename ATYPE::value_type   value_type;
        typedef dynamic_array<value_type> darray;
        
        typedef array_view_unary_arithmetic_test<ATYPE> test_type;
        CPPUNIT_TEST_SUITE(test_type);
        CPPUNIT_TEST(test_add_scalar);
        CPPUNIT_TEST(test_add_array);

        CPPUNIT_TEST(test_sub_scalar);
        CPPUNIT_TEST(test_sub_array);

        CPPUNIT_TEST(test_mult_scalar);
        CPPUNIT_TEST(test_mult_array);

        CPPUNIT_TEST(test_div_scalar);
        CPPUNIT_TEST(test_div_array);
        CPPUNIT_TEST_SUITE_END();
    private:
         
        std::vector<value_type> ref_data; //buffer with reference data
        ATYPE array;
        ATYPE orig_array;
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
        void test_add_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto view = array(1,slice(0,3),slice(0,5));
            darray orig(view);
            auto rhs = create_random_array<darray>(view.template shape<shape_t>());

            view += rhs;

            auto orig_iter = orig.begin();
            auto rhs_iter  = rhs.begin();
            for(auto v: view)
                compare(v,(*orig_iter++)+(*rhs_iter++));
        }
        
        //---------------------------------------------------------------------
        void test_sub_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto view = array(1,slice(0,3),slice(0,5));
            darray orig(view);
            auto rhs = create_random_array<darray>(view.template shape<shape_t>());

            view -= rhs;

            auto orig_iter = orig.begin();
            auto rhs_iter  = rhs.begin();
            for(auto v: view)
                compare(v,(*orig_iter++)-(*rhs_iter++));
        }
        
        //---------------------------------------------------------------------
        void test_mult_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto view = array(1,slice(0,3),slice(0,5));
            darray orig(view);
            auto rhs = create_random_array<darray>(view.template shape<shape_t>());

            view *= rhs;

            auto orig_iter = orig.begin();
            auto rhs_iter  = rhs.begin();
            for(auto v: view)
                compare(v,(*orig_iter++)*(*rhs_iter++));
        }
        
        //---------------------------------------------------------------------
        void test_div_array()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            auto view = array(1,slice(0,3),slice(0,5));
            darray orig(view);
            auto rhs = create_random_array<darray>(view.template shape<shape_t>());

            view /= rhs;

            auto orig_iter = orig.begin();
            auto rhs_iter  = rhs.begin();
            for(auto v: view)
                compare(v,(*orig_iter++)/(*rhs_iter++));
        }
};

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_unary_arithmetic_test<ATYPE>::setUp()
{
    shape = {2,3,5};
    ref_data = std::vector<value_type>(2*3*5);
    std::generate(ref_data.begin(),ref_data.end(),random_generator<value_type>());
    
    //create the target array
    array = array_factory<ATYPE>::create(shape);
    std::copy(ref_data.begin(),ref_data.end(),array.begin());
    orig_array = array;
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_unary_arithmetic_test<ATYPE>::tearDown() { }

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_unary_arithmetic_test<ATYPE>::test_add_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    auto view = array(0,slice(0,3),slice(0,5));
    view += s;

    //check if data has gone through
    for(size_t i=0;i<3;++i)
        for(size_t j=0;j<5;++j)
        {
            compare(view(i,j),array(0,i,j));
            compare(view(i,j),orig_array(0,i,j)+s);
        }

}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_unary_arithmetic_test<ATYPE>::test_sub_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    auto view = array(slice(0,2),0,slice(0,5));

    view -= s;
    for(size_t i=0;i<2;++i)
        for(size_t j=0;j<5;++j)
        {
            compare(view(i,j),array(i,0,j));
            compare(view(i,j),orig_array(i,0,j)-s);
        }
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_unary_arithmetic_test<ATYPE>::test_mult_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    auto view = array(slice(0,2),slice(0,2),3);
    view *= s;
    
    for(size_t i=0;i<2;++i)
        for(size_t j=0;j<2;++j)
        {
            compare(view(i,j),array(i,j,3));
            compare(view(i,j),orig_array(i,j,3)*s);
        }
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_unary_arithmetic_test<ATYPE>::test_div_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto s = random_generator<value_type>()();
    auto view = array(slice(0,2),slice(1,3),slice(2,5));
    view /= s;

    for(size_t i=0;i<2;++i)
        for(size_t j=0;j<2;++j)
            for(size_t k=0;k<3;++k)
            {
                compare(view(i,j,k),array(i,j+1,k+2));
                compare(view(i,j,k),orig_array(i,j+1,k+2)/s);
            }
}
