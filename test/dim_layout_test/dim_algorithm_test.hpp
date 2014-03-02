//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
//=============================================================================
//
//  Created on: Mar 1, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>

#include <pni/core/dimension_layout/algorithms.hpp>
#include <pni/core/dimension_layout/dimension_layout.hpp>
#include <functional>

using namespace pni::core;

//!
//! \brief test of algorithms
//!
//! Thest the dimension layout algorithms.
//! 
class dim_algorithm_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(dim_algorithm_test);
        CPPUNIT_TEST(test_span);
        CPPUNIT_TEST(test_size);
        CPPUNIT_TEST(test_rank);
        CPPUNIT_TEST(test_effective_rank);
        CPPUNIT_TEST(test_is_compact);
        CPPUNIT_TEST(test_effective_shape);
        CPPUNIT_TEST(test_shape);
        CPPUNIT_TEST_SUITE_END();

        typedef default_dim_layout         layout_type;
        typedef layout_type::storage_type vector_type;

        layout_type layout1,layout2;

    public:
        void setUp();
        void tearDown();

        //!
        //! \brief test the span algorithm
        //! 
        void test_span();

        //!
        //! \brief test the size algorithm
        //! 
        void test_size();

        //!
        //! \brief test the rank algorithm
        //! 
        void test_rank();
        
        //!
        //! \brief test the effective rank algorithm
        //! 
        void test_effective_rank();
        
        //!
        //! \brief test is_compact
        //! 
        void test_is_compact();
        
        //!
        //! \brief test effective shape
        //! 
        void test_effective_shape();
        
        //!
        //! \brief test the shape algorithm
        //! 
        void test_shape();
};



