//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>

#include "array.hpp"
#include "arrayshape.hpp"
#include "libpniutils_array.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayTest);

void ArrayTest::setUp(){
	_r1 = 2;
	_r2 = 3;

	_s1 = new unsigned int[_r1];
	_s2 = new unsigned int[_r2];

	_s1[0] = 3; _s1[1] = 4;
	_s2[0] = 2; _s2[1] = 3; _s2[2] = 5;

	_sh1 = ArrayShape(_r1,_s1);
	_sh2 = ArrayShape(_r2,_s2);
}

void ArrayTest::tearDown(){
	if(_s1!=NULL) delete [] _s1;
	if(_s2!=NULL) delete [] _s2;
}

void ArrayTest::testConstructors(){
	Array<double> a1(_sh1);
	Array<double> a2(_r2,_s2);

}

void ArrayTest::testSetAndGet(){
	Array<double> a1(_r1,_s1);
	unsigned int i,j;

	//access via [] operator
	for(i=0;i<a1.getShape().getSize();i++) a1[i] = (double)i;

	//check if data values have been transfered correctly
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(((double)i)==a1[i]);

	//check access via () operator
	for(i=0;i<a1.getShape()[0];i++){
		for(j=0;j<a1.getShape()[1];j++){
			a1(i,j) = (double)i;
		}
	}
	for(i=0;i<a1.getShape()[0];i++){
		for(j=0;j<a1.getShape()[1];j++){
			CPPUNIT_ASSERT(a1(i,j) == ((double)i));
		}
	}

}

void ArrayTest::testComparison(){
	Array<double> a1(_sh1);
	Array<double> b1(_sh1);
	Array<double> a2(_sh2);
	Array<double> b2(_sh2);
	unsigned int i,j,k;

	for(i=0;i<a1.getShape()[0];i++){
		for(j=0;j<a1.getShape()[1];j++){
			a1(i,j) = (double)i;
			b1(i,j) = (double)i*10;
		}
	}
	CPPUNIT_ASSERT(a1==a1);
	CPPUNIT_ASSERT(a1!=b1);
	CPPUNIT_ASSERT(b1==b1);

	for(i=0;i<a2.getShape()[0];i++){
		for(j=0;j<a2.getShape()[1];j++){
			for(k=0;k<a2.getShape()[2];k++){
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
	Array<double> a1(_sh1);
	Array<double> b1(_sh1);
	Array<double> c1(_sh1);
	double b,a;
	unsigned long i;

	b = 5.;
	a = 10;

	//check setting all array values to the same value
	a1 = b;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==b);

	//checking addition
	a1 = a;
	b1 = b;
	c1 = a1+b1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a+b));
	c1 = a1+b;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a+b));
	c1 = b+a1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a+b));

	//checking subtraction
	c1 = a1-b1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a-b));
	c1 = a1-b;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a-b));
	c1 = b-a1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(b-a));

	//checking multiplication
	c1 = a1*b1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a*b));
	c1 = a1*b;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a*b));
	c1 = b*a1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(b*a));

	//checking division
	c1 = a1/b1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a/b));
	c1 = a1/b;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(a/b));
	c1 = b/a1;
	for(i=0;i<c1.getShape().getSize();i++) CPPUNIT_ASSERT(c1[i]==(b/a));



}

void ArrayTest::testUnaryOperations(){
	Array<double> a1(_sh1);
	Array<double> b1(_sh1);
	double b,a;
	unsigned long i;

	b = 5.;
	a = 10;

	//check setting all array values to the same value
	a1 = b;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==b);

	//checking addition
	a1 = a;
	b1 = b;
	a1 += b1;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a+b));
	a1 = a;
	a1 += b;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a+b));

	//checking subtraction
	a1 = a;
	a1 -= b1;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a-b));
	a1 = a;
	a1 -= b;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a-b));

	//checking multiplication
	a1 = a;
	a1 *= b1;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a*b));
	a1 = a;
	a1 *= b;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a*b));

	//checking division
	a1 = a;
	a1 /= b1;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a/b));
	a1 = a;
	a1 /= b;
	for(i=0;i<a1.getShape().getSize();i++) CPPUNIT_ASSERT(a1[i]==(a/b));

}
