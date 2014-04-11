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
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "container_trait_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(container_trait_test);

//-----------------------------------------------------------------------------
void container_trait_test::setUp(){ }

//-----------------------------------------------------------------------------
void container_trait_test::tearDown(){ }

//-----------------------------------------------------------------------------
void container_trait_test::test_vector()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::vector<size_t> vector_type;
    typedef container_trait<vector_type> trait_type;

    CPPUNIT_ASSERT(trait_type::is_random_access);
    CPPUNIT_ASSERT(trait_type::is_iterable);
    CPPUNIT_ASSERT(trait_type::is_contiguous);
    CPPUNIT_ASSERT(!trait_type::is_multidim);
}

//-----------------------------------------------------------------------------
void container_trait_test::test_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::array<size_t,4> array_type;
    typedef container_trait<array_type> trait_type;

    CPPUNIT_ASSERT(trait_type::is_random_access);
    CPPUNIT_ASSERT(trait_type::is_iterable);
    CPPUNIT_ASSERT(trait_type::is_contiguous);
    CPPUNIT_ASSERT(!trait_type::is_multidim);
}

//-----------------------------------------------------------------------------
void container_trait_test::test_list()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::list<size_t> list_type;
    typedef container_trait<list_type> trait_type;

    CPPUNIT_ASSERT(!trait_type::is_random_access);
    CPPUNIT_ASSERT(trait_type::is_iterable);
    CPPUNIT_ASSERT(!trait_type::is_contiguous);
    CPPUNIT_ASSERT(!trait_type::is_multidim);
}
