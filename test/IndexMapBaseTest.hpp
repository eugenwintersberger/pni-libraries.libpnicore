//test case for the IndexMapBase base class

#ifndef __INDEXMAPBASETEST_HPP__
#define __INDEXMAPBASETEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>
#include <pni/utils/IndexMapBase.hpp>

using namespace pni::utils;

class IndexMapBaseTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(IndexMapBaseTest);
	CPPUNIT_TEST(test_construction);
	CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_access);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
    
    void test_construction();
    void test_assignment();
    void test_access();

};

#endif
