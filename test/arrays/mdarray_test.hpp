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
 *  Created on: Oct 28, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include <algorithm>

#include "common.hpp"

#include "../data_generator.hpp"
#include "../EqualityCheck.hpp"

using namespace pni::core;

/*!
\brief darray template test

\tparam STORAGE type
\tparam MAPT index map type
 */
template<typename ATYPE>
class mdarray_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(mdarray_test);
        CPPUNIT_TEST(test_linear_access_operator);
        CPPUNIT_TEST(test_linear_access_at);
        CPPUNIT_TEST(test_linear_access_iterators);
        CPPUNIT_TEST(test_linear_access_reverse_iterators);
        CPPUNIT_TEST(test_multiindex_access_operator);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef typename ATYPE::map_type     index_map_type;
        typedef typename ATYPE::storage_type storage_type;
        typedef typename ATYPE::value_type   value_type;
        std::vector<value_type> ref_data; //buffer with reference data
        ATYPE array;
        shape_t shape;

        //---------------------------------------------------------------------
        template<typename CTYPE> 
        static void allocate_storage(CTYPE &s,size_t n)
        {
            s = CTYPE(n);
        }

        //---------------------------------------------------------------------
        template<typename T,size_t N>
        static void allocate_storage(std::array<T,N> &c,size_t n)
        {
        }
    public:
        void setUp();
        void tearDown();
        void test_linear_access_operator();
        void test_linear_access_at();
        void test_linear_access_iterators();
        void test_linear_access_reverse_iterators();
        void test_reverse_iterators();
        void test_multiindex_access_operator();
        void test_inquery();
};

//------------------------------------------------------------------------------
template<typename ATYPE> void mdarray_test<ATYPE>::setUp()
{
    shape = {2,3,5};
    ref_data = std::vector<value_type>(2*3*5);
    std::generate(ref_data.begin(),ref_data.end(),random_generator<value_type>());
    
    //create reference data 
    std::iota(ref_data.begin(),ref_data.end(),0.);    

    //create the target array
    auto map = map_utils<index_map_type>::create(shape);
    storage_type storage;
    allocate_storage(storage,map.max_elements());
    array = ATYPE(map,storage);
}

//------------------------------------------------------------------------------
template<typename ATYPE> void mdarray_test<ATYPE>::tearDown() { }

//------------------------------------------------------------------------------
template<typename ATYPE> void mdarray_test<ATYPE>::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(array.rank() == 3);
    CPPUNIT_ASSERT(array.size() == 30);
    CPPUNIT_ASSERT(ATYPE::type_id == type_id_map<value_type>::type_id);
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_test<ATYPE>::test_linear_access_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //write data to the array
    for(size_t i=0;i<array.size();++i) array[i] = ref_data[i];

    //read data back
    for(size_t i=0;i<array.size();++i) check_equality(array[i],ref_data[i]);

    //test with constant access
    const ATYPE &ca = array;

    //read data back
    for(size_t i=0;i<array.size();++i) check_equality(array[i],ref_data[i]);
}

//------------------------------------------------------------------------------
template<typename ATYPE>
void mdarray_test<ATYPE>::test_linear_access_at()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    //write data to the array
    for(size_t i=0;i<array.size();++i) array.at(i) = ref_data.at(i);

    //read data back
    for(size_t i=0;i<array.size();++i) 
        check_equality(array.at(i),ref_data.at(i));

    CPPUNIT_ASSERT_THROW(array.at(array.size()),index_error);

    //test with constant access
    const ATYPE &ca = array;

    //read data back
    for(size_t i=0;i<ca.size();++i) 
        check_equality(ca.at(i),ref_data.at(i));
    
    CPPUNIT_ASSERT_THROW(ca.at(array.size()),index_error);
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_test<ATYPE>::test_linear_access_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    auto aiter = array.begin();
    auto viter = ref_data.begin();

    //write data
    for(;aiter!=array.end();++aiter,++viter)
        *aiter = *viter;
   
    //read data back
    aiter = array.begin();
    viter = ref_data.begin();
    for(;aiter!=array.end();++aiter,++viter)
        check_equality(*aiter,*viter);

    //test with constant iterator
    const ATYPE &ca = array;
    auto caiter = ca.begin();
    viter = ref_data.begin();
    for(;caiter != ca.end();++caiter,++viter)
        check_equality(*caiter,*viter);
}

//------------------------------------------------------------------------------
template<typename ATYPE>
void mdarray_test<ATYPE>::test_linear_access_reverse_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    auto aiter = array.rbegin();
    auto viter = ref_data.rbegin();

    //write data
    for(;aiter!=array.rend();++aiter,++viter)
        *aiter = *viter;
   
    //read data back
    aiter = array.rbegin();
    viter = ref_data.rbegin();
    for(;aiter!=array.rend();++aiter,++viter)
        check_equality(*aiter,*viter);

    //test with constant iterator
    const ATYPE &ca = array;
    auto caiter = ca.rbegin();
    viter = ref_data.rbegin();
    for(;caiter != ca.rend();++caiter,++viter)
        check_equality(*caiter,*viter);
}

//-----------------------------------------------------------------------------
template<typename ATYPE> 
void mdarray_test<ATYPE>::test_multiindex_access_operator()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //write data
    auto viter = ref_data.begin();
    for(size_t i=0;i<shape[0];++i)
        for(size_t j=0;j<shape[1];++j)
            for(size_t k=0;k<shape[2];++k)
                array(i,j,k) = *viter++;

    //read data back
    viter = ref_data.begin();
    for(size_t i=0;i<shape[0];++i)
        for(size_t j=0;j<shape[1];++j)
            for(size_t k=0;k<shape[2];++k)
                check_equality(array(i,j,k),*viter++);

    //test with a const reference
    viter = ref_data.begin();
    const ATYPE &ca = array;
    for(size_t i=0;i<shape[0];++i)
        for(size_t j=0;j<shape[1];++j)
            for(size_t k=0;k<shape[2];++k)
                check_equality(array(i,j,k),*viter++);

}


