

#ifndef __LIBDDFDATA_SCALAR_HPP__
#define __LIBDDFDATA_SCALAR_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "scalar.hpp"

class ScalarTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(ScalarTest);
    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testCharOperations);
    CPPUNIT_TEST(testUCharOperations);
    CPPUNIT_TEST(testStringOperations);
    CPPUNIT_TEST_SUITE_END();
    private:
        //create some variables of native types
        char v1_char,v2_char;
        CharScalar *s1_char,*s2_char;
        
        unsigned char v1_uchar,v2_uchar;
        UCharScalar *s1_uchar,*s2_uchar;
        
        short v1_short,v2_short;
        unsigned short v1_ushort,v2_ushort;
        int v1_int,v2_int;
        unsigned int v1_uint,v2_uint;
        long v1_long,v2_long;
        unsigned long v1_ulong,v2_ulong;
        float v1_float,v2_float;
        double v1_double,v2_double;
        String v1_string,v2_string;        
        StringScalar *s1_string,*s2_string;
    public:
        void tearDown();
        void setUp();
        
        void testConstructors();
        void testCharOperations();
        void testUCharOperations();
        void testStringOperations();
};

#endif
