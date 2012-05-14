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
    s1 = {3,4};
    s2 = {2,3,5};
}

//------------------------------------------------------------------------------
void ArrayTest::tearDown(){

}

//------------------------------------------------------------------------------
void ArrayTest::testConstruction(){
    typedef Array<double,Buffer> DArray;
	//check for simple array-construction
	DArray a1(s1);
	DArray a2(s2);

	//this should check if third
	DArray a3;
	CPPUNIT_ASSERT_NO_THROW(a3 = DArray(s2));

	Int16Array a4;
	CPPUNIT_ASSERT_NO_THROW(a4 = Int16Array());
	CPPUNIT_ASSERT_NO_THROW(a4 = Int16Array());

	CPPUNIT_ASSERT_NO_THROW(a3 = DArray());

}

//------------------------------------------------------------------------------
void ArrayTest::testAssignment(){

}

//------------------------------------------------------------------------------
void ArrayTest::testSlowArrayConstruction(){

	//construct the shape object
	Shape s = {1024,2048};

	Int32Array a;
	a.shape(s);
	Buffer<Int32> buffer;
	buffer.allocate(s.size());
	a.buffer(buffer);
    CPPUNIT_ASSERT(a.is_allocated());

	CPPUNIT_ASSERT_NO_THROW(a({100,100}) = 1000);
	CPPUNIT_ASSERT_NO_THROW(a({50,23}) = -10);
 	CPPUNIT_ASSERT_NO_THROW(a({1023,2047}) = 50);

	CPPUNIT_ASSERT(a.min() == -10);
	CPPUNIT_ASSERT(a.max() == 1000);
}

//------------------------------------------------------------------------------
void ArrayTest::testSetAndGet(){
	Array<double,Buffer> a1(s1);
	Index in;

	//access via [] operator
	Shape s = a1.shape();
	for(size_t i=0;i<s.size();i++) a1[i] = (double)i;

	//check if data values have been transfered correctly
	for(size_t i=0;i<s.size();i++) CPPUNIT_ASSERT(((double)i)==a1[i]);

    /*
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
    */

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

    /*
	for(in1[0]=0; in1[0]<s1[0]; in1.inc(0)){
		for(in1[1]=0; in1[1]<s1[1]; in1.inc(1)){
			a1(in1) = (Float64)in1[0];
			b1(in1) = (Float64)in1[1]*10;
		}
	}
    */
	CPPUNIT_ASSERT(a1==a1);
	CPPUNIT_ASSERT(a1!=b1);
	CPPUNIT_ASSERT(b1==b1);


    /*
	for(in2[0]=0; in2[0]<s2[0]; in2.inc(0)){
		for(in2[1]=0; in2[1]<s2[1]; in2.inc(1)){
			for(in2[2]=0; in2[2]<s2[2]; in2.inc(2)){
				a2(in2) = (Float64)in2[0];
				b2(in2) = (Float64)in2[0]*10;
			}
		}
	}
    */
	CPPUNIT_ASSERT(a2==a2);
	CPPUNIT_ASSERT(a2!=b2);
	CPPUNIT_ASSERT(b2==b2);

}

//------------------------------------------------------------------------------
void ArrayTest::testTypeInfo(){
    
	CPPUNIT_ASSERT(Int8Array::type_id==TypeID::INT8);
	CPPUNIT_ASSERT(UInt8Array::type_id==TypeID::UINT8);
	CPPUNIT_ASSERT(Int16Array::type_id==TypeID::INT16);
    CPPUNIT_ASSERT(UInt16Array::type_id==TypeID::UINT16);
	CPPUNIT_ASSERT(Int32Array::type_id==TypeID::INT32);
	CPPUNIT_ASSERT(UInt32Array::type_id==TypeID::UINT32);
	CPPUNIT_ASSERT(Int64Array::type_id==TypeID::INT64);
	CPPUNIT_ASSERT(UInt64Array::type_id==TypeID::UINT64);
	CPPUNIT_ASSERT(Float32Array::type_id==TypeID::FLOAT32);
	CPPUNIT_ASSERT(Float64Array::type_id==TypeID::FLOAT64);
	CPPUNIT_ASSERT(Float128Array::type_id==TypeID::FLOAT128);
	CPPUNIT_ASSERT(Complex32Array::type_id==TypeID::COMPLEX32);
	CPPUNIT_ASSERT(Complex64Array::type_id==TypeID::COMPLEX64);
	CPPUNIT_ASSERT(Complex128Array::type_id==TypeID::COMPLEX128);
}
