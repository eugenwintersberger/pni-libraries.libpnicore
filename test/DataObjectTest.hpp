/*
 * DataObjectTest.hpp
 *
 *  Created on: Sep 2, 2011
 *      Author: eugen
 */

#ifndef DATAOBJECTTEST_HPP_
#define DATAOBJECTTEST_HPP_

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "DataObject.hpp"

using namespace pni::utils;

class DataObjectTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(DataObjectTest);
	CPPUNIT_TEST(testCreation);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void testCreation();
	void testAssignment();


};

#endif /* DATAOBJECTTEST_HPP_ */
