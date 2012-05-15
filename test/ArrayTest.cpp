//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "Buffer.hpp"
#include "Shape.hpp"
#include "ArrayTest.hpp"
#include "ArrayView.hpp"
#include "Slice.hpp"

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

	CPPUNIT_ASSERT_NO_THROW(a(100,100) = 1000);
	CPPUNIT_ASSERT_NO_THROW(a(50,23) = -10);
 	CPPUNIT_ASSERT_NO_THROW(a(1023,2047) = 50);

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

	//check access via () operator
	for(size_t i=0;i<s[0];i++){
		for(size_t j=0;j<s[1];j++){
			a1(i,j) = (double)i*j;
		}
	}

	for(size_t i=0;i<s[0];i++){
		for(size_t j=0;j<s[1];j++){
			CPPUNIT_ASSERT_DOUBLES_EQUAL(a1(i,j),((double)i*j),1.e-8);
		}
	}

}

//------------------------------------------------------------------------------
void ArrayTest::testComparison(){
	Float64Array a1(s1);
	Float64Array b1(s1);
	Float64Array a2(s2);
	Float64Array b2(s2);

	for(size_t i=0;i<s1[0];i++)
    {
		for(size_t j=0;j<s1[1];j++)
        {
			a1(i,j) = (Float64)i;
			b1(i,j) = (Float64)j*10;
		}
	}
	CPPUNIT_ASSERT(a1==a1);
	CPPUNIT_ASSERT(a1!=b1);
	CPPUNIT_ASSERT(b1==b1);


	for(size_t i=0;i<s2[0];i++)
    {
		for(size_t j=0;j<s2[1];j++)
        {
			for(size_t k=0;k<s2[2];k++)
            {
				a2(i,j,k) = (Float64)i;
				b2(i,j,k) = (Float64)i*10;
			}
		}
	}
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
