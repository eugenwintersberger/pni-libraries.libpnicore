//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "arrayshape.hpp"

class ArrayTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(ArrayTest);
	CPPUNIT_TEST(testConstructors);
	CPPUNIT_TEST(testSetAndGet);
	CPPUNIT_TEST_SUITE_END();
private:
	unsigned int *_s1;
	unsigned int _r1,_r2;
	unsigned int *_s2;
	ArrayShape _sh1,_sh2;
public:
	void setUp();
	void tearDown();
	void testConstructors();
	void testSetAndGet();
	void testBinaryOperations();
	void testUnaryOperations();
	void testComparison();


};
