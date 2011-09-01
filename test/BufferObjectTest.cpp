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

	buffer1.setElementSize(e1);
	buffer1.setSize(n1);
	buffer1.allocate();

	buffer2.setElementSize(e2);
	buffer2.setSize(n2);
	buffer2.allocate();
}

void BufferObjectTest::tearDown(){
	buffer1.free();
	buffer2.free();
}

void BufferObjectTest::testAccess(){
	BufferObject buffer;
	UInt8 *ptr;

	CPPUNIT_ASSERT_NO_THROW(buffer.setSize(n1));
	CPPUNIT_ASSERT_NO_THROW(buffer.setElementSize(e1));
	CPPUNIT_ASSERT_NO_THROW(buffer.allocate());

	ptr = (UInt8 *)buffer.getVoidPtr();
	for(UInt64 i=0;i<n1;i++){
		*(ptr + i*e1) = 100;
	}

	for(UInt64 i=0;i<n1;i++){
		CPPUNIT_ASSERT(*(ptr+i*e1)==100);
		CPPUNIT_ASSERT(*(ptr+i*e1)!= 1);
	}

	CPPUNIT_ASSERT(buffer.getMemSize()==n1*e1);

}

void BufferObjectTest::testComparison(){
	BufferObject a,b;

	a.setSize(100);
	a.setElementSize(1);
	a.allocate();

	b.setSize(200);
	b.setElementSize(2);
	b.allocate();

	CPPUNIT_ASSERT(a!=b);

}

void BufferObjectTest::testReallocation(){
	BufferObject buffer;

	CPPUNIT_ASSERT_NO_THROW(buffer.setSize(n1));
	CPPUNIT_ASSERT_NO_THROW(buffer.setElementSize(e1));
	CPPUNIT_ASSERT_NO_THROW(buffer.allocate());

	CPPUNIT_ASSERT(buffer.getMemSize()==n1*e1);
	CPPUNIT_ASSERT_NO_THROW(buffer.free());

	CPPUNIT_ASSERT_NO_THROW(buffer.setSize(n2));
	CPPUNIT_ASSERT_NO_THROW(buffer.setElementSize(e2));
	CPPUNIT_ASSERT_NO_THROW(buffer.allocate());

	CPPUNIT_ASSERT(buffer.getMemSize()==n2*e2);
	CPPUNIT_ASSERT_NO_THROW(buffer.free());
}

void BufferObjectTest::testAllocation(){
	BufferObject buffer;

	CPPUNIT_ASSERT_NO_THROW(buffer.setSize(n1));
	CPPUNIT_ASSERT_NO_THROW(buffer.setElementSize(e1));
	CPPUNIT_ASSERT_NO_THROW(buffer.allocate());
	CPPUNIT_ASSERT_NO_THROW(buffer.free());
}

void BufferObjectTest::testAssignment(){

}

void BufferObjectTest::testCopyConstructor(){

}


