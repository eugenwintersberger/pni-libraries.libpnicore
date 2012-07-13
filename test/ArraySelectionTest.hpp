#ifndef __ARRAYSELECTIONTEST_HPP__
#define __ARRAYSELECTIONTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>
#include "ArraySelection.hpp"

using namespace pni::utils;

class ArraySelectionTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ArraySelectionTest);
	CPPUNIT_TEST(test_construction);
	CPPUNIT_TEST(test_assignment);
	CPPUNIT_TEST(test_index);
	CPPUNIT_TEST_SUITE_END();
private:
    typedef std::vector<size_t> itype;
public:
	void setUp();
	void tearDown();

	void test_construction();
	void test_assignment();
	void test_index();

};

#endif
