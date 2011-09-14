/*
 * BufferObjectTest.cpp
 *
 *  Created on: Sep 1, 2011
 *      Author: eugen
 */

#include "BufferObjectTest.hpp"
#include "Exceptions.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(BufferObjectTest);

using namespace pni::utils;

void BufferObjectTest::setUp(){
	n1 = 100000;
	n2 = 200000;
	e1 = 1;
	e2 = 3;


}

void BufferObjectTest::tearDown(){

}

void BufferObjectTest::testConstruction(){
	BufferObject b1;  //default constructor

	CPPUNIT_ASSERT(b1.getSize() == 0);
	CPPUNIT_ASSERT(b1.getElementSize() == 0);
	CPPUNIT_ASSERT(b1.getMemSize() == 0);

	BufferObject b2(n1,e1);
	CPPUNIT_ASSERT(b2.getSize() == n1);
	CPPUNIT_ASSERT(b2.getElementSize() == e1);
	CPPUNIT_ASSERT(b2.getMemSize() == n1*e1);

	BufferObject b3(b2);
	CPPUNIT_ASSERT(b3.getSize() == b2.getSize());
	CPPUNIT_ASSERT(b3.getElementSize() == b2.getElementSize());
	CPPUNIT_ASSERT(b3.getMemSize() == b2.getMemSize());
}

void BufferObjectTest::testAccess(){
	BufferObject buffer;

	CPPUNIT_ASSERT(buffer.getVoidPtr() == NULL);

	const BufferObject &bref = buffer;
	CPPUNIT_ASSERT(buffer.getVoidPtr() == NULL);

}

void BufferObjectTest::testParameters(){
	BufferObject b1;

	//setup base class
	b1.setElementSize(e1);
	CPPUNIT_ASSERT(b1.getElementSize() == e1);
	CPPUNIT_ASSERT(b1.getMemSize() == 0);
	b1.setSize(n1);
	CPPUNIT_ASSERT(b1.getSize() == n1);
	CPPUNIT_ASSERT(b1.getMemSize() == n1*e1);

	//change order of setup
	BufferObject b2;
	b2.setSize(n1);
	CPPUNIT_ASSERT(b2.getSize() == n1);
	CPPUNIT_ASSERT(b2.getMemSize() == 0);
	b2.setElementSize(e1);
	CPPUNIT_ASSERT(b2.getElementSize() == e1);
	CPPUNIT_ASSERT(b2.getMemSize() == n1*e1);



}



