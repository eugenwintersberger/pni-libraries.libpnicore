/*
 * BufferObjectTest.hpp
 *
 *  Created on: Sep 1, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef BUFFEROBJECTTEST_HPP_
#define BUFFEROBJECTTEST_HPP_

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "BufferObject.hpp"
#include "PNITypes.hpp"

using namespace pni::utils;

class BufferObjectTest:public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(BufferObjectTest);
	CPPUNIT_TEST(testConstruction);
	CPPUNIT_TEST(testAccess);
	CPPUNIT_TEST(testParameters);
	CPPUNIT_TEST_SUITE_END();
private:
	UInt64 n1;
	UInt64 n2;
	UInt64 e1;
	UInt64 e2;
public:
	void setUp();
	void tearDown();

	void testParameters();
	void testConstruction();
	void testAccess();

};

#endif /* BUFFEROBJECTTEST_HPP_ */
