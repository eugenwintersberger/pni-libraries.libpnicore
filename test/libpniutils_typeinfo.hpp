/*
 * libpniutils_typeinfo.hpp
 *
 *  Created on: Jun 14, 2011
 *      Author: eugen
 */

#ifndef LIBPNIUTILS_TYPEINFO_HPP_
#define LIBPNIUTILS_TYPEINFO_HPP_
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "PNITypeInfo.hpp"
#include "PNITypes.hpp"
#include "Array.hpp"

class PNITypeInfoTest : public CppUnit::TestFixture{
	CPPUNIT_TEST_SUITE(PNITypeInfoTest);
	CPPUNIT_TEST(testStatic);
	CPPUNIT_TEST(testMethods);
	CPPUNIT_TEST_SUITE_END();
private:
	//integer types
	typedef pni::utils::PNITypeInfo<pni::utils::UInt8> tui8;
	typedef pni::utils::PNITypeInfo<pni::utils::Int8> ti8;
	typedef pni::utils::PNITypeInfo<pni::utils::UInt16> tui16;
	typedef pni::utils::PNITypeInfo<pni::utils::Int16> ti16;
	typedef pni::utils::PNITypeInfo<pni::utils::Int32> ti32;
	typedef pni::utils::PNITypeInfo<pni::utils::UInt32> tui32;
	typedef pni::utils::PNITypeInfo<pni::utils::Int64> ti64;
	typedef pni::utils::PNITypeInfo<pni::utils::UInt64> tui64;

	//float types
	typedef pni::utils::PNITypeInfo<pni::utils::Float32> tf32;
	typedef pni::utils::PNITypeInfo<pni::utils::Float64> tf64;
	typedef pni::utils::PNITypeInfo<pni::utils::Float128> tf128;

	//complex types
	typedef pni::utils::PNITypeInfo<pni::utils::Complex32> tc32;
	typedef pni::utils::PNITypeInfo<pni::utils::Complex64> tc64;
	typedef pni::utils::PNITypeInfo<pni::utils::Complex128> tc128;
public:
	void setUp();
	void tearDown();

	void testStatic();
	void testMethods();

};

#endif /* LIBPNIUTILS_TYPEINFO_HPP_ */
