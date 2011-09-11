

#ifndef __LIBDDFDATA_SCALAR_HPP__
#define __LIBDDFDATA_SCALAR_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "Scalar.hpp"

#define DOUBLE_PREC 1.e-12

using namespace pni::utils;

class ScalarTest : public CppUnit::TestFixture{
    CPPUNIT_TEST_SUITE(ScalarTest);
    CPPUNIT_TEST(testConstructors);

    CPPUNIT_TEST(testConversion);
    CPPUNIT_TEST(testAssignment);
    CPPUNIT_TEST(testSetGetValue);
    CPPUNIT_TEST(testBinaryAddOperation);
    CPPUNIT_TEST(testUnaryAddOperation);
    CPPUNIT_TEST(testUnaryDivOperation);
    CPPUNIT_TEST(testUnarySubOperation);
    CPPUNIT_TEST(testUnaryMultOperation);
    CPPUNIT_TEST(testComparison);
    CPPUNIT_TEST_SUITE_END();
    private:
    public:
        void tearDown();
        void setUp();
        
        void testConstructors();
        void testAssignment();
        void testSetGetValue();
        void testComparison();

        //some remarks about testing binary operations:
        //In all cases the temporary type of the result
        //is ok - so exceptions are raised only in cases
        //where the assignment operation and the type of the
        //l-value object do not satisfy the requirements for
        //assignment.
        void testBinaryAddOperation();
        void testBinarySubtractionOperation();
        void testBinaryDivisionOperation();
        void testBinaryMultiplicationOperation();


        void testUnaryAddOperation();
        void testUnaryMultOperation();
        void testUnaryDivOperation();
        void testUnarySubOperation();
        void testConversion();
};

#endif
