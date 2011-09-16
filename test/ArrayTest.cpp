//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "Buffer.hpp"
#include "ArrayShape.hpp"
#include "ArrayTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayTest);

using namespace pni::utils;

void ArrayTest::setUp(){
	r1 = 2;
	r2 = 3;

	s1.setRank(r1);
	s2.setRank(r2);

	s1.setDimension(0,3); s1.setDimension(1,4);
	s2.setDimension(0,2);
	s2.setDimension(1,3);
	s2.setDimension(2,5);

}

void ArrayTest::tearDown(){

}

void ArrayTest::testConstruction(){
	//check for simple array-construction
	Array<double> a1(s1);
	Array<double> a2(s2);

	//this should check if third
	Array<double> a3;
	CPPUNIT_ASSERT_NO_THROW(a3 = Array<double>(s2));

	Int16Array a4;
	CPPUNIT_ASSERT_NO_THROW(a4 = Int16Array());
	CPPUNIT_ASSERT_NO_THROW(a4 = Int16Array());

	CPPUNIT_ASSERT_NO_THROW(a3 = Array<double>());

}

void ArrayTest::testAssignment(){

}

void ArrayTest::testSlowArrayConstruction(){
	ArrayShape s;
	Int32Array a;
	Index in;

	//construct the shape object
	s.setRank(2);
	in.setRank(s.getRank());
	s.setDimension(0,1024);
	s.setDimension(1,2048);

	a.setShape(s);
	Buffer<Int32> buffer;
	buffer.setSize(s.getSize());
	buffer.allocate();
	a.setBuffer(buffer);

	in[0] = 100; in[1] = 100;
	a(in) = 1000;
	in[0] = 50; in[1] = 23;
	a(in) = -10;
	in[0] = 1023; in[1] = 2047;
 	a(in) = 50;

	CPPUNIT_ASSERT(a.Min() == -10);
	CPPUNIT_ASSERT(a.Max() == 1000);
}


void ArrayTest::testSetAndGet(){
	Array<double> a1(s1);
	UInt32 i;
	Index in;

	//access via [] operator
	ArrayShape s = a1.getShape();
	for(i=0;i<s.getSize();i++) a1[i] = (double)i;

	//check if data values have been transfered correctly
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(((double)i)==a1[i]);

	//check access via () operator
	in.setRank(s.getRank());
	for(in[0]=0; in[0]<s[0]; in.increment(0)){
		for(in[1]=0; in[1]<s[1]; in.increment(1)){
			a1(in) = (double)i;
		}
	}
	for(in[0]=0;in[0]<s[0];in.increment(0)){
		for(in[1]=0;in[1]<s[1];in.increment(1)){
			CPPUNIT_ASSERT(a1(in) == ((double)i));
		}
	}

}

void ArrayTest::testComparison(){
	Float64Array a1(s1);
	Float64Array b1(s1);
	Float64Array a2(s2);
	Float64Array b2(s2);
	Index in1,in2;

	in1.setRank(s1.getRank());
	in2.setRank(s2.getRank());

	for(in1[0]=0; in1[0]<s1[0]; in1.increment(0)){
		for(in1[1]=0; in1[1]<s1[1]; in1.increment(1)){
			a1(in1) = (Float64)in1[0];
			b1(in1) = (Float64)in1[1]*10;
		}
	}
	CPPUNIT_ASSERT(a1==a1);
	CPPUNIT_ASSERT(a1!=b1);
	CPPUNIT_ASSERT(b1==b1);


	for(in2[0]=0; in2[0]<s2[0]; in2.increment(0)){
		for(in2[1]=0; in2[1]<s2[1]; in2.increment(1)){
			for(in2[2]=0; in2[2]<s2[2]; in2.increment(2)){
				a2(in2) = (Float64)in2[0];
				b2(in2) = (Float64)in2[0]*10;
			}
		}
	}
	CPPUNIT_ASSERT(a2==a2);
	CPPUNIT_ASSERT(a2!=b2);
	CPPUNIT_ASSERT(b2==b2);

}



void ArrayTest::testTypeInfo(){
	pni::utils::ArrayObject *ptr;

	ptr = new pni::utils::ArrayObject();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::NONE);
	delete ptr;

	ptr = new pni::utils::Int8Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::INT8);
	delete ptr;

	ptr = new pni::utils::UInt8Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::UINT8);
	delete ptr;

	ptr = new pni::utils::Int16Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::INT16);
	delete ptr;

	ptr = new pni::utils::UInt16Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::UINT16);
	delete ptr;

	ptr = new pni::utils::Int32Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::INT32);
	delete ptr;

	ptr = new pni::utils::UInt32Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::UINT32);
	delete ptr;

	ptr = new pni::utils::Int64Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::INT64);
	delete ptr;

	ptr = new pni::utils::UInt64Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::UINT64);
	delete ptr;

	ptr = new pni::utils::Float32Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::FLOAT32);
	delete ptr;

	ptr = new pni::utils::Float64Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::FLOAT64);
	delete ptr;

	ptr = new pni::utils::Float128Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::FLOAT128);
	delete ptr;

	ptr = new pni::utils::Complex32Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::COMPLEX32);
	delete ptr;

	ptr = new pni::utils::Complex64Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::COMPLEX64);
	delete ptr;

	ptr = new pni::utils::Complex128Array();
	CPPUNIT_ASSERT(ptr->getTypeID()==pni::utils::COMPLEX128);
	delete ptr;
}
