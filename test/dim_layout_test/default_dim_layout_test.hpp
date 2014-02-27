/*
 * (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Feb 27, 2014
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/index_map/dim_layout.hpp>
#include <functional>

using namespace pni::core;

class default_layout_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(default_layout_test);
        CPPUNIT_TEST(test_default_construction);
        CPPUNIT_TEST(test_move_construction);
        CPPUNIT_TEST(test_copy_construction);
        CPPUNIT_TEST(test_copy_assignment);
        CPPUNIT_TEST(test_move_assignment);
        CPPUNIT_TEST(test_counts_access);
        CPPUNIT_TEST(test_offset_access);
        CPPUNIT_TEST(test_stride_access);
        CPPUNIT_TEST_SUITE_END();
        
        default_dim_layout layout1,layout2;
    public:
        void setUp();
        void tearDown();

        void test_default_construction();
        void test_move_construction();
        void test_copy_construction();
        void test_copy_assignment();
        void test_move_assignment();

        void test_counts_access();
        void test_offset_access();
        void test_stride_access();

};



