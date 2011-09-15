//implementation for the Buffer test

#include<cppunit/extensions/HelperMacros.h>

#include "BufferTest.hpp"
#include "Buffer.hpp"

//register the test at the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest);

void BufferTest::setUp(){
	n1 = 1000;
	n2 = 2000;
}

void BufferTest::tearDown(){


}

void BufferTest::testConstructors(){
	//create first buffer using the default constructor
	Buffer<Float64> dbuffer; //default constructor
	CPPUNIT_ASSERT(!dbuffer.isAllocated());

	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate(n1));
	CPPUNIT_ASSERT(dbuffer.isAllocated());

	//create the second constructor with the standard constructor
	//allocating memory
	Buffer<Float64> dbuffer2(n2);
	CPPUNIT_ASSERT(dbuffer2.isAllocated());

	//using copy constructor
	Buffer<Float64> dbuffer3(dbuffer2);
	CPPUNIT_ASSERT(dbuffer3.isAllocated());
	CPPUNIT_ASSERT(dbuffer3.getSize() == dbuffer2.getSize());

	//using copy constructor with a not allocated buffer
	Buffer<Float64> dbuffer4;
	dbuffer4.setSize(n1);
	CPPUNIT_ASSERT(!dbuffer4.isAllocated());

	Buffer<Float64> dbuffer5(dbuffer4);
	CPPUNIT_ASSERT(dbuffer5.getSize() == dbuffer4.getSize());
	CPPUNIT_ASSERT(!dbuffer5.isAllocated());

	dbuffer4.allocate();
	dbuffer4 = 1.3091;
	Buffer<Float64> dbuffer6(dbuffer4);
	CPPUNIT_ASSERT(dbuffer6 == dbuffer4);


}

void BufferTest::testAllocation(){
	Buffer<Float64> dbuffer;

	CPPUNIT_ASSERT_THROW(dbuffer.allocate(),MemoryAllocationError);

	CPPUNIT_ASSERT_NO_THROW(dbuffer.setSize(n1));
	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate());
	//subsequent call to allocate causes exception
	CPPUNIT_ASSERT_THROW(dbuffer.allocate(),MemoryAllocationError);

	dbuffer.free();
	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate());

	dbuffer.free();
	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate(n1));
	CPPUNIT_ASSERT_THROW(dbuffer.allocate(n1),MemoryAllocationError);
	//CPPUNIT_ASSERT_THROW(dbuffer.setSize(1000),MemoryAllocationError);

	dbuffer.free();
	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate(n2));
	CPPUNIT_ASSERT(dbuffer.getSize() == n2);
	CPPUNIT_ASSERT_THROW(dbuffer.allocate(),MemoryAllocationError);
}

void BufferTest::testAccess(){
	Buffer<Float64> dbuffer(1000);

	for(UInt64 i=0;i<1000;i++) dbuffer[i] = (Float64)i;

	for(UInt64 i=0;i<1000;i++){
		CPPUNIT_ASSERT(((Float64)i)==dbuffer[i]);
	}
}


void BufferTest::testAssignment(){
	//testing here the assignment of equally typed buffers
	Buffer<Float64> buffer1;
	Buffer<Float64> buffer2;
	Buffer<UInt32> buffer3;
	Buffer<Int64> buffer4;

	//check first for some standard problems
	//nothing happens - both are not allocated
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	//now the lhs is not allocated
	buffer2.allocate(n1);
	buffer1.setSize(n2);
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	buffer1.allocate();
	CPPUNIT_ASSERT_THROW(buffer1 = buffer2,SizeMissmatchError);
	buffer1.free();
	buffer1.allocate(n1);
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);

	//allocate now all other bufers
	buffer3.allocate(n1);
	buffer4.allocate(n1);

	//assign a single number to the buffer
	CPPUNIT_ASSERT_NO_THROW(buffer1 = 1.0);
	for(UInt64 i=0;i<buffer1.getSize();i++){
		CPPUNIT_ASSERT(buffer1[i] == 1.0);
	}

	//assign a single number of different type
	CPPUNIT_ASSERT_NO_THROW(buffer1 = 1);
	for(UInt64 i=0;i<buffer1.getSize();i++) CPPUNIT_ASSERT(buffer1[i] == 1);
	CPPUNIT_ASSERT_THROW(buffer3 = -5,RangeError);

	//starting with integer buffers
	CPPUNIT_ASSERT_THROW(buffer3 = buffer1,TypeError); //cannot assign double to integer

	buffer4 = 100;
	buffer4[100] = -1;
	CPPUNIT_ASSERT_THROW(buffer3 = buffer4,RangeError);


	Buffer<Complex32> buffer5(n1);
	Buffer<Complex128> buffer6(n1);

	buffer5 = Complex32(1,-2093);
	//will not work - gives already compile time error
	//CPPUNIT_ASSERT_THROW(buffer2 = buffer5,TypeError);
	//CPPUNIT_ASSERT_THROW(buffer3 = buffer5,TypeError);
	CPPUNIT_ASSERT_NO_THROW(buffer5 = buffer4);
	CPPUNIT_ASSERT_NO_THROW(buffer6 = buffer1);
	buffer1 = 1.e+300;
	CPPUNIT_ASSERT_THROW(buffer5 = buffer1,RangeError);

}

void BufferTest::testComparison(){
	Buffer<Float64> b1(100);
	Buffer<Float64> b2(100);
	Buffer<UInt64> b3(100);
	b1 = 1.;
	b2 = 2.;

	CPPUNIT_ASSERT(b1 != b2);
	b2 = 1.;
	CPPUNIT_ASSERT(b1 == b2);

	// should work
	b3 = 1;
	CPPUNIT_ASSERT(b3 == b1);
}


