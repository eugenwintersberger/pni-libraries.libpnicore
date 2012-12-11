/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Feb 08, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/current_function.hpp>

#include <pni/utils/Types.hpp>
#include <pni/utils/Binary.hpp>

#include "BinaryTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(BinaryTest);

using namespace pni::utils;

//-----------------------------------------------------------------------------
void BinaryTest::setUp(){ }

//-----------------------------------------------------------------------------
void BinaryTest::tearDown(){ }

//-----------------------------------------------------------------------------
void BinaryTest::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    BinaryType<UInt8> bvalue;
    
    BinaryType<UInt8> bvalue2 = 8; 
}

//-----------------------------------------------------------------------------
void BinaryTest::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    BinaryType<UInt8> v1 = 8;
    BinaryType<UInt8> v2 = 10;
    BinaryType<UInt8> v3 = 8;

    CPPUNIT_ASSERT(v1 != v2);
    CPPUNIT_ASSERT(v1 == v3);
}

//-----------------------------------------------------------------------------
void BinaryTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    BinaryType<UInt8> v1;

    v1 = 10;

    BinaryType<UInt8> v2 = 10;
    CPPUNIT_ASSERT(v1 == v2);
}

//-----------------------------------------------------------------------------
void BinaryTest::test_compatability()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    UInt8 rv;
    BinaryType<UInt8> bv = 10;
   
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
    BinaryType<UInt8> *bptr = new BinaryType<UInt8>[10];

    for(size_t i=0;i<10;i++){
        *rptr = i;
        *bptr = i;
    }

    for(size_t i=0;i<10;i++) CPPUNIT_ASSERT(*rptr == *bptr);


    delete [] rptr;
    delete [] bptr;
}

//-----------------------------------------------------------------------------
void BinaryTest::test_io_operator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    BinaryType<UInt8>  b = 'a';

    CPPUNIT_ASSERT(b == 'a');
    b = 'x';
    CPPUNIT_ASSERT(b == 'x');

    BinaryType<UInt8>::binary_type bvalue;

    bvalue = b;
    CPPUNIT_ASSERT(bvalue == 'x');
    
    std::cout<<"value = "<<bvalue<<std::endl;
    std::cout<<"value = "<<b<<std::endl;
    Int8 ivalue = 'z';
    b = ivalue;
    std::cout<<"value = "<<b<<std::endl;
}

//-----------------------------------------------------------------------------
void BinaryTest::test_io()
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

    BinaryType<UInt8> buffer;
    while(istream.get(((char&)buffer)))
    {
        ostream.put(((char&)buffer));
    }

    istream.close();
    ostream.close();
}


