//unit test for the Buffer class

#ifndef __LIBPNIUTILS_BUFFER_HPP__
#define __LIBPNIUTILS_BUFFER_HPP__



#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Buffer.hpp"
#include "Types.hpp"

using namespace pni::utils;

//testing Buffer<T> and BufferObject concepts.
class BufferTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(BufferTest);
        CPPUNIT_TEST(testConstructors);
        CPPUNIT_TEST(testAllocation);
        CPPUNIT_TEST(testAccess);
        CPPUNIT_TEST(testAssignment);
        CPPUNIT_TEST(testComparison);
        CPPUNIT_TEST_SUITE_END();
    private:
        UInt64 n1,n2;
    public:
        void setUp();
        void tearDown();

        void testConstructors();
        void testAssignment();
        void testComparison();
        void testAllocation();
        void testAccess();

};


#endif
