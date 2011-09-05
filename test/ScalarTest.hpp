

#ifndef __LIBDDFDATA_SCALAR_HPP__
#define __LIBDDFDATA_SCALAR_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "Scalar.hpp"

using namespace pni::utils;

class ScalarTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(ScalarTest);
    CPPUNIT_TEST(testConstructors);

    //CPPUNIT_TEST(testCharOperations);
    //CPPUNIT_TEST(testUCharOperations);
    CPPUNIT_TEST(testConversion);
    CPPUNIT_TEST(testAssignment);
    CPPUNIT_TEST(testSetGetValue);
    CPPUNIT_TEST(testBinaryAddOperation);
    CPPUNIT_TEST(testUnaryAddOperation);
    CPPUNIT_TEST_SUITE_END();
    private:
        //create some variables of native types
        Int8 v1_i8,v2_i8;
        Int8Scalar *s1_i8, *s2_i8;
        UInt8 v1_ui8,v2_ui8;
        UInt8Scalar *s1_ui8,*s2_ui8;
        Int16 v1_i16,v2_i16;
        UInt16 v1_ui16,v2_ui16;
        Int32 v1_i32,v2_i32;
        UInt32 v1_ui32,v2_ui32;
        Int64 v1_i64,v2_i64;
        UInt64 v1_ui64,v2_ui64;

        Float32 v1_f32,v2_f32;
        Float64 v1_f64,v2_f64;
        Float128 v1_f128,v2_f128;

        Complex32 v1_c32,v2_c32;
        Complex64 v1_c64,v2_c64;
        Complex128 v1_c128,v2_c128;
    public:
        void tearDown();
        void setUp();
        
        void testConstructors();
        void testAssignment();
        void testSetGetValue();
        void testBinaryAddOperation();
        void testUnaryAddOperation();
        void testConversion();
};

#endif
