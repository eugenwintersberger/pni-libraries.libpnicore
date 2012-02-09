//implementation of the unit tests for Binary

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "../src/Binary.hpp"
#include "BinaryTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(BinaryTest);

using namespace pni::utils;

void BinaryTest::setUp(){

}

void BinaryTest::tearDown(){

}

void BinaryTest::test_construction(){
    BinaryType<UInt8> bvalue;
    
    BinaryType<UInt8> bvalue2 = 8; 
     

}

void BinaryTest::test_comparison(){
    BinaryType<UInt8> v1 = 8;
    BinaryType<UInt8> v2 = 10;
    BinaryType<UInt8> v3 = 8;

    CPPUNIT_ASSERT(v1 != v2);
    CPPUNIT_ASSERT(v1 == v3);

}

void BinaryTest::test_assignment(){
    BinaryType<UInt8> v1;

    v1 = 10;

    BinaryType<UInt8> v2 = 10;
    CPPUNIT_ASSERT(v1 == v2);
}

void BinaryTest::test_compatability(){
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

void BinaryTest::test_io_operator(){
    std::cout<<"void BinaryTest::test_io_operator()---------------------------";
    std::cout<<std::endl;
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

void BinaryTest::test_io(){
    std::cout<<"void BinaryTest::test_io()------------------------------------";
    std::cout<<std::endl;

    typedef
        std::fstream fstream;

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
    while(istream.get(((char&)buffer))){
        ostream.put(((char&)buffer));
    }

    istream.close();
    ostream.close();

}


