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
 *  Created on: Nov 13, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/container_utils.hpp>

using namespace pni::core;

/*!
\brief test for index policy implementations

This template is a general approach to test index policy maps. The entire test
can be parametrized via its template parameters.

\tparam PIMPT policy type for which the test should be performed
\tparam TPARAMS test parameters
\tparam STYPE container type for shape data
\tparam ITYPE container type for index data
\tparam offset the offset for which we run the test
\tparam INDEXES the indexes for offset
*/
template<
         typename  PIMPT,
         typename  TPARAMS,
         typename  STYPE,
         typename  ITYPE,
         size_t    offset,
         size_t... INDEXES
        > 
class index_policy_implementation_test: public CppUnit::TestFixture 
{
        typedef index_policy_implementation_test<PIMPT,TPARAMS,STYPE,ITYPE,
                                                 offset,INDEXES...> test_type;
        CPPUNIT_TEST_SUITE(test_type);
        CPPUNIT_TEST(test_index_to_offset);
        CPPUNIT_TEST(test_offset_to_index);
        CPPUNIT_TEST_SUITE_END();

        //local private variables
        STYPE shape;
        ITYPE index;

    public:
        //---------------------------------------------------------------------
        void setUp() 
        { 
            shape = container_utils<STYPE>::create(TPARAMS::shape.begin(),
                                                   TPARAMS::shape.end());
            index = container_utils<ITYPE>::create({INDEXES...});
        }

        //---------------------------------------------------------------------
        void tearDown(){}

        //---------------------------------------------------------------------
        void test_index_to_offset()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

            CPPUNIT_ASSERT(PIMPT::offset(shape,index)==offset);
        }

        //---------------------------------------------------------------------
        void test_offset_to_index()
        {
            std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

            ITYPE i = container_utils<ITYPE>::create(TPARAMS::rank,
                                                     typename ITYPE::value_type());
            PIMPT::index(shape,i,offset);
            CPPUNIT_ASSERT(std::equal(index.begin(),index.end(),i.begin()));

        }

};

