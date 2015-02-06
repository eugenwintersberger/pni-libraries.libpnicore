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
//  Created on: Jan 7, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>
#include <pni/core/types/types.hpp>
#include <pni/core/types/traits.hpp>

#include <iostream>

#include "is_complex_test.hpp"
using namespace pni::core;

CPPUNIT_TEST_SUITE_REGISTRATION(is_complex_test);

//-----------------------------------------------------------------------------
void is_complex_test::setUp(){ }

//-----------------------------------------------------------------------------
void is_complex_test::tearDown(){ }
        

//-----------------------------------------------------------------------------
void is_complex_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::UINT8));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::UINT16));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::UINT32));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::UINT64));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::INT8));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::INT16));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::INT32));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::INT64));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::FLOAT32));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::FLOAT64));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::FLOAT128));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_complex(type_id_t::COMPLEX32));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_complex(type_id_t::COMPLEX64));
}

//-----------------------------------------------------------------------------
void is_complex_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(is_complex(type_id_t::COMPLEX128));
}

//----------------------------------------------------------------------------
void is_complex_test::test_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::STRING));
}

//----------------------------------------------------------------------------
void is_complex_test::test_none()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::NONE));
}

//----------------------------------------------------------------------------
void is_complex_test::test_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::BOOL));
}

//----------------------------------------------------------------------------
void is_complex_test::test_binary()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(!is_complex(type_id_t::BINARY));
}
