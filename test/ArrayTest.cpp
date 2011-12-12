//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "Buffer.hpp"
#include "Shape.hpp"
#include "ArrayTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayTest);

using namespace pni::utils;

//------------------------------------------------------------------------------
void ArrayTest::setUp(){
	r1 = 2;
	r2 = 3;

	s1.rank(r1);
	s2.rank(r2);

	s1.dim(0,3); s1.dim(1,4);
	s2.dim(0,2);
	s2.dim(1,3);
	s2.dim(2,5);

}

//------------------------------------------------------------------------------
void ArrayTest::tearDown(){

}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
void ArrayTest::testAssignment(){

}

//------------------------------------------------------------------------------
void ArrayTest::testSlowArrayConstruction(){
	Shape s;
	Int32Array a;
	Index in;

	//construct the shape object
	s.rank(2);
	in.rank(s.rank());
	s.dim(0,1024);
	s.dim(1,2048);

	a.shape(s);
	Buffer<Int32> buffer;
	buffer.allocate(s.size());
	a.buffer(buffer);

	in[0] = 100; in[1] = 100;
	a(in) = 1000;
	in[0] = 50; in[1] = 23;
	a(in) = -10;
	in[0] = 1023; in[1] = 2047;
 	a(in) = 50;

	CPPUNIT_ASSERT(a.Min() == -10);
	CPPUNIT_ASSERT(a.Max() == 1000);
}

//------------------------------------------------------------------------------
void ArrayTest::testSetAndGet(){
	Array<double> a1(s1);
	Index in;

	//access via [] operator
	Shape s = a1.shape();
	for(size_t i=0;i<s.size();i++) a1[i] = (double)i;

	//check if data values have been transfered correctly
	for(size_t i=0;i<s.size();i++) CPPUNIT_ASSERT(((double)i)==a1[i]);

	//check access via () operator
	in.rank(s.rank());
	for(in[0]=0; in[0]<s[0]; in.inc(0)){
		for(in[1]=0; in[1]<s[1]; in.inc(1)){
			a1(in) = (double)in[0]*in[1];
		}
	}
	for(in[0]=0;in[0]<s[0];in.inc(0)){
		for(in[1]=0;in[1]<s[1];in.inc(1)){
			CPPUNIT_ASSERT(a1(in) == ((double)in[0]*in[1]));
		}
	}

}

//------------------------------------------------------------------------------
void ArrayTest::testComparison(){
	Float64Array a1(s1);
	Float64Array b1(s1);
	Float64Array a2(s2);
	Float64Array b2(s2);
	Index in1,in2;

	in1.rank(s1.rank());
	in2.rank(s2.rank());

	for(in1[0]=0; in1[0]<s1[0]; in1.inc(0)){
		for(in1[1]=0; in1[1]<s1[1]; in1.inc(1)){
			a1(in1) = (Float64)in1[0];
			b1(in1) = (Float64)in1[1]*10;
		}
	}
	CPPUNIT_ASSERT(a1==a1);
	CPPUNIT_ASSERT(a1!=b1);
	CPPUNIT_ASSERT(b1==b1);


	for(in2[0]=0; in2[0]<s2[0]; in2.inc(0)){
		for(in2[1]=0; in2[1]<s2[1]; in2.inc(1)){
			for(in2[2]=0; in2[2]<s2[2]; in2.inc(2)){
				a2(in2) = (Float64)in2[0];
				b2(in2) = (Float64)in2[0]*10;
			}
		}
	}
	CPPUNIT_ASSERT(a2==a2);
	CPPUNIT_ASSERT(a2!=b2);
	CPPUNIT_ASSERT(b2==b2);

}

//------------------------------------------------------------------------------
void ArrayTest::testTypeInfo(){
	ArrayObject *ptr;

	ptr = new Int8Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::INT8);
	delete ptr;

	ptr = new UInt8Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::UINT8);
	delete ptr;

	ptr = new Int16Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::INT16);
	delete ptr;

	ptr = new UInt16Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::UINT16);
	delete ptr;

	ptr = new Int32Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::INT32);
	delete ptr;

	ptr = new UInt32Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::UINT32);
	delete ptr;

	ptr = new Int64Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::INT64);
	delete ptr;

	ptr = new pni::utils::UInt64Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::UINT64);
	delete ptr;

	ptr = new Float32Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::FLOAT32);
	delete ptr;

	ptr = new Float64Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::FLOAT64);
	delete ptr;

	ptr = new Float128Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::FLOAT128);
	delete ptr;

	ptr = new Complex32Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::COMPLEX32);
	delete ptr;

	ptr = new Complex64Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::COMPLEX64);
	delete ptr;

	ptr = new Complex128Array();
	CPPUNIT_ASSERT(ptr->type_id()==TypeID::COMPLEX128);
	delete ptr;
}
