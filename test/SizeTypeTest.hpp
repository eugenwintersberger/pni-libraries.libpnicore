#ifndef __SIZETYPETEST_HPP__
#define __SIZETYPETEST_HPP__

#include<random>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "SizeType.hpp"


class SizeTypeTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SizeTypeTest);
    CPPUNIT_TEST(test_size); 
    CPPUNIT_TEST_SUITE_END();
    public:
    void test_size();
};


#endif
