//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "Buffer.hpp"
#include "ArrayShape.hpp"
#include "libpniutils_array.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayTest);

void ArrayTest::setUp(){
	_r1 = 2;
	_r2 = 3;

	_s1 = new unsigned int[_r1];
	_s2 = new unsigned int[_r2];

	_s1[0] = 3; _s1[1] = 4;
	_s2[0] = 2; _s2[1] = 3; _s2[2] = 5;

	_sh1 = pni::utils::ArrayShape(_r1,_s1);
	_sh2 = pni::utils::ArrayShape(_r2,_s2);
}

void ArrayTest::tearDown(){
	if(_s1!=NULL) delete [] _s1;
	if(_s2!=NULL) delete [] _s2;
}

void ArrayTest::testConstructors(){
	//check for simple array-construction
	pni::utils::Array<double> a1(_sh1);
	pni::utils::Array<double> a2(_r2,_s2);

}

void ArrayTest::testSlowArrayConstruction(){
	pni::utils::ArrayShape s;
	pni::utils::Int32Array a;

	//construct the shape object
	s.setRank(2);
	s.setDimension(0,1024);
	s.setDimension(1,2048);

	a.setShape(s);
	pni::utils::Buffer<pni::utils::Int32> buffer;
	buffer.allocate(s.getSize());
	a.setBuffer(buffer);

	a(100,100) = 1000;
	a(50,23) = -10;
	a(1023,2047) = 50;

	CPPUNIT_ASSERT(a.Min() == -10);
	CPPUNIT_ASSERT(a.Max() == 1000);
}

void ArrayTest::testConstructorsShared(){
	pni::utils::ArrayShape::sptr shape(new pni::utils::ArrayShape(_r1,_s1));
	pni::utils::Buffer<double>::sptr buffer(new pni::utils::Buffer<double>(shape->getSize()));

	pni::utils::Array<double> *a = new pni::utils::Array<double>(shape,buffer);

	for(unsigned long i=0;i<shape->getSize();i++) CPPUNIT_ASSERT((*a)[i]==(*buffer)[i]);

	CPPUNIT_ASSERT(shape.use_count()==2);
	CPPUNIT_ASSERT(buffer.use_count()==2);

	delete a;

	CPPUNIT_ASSERT(shape.use_count()==1);
	CPPUNIT_ASSERT(buffer.use_count()==1);

	a = new pni::utils::Array<double>(_r2,_s2);
	shape = a->getShape();
    buffer = boost::dynamic_pointer_cast<pni::utils::Buffer<double> >(a->getBuffer());

	CPPUNIT_ASSERT(shape.use_count()==2);
	CPPUNIT_ASSERT(buffer.use_count()==2);

	CPPUNIT_ASSERT(*shape==_sh2);

}

void ArrayTest::testSetAndGet(){
	pni::utils::Array<double> a1(_r1,_s1);
	unsigned int i,j;

	//access via [] operator
	pni::utils::ArrayShape s = *(a1.getShape());
	for(i=0;i<s.getSize();i++) a1[i] = (double)i;

	//check if data values have been transfered correctly
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(((double)i)==a1[i]);

	//check access via () operator
	for(i=0;i<s[0];i++){
		for(j=0;j<s[1];j++){
			a1(i,j) = (double)i;
		}
	}
	for(i=0;i<s[0];i++){
		for(j=0;j<s[1];j++){
			CPPUNIT_ASSERT(a1(i,j) == ((double)i));
		}
	}

}

void ArrayTest::testComparison(){
	pni::utils::Array<double> a1(_sh1);
	pni::utils::Array<double> b1(_sh1);
	pni::utils::Array<double> a2(_sh2);
	pni::utils::Array<double> b2(_sh2);
	unsigned int i,j,k;

	pni::utils::ArrayShape s = *(a1.getShape());
	for(i=0;i<s[0];i++){
		for(j=0;j<s[1];j++){
			a1(i,j) = (double)i;
			b1(i,j) = (double)i*10;
		}
	}
	CPPUNIT_ASSERT(a1==a1);
	CPPUNIT_ASSERT(a1!=b1);
	CPPUNIT_ASSERT(b1==b1);

	s = *(a2.getShape());
	for(i=0;i<s[0];i++){
		for(j=0;j<s[1];j++){
			for(k=0;k<s[2];k++){
				a2(i,j,k) = (double)i;
				b2(i,j,k) = (double)i*10;
			}
		}
	}
	CPPUNIT_ASSERT(a2==a2);
	CPPUNIT_ASSERT(a2!=b2);
	CPPUNIT_ASSERT(b2==b2);

}

void ArrayTest::testBinaryOperations(){
	pni::utils::Array<double> a1(_sh1);
	pni::utils::Array<double> b1(_sh1);
	pni::utils::Array<double> c1(_sh1);
	double b,a;
	unsigned long i;

	b = 5.;
	a = 10;

	//check setting all array values to the same value
	a1 = b;
	pni::utils::ArrayShape s = *(a1.getShape());
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==b);

	//checking addition
	a1 = a;
	b1 = b;
	c1 = a1+b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a+b));
	c1 = a1+b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a+b));
	c1 = b+a1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a+b));

	//checking subtraction
	c1 = a1-b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a-b));
	c1 = a1-b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a-b));
	c1 = b-a1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(b-a));

	//checking multiplication
	c1 = a1*b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a*b));
	c1 = a1*b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a*b));
	c1 = b*a1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(b*a));

	//checking division
	c1 = a1/b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a/b));
	c1 = a1/b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(a/b));
	c1 = b/a1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(c1[i]==(b/a));



}

void ArrayTest::testUnaryOperations(){
	pni::utils::Array<double> a1(_sh1);
	pni::utils::Array<double> b1(_sh1);
	double b,a;
	unsigned long i;

	b = 5.;
	a = 10;

	//check setting all array values to the same value
	a1 = b;
	pni::utils::ArrayShape s = *(a1.getShape());
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==b);

	//checking addition
	a1 = a;
	b1 = b;
	a1 += b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a+b));
	a1 = a;
	a1 += b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a+b));

	//checking subtraction
	a1 = a;
	a1 -= b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a-b));
	a1 = a;
	a1 -= b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a-b));

	//checking multiplication
	a1 = a;
	a1 *= b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a*b));
	a1 = a;
	a1 *= b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a*b));

	//checking division
	a1 = a;
	a1 /= b1;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a/b));
	a1 = a;
	a1 /= b;
	for(i=0;i<s.getSize();i++) CPPUNIT_ASSERT(a1[i]==(a/b));

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
