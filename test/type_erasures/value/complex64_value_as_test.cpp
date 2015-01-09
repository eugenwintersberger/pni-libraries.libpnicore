//!
//! (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Jan 9, 2015
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "complex64_value_as_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(complex64_value_as_test);

//-----------------------------------------------------------------------------
void complex64_value_as_test::setUp() 
{ 
    generator = generator_type(0,100);
    value_1 = generator();
    v = value(value_1);
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::tearDown() { }

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_uint8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint8 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_uint16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint16 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_uint32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint32 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_uint64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef uint64 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_int8()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int8 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_int16()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int16 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_int32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int32 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_int64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef int64 target_type;
    //would not compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_float32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef float32 target_type;
    //wont compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_float64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef float64 target_type;
    //wont compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_float128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef float128 target_type;
    //wont compile
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_complex32()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex32 target_type;

    compare(as<target_type>(v),convert<target_type>(value_1));

    value x(value_type(1.e+400,-1.e+400));
    CPPUNIT_ASSERT_THROW(as<target_type>(x),range_error);
    x = value(value_type(-1.e+400,1.e+400));
    CPPUNIT_ASSERT_THROW(as<target_type>(x),range_error);
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_complex64()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex64 target_type;
    compare(as<target_type>(v),convert<target_type>(value_1));
}

//-----------------------------------------------------------------------------
void complex64_value_as_test::test_as_complex128()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef complex128 target_type;
    compare(as<target_type>(v),convert<target_type>(value_1));
}

//----------------------------------------------------------------------------
void complex64_value_as_test::test_as_string()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef string target_type;
    
    CPPUNIT_ASSERT_THROW(as<target_type>(v),type_error);
}

//----------------------------------------------------------------------------
void complex64_value_as_test::test_as_binary()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef binary target_type;
    
    CPPUNIT_ASSERT_THROW(as<target_type>(v),type_error);
}

//----------------------------------------------------------------------------
void complex64_value_as_test::test_as_bool()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef bool_t target_type;
    
    CPPUNIT_ASSERT_THROW(as<target_type>(v),type_error);
}

