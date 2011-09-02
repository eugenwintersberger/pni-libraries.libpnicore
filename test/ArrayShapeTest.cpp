//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "PNITypes.hpp"
#include "ArrayShape.hpp"
#include "ArrayShapeTest.hpp"
#include "Index.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayShapeTest);

void ArrayShapeTest::setUp(){
	_r1 = 2;
	_r2 = 3;

	_s1 = new unsigned int[_r1];
	_s2 = new unsigned int[_r2];

	_s1[0] = 3; _s1[1] = 4;
	_s2[0] = 2; _s2[1] = 3; _s2[2] = 5;
}

void ArrayShapeTest::tearDown(){
	if (_s1!=NULL) delete [] _s1;
	if (_s2!=NULL) delete [] _s2;
}

void ArrayShapeTest::testConstruction(){
	ArrayShape s;
	UInt32 i;
	const UInt32 *shape;

	//manual construction
	s.setRank(_r1);
	s.setDimensions(_s1);

	//check here if all parameters are set correctly
	CPPUNIT_ASSERT(_r1==s.getRank());
	shape = s.getDimensions();
	for(i=0;i<_r1;i++){
		CPPUNIT_ASSERT(_s1[i]==shape[i]);
		CPPUNIT_ASSERT(s[i]==_s1[i]);
	}

	//now we change rank and shape of the object
	s.setRank(_r2);
	s.setDimensions(_s2);

	//check here if all parameters are set correctly
	CPPUNIT_ASSERT(_r2==s.getRank());
	shape = s.getDimensions();
	for (i = 0; i < _r2; i++) {
		CPPUNIT_ASSERT(_s2[i]==shape[i]);
		CPPUNIT_ASSERT(s[i]==_s2[i]);
	}

	//construction using directly the constructor
	ArrayShape s1(_r1,_s1);
	//check here if all parameters are set correctly
	CPPUNIT_ASSERT(_r1==s1.getRank());
	shape = s1.getDimensions();
	for (i = 0; i < _r1; i++) {
		CPPUNIT_ASSERT(_s1[i]==shape[i]);
		CPPUNIT_ASSERT(s1[i]==_s1[i]);
	}

	//copy constructor
	ArrayShape s2(s);
	CPPUNIT_ASSERT(s==s2);

	//assignment operator
	s1 = s;
	CPPUNIT_ASSERT(s1==s);

}

void ArrayShapeTest::testComparison(){
	ArrayShape s1(_r1,_s1);
	ArrayShape s2(_r2,_s2);
	ArrayShape s3(s2);

	CPPUNIT_ASSERT(s1 == s1);
	CPPUNIT_ASSERT(s2 == s3);
	CPPUNIT_ASSERT(s1 != s2);
}

void ArrayShapeTest::testOffset(){
	ArrayShape s1(_r1,_s1);
	ArrayShape s2(_r2,_s2);
	Index index;
	UInt32 *i1,*i2;

	i1 = new UInt32 [_r1];
	i1[0] = 2; i1[1] = 1;

	i2 = new UInt32 [_r2];
	i2[0] = 0; i2[1] = 1; i2[2] = 3;

	CPPUNIT_ASSERT(s1.getOffset(i1)==9);
	CPPUNIT_ASSERT(s2.getOffset(i2)==8);

	index.setRank(s1.getRank());
	index[0] = 2;
	index[1] = 1;
	CPPUNIT_ASSERT(s1.getOffset(index)==9);

	index.setRank(s2.getRank());
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	CPPUNIT_ASSERT(s2.getOffset(index)==8);

}
