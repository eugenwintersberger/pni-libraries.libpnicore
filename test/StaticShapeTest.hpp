//testing class for ArrayShape objects

#ifndef __STATICSHAPETEST_HPP__
#define __STATICSHAPETEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>
#include "StaticShape.hpp"

using namespace pni::utils;

class StaticShapeTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(StaticShapeTest);
	CPPUNIT_TEST(test_construction);
	CPPUNIT_TEST(test_offset);
	CPPUNIT_TEST(test_index);
	CPPUNIT_TEST_SUITE_END();
private:
public:
	void setUp();
	void tearDown();

	void test_construction();
	void test_offset();
	void test_index();

};

#endif
