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
#include <pni/core/types/convert.hpp>

#include <iostream>

#include "convert_uint8_test.hpp"
using namespace pni::core;

CPPUNIT_TEST_SUITE_REGISTRATION(convert_uint8_test);

//-----------------------------------------------------------------------------
void convert_uint8_test::setUp(){ }

//-----------------------------------------------------------------------------
void convert_uint8_test::tearDown(){ }
        

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<uint8>(uint8(1)) == uint8(1));
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<uint16>(uint8(19))==uint16(19));
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<uint32>(uint8(19))==uint32(19));
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<uint64>(uint8(19))==uint64(19));
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<int8>(uint8(19))==int8(19));

    //we can only produce a negative overflow
    CPPUNIT_ASSERT_THROW(convert<int8>(uint8(200)),pni::core::range_error);
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<int16>(uint8(19))==int16(19));
    
    //we cannot do any overflow to int16
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<int32>(uint8(19))==int32(19));

    //we cannot do any overflow to int16
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(convert<int64>(uint8(19))==int64(19));

    //we cannot do any overflow to int16
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float32(19),convert<float32>(uint8(19)),
                                 1.e-6);
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float64(19),convert<float64>(uint8(19)),
                                 1.e-16);

}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float128(19),convert<float128>(uint8(19)),
                                 1.e-16);
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    complex32 value = convert<complex32>(uint8(19));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float32(19),value.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float32(0),value.imag(),1.e-6);
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    complex64 value = convert<complex64>(uint8(19));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float64(19),value.real(),1.e-16);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float64(0),value.imag(),1.e-16);
}

//-----------------------------------------------------------------------------
void convert_uint8_test::test_to_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    complex128 value = convert<complex128>(uint8(19));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float128(19),value.real(),1.e-16);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(float128(0),value.imag(),1.e-16);
}
