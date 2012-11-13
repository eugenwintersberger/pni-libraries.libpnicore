#ifndef __TYPECLASSTEST_HPP__
#define __TYPECLASSTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/utils/Types.hpp>
#include <pni/utils/TypeClassMap.hpp>

using namespace pni::utils;

class TypeClassTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TypeClassTest);
        CPPUNIT_TEST(test_map);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_map();
};

#endif
