//unit test for the Buffer class

#ifndef __LIBPNIUTILS_BUFFER_HPP__
#define __LIBPNIUTILS_BUFFER_HPP__



#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Buffer.hpp"
#include "PNITypes.hpp"

using namespace pni::utils;

//testing Buffer<T> and BufferObject concepts.
class BufferTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(BufferTest);
	CPPUNIT_TEST(testAllocation);
	CPPUNIT_TEST(testAccess);
	CPPUNIT_TEST(testCopy);
	CPPUNIT_TEST(testAssignment);
	CPPUNIT_TEST(testComparison);
	CPPUNIT_TEST(testConversion);
	CPPUNIT_TEST_SUITE_END();
private:
public:
	void setUp();
	void tearDown();

	void testAssignment();
	void testComparison();
	void testCopy();
	void testAllocation();
	void testAccess();
	void testConversion();

};


#endif
