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

#include <pni/core/index_map/dim_layout.hpp>
#include <functional>

using namespace pni::core;

//!
//! \brief test default_dim_layout
//!
//! Test the basic functionality of default_dim_layout. 
//! 
class fixed_rank_dim_layout_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(fixed_rank_dim_layout_test);
        CPPUNIT_TEST(test_default_construction);
        CPPUNIT_TEST(test_construction_lvalue);
        CPPUNIT_TEST(test_construction_rvalue);
        CPPUNIT_TEST(test_construction_init_list);
        CPPUNIT_TEST(test_move_construction);
        CPPUNIT_TEST(test_copy_construction);
        CPPUNIT_TEST(test_copy_assignment);
        CPPUNIT_TEST(test_move_assignment);
        CPPUNIT_TEST(test_counts_access);
        CPPUNIT_TEST(test_offset_access);
        CPPUNIT_TEST(test_stride_access);
        CPPUNIT_TEST_SUITE_END();

        typedef fixed_rank_dim_layout<2> layout2_type;
        typedef fixed_rank_dim_layout<3> layout3_type;
        
        typedef layout2_type::storage_type index2_type;
        typedef layout3_type::storage_type index3_type;

        template<typename LTYPE>
        bool check_rank(const LTYPE &l,size_t r)
        {
            if (l.stride().size() != r) return false;
            if (l.offset().size() != r) return false;
            if (l.counts().size() != r) return false;

            return true;
        }
    public:
        void setUp();
        void tearDown();

        //!
        //! \brief test the default constructor
        //! 
        void test_default_construction();

        //! 
        //! \brief test lvalue construction
        //!
        //! Test the construction fo a default_dim_layout from the lvalues to
        //! containers. 
        void test_construction_lvalue();

        //! 
        //! \brief test rvalue construction
        //!
        //! Test the construction fo a default_dim_layout from the rvalues to
        //! containers. 
        void test_construction_rvalue();

        //! 
        //! \brief test init list construction
        //!
        //! Test the construction fo a default_dim_layout by means of init lists
        void test_construction_init_list();

        //!
        //! \brief test move constructor
        //! 
        //! Test the function of the move constructor (use the implicit move
        //! constructor as provided by the compiler).
        void test_move_construction();
        
        //!
        //! \brief test copy constructor
        //! 
        //! Test the function of the copy constructor (use the implicit copy
        //! constructor as provided by the compiler).
        void test_copy_construction();

        //!
        //! \brief test copy assignment
        //! 
        void test_copy_assignment();
        
        //!
        //! \brief test move assignment
        //! 
        void test_move_assignment();

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



