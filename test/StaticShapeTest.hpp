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
	CPPUNIT_TEST(testConstruction);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testComparison);
	CPPUNIT_TEST(testOffset);
	CPPUNIT_TEST(testIndex);
	CPPUNIT_TEST(testExceptions);
	CPPUNIT_TEST_SUITE_END();
private:
public:
	void setUp();
	void tearDown();

	void testConstruction();
	void testAssignment();
	void testComparison();
	void testOffset();
	void testIndex();
	void testExceptions();

};

#endif
