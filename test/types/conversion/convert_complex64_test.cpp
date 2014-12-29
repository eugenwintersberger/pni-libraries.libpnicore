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
//  Created on: Dec 29, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>
#include <pni/core/types/convert.hpp>

#include <iostream>

#include "convert_complex64_test.hpp"
using namespace pni::core;

CPPUNIT_TEST_SUITE_REGISTRATION(convert_complex64_test);

//-----------------------------------------------------------------------------
void convert_complex64_test::setUp(){ }

//-----------------------------------------------------------------------------
void convert_complex64_test::tearDown(){ }
        

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef uint8 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(1)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef uint16 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef uint32 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef uint64 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef int8 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef int16 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef int32 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(-20)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef int64 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef float32 target_type;
#pragma GCC diagnostic pop
   
    //does not compile
    //CPPUNIT_ASSERT_THROWS(convert<target_type>(source_type{19,-4.5}),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef float64 target_type;
#pragma GCC diagnostic pop
    
    //does not compile
    //CPPUNIT_ASSERT_THROWS(convert<target_type>(source_type(19,-4.5)),type_error);

}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
    typedef float128 target_type;
#pragma GCC diagnostic pop
    
    //does not compile
    //CPPUNIT_ASSERT_THROWS(convert<target_type>(source_type(19)),type_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex32 target_type;
    typedef float32   base_type;
   
    auto value = convert<target_type>(source_type(19,-4.5));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(19),value.real(),1.e-6);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-4.5),value.imag(),1.e-6);

    CPPUNIT_ASSERT_THROW(convert<target_type>(source_type(1.e+100,-2e+100)),
                         range_error);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex64 target_type;
    typedef float64   base_type;
    
    auto value = convert<target_type>(source_type(19,-4.5));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(19),value.real(),1.e-16);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-4.5),value.imag(),1.e-16);
}

//-----------------------------------------------------------------------------
void convert_complex64_test::test_to_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex128 target_type;
    typedef float128   base_type;
    
    auto value = convert<target_type>(source_type(19,-4.5));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(19),value.real(),1.e-16);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(base_type(-4.5),value.imag(),1.e-16);
}
