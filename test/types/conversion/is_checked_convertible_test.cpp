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
// ===========================================================================
//
//  Created on: Dec 22, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "is_checked_convertible_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(is_checked_convertible_test);

//-----------------------------------------------------------------------------
void is_checked_convertible_test::setUp(){ }

//-----------------------------------------------------------------------------
void is_checked_convertible_test::tearDown(){ }
//--------------------------------------------------------------------
void is_checked_convertible_test::always_fails(type_id_t sid)
{
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::BOOL));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::BINARY));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::STRING));
}

//--------------------------------------------------------------------
void is_checked_convertible_test::uint_always_fails(type_id_t sid)
{
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::UINT8));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::UINT16));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::UINT32));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::UINT64));
}

//--------------------------------------------------------------------
void is_checked_convertible_test::int_always_fails(type_id_t sid)
{
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::INT8));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::INT16));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::INT64));
}

//--------------------------------------------------------------------
void is_checked_convertible_test::float_always_fails(type_id_t sid)
{
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::FLOAT32));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::FLOAT64));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::FLOAT128));
}

//--------------------------------------------------------------------
void is_checked_convertible_test::complex_always_fails(type_id_t sid)
{
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(!is_checked_convertible(sid,type_id_t::COMPLEX128));
}

//--------------------------------------------------------------------
void is_checked_convertible_test::uint_always_pass(type_id_t sid)
{
    CPPUNIT_ASSERT(is_checked_convertible(sid,type_id_t::UINT8));
    CPPUNIT_ASSERT(is_checked_convertible(sid,type_id_t::UINT16));
    CPPUNIT_ASSERT(is_checked_convertible(sid,type_id_t::UINT32));
    CPPUNIT_ASSERT(is_checked_convertible(sid,type_id_t::UINT64));
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::UINT8));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::UINT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::UINT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::UINT64));

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT8,type_id_t::INT8));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::INT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT8,type_id_t::INT64));

    float_always_fails(type_id_t::UINT8);
    complex_always_fails(type_id_t::UINT8);
    always_fails(type_id_t::UINT8);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT16,type_id_t::UINT8));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT16,type_id_t::UINT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT16,type_id_t::UINT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT16,type_id_t::UINT64));

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT16,type_id_t::INT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT16,type_id_t::INT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT16,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT16,type_id_t::INT64));

    float_always_fails(type_id_t::UINT16);
    complex_always_fails(type_id_t::UINT16);
    always_fails(type_id_t::UINT16);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT32,type_id_t::UINT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT32,type_id_t::UINT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT32,type_id_t::UINT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT32,type_id_t::UINT64));

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT32,type_id_t::INT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT32,type_id_t::INT16));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT32,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT32,type_id_t::INT64));

    float_always_fails(type_id_t::UINT32);
    complex_always_fails(type_id_t::UINT32);
    always_fails(type_id_t::UINT32);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::UINT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::UINT16));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::UINT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::UINT64,type_id_t::UINT64));
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::INT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::INT16));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::INT32));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::UINT64,type_id_t::INT64));

    float_always_fails(type_id_t::UINT64);
    complex_always_fails(type_id_t::UINT64);
    always_fails(type_id_t::UINT64);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass(type_id_t::INT8);

    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT8,type_id_t::INT8));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT8,type_id_t::INT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT8,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT8,type_id_t::INT64));

    float_always_fails(type_id_t::INT8);
    complex_always_fails(type_id_t::INT8);
    always_fails(type_id_t::INT8);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass(type_id_t::INT16);

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::INT16,type_id_t::INT8));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT16,type_id_t::INT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT16,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT16,type_id_t::INT64));

    float_always_fails(type_id_t::INT16);
    complex_always_fails(type_id_t::INT16);
    always_fails(type_id_t::INT16);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass(type_id_t::INT32);

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::INT32,type_id_t::INT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::INT32,type_id_t::INT16));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT32,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT32,type_id_t::INT64));

    float_always_fails(type_id_t::INT32);
    complex_always_fails(type_id_t::INT32);
    always_fails(type_id_t::INT32);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass(type_id_t::INT64);

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::INT64,type_id_t::INT8));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::INT64,type_id_t::INT16));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::INT64,type_id_t::INT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::INT64,type_id_t::INT64));

    float_always_fails(type_id_t::INT64);
    complex_always_fails(type_id_t::INT64);
    always_fails(type_id_t::INT64);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    uint_always_fails(type_id_t::FLOAT32);
    int_always_fails(type_id_t::FLOAT32);

    float_always_fails(type_id_t::FLOAT32);
    complex_always_fails(type_id_t::FLOAT32);
    always_fails(type_id_t::FLOAT32);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails(type_id_t::FLOAT64);
    int_always_fails(type_id_t::FLOAT64);

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::FLOAT64,type_id_t::FLOAT32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::FLOAT64,type_id_t::FLOAT64));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::FLOAT64,type_id_t::FLOAT128));
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::FLOAT64,type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::FLOAT64,type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::FLOAT64,type_id_t::COMPLEX128));
    
    always_fails(type_id_t::FLOAT64);

}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails(type_id_t::FLOAT128);
    int_always_fails(type_id_t::FLOAT128);

    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::FLOAT128,type_id_t::FLOAT32));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::FLOAT128,type_id_t::FLOAT64));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::FLOAT128,type_id_t::FLOAT128));
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::FLOAT128,type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::FLOAT128,type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::FLOAT128,type_id_t::COMPLEX128));
   
    always_fails(type_id_t::FLOAT128);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails(type_id_t::COMPLEX32);
    int_always_fails(type_id_t::COMPLEX32);

    float_always_fails(type_id_t::COMPLEX32);
    complex_always_fails(type_id_t::COMPLEX32);

    always_fails(type_id_t::COMPLEX32);
}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails(type_id_t::COMPLEX64);
    int_always_fails(type_id_t::COMPLEX64);

    float_always_fails(type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::COMPLEX64,type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::COMPLEX64,type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::COMPLEX64,type_id_t::COMPLEX128));
    
    always_fails(type_id_t::COMPLEX64);

}

//-----------------------------------------------------------------------------
void is_checked_convertible_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails(type_id_t::COMPLEX128);
    int_always_fails(type_id_t::COMPLEX128);

    float_always_fails(type_id_t::COMPLEX128);
    
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::COMPLEX128,type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(is_checked_convertible(type_id_t::COMPLEX128,type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(!is_checked_convertible(type_id_t::COMPLEX128,type_id_t::COMPLEX128));
   
    always_fails(type_id_t::COMPLEX128);
}
