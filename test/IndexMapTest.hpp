#ifndef __INDEXMAPTEST_HPP__
#define __INDEXMAPTEST_HPP__


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "IndexMap.hpp"

using namespace pni::utils;


class IndexMapTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(IndexMapTest);
        CPPUNIT_TEST(test_offset);
        CPPUNIT_TEST(test_index);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp(){}
        void tearDown() {}

        void test_offset();
        void test_index();
};


#endif
