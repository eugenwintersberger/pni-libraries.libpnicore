#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "TypeClassTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeClassTest);

using namespace pni::utils;

//-----------------------------------------------------------------------------
void TypeClassTest::setUp(){ }

//-----------------------------------------------------------------------------
void TypeClassTest::tearDown(){ }

//-----------------------------------------------------------------------------
void TypeClassTest::test_map()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    CPPUNIT_ASSERT(TypeClassMap<UInt8>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<Int8>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<UInt16>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<Int16>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<UInt32>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<Int32>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<UInt64>::type_class == TypeClass::INTEGER);
    CPPUNIT_ASSERT(TypeClassMap<Int64>::type_class == TypeClass::INTEGER);

    CPPUNIT_ASSERT(TypeClassMap<Float32>::type_class == TypeClass::FLOAT);
    CPPUNIT_ASSERT(TypeClassMap<Float64>::type_class == TypeClass::FLOAT);
    CPPUNIT_ASSERT(TypeClassMap<Float128>::type_class == TypeClass::FLOAT);

    CPPUNIT_ASSERT(TypeClassMap<Complex32>::type_class == TypeClass::COMPLEX);
    CPPUNIT_ASSERT(TypeClassMap<Complex64>::type_class == TypeClass::COMPLEX);
    CPPUNIT_ASSERT(TypeClassMap<Complex128>::type_class == TypeClass::COMPLEX);

    CPPUNIT_ASSERT(TypeClassMap<String>::type_class == TypeClass::STRING);
    CPPUNIT_ASSERT(TypeClassMap<Binary>::type_class == TypeClass::BINARY);
    CPPUNIT_ASSERT(TypeClassMap<Bool>::type_class == TypeClass::BOOL);

}
