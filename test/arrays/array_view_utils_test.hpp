//!
//! (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Apr 6, 2014
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<vector>
#include <pni/core/arrays.hpp>

using namespace pni::core;

class array_view_utils_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_view_utils_test);
        CPPUNIT_TEST(test_is_index_type);
        CPPUNIT_TEST(test_is_index_types);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();

        //---------------------------------------------------------------------
        //! 
        //! \brief test is_view_index template
        //!
        void test_is_index_type();

        //---------------------------------------------------------------------
        //!
        //! \brief test is_view_types template
        //!
        void test_is_index_types();
};

