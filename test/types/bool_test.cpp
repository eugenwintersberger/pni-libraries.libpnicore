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
//  Created on: Apr 11, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/current_function.hpp>

#include <pni/core/types/bool.hpp>

#include "bool_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(bool_test);


//-----------------------------------------------------------------------------
void bool_test::setUp(){ }

//-----------------------------------------------------------------------------
void bool_test::tearDown(){ }

//-----------------------------------------------------------------------------
void bool_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    bool_t bvalue;
    CPPUNIT_ASSERT(!bvalue);
    
    bool_t bvalue2 = true; 
    CPPUNIT_ASSERT(bvalue2);
}

//-----------------------------------------------------------------------------
void bool_test::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    bool_t v1;
    bool_t v2 = true;
    bool_t v3 = false;

    CPPUNIT_ASSERT(v1 != v2);
    CPPUNIT_ASSERT(v1 == v3);
}

//-----------------------------------------------------------------------------
void bool_test::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    bool_t v1;
    CPPUNIT_ASSERT(!v1);

    v1 = true;

    CPPUNIT_ASSERT(v1);
}

//-----------------------------------------------------------------------------
void bool_test::test_compatability()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::vector<bool_t> vector_type;

    vector_type v(10);
    
    bool_t *ptr = v.data();
    for(auto x: v)
        CPPUNIT_ASSERT(x==*ptr++);

}

