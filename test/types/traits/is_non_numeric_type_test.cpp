//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
//  Created on: Jan 5, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>
#include <pni/core/types/types.hpp>
#include <pni/core/types/traits.hpp>

#include <iostream>

#include "is_non_numeric_type_test.hpp"
using namespace pni::core;

CPPUNIT_TEST_SUITE_REGISTRATION(is_non_numeric_type_test);

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::setUp(){ }

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::tearDown(){ }
        

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<uint8>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<uint16>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<uint32>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<uint64>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<int8>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<int16>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<int32>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<int64>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<float32>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<float64>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<float128>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<complex32>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<complex64>::value);
}

//-----------------------------------------------------------------------------
void is_non_numeric_type_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_non_numeric_type<complex128>::value);
}

//----------------------------------------------------------------------------
void is_non_numeric_type_test::test_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_non_numeric_type<string>::value);
}

//----------------------------------------------------------------------------
void is_non_numeric_type_test::test_none()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_non_numeric_type<none>::value);
}

//----------------------------------------------------------------------------
void is_non_numeric_type_test::test_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_non_numeric_type<bool_t>::value);
}

//----------------------------------------------------------------------------
void is_non_numeric_type_test::test_binary()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_non_numeric_type<binary>::value);
}
