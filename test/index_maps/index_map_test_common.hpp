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
 *  Created on: Oct 18, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <list>
#include <array>
#include <functional>
#include <algorithm>

#include <pni/core/cindex_map.hpp>
#include <pni/core/static_cindex_map.hpp>

using namespace pni::core;

template<size_t... DIMS>
struct index_test_params
{
    typedef std::array<size_t,sizeof...(DIMS)> index_t;
    constexpr static index_t shape{{DIMS...}};
    constexpr static size_t rank = sizeof...(DIMS);
};

template<size_t... DIMS> 
constexpr typename index_test_params<DIMS...>::index_t index_test_params<DIMS...>::shape;
template<size_t... DIMS>
constexpr size_t index_test_params<DIMS...>::rank; 



/*!
\brief general test

This class provides all tests that a particular index map has to pass. The
following functionality has to be provided by each index map class

\li offset from  container
\li offset from variadic template indices
\li index from offset (index as a general container)

All maps can be constructed from a container - thus this is the only
construction method we are using. Special construction methods must be tested by
other test fixtures.

\tparam IMAP index map type
\tparam offset the correct offset for the test
\tparam indexes the indexes for the offset 
*/
template<typename TPARAM,typename IMAP,size_t offset,size_t... indexes> 
class index_map_test_common: public CppUnit::TestFixture 
{
        typedef index_map_test_common<TPARAM,IMAP,offset,indexes...> test_type;
        CPPUNIT_TEST_SUITE(test_type);
        CPPUNIT_TEST(test_creation);
        CPPUNIT_TEST(test_offset_from_container<std::vector<size_t> >);
        CPPUNIT_TEST(test_offset_from_container<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_offset_from_container<std::vector<int> >);
        CPPUNIT_TEST(test_offset_from_container<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_offset_from_container<std::list<size_t> >);
        CPPUNIT_TEST(test_offset_from_container<std::list<ssize_t> >);
        CPPUNIT_TEST(test_offset_from_container<std::list<int> >);
        CPPUNIT_TEST(test_offset_from_container<std::list<unsigned int> >);
        CPPUNIT_TEST(test_index_from_offset<std::vector<size_t> >);
        CPPUNIT_TEST(test_index_from_offset<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_index_from_offset<std::vector<int> >);
        CPPUNIT_TEST(test_index_from_offset<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_index_from_offset<std::list<size_t> >);
        CPPUNIT_TEST(test_index_from_offset<std::list<ssize_t> >);
        CPPUNIT_TEST(test_index_from_offset<std::list<int> >);
        CPPUNIT_TEST(test_index_from_offset<std::list<unsigned int> >);
        CPPUNIT_TEST(test_inquery<std::vector<size_t> >);
        CPPUNIT_TEST(test_inquery<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_inquery<std::vector<int> >);
        CPPUNIT_TEST(test_inquery<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_inquery<std::list<size_t> >);
        CPPUNIT_TEST(test_inquery<std::list<ssize_t> >);
        CPPUNIT_TEST(test_inquery<std::list<int> >);
        CPPUNIT_TEST(test_inquery<std::list<unsigned int> >);
        CPPUNIT_TEST_SUITE_END();
    private:
        shape_t _shape;
        IMAP _map;

        //---------------------------------------------------------------------
        template<typename MAPT> void create_map(MAPT &map)
        {
            _shape = shape_t(TPARAM::rank);
            std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),_shape.begin());
            map = IMAP(_shape);
        }

        //---------------------------------------------------------------------
        template<size_t... DIMS> 
        void create_map(static_cindex_map<DIMS...> &map) 
        { 
            _shape = shape_t(TPARAM::rank);
            std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),_shape.begin());
        }

    public:
        //---------------------------------------------------------------------
        void setUp()
        {
            create_map(_map);
        }

        //---------------------------------------------------------------------
        void tearDown(){}

        //---------------------------------------------------------------------
        void test_creation()
        {
            IMAP m;
            creation_test(m);
        }

        //---------------------------------------------------------------------
        /*!
        \brief test offset computation

        Here we test the offset computation from an arbitrary contianer type. 
        Should be used with the following containers

        \li std::vector 
        \li std::array (currently missing)
        \li std::list

        Besides the offset computation we have to check for the following
        exceptions

        \li shape_missmatch_error - if index and map ranks do not match
        \li index_error - if the rank matches but an index overflow occurs

        */
        template<typename CTYPE> void test_offset_from_container()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl; 
            
            CTYPE index{indexes...};

            CPPUNIT_ASSERT(_map.offset(index) == offset);

            //check for exceptions
            //check if larger rank
            shape_t s{indexes...};
            s.push_back(10);
            CPPUNIT_ASSERT_THROW(_map.offset(s),shape_mismatch_error);
            //check if smaller rank
            s = shape_t{indexes...};
            s.pop_back();
            CPPUNIT_ASSERT_THROW(_map.offset(s),shape_mismatch_error);

            for(size_t i=0;i<TPARAM::rank;++i)
            {
                s = shape_t{indexes...};
                s[i] = TPARAM::shape[i];
                CPPUNIT_ASSERT_THROW(_map.offset(s),index_error);
            }
        }

        //---------------------------------------------------------------------
        void test_offset_from_variadic()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
            CPPUNIT_ASSERT(_map.offset(indexes...) == offset);
        }

        //---------------------------------------------------------------------
        template<typename CTYPE> void test_index_from_offset()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

            CTYPE index_ref{indexes...};
            CTYPE index1(index_ref.size());
           
            _map.index(offset,index1);
            CPPUNIT_ASSERT(index1.size() == index_ref.size());
            CPPUNIT_ASSERT(std::equal(index_ref.begin(),index_ref.end(),
                                      index1.begin()));

            CPPUNIT_ASSERT_THROW(_map.index(_map.size(),index1),size_mismatch_error);
            index1.push_back(10);
            CPPUNIT_ASSERT_THROW(_map.index(offset,index1),shape_mismatch_error);
            index1.pop_back();index1.pop_back();
            CPPUNIT_ASSERT_THROW(_map.index(offset,index1),shape_mismatch_error);

            index1 = _map.template index<CTYPE>(offset);
            CPPUNIT_ASSERT(std::equal(index1.begin(),index1.end(),index_ref.begin()));
            
            CPPUNIT_ASSERT_THROW(_map.template index<CTYPE>(_map.size()),size_mismatch_error);

        }

        //---------------------------------------------------------------------
        template<typename CTYPE> void test_inquery()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

            CPPUNIT_ASSERT(_map.rank() == _shape.size());
            CPPUNIT_ASSERT(_map.size() ==
                    std::accumulate(_shape.begin(),_shape.end(),
                        1,std::multiplies<size_t>()));

            auto s =_map.template shape<CTYPE>();
            CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),_shape.begin()));
        }
};

