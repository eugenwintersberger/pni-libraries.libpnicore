//Unit test for the binary object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::utils;

class BinaryTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(BinaryTest);
    CPPUNIT_TEST(test_construction);
    CPPUNIT_TEST(test_comparison);
    CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_compatability);
    CPPUNIT_TEST(test_io_operator);
    CPPUNIT_TEST(test_io);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
    void test_construction();
    void test_comparison();
    void test_assignment();
    void test_compatability();
    void test_io_operator();
    void test_io();

};
