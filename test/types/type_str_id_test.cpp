//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: Oct 15, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include <pni/core/error.hpp>
#include "type_str_id_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(type_str_id_test);


//-----------------------------------------------------------------------------
void type_str_id_test::setUp(){ }

//-----------------------------------------------------------------------------
void type_str_id_test::tearDown(){ }

//-----------------------------------------------------------------------------
void type_str_id_test::test_id_to_str()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(str_from_type_id(type_id_t::INT8)=="int8");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::UINT8)=="uint8");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::INT16)=="int16");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::UINT16)=="uint16");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::INT32)=="int32");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::UINT32)=="uint32");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::INT32)=="int32");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::UINT32)=="uint32");
    
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::FLOAT32)=="float32");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::FLOAT64)=="float64");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::FLOAT128)=="float128");
   
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::COMPLEX32)=="complex32");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::COMPLEX64)=="complex64");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::COMPLEX128)=="complex128");

    CPPUNIT_ASSERT(str_from_type_id(type_id_t::STRING)=="string");
    CPPUNIT_ASSERT(str_from_type_id(type_id_t::BINARY)=="binary");
    
    CPPUNIT_ASSERT_THROW(str_from_type_id(type_id_t::NONE),key_error);
}

//-----------------------------------------------------------------------------
void type_str_id_test::test_str_to_id()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(type_id_from_str("int8")==type_id_t::INT8);
    CPPUNIT_ASSERT(type_id_from_str("i8")==type_id_t::INT8);
    CPPUNIT_ASSERT(type_id_from_str("uint8")==type_id_t::UINT8);
    CPPUNIT_ASSERT(type_id_from_str("ui8")==type_id_t::UINT8);
    
    CPPUNIT_ASSERT(type_id_from_str("i16")==type_id_t::INT16);
    CPPUNIT_ASSERT(type_id_from_str("int16")==type_id_t::INT16);
    CPPUNIT_ASSERT(type_id_from_str("uint16")==type_id_t::UINT16);
    CPPUNIT_ASSERT(type_id_from_str("ui16")==type_id_t::UINT16);

    CPPUNIT_ASSERT(type_id_from_str("i32")==type_id_t::INT32);
    CPPUNIT_ASSERT(type_id_from_str("int32")==type_id_t::INT32);
    CPPUNIT_ASSERT(type_id_from_str("uint32")==type_id_t::UINT32);
    CPPUNIT_ASSERT(type_id_from_str("ui32")==type_id_t::UINT32);
    
    CPPUNIT_ASSERT(type_id_from_str("i64")==type_id_t::INT64);
    CPPUNIT_ASSERT(type_id_from_str("int64")==type_id_t::INT64);
    CPPUNIT_ASSERT(type_id_from_str("uint64")==type_id_t::UINT64);
    CPPUNIT_ASSERT(type_id_from_str("ui64")==type_id_t::UINT64);

    CPPUNIT_ASSERT(type_id_from_str("float32")==type_id_t::FLOAT32);
    CPPUNIT_ASSERT(type_id_from_str("f32")==type_id_t::FLOAT32);

    CPPUNIT_ASSERT(type_id_from_str("float64")==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(type_id_from_str("f64")==type_id_t::FLOAT64);

    CPPUNIT_ASSERT(type_id_from_str("float128")==type_id_t::FLOAT128);
    CPPUNIT_ASSERT(type_id_from_str("f128")==type_id_t::FLOAT128);

    CPPUNIT_ASSERT(type_id_from_str("complex32")==type_id_t::COMPLEX32);
    CPPUNIT_ASSERT(type_id_from_str("c32")==type_id_t::COMPLEX32);

    CPPUNIT_ASSERT(type_id_from_str("complex64")==type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(type_id_from_str("c64")==type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(type_id_from_str("complex128")==type_id_t::COMPLEX128);
    CPPUNIT_ASSERT(type_id_from_str("c128")==type_id_t::COMPLEX128);

    CPPUNIT_ASSERT(type_id_from_str("string")==type_id_t::STRING);
    CPPUNIT_ASSERT(type_id_from_str("str")==type_id_t::STRING);
    CPPUNIT_ASSERT(type_id_from_str("binary")==type_id_t::BINARY);

    CPPUNIT_ASSERT_THROW(type_id_from_str("blabla"),key_error);

}

