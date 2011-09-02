/*
 * NumericObjectTest.hpp
 *
 *  Created on: Sep 2, 2011
 *      Author: eugen
 */

#ifndef NUMERICOBJECTTEST_HPP_
#define NUMERICOBJECTTEST_HPP_

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "NumericObject.hpp"

using namespace pni::utils;

class NumericObjectTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(NumericObjectTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void testCreation();
	void testAssignment();

};

#endif /* NUMERICOBJECTTEST_HPP_ */
