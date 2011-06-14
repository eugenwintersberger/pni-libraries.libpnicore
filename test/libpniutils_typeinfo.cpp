/*
 * libpniutils_typeinfo.cpp
 *
 *  Created on: Jun 14, 2011
 *      Author: eugen
 */

#include<cppunit/extensions/HelperMacros.h>

#include "libpniutils_typeinfo.hpp"
#include "PNITypeInfo.hpp"

//register the test at the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(PNITypeInfoTest);

void PNITypeInfoTest::tearDown(){

}

void PNITypeInfoTest::setUp(){

}

void PNITypeInfoTest::testStatic(){
	//check for integer types
	CPPUNIT_ASSERT(tui8::isSigned == false);
	CPPUNIT_ASSERT(tui8::ByteSize == sizeof(pni::utils::UInt8));
	CPPUNIT_ASSERT(tui8::TypeID == pni::utils::UINT8);

	CPPUNIT_ASSERT(ti8::isSigned == true);
	CPPUNIT_ASSERT(ti8::ByteSize == sizeof(pni::utils::Int8));
	CPPUNIT_ASSERT(ti8::TypeID == pni::utils::INT8);

	CPPUNIT_ASSERT(tui16::isSigned == false);
	CPPUNIT_ASSERT(tui16::ByteSize == sizeof(pni::utils::UInt16));
	CPPUNIT_ASSERT(tui16::TypeID == pni::utils::UINT16);

	CPPUNIT_ASSERT(ti16::isSigned == true);
	CPPUNIT_ASSERT(ti16::ByteSize == sizeof(pni::utils::Int16));
	CPPUNIT_ASSERT(ti16::TypeID == pni::utils::INT16);

	CPPUNIT_ASSERT(tui32::isSigned == false);
	CPPUNIT_ASSERT(tui32::ByteSize == sizeof(pni::utils::UInt32));
	CPPUNIT_ASSERT(tui32::TypeID == pni::utils::UINT32);

	CPPUNIT_ASSERT(ti32::isSigned == true);
	CPPUNIT_ASSERT(ti32::ByteSize == sizeof(pni::utils::Int32));
	CPPUNIT_ASSERT(ti32::TypeID == pni::utils::INT32);

	CPPUNIT_ASSERT(tui64::isSigned == false);
	CPPUNIT_ASSERT(tui64::ByteSize == sizeof(pni::utils::UInt64));
	CPPUNIT_ASSERT(tui64::TypeID == pni::utils::UINT64);

	CPPUNIT_ASSERT(ti64::isSigned == true);
	CPPUNIT_ASSERT(ti64::ByteSize == sizeof(pni::utils::Int64));
	CPPUNIT_ASSERT(ti64::TypeID == pni::utils::INT64);

	CPPUNIT_ASSERT(tf32::isSigned == true);
	CPPUNIT_ASSERT(tf32::ByteSize == sizeof(pni::utils::Float32));
	CPPUNIT_ASSERT(tf32::TypeID == pni::utils::FLOAT32);

	CPPUNIT_ASSERT(tf64::isSigned == true);
	CPPUNIT_ASSERT(tf64::ByteSize == sizeof(pni::utils::Float64));
	CPPUNIT_ASSERT(tf64::TypeID == pni::utils::FLOAT64);

	CPPUNIT_ASSERT(tf128::isSigned == true);
	CPPUNIT_ASSERT(tf128::ByteSize == sizeof(pni::utils::Float128));
	CPPUNIT_ASSERT(tf128::TypeID == pni::utils::FLOAT128);

	CPPUNIT_ASSERT(tc32::isSigned == true);
	CPPUNIT_ASSERT(tc32::ByteSize == sizeof(pni::utils::Complex32));
	CPPUNIT_ASSERT(tc32::TypeID == pni::utils::COMPLEX32);

	CPPUNIT_ASSERT(tc64::isSigned == true);
	CPPUNIT_ASSERT(tc64::ByteSize == sizeof(pni::utils::Complex64));
	CPPUNIT_ASSERT(tc64::TypeID == pni::utils::COMPLEX64);

	CPPUNIT_ASSERT(tc128::isSigned == true);
	CPPUNIT_ASSERT(tc128::ByteSize == sizeof(pni::utils::Complex128));
	CPPUNIT_ASSERT(tc128::TypeID == pni::utils::COMPLEX128);
}

void PNITypeInfoTest::testMethods(){

}
