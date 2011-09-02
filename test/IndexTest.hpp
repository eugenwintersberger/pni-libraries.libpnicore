/*
 * IndexTest.hpp
 *
 *  Created on: Sep 2, 2011
 *      Author: eugen
 */

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Index.hpp"

using namespace pni::utils;

#ifndef INDEXTEST_HPP_
#define INDEXTEST_HPP_

class IndexTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(IndexTest);
	CPPUNIT_TEST(testInstantiation);
	CPPUNIT_TEST(testComparison);
	CPPUNIT_TEST(testAccess);
	CPPUNIT_TEST(testIndexManipulation);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();

	void testInstantiation();
	void testComparison();
	void testAccess();
	void testIndexManipulation();


};

#endif /* INDEXTEST_HPP_ */
