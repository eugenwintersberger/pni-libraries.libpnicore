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
 *  Created on: Oct 23, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <array>
#include <vector>
#include <algorithm>

using namespace pni::core;

template<size_t... DIMS> struct index_test_params
{
    typedef std::array<size_t,sizeof...(DIMS)> index_t;
    constexpr static index_t shape{{DIMS...}};
    constexpr static size_t rank = sizeof...(DIMS);
};

template<size_t... DIMS> 
constexpr typename index_test_params<DIMS...>::index_t index_test_params<DIMS...>::shape;
template<size_t... DIMS>
constexpr size_t index_test_params<DIMS...>::rank; 

template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
class index_policy_test: public CppUnit::TestFixture 
{
        typedef index_policy_test<TPARAM,POL,offset,indexes...> test_type;
        CPPUNIT_TEST_SUITE(test_type);
        CPPUNIT_TEST(test_offset_ref_ref);
        CPPUNIT_TEST(test_offset_ref_move);
        CPPUNIT_TEST(test_offset_array_ref);
        CPPUNIT_TEST(test_offset_array_move);
        CPPUNIT_TEST(test_index_ref);
        CPPUNIT_TEST(test_index_array);
        CPPUNIT_TEST_SUITE_END();

    private:
        //define some types
        typedef std::vector<size_t> vector_t;
        typedef std::list<size_t>   list_t;
        typedef std::array<size_t,TPARAM::rank> array_t;
        //some private data that will be used
        vector_t vector_shape;
        array_t  array_shape; 
    public:
        void setUp();
        void tearDown();
    

        void test_offset_ref_ref();
        void test_offset_ref_move();
        void test_offset_array_ref();
        void test_offset_array_move();
        void test_index_ref();
        void test_index_array();

};

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::setUp() 
{
    vector_shape = vector_t(TPARAM::rank);
    
    std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),
              vector_shape.begin());
    std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),
              array_shape.begin());

}


//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::tearDown() {}

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::test_offset_ref_ref()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_t v_index{indexes...};
    list_t   l_index{indexes...};

    CPPUNIT_ASSERT(POL::offset(vector_shape,v_index)==offset);
    CPPUNIT_ASSERT(POL::offset(vector_shape,l_index)==offset);

}

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::test_offset_ref_move()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(POL::offset(vector_shape,vector_t{indexes...}) == offset);
    CPPUNIT_ASSERT(POL::offset(vector_shape,list_t{indexes...})   == offset);
    CPPUNIT_ASSERT(POL::offset(vector_shape,array_t{{indexes...}}) == offset);

}

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::test_offset_array_ref()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_t v_index{indexes...};
    list_t   l_index{indexes...};
    array_t  a_index{indexes...};

    CPPUNIT_ASSERT(POL::offset(array_shape,v_index)==offset);
    CPPUNIT_ASSERT(POL::offset(array_shape,l_index) == offset);
    CPPUNIT_ASSERT(POL::offset(array_shape,a_index) == offset);
}

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::test_offset_array_move()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(POL::offset(array_shape,vector_t{indexes...})==offset);
    CPPUNIT_ASSERT(POL::offset(array_shape,list_t{indexes...}) == offset);
    CPPUNIT_ASSERT(POL::offset(array_shape,array_t{{indexes...}}) == offset);

}

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::test_index_ref()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    vector_t ref_index{indexes...};
    auto v_index = POL::template index<vector_t>(vector_shape,offset);
    for(auto i: v_index)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    CPPUNIT_ASSERT(std::equal(ref_index.begin(),ref_index.end(),v_index.begin()));

    auto l_index = POL::template index<list_t>(vector_shape,offset);
    CPPUNIT_ASSERT(std::equal(ref_index.begin(),ref_index.end(),l_index.begin()));
    
    auto a_index = POL::template index<array_t>(vector_shape,offset);
    CPPUNIT_ASSERT(std::equal(ref_index.begin(),ref_index.end(),a_index.begin()));
}

//-----------------------------------------------------------------------------
template<typename TPARAM,
         typename POL,
         size_t offset,
         size_t... indexes
        >
void index_policy_test<TPARAM,POL,offset,indexes...>::test_index_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    vector_t ref_index{indexes...};
    auto v_index = POL::template index<vector_t>(array_shape,offset);
    for(auto i: v_index)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    CPPUNIT_ASSERT(std::equal(ref_index.begin(),ref_index.end(),v_index.begin()));

    auto l_index = POL::template index<list_t>(array_shape,offset);
    CPPUNIT_ASSERT(std::equal(ref_index.begin(),ref_index.end(),l_index.begin()));
    
    auto a_index = POL::template index<array_t>(array_shape,offset);
    CPPUNIT_ASSERT(std::equal(ref_index.begin(),ref_index.end(),a_index.begin()));
}

