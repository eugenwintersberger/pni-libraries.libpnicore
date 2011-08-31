/*
 * InplaceArithmeticsTest.cpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#include "InplaceArithmeticsTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(InplaceArithmeticsTest);

void InplaceArithmeticsTest::setUp(){
	s.setRank(2);
	s.setDimension(0,1024);
	s.setDimension(1,512);

	f32a = Float32Array(s);
	u8a  = UInt8Array(s);
	i64a = Int64Array(s);
	c64a = Complex64Array(s);
}

void InplaceArithmeticsTest::tearDown(){

}

void InplaceArithmeticsTest::addTest(){
	double x = 1000.;
	int w = 34;
	UInt32 ui = 1;

	CPPUNIT_ASSERT_NO_THROW(ar.add_inplace(f32a,2.));
	CPPUNIT_ASSERT_NO_THROW(ar.add_inplace(f32a,x));
	CPPUNIT_ASSERT_NO_THROW(ar.add_inplace(f32a,w));
	CPPUNIT_ASSERT_THROW(ar.add_inplace(f32a,ui),RangeError);

	CPPUNIT_ASSERT_NO_THROW(ar.add_inplace(c64a,w));



}
