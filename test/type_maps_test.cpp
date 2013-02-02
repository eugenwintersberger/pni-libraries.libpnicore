/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Feb 09, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "type_maps_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(type_maps_test);

using namespace pni::core;

//-----------------------------------------------------------------------------
void type_maps_test::setUp(){ }

//-----------------------------------------------------------------------------
void type_maps_test::tearDown(){ }

//-----------------------------------------------------------------------------
void type_maps_test::test_type2id()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(type_id_map<int8>::type_id == type_id_t::INT8);
    CPPUNIT_ASSERT(type_id_map<uint8>::type_id == type_id_t::UINT8);
    
    CPPUNIT_ASSERT(type_id_map<int16>::type_id == type_id_t::INT16);
    CPPUNIT_ASSERT(type_id_map<uint16>::type_id == type_id_t::UINT16);
    
    CPPUNIT_ASSERT(type_id_map<int32>::type_id == type_id_t::INT32);
    CPPUNIT_ASSERT(type_id_map<uint32>::type_id == type_id_t::UINT32);
    
    CPPUNIT_ASSERT(type_id_map<int64>::type_id == type_id_t::INT64);
    CPPUNIT_ASSERT(type_id_map<uint64>::type_id == type_id_t::UINT64);
    
    CPPUNIT_ASSERT(type_id_map<float32>::type_id == type_id_t::FLOAT32); 
    CPPUNIT_ASSERT(type_id_map<float64>::type_id == type_id_t::FLOAT64); 
    CPPUNIT_ASSERT(type_id_map<float128>::type_id == type_id_t::FLOAT128); 
    
    CPPUNIT_ASSERT(type_id_map<complex32>::type_id == type_id_t::COMPLEX32); 
    CPPUNIT_ASSERT(type_id_map<complex64>::type_id == type_id_t::COMPLEX64); 
    CPPUNIT_ASSERT(type_id_map<complex128>::type_id == type_id_t::COMPLEX128); 

    CPPUNIT_ASSERT(type_id_map<string>::type_id == type_id_t::STRING);
    CPPUNIT_ASSERT(type_id_map<binary>::type_id == type_id_t::BINARY);
    CPPUNIT_ASSERT(type_id_map<bool>::type_id == type_id_t::BOOL);
}

//-----------------------------------------------------------------------------
void type_maps_test::test_id2type()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::INT8>::type >::type_id == type_id_t::INT8);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::UINT8>::type >::type_id == type_id_t::UINT8);
    
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::INT16>::type >::type_id == type_id_t::INT16);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::UINT16>::type >::type_id == type_id_t::UINT16);
    
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::INT32>::type >::type_id == type_id_t::INT32);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::UINT32>::type >::type_id == type_id_t::UINT32);
    
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::INT64>::type >::type_id == type_id_t::INT64);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::UINT64>::type >::type_id == type_id_t::UINT64);

    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::FLOAT32>::type >::type_id ==
            type_id_t::FLOAT32);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::FLOAT64>::type >::type_id ==
            type_id_t::FLOAT64);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::FLOAT128>::type >::type_id ==
            type_id_t::FLOAT128);
    
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::COMPLEX32>::type >::type_id ==
            type_id_t::COMPLEX32);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::COMPLEX64>::type >::type_id ==
            type_id_t::COMPLEX64);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::COMPLEX128>::type >::type_id ==
            type_id_t::COMPLEX128);

    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::STRING>::type >::type_id ==
            type_id_t::STRING);
    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::BINARY>::type >::type_id ==
            type_id_t::BINARY);

    CPPUNIT_ASSERT(
            type_id_map<id_type_map<type_id_t::BOOL>::type >::type_id ==
            type_id_t::BOOL);
}

