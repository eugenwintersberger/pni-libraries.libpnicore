//unit test for buffer type erasure

#ifndef __BUFFERTEST_HPP__
#define __BUFFERTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "Types.hpp"
#include "Buffer.hpp"

using namespace pni::utils;

class BufferTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BufferTest);
    CPPUNIT_TEST(test_construction);
    CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_size);
    CPPUNIT_TEST(test_ptr);
    CPPUNIT_TEST(test_typeid);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void test_construction();
    void test_assignment();
    void test_size();
    void test_ptr();
    void test_typeid();


};

#endif
