#ifndef __ARRAYVIEWSELECTORTEST_HPP__
#define __ARRAYVIEWSELECTORTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "ArrayViewSelector.hpp"

using namespace pni::utils;

class ArrayViewSelectorTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ArrayViewSelectorTest);
    CPPUNIT_TEST(test_selector);
    CPPUNIT_TEST_SUITE_END();
    public:
    void test_selector();
};

#endif
