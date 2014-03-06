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
//!  Created on: Sep 27, 2012
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "type_class_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(type_class_test);

//-----------------------------------------------------------------------------
void type_class_test::setUp(){ }

//-----------------------------------------------------------------------------
void type_class_test::tearDown(){ }

//-----------------------------------------------------------------------------
void type_class_test::test_map()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(type_class_map<uint8>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<int8>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<uint16>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<int16>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<uint32>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<int32>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<uint64>::type_class == type_class_t::INTEGER);
    CPPUNIT_ASSERT(type_class_map<int64>::type_class == type_class_t::INTEGER);

    CPPUNIT_ASSERT(type_class_map<float32>::type_class == type_class_t::FLOAT);
    CPPUNIT_ASSERT(type_class_map<float64>::type_class == type_class_t::FLOAT);
    CPPUNIT_ASSERT(type_class_map<float128>::type_class == type_class_t::FLOAT);

    CPPUNIT_ASSERT(type_class_map<complex32>::type_class == type_class_t::COMPLEX);
    CPPUNIT_ASSERT(type_class_map<complex64>::type_class == type_class_t::COMPLEX);
    CPPUNIT_ASSERT(type_class_map<complex128>::type_class == type_class_t::COMPLEX);

    CPPUNIT_ASSERT(type_class_map<string>::type_class == type_class_t::STRING);
    CPPUNIT_ASSERT(type_class_map<binary>::type_class == type_class_t::BINARY);
    CPPUNIT_ASSERT(type_class_map<bool>::type_class == type_class_t::BOOL);

}
