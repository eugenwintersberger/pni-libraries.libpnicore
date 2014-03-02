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
//  Created on: Feb 28, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>

#include <pni/core/dimension_layout/dimension_layout.hpp>
#include <functional>

using namespace pni::core;

//!
//! \brief test static dimension layout
//!
//! Test the basic functionality of the static dimension layout type.
//! 
class static_dim_layout_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(static_dim_layout_test);
        CPPUNIT_TEST(test_counts_access);
        CPPUNIT_TEST(test_offset_access);
        CPPUNIT_TEST(test_stride_access);
        CPPUNIT_TEST_SUITE_END();

        typedef static_dim_layout<2,3,4> layout3_type;
        typedef static_dim_layout<4,10>  layout2_type;

        typedef layout3_type::storage_type index3_type;
        typedef layout2_type::storage_type index2_type;

    public:
        void setUp();
        void tearDown();

        //!
        //! \brief test access to count values
        //! 
        void test_counts_access();

        //! 
        //! \brief test access to offset values
        //!
        void test_offset_access();
        
        //! 
        //! \brief test access to stride values
        //!
        void test_stride_access();

};



