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
//  Created on: Dec 20, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "checked_convertible_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(checked_convertible_test);

//-----------------------------------------------------------------------------
void checked_convertible_test::setUp(){ }

//-----------------------------------------------------------------------------
void checked_convertible_test::tearDown(){ }

//-----------------------------------------------------------------------------
void checked_convertible_test::test_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT(!(checked_convertible<uint8,uint8>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint8,uint16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint8,uint32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint8,uint64>::value));

    CPPUNIT_ASSERT((checked_convertible<uint8,int8>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint8,int16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint8,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint8,int64>::value));

    float_always_fails<uint8>();
    complex_always_fails<uint8>();
    always_fails<uint8>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT((checked_convertible<uint16,uint8>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint16,uint16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint16,uint32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint16,uint64>::value));

    CPPUNIT_ASSERT((checked_convertible<uint16,int8>::value));
    CPPUNIT_ASSERT((checked_convertible<uint16,int16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint16,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint16,int64>::value));

    float_always_fails<uint16>();
    complex_always_fails<uint16>();
    always_fails<uint16>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT((checked_convertible<uint32,uint8>::value));
    CPPUNIT_ASSERT((checked_convertible<uint32,uint16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint32,uint32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint32,uint64>::value));

    CPPUNIT_ASSERT((checked_convertible<uint32,int8>::value));
    CPPUNIT_ASSERT((checked_convertible<uint32,int16>::value));
    CPPUNIT_ASSERT((checked_convertible<uint32,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint32,int64>::value));

    float_always_fails<uint32>();
    complex_always_fails<uint32>();
    always_fails<uint32>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    CPPUNIT_ASSERT((checked_convertible<uint64,uint8>::value));
    CPPUNIT_ASSERT((checked_convertible<uint64,uint16>::value));
    CPPUNIT_ASSERT((checked_convertible<uint64,uint32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<uint64,uint64>::value));
    
    CPPUNIT_ASSERT((checked_convertible<uint64,int8>::value));
    CPPUNIT_ASSERT((checked_convertible<uint64,int16>::value));
    CPPUNIT_ASSERT((checked_convertible<uint64,int32>::value));
    CPPUNIT_ASSERT((checked_convertible<uint64,int64>::value));

    float_always_fails<uint64>();
    complex_always_fails<uint64>();
    always_fails<uint64>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int8>();

    CPPUNIT_ASSERT(!(checked_convertible<int8,int8>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int8,int16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int8,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int8,int64>::value));

    float_always_fails<int8>();
    complex_always_fails<int8>();
    always_fails<int8>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int16>();

    CPPUNIT_ASSERT((checked_convertible<int16,int8>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int16,int16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int16,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int16,int64>::value));

    float_always_fails<int16>();
    complex_always_fails<int16>();
    always_fails<int16>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int32>();

    CPPUNIT_ASSERT((checked_convertible<int32,int8>::value));
    CPPUNIT_ASSERT((checked_convertible<int32,int16>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int32,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int32,int64>::value));

    float_always_fails<int32>();
    complex_always_fails<int32>();
    always_fails<int32>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_pass<int64>();

    CPPUNIT_ASSERT((checked_convertible<int64,int8>::value));
    CPPUNIT_ASSERT((checked_convertible<int64,int16>::value));
    CPPUNIT_ASSERT((checked_convertible<int64,int32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<int64,int64>::value));

    float_always_fails<int64>();
    complex_always_fails<int64>();
    always_fails<int64>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    uint_always_fails<float32>();
    int_always_fails<float32>();

    float_always_fails<float32>();
    complex_always_fails<float32>();
    always_fails<float32>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float64>();
    int_always_fails<float64>();

    CPPUNIT_ASSERT((checked_convertible<float64,float32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<float64,float64>::value));
    CPPUNIT_ASSERT(!(checked_convertible<float64,float128>::value));
    
    CPPUNIT_ASSERT((checked_convertible<float64,complex32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<float64,complex64>::value));
    CPPUNIT_ASSERT(!(checked_convertible<float64,complex128>::value));
    
    always_fails<float64>();

}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<float128>();
    int_always_fails<float128>();

    CPPUNIT_ASSERT((checked_convertible<float128,float32>::value));
    CPPUNIT_ASSERT((checked_convertible<float128,float64>::value));
    CPPUNIT_ASSERT(!(checked_convertible<float128,float128>::value));
    
    CPPUNIT_ASSERT((checked_convertible<float128,complex32>::value));
    CPPUNIT_ASSERT((checked_convertible<float128,complex64>::value));
    CPPUNIT_ASSERT(!(checked_convertible<float128,complex128>::value));
   
    always_fails<float128>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex32>();
    int_always_fails<complex32>();

    float_always_fails<complex32>();
    complex_always_fails<complex32>();

    always_fails<complex32>();
}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex64>();
    int_always_fails<complex64>();

    float_always_fails<complex64>(); 
    CPPUNIT_ASSERT((checked_convertible<complex64,complex32>::value));
    CPPUNIT_ASSERT(!(checked_convertible<complex64,complex64>::value));
    CPPUNIT_ASSERT(!(checked_convertible<complex64,complex128>::value));
    
    always_fails<complex64>();

}

//-----------------------------------------------------------------------------
void checked_convertible_test::test_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    uint_always_fails<complex128>();
    int_always_fails<complex128>();

    float_always_fails<complex128>();
    
    CPPUNIT_ASSERT((checked_convertible<complex128,complex32>::value));
    CPPUNIT_ASSERT((checked_convertible<complex128,complex64>::value));
    CPPUNIT_ASSERT(!(checked_convertible<complex128,complex128>::value));
   
    always_fails<complex128>();
}
