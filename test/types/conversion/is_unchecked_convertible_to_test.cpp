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
//  Created on: Dec 18, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "is_unchecked_convertible_to_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(is_unchecked_convertible_to_test);

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::setUp(){ }

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::tearDown(){ }

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::UINT8));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::UINT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::UINT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::UINT64));

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint8>(type_id_t::INT8));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::INT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint8>(type_id_t::INT64));

    float_always_pass<uint8>();
    complex_always_pass<uint8>();
    always_fails<uint8>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint16>(type_id_t::UINT8));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint16>(type_id_t::UINT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint16>(type_id_t::UINT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint16>(type_id_t::UINT64));

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint16>(type_id_t::INT8));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint16>(type_id_t::INT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint16>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint16>(type_id_t::INT64));

    float_always_pass<uint16>();
    complex_always_pass<uint16>();
    always_fails<uint16>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint32>(type_id_t::UINT8));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint32>(type_id_t::UINT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint32>(type_id_t::UINT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint32>(type_id_t::UINT64));

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint32>(type_id_t::INT8));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint32>(type_id_t::INT16));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint32>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint32>(type_id_t::INT64));

    float_always_pass<uint32>();
    complex_always_pass<uint32>();
    always_fails<uint32>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint64>(type_id_t::UINT8));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint64>(type_id_t::UINT16));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<uint64>(type_id_t::UINT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<uint64>(type_id_t::UINT64));

    int_always_fails<uint64>();
    float_always_pass<uint64>();
    complex_always_pass<uint64>();
    always_fails<uint64>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<int8>();

    CPPUNIT_ASSERT(is_unchecked_convertible_to<int8>(type_id_t::INT8));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int8>(type_id_t::INT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int8>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int8>(type_id_t::INT64));

    float_always_pass<int8>();
    complex_always_pass<int8>();
    always_fails<int8>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<int16>();

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<int16>(type_id_t::INT8));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int16>(type_id_t::INT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int16>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int16>(type_id_t::INT64));

    float_always_pass<int16>();
    complex_always_pass<int16>();
    always_fails<int16>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<int32>();

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<int32>(type_id_t::INT8));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<int32>(type_id_t::INT16));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int32>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int32>(type_id_t::INT64));

    float_always_pass<int32>();
    complex_always_pass<int32>();
    always_fails<int32>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<int64>();

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<int64>(type_id_t::INT8));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<int64>(type_id_t::INT16));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<int64>(type_id_t::INT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<int64>(type_id_t::INT64));

    float_always_pass<int64>();
    complex_always_pass<int64>();
    always_fails<int64>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float32>();
    int_always_fails<float32>();

    float_always_pass<float32>();
    complex_always_pass<float32>();
    always_fails<float32>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float64>();
    int_always_fails<float64>();

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<float64>(type_id_t::FLOAT32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<float64>(type_id_t::FLOAT64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<float64>(type_id_t::FLOAT128));
    
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<float64>(type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<float64>(type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<float64>(type_id_t::COMPLEX128));
    
    always_fails<float64>();

}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float128>();
    int_always_fails<float128>();

    CPPUNIT_ASSERT(!is_unchecked_convertible_to<float128>(type_id_t::FLOAT32));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<float128>(type_id_t::FLOAT64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<float128>(type_id_t::FLOAT128));
    
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<float128>(type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<float128>(type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<float128>(type_id_t::COMPLEX128));
   
    always_fails<float128>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex32>();
    int_always_fails<complex32>();

    float_always_fails<complex32>();

    CPPUNIT_ASSERT(is_unchecked_convertible_to<complex32>(type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<complex32>(type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<complex32>(type_id_t::COMPLEX128));

    always_fails<complex32>();
}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex64>();
    int_always_fails<complex64>();

    float_always_fails<complex64>(); 
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<complex64>(type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<complex64>(type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<complex64>(type_id_t::COMPLEX128));
    
    always_fails<complex64>();

}

//-----------------------------------------------------------------------------
void is_unchecked_convertible_to_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex128>();
    int_always_fails<complex128>();

    float_always_fails<complex128>();
    
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<complex128>(type_id_t::COMPLEX32));
    CPPUNIT_ASSERT(!is_unchecked_convertible_to<complex128>(type_id_t::COMPLEX64));
    CPPUNIT_ASSERT(is_unchecked_convertible_to<complex128>(type_id_t::COMPLEX128));
   
    always_fails<complex128>();
}
