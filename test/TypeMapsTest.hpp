#ifndef __TYPEMAPSTEST_HPP__
#define __TYPEMAPSTEST_HPP__

#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/utils/Types.hpp>
#include <pni/utils/IDTypeMap.hpp>
#include <pni/utils/TypeIDMap.hpp>

using namespace pni::utils;

class TypeMapsTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(TypeMapsTest);
    CPPUNIT_TEST(test_id2type);
    CPPUNIT_TEST(test_type2id);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
    void test_id2type();
    void test_type2id();

};


#endif
