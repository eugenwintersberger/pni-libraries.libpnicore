#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "TypeMapsTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeMapsTest);

using namespace pni::utils;

//-----------------------------------------------------------------------------
void TypeMapsTest::setUp(){ }

//-----------------------------------------------------------------------------
void TypeMapsTest::tearDown(){ }

//-----------------------------------------------------------------------------
void TypeMapsTest::test_type2id()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(TypeIDMap<Int8>::type_id == TypeID::INT8);
    CPPUNIT_ASSERT(TypeIDMap<UInt8>::type_id == TypeID::UINT8);
    
    CPPUNIT_ASSERT(TypeIDMap<Int16>::type_id == TypeID::INT16);
    CPPUNIT_ASSERT(TypeIDMap<UInt16>::type_id == TypeID::UINT16);
    
    CPPUNIT_ASSERT(TypeIDMap<Int32>::type_id == TypeID::INT32);
    CPPUNIT_ASSERT(TypeIDMap<UInt32>::type_id == TypeID::UINT32);
    
    CPPUNIT_ASSERT(TypeIDMap<Int64>::type_id == TypeID::INT64);
    CPPUNIT_ASSERT(TypeIDMap<UInt64>::type_id == TypeID::UINT64);
    
    CPPUNIT_ASSERT(TypeIDMap<Float32>::type_id == TypeID::FLOAT32); 
    CPPUNIT_ASSERT(TypeIDMap<Float64>::type_id == TypeID::FLOAT64); 
    CPPUNIT_ASSERT(TypeIDMap<Float128>::type_id == TypeID::FLOAT128); 
    
    CPPUNIT_ASSERT(TypeIDMap<Complex32>::type_id == TypeID::COMPLEX32); 
    CPPUNIT_ASSERT(TypeIDMap<Complex64>::type_id == TypeID::COMPLEX64); 
    CPPUNIT_ASSERT(TypeIDMap<Complex128>::type_id == TypeID::COMPLEX128); 

    CPPUNIT_ASSERT(TypeIDMap<String>::type_id == TypeID::STRING);
    CPPUNIT_ASSERT(TypeIDMap<Binary>::type_id == TypeID::BINARY);
}

//-----------------------------------------------------------------------------
void TypeMapsTest::test_id2type()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::INT8>::type >::type_id == TypeID::INT8);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::UINT8>::type >::type_id == TypeID::UINT8);
    
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::INT16>::type >::type_id == TypeID::INT16);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::UINT16>::type >::type_id == TypeID::UINT16);
    
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::INT32>::type >::type_id == TypeID::INT32);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::UINT32>::type >::type_id == TypeID::UINT32);
    
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::INT64>::type >::type_id == TypeID::INT64);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::UINT64>::type >::type_id == TypeID::UINT64);

    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::FLOAT32>::type >::type_id ==
            TypeID::FLOAT32);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::FLOAT64>::type >::type_id ==
            TypeID::FLOAT64);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::FLOAT128>::type >::type_id ==
            TypeID::FLOAT128);
    
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::COMPLEX32>::type >::type_id ==
            TypeID::COMPLEX32);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::COMPLEX64>::type >::type_id ==
            TypeID::COMPLEX64);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::COMPLEX128>::type >::type_id ==
            TypeID::COMPLEX128);

    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::STRING>::type >::type_id ==
            TypeID::STRING);
    CPPUNIT_ASSERT(
            TypeIDMap<IDTypeMap<TypeID::BINARY>::type >::type_id ==
            TypeID::BINARY);
}

