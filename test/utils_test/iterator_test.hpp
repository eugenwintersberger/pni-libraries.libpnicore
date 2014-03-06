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
//!  Created on: Jul 12, 2012
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>
#include <pni/core/utilities/container_iterator.hpp>

using namespace pni::core;

class iterator_test: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(iterator_test);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST(test_unary_arithmetics);
        CPPUNIT_TEST(test_binary_arithmetics);
        CPPUNIT_TEST(test_stl_algos);
        CPPUNIT_TEST(test_increment);
        CPPUNIT_TEST(test_ptr_access);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef std::vector<double> iterable;
        typedef container_iterator<iterable> const_iterator;
        typedef container_iterator<const iterable> iterator;
        iterable vector;
    public:
        void setUp();
        void tearDown();

        void test_construction();
        void test_assignment();
        void test_comparison();
        void test_unary_arithmetics();
        void test_binary_arithmetics();
        void test_stl_algos();
        void test_increment();
        void test_ptr_access();
};
