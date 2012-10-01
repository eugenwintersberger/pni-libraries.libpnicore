
#ifndef __TYPEINFOTEST_HPP__
#define __TYPEINFOTEST_HPP__

#include <boost/current_function.hpp>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include <limits>
#include <climits>
#include "Types.hpp"
#include "TypeInfo.hpp"


using namespace pni::utils;

class TypeInfoTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(TypeInfoTest);
        CPPUNIT_TEST(test_min_max);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp() {}
        void tearDown() {}
        
        void test_min_max();


};

//-----------------------------------------------------------------------------

#endif
