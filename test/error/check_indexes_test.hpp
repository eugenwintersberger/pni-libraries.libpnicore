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
// ============================================================================
//
//  Created on: Apr 8, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<pni/core/error/exception_utils.hpp>

#include "types.hpp"


using namespace pni::core;

class check_indexes_test: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(check_indexes_test);
        CPPUNIT_TEST(test_no_throw);
        CPPUNIT_TEST(test_throw);
        CPPUNIT_TEST(test_invalid_input);
        CPPUNIT_TEST_SUITE_END();

        vector_type std_vector;
        std::array<size_t,1> index_1;
        std::array<size_t,2> index_2;
        std::array<size_t,3> index_3;

    public:
        void setUp();
        void tearDown();

        void test_no_throw();
        void test_throw();
        void test_invalid_input();
};
