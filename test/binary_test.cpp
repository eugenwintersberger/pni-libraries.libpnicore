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
 *  Created on: Feb 08, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/current_function.hpp>

#include <pni/core/Types.hpp>
#include <pni/core/Binary.hpp>

#include "binary_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(binary_test);

using namespace pni::core;

//-----------------------------------------------------------------------------
void binary_test::setUp(){ }

//-----------------------------------------------------------------------------
void binary_test::tearDown(){ }

//-----------------------------------------------------------------------------
void binary_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    binary_t bvalue;
    
    binary_t bvalue2 = 8; 
}

//-----------------------------------------------------------------------------
void binary_test::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    binary_t v1 = 8;
    binary_t v2 = 10;
    binary_t v3 = 8;

    CPPUNIT_ASSERT(v1 != v2);
    CPPUNIT_ASSERT(v1 == v3);
}

//-----------------------------------------------------------------------------
void binary_test::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    binary_t v1;

    v1 = 10;

    binary_t v2 = 10;
    CPPUNIT_ASSERT(v1 == v2);
}

//-----------------------------------------------------------------------------
void binary_test::test_compatability()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef BinaryType<UInt8> binary_t;
    UInt8 rv;
    binary_t bv = 10;
   
    //this should work
    rv = bv;
    CPPUNIT_ASSERT(rv == bv);
    rv = 100;
    bv = rv;
    CPPUNIT_ASSERT(bv == rv);

    //should not work
    Float64 f64 = 12.3445;
    bv = f64;

    UInt8 *rptr = new UInt8[10];
    binary_t *bptr = new binary_t[10];

    for(size_t i=0;i<10;i++)
    {
        rptr[i] = i;
        bptr[i] = i;
    }

    for(size_t i=0;i<10;i++) CPPUNIT_ASSERT(rptr[i] == bptr[i]);


    delete [] rptr;
    delete [] bptr;
}

//-----------------------------------------------------------------------------
void binary_test::test_io_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    binary_t  b = 'a';

    CPPUNIT_ASSERT(b == 'a');
    b = 'x';
    CPPUNIT_ASSERT(b == 'x');

    binary_t::binary_type bvalue;

    bvalue = b;
    CPPUNIT_ASSERT(bvalue == 'x');
    
    std::cout<<"value = "<<bvalue<<std::endl;
    std::cout<<"value = "<<b<<std::endl;
    Int8 ivalue = 'z';
    b = ivalue;
    std::cout<<"value = "<<b<<std::endl;
}

//-----------------------------------------------------------------------------
void binary_test::test_io()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef std::fstream fstream;

    std::ifstream istream;
    std::ofstream ostream;

    //open the file for reading
    istream.open("mscp03_au_sputter2_00057.tif", 
            std::ifstream::in | std::ifstream::binary);
   
    //need to determine the size of the file
    istream.seekg(0,std::ios::end);
    size_t size = istream.tellg();
    istream.seekg(0,std::ios::beg);


    ostream.open("test.tif", 
            std::ofstream::out | std::ofstream::binary);
   
    //copy binary file

    binary_t buffer;
    while(istream.get(((char&)buffer)))
    {
        ostream.put(((char&)buffer));
    }

    istream.close();
    ostream.close();
}


