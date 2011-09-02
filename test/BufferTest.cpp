//implementation for the Buffer test

#include<cppunit/extensions/HelperMacros.h>

#include "BufferTest.hpp"
#include "Buffer.hpp"

//register the test at the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest);

void BufferTest::setUp(){
}

void BufferTest::tearDown(){


}

void BufferTest::testAllocation(){
	Buffer<Float64> dbuffer;
	UInt64 n;

	n = 100;
	CPPUNIT_ASSERT_NO_THROW(dbuffer.setSize(n));
	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate());
	CPPUNIT_ASSERT(dbuffer.getSize()==n);
	CPPUNIT_ASSERT(dbuffer.getMemSize()==(sizeof(Float64)*n));

	for(UInt64 i=0;i<n;i++) dbuffer[i] = (Float64)i;

	CPPUNIT_ASSERT_NO_THROW(dbuffer.free());
	n = 100000000;
	CPPUNIT_ASSERT_NO_THROW(dbuffer.setSize(n));
	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate());
	CPPUNIT_ASSERT(dbuffer.getSize()==n);
	CPPUNIT_ASSERT(dbuffer.getMemSize()==(sizeof(Float64)*n));

	for(UInt64 i=0;i<n;i++) dbuffer[i] = (Float64)i;

}

void BufferTest::testAccess(){
	Buffer<Float64> dbuffer(1000);

	for(UInt64 i=0;i<1000;i++) dbuffer[i] = (Float64)i;

	for(UInt64 i=0;i<1000;i++){
		CPPUNIT_ASSERT(((Float64)i)==dbuffer[i]);
	}
}

void BufferTest::testCopy(){
	Buffer<Float64> buffer1(1000);

	buffer1 = 100.234;
	Buffer<Float64> buffer2(buffer1);
	CPPUNIT_ASSERT(buffer1 == buffer2);
}

void BufferTest::testAssignment(){
	//testing here the assignment of equally typed buffers
	Buffer<Float64> buffer1(1000);
	Buffer<Float64> buffer2(2000);

	//assign a single number to the buffer
	buffer1 = 1.0;
	for(UInt64 i=0;i<buffer1.getSize();i++){
		CPPUNIT_ASSERT(buffer1[i] == 1.0);
	}

	CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);
	CPPUNIT_ASSERT(buffer2.getSize() == buffer1.getSize());
	CPPUNIT_ASSERT(buffer2 == buffer1);

}

void BufferTest::testComparison(){
	Buffer<Float64> b1(100);
	Buffer<Float64> b2(100);
	Buffer<UInt64> b3(100)
;
	b1 = 1.;
	b2 = 2.;

	CPPUNIT_ASSERT(b1 != b2);
	b2 = 1.;
	CPPUNIT_ASSERT(b1 == b2);

	// must fail because the buffers are of different type
	b3 = 1;
	CPPUNIT_ASSERT(b3 != b1);
}

void BufferTest::testConversion(){
	Buffer<Float64> buffer(100);
	buffer = -100.23;

	//cannot convert a float buffer to an integer
	Buffer<UInt64> uibuffer;
	CPPUNIT_ASSERT_THROW(buffer.convert(uibuffer),TypeError);

	//the other way around should work
	uibuffer.setSize(100);
	uibuffer.allocate();
	uibuffer = 10;
	CPPUNIT_ASSERT_NO_THROW(uibuffer.convert(buffer));
	for(UInt64 i=0; i<buffer.getSize();i++) CPPUNIT_ASSERT(buffer[i]==10);

	//we cannot convert a signed buffer to an unsigned buffer
	Buffer<Int64> ibuffer(200);
	ibuffer = -1;
	CPPUNIT_ASSERT_THROW(ibuffer.convert(uibuffer),RangeError);
	//but this should work again
	ibuffer = 100;
	CPPUNIT_ASSERT_NO_THROW(ibuffer.convert(uibuffer));


	//cannot convert a float buffer to a complex buffer
	Buffer<Complex32> cbuffer;
	CPPUNIT_ASSERT_NO_THROW(buffer.convert(cbuffer));



	Buffer<Float128> lfbuffer;
	CPPUNIT_ASSERT_NO_THROW(buffer.convert(lfbuffer));

	//in the end we try this
	lfbuffer.setSize(500);
	lfbuffer.allocate();
	lfbuffer = -100.23501;
	CPPUNIT_ASSERT_THROW(lfbuffer.convert(buffer),TypeError);



}
