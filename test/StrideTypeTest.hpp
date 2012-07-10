#ifndef __STRIDETYPETEST_HPP__
#define __STRIDETYPETEST_HPP__

#include<random>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "StrideType.hpp"

using namespace pni::utils;

class StrideTypeTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StrideTypeTest);
    CPPUNIT_TEST(test_computation);
    CPPUNIT_TEST(test_calc);
    CPPUNIT_TEST_SUITE_END();
    public:
    void test_computation();
    void test_calc();
};


#endif
