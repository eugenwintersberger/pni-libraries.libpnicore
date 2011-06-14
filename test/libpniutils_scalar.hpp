

#ifndef __LIBDDFDATA_SCALAR_HPP__
#define __LIBDDFDATA_SCALAR_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "Scalar.hpp"

class ScalarTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(ScalarTest);
    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testCharOperations);
    CPPUNIT_TEST(testUCharOperations);
    CPPUNIT_TEST_SUITE_END();
    private:
        //create some variables of native types
        pni::utils::Int8 v1_i8,v2_i8;
        pni::utils::Int8Scalar *s1_i8, *s2_i8;
        pni::utils::UInt8 v1_ui8,v2_ui8;
        pni::utils::UInt8Scalar *s1_ui8,*s2_ui8;
        pni::utils::Int16 v1_i16,v2_i16;
        pni::utils::UInt16 v1_ui16,v2_ui16;
        pni::utils::Int32 v1_i32,v2_i32;
        pni::utils::UInt32 v1_ui32,v2_ui32;
        pni::utils::Int64 v1_i64,v2_i64;
        pni::utils::UInt64 v1_ui64,v2_ui64;

        pni::utils::Float32 v1_f32,v2_f32;
        pni::utils::Float64 v1_f64,v2_f64;
        pni::utils::Float128 v1_f128,v2_f128;

        pni::utils::Complex32 v1_c32,v2_c32;
        pni::utils::Complex64 v1_c64,v2_c64;
        pni::utils::Complex128 v1_c128,v2_c128;
    public:
        void tearDown();
        void setUp();
        
        void testConstructors();
        void testCharOperations();
        void testUCharOperations();
};

#endif
