//testing class for ArrayShape objects

#ifndef __LIBPNIUTILS_SHAPE_HPP__
#define __LIBPNIUTILS_SHAPE_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Shape.hpp"

using namespace pni::utils;

class ShapeTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ShapeTest);
	CPPUNIT_TEST(testConstruction);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testComparison);
	CPPUNIT_TEST(testOffset);
	CPPUNIT_TEST(testIndex);
	CPPUNIT_TEST(testExceptions);
	CPPUNIT_TEST_SUITE_END();
private:
	unsigned int *_s1;
	size_t _r1, _r2;
	unsigned int *_s2;
	Shape _sh1, _sh2;
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
