//unit test for the Buffer class

#ifndef __LIBPNIUTILS_BUFFER_HPP__
#define __LIBPNIUTILS_BUFFER_HPP__



#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Buffer.hpp"

class BufferTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(BufferTest);
	CPPUNIT_TEST(testAllocation);
	CPPUNIT_TEST(testAccess);
	CPPUNIT_TEST_SUITE_END();
private:
public:
	void setUp();
	void tearDown();

	void testAllocation();
	void testAccess();

};


#endif
