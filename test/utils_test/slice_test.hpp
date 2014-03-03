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
 *  Created on: May 15, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/slice.hpp>

using namespace pni::core;

class slice_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(slice_test);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_functions);
        CPPUNIT_TEST_SUITE_END();
    private:
        void _construct(size_t start,size_t stop);
        void _construct(size_t start,size_t stop,size_t stride);
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
        void test_functions();
};
