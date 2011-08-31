/*
 * InplaceArithmeticsTest.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#ifndef INPLACEARITHMETICSTEST_HPP_
#define INPLACEARITHMETICSTEST_HPP_

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "policies/InplaceArithmetics.hpp"
#include "Exceptions.hpp"
#include "Array.hpp"
#include "PNITypes.hpp"

using namespace pni::utils;

class InplaceArithmeticsTest:public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(InplaceArithmeticsTest);
	CPPUNIT_TEST(addTest);
	CPPUNIT_TEST_SUITE_END();
private:
	Float32Array f32a;
	UInt8Array u8a;
	Int64Array i64a;
	Complex64Array c64a;
	ArrayShape s;
	InplaceArithmetics ar;
public:
	void setUp();
	void tearDown();

	void addTest();


};

#endif /* INPLACEARITHMETICSTEST_HPP_ */
