/*
 * IndexTest.cpp
 *
 *  Created on: Sep 2, 2011
 *      Author: eugen
 */

#include<cppunit/extensions/HelperMacros.h>

#include "IndexTest.hpp"
#include "Exceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(IndexTest);

void IndexTest::setUp(){

}

void IndexTest::tearDown(){

}

void IndexTest::testInstantiation(){
	Index i1;

	CPPUNIT_ASSERT_NO_THROW(i1.setRank(3));
	i1[0] = 5; i1[1] = 6; i1[2] = 7;

	//using copy constructor
	Index i2(i1);
	CPPUNIT_ASSERT(i1 == i2);
}

void IndexTest::testComparison(){
	Index i1(3);
	Index i2(3);
	Index i3(4);

	CPPUNIT_ASSERT(i1 != i3);
	i1[0] = 1; i2[0] = 1;
	i1[1] = 2; i2[1] = 2;
	i1[2] = 3; i2[2] = 4;
	CPPUNIT_ASSERT(i1 != i2);
	i2[2] = 3;
	CPPUNIT_ASSERT(i1 == i2);
}

void IndexTest::testAccess(){
	//test here basically exceptions and [] operator
	Index i1(4);

	//checking operators
	CPPUNIT_ASSERT_NO_THROW(i1[3]=5);
	CPPUNIT_ASSERT_THROW(i1[10]=45,IndexError);

	CPPUNIT_ASSERT_NO_THROW(i1.setIndex(2,23));
	CPPUNIT_ASSERT_THROW(i1.setIndex(100,23),IndexError);

	CPPUNIT_ASSERT_NO_THROW(i1.getIndex(1));
	CPPUNIT_ASSERT_THROW(i1.getIndex(200),IndexError);

	CPPUNIT_ASSERT(i1.getIndex(2) == 23);
	CPPUNIT_ASSERT(i1[3] == 5);

}

void IndexTest::testIndexManipulation(){
	Index i1(3);

	CPPUNIT_ASSERT_NO_THROW(i1[0] = 1);
	CPPUNIT_ASSERT_NO_THROW(i1[1] = 2);
	CPPUNIT_ASSERT_NO_THROW(i1[2] = 5);

	CPPUNIT_ASSERT_NO_THROW(i1.decrement(0));
	CPPUNIT_ASSERT(i1[0] == 0);
	CPPUNIT_ASSERT_THROW(i1.decrement(0),RangeError);
	CPPUNIT_ASSERT_THROW(i1.decrement(100),IndexError);
	CPPUNIT_ASSERT_THROW(i1.decrement(-1),IndexError);

	CPPUNIT_ASSERT_NO_THROW(i1.increment(2));
	CPPUNIT_ASSERT(i1[2] == 6);
	CPPUNIT_ASSERT_THROW(i1.increment(100),IndexError);
	CPPUNIT_ASSERT_THROW(i1.increment(-5),IndexError);

}



