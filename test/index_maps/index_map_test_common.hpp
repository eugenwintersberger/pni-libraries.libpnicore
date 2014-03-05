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
//!  Created on: Oct 18, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "common.hpp"

//!
//! \brief general test
//! 
//! This class provides all tests that a particular index map has to pass. The
//! following functionality has to be provided by each index map class
//! 
//! \li offset from  container
//! \li offset from variadic template indices
//! \li index from offset (index as a general container)
//! 
//! All maps can be constructed from a container - thus this is the only
//! construction method we are using. Special construction methods must be 
//! tested by other test fixtures.
//! 
//! \tparam IMAP index map type
//! \tparam offset the correct offset for the test
//! \tparam indexes the indexes for the offset 
//! 
template<typename TPARAM,typename IMAP,size_t offset,size_t... indexes> 
class index_map_test_common: public CppUnit::TestFixture 
{
        typedef index_map_test_common<TPARAM,IMAP,offset,indexes...> test_type;
        CPPUNIT_TEST_SUITE(test_type);
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
        template<typename CTYPE> void copy_storage(CTYPE &c)
        {
            c = CTYPE(TPARAM::rank);
            std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),c.begin());
        }

        //---------------------------------------------------------------------
        template<typename T,size_t... DIMS> 
        void copy_storage(std::array<T,DIMS...> &c) 
        {
            std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),c.begin());
        }

        //---------------------------------------------------------------------
        template<typename MAPT> void create_index_map(MAPT &m)
        {
            typedef typename MAPT::storage_type storage_type;
            
            //copy shape to storage
            storage_type storage;
            copy_storage(storage);
    
            _map = IMAP(storage);
        }

        //---------------------------------------------------------------------
        template<typename POL,size_t... DIMS> 
        void create_index_map(static_index_map<POL,DIMS...> &m)
        {
            //there is nothing we would have to do here
        }

    public:
        //---------------------------------------------------------------------
        void setUp()
        {
            //create the shape
            _shape = shape_t(TPARAM::rank);
            std::copy(TPARAM::shape.begin(),TPARAM::shape.end(),_shape.begin());

            create_index_map(_map);
            
        }

        //---------------------------------------------------------------------
        void tearDown(){}

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
           
            auto index1 = _map.template index<CTYPE>(offset);
            CPPUNIT_ASSERT(std::equal(index1.begin(),index1.end(),index_ref.begin()));
        }

        //---------------------------------------------------------------------
        template<typename CTYPE> void test_inquery()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

            CPPUNIT_ASSERT(_map.rank() == _shape.size());
            CPPUNIT_ASSERT(_map.max_elements() ==
                    std::accumulate(_shape.begin(),_shape.end(),
                        1,std::multiplies<size_t>()));

            CPPUNIT_ASSERT(std::equal(_map.begin(),_map.end(),_shape.begin()));
        }
};

