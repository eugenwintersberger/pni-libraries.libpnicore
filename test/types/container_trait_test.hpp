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
//!  Created on: Apr 11, 2014
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/types.hpp>

using namespace pni::core;

class container_trait_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(container_trait_test);
        CPPUNIT_TEST(test_vector);
        CPPUNIT_TEST(test_array);
        CPPUNIT_TEST(test_list);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();

        void test_vector();
        void test_array();
        void test_list();
};
