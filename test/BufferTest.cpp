//implementation for the Buffer test

#include<cppunit/extensions/HelperMacros.h>

#include "BufferTest.hpp"
#include "Buffer.hpp"

//register the test at the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest);

//------------------------------------------------------------------------------
void BufferTest::setUp(){
	n1 = 1000;
	n2 = 2000;
}

//------------------------------------------------------------------------------
void BufferTest::tearDown(){


}

//------------------------------------------------------------------------------
void BufferTest::testConstructors(){
	//create first buffer using the default constructor
	Buffer<Float64> dbuffer; //default constructor
	CPPUNIT_ASSERT(!dbuffer.is_allocated());

	CPPUNIT_ASSERT_NO_THROW(dbuffer.allocate(n1));
	CPPUNIT_ASSERT(dbuffer.is_allocated());

	//create the second constructor with the standard constructor
	//allocating memory
	Buffer<Float64> dbuffer2(n2);
	CPPUNIT_ASSERT(dbuffer2.is_allocated());

	//using copy constructor
	Buffer<Float64> dbuffer3(dbuffer2);
	CPPUNIT_ASSERT(dbuffer3.is_allocated());
	CPPUNIT_ASSERT(dbuffer2.is_allocated());
	CPPUNIT_ASSERT(dbuffer3.size() == dbuffer2.size());

	//using the move constructor
	Buffer<Float64> dbuffer4 = std::move(dbuffer2);
	CPPUNIT_ASSERT(dbuffer4.is_allocated());
	CPPUNIT_ASSERT(dbuffer4.size() == dbuffer3.size());
	CPPUNIT_ASSERT(!dbuffer2.is_allocated());

    //test constructor with initializer list
    Buffer<Int32> ibuffer = {1,-6,12};
    CPPUNIT_ASSERT(ibuffer[0] == 1);
    CPPUNIT_ASSERT(ibuffer[1] == -6);
    CPPUNIT_ASSERT(ibuffer[2] == 12);

    //test constructor with vector
    std::vector<Int64> vec = {3,9,1};
    Buffer<Int64> vbuffer = vec;
    CPPUNIT_ASSERT(vbuffer.is_allocated());
    CPPUNIT_ASSERT(vbuffer.size() == 3);
    CPPUNIT_ASSERT(vbuffer[0] == 3);
    CPPUNIT_ASSERT(vbuffer[1] == 9);
    CPPUNIT_ASSERT(vbuffer[2] == 1);
}

//------------------------------------------------------------------------------
void BufferTest::testAssignment(){
	//testing here the assignment of equally typed buffers
	Buffer<Float64> buffer1;
	Buffer<Float64> buffer2;

	//check first for some standard problems
	//nothing happens - both are not allocated
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	//now the lhs is not allocated and the rhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2.allocate(n1));
    CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
    //now the rhs is not allocate dnad the lhs is
    CPPUNIT_ASSERT_NO_THROW(buffer1.free());
    CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);


    //booth buffers are allocated
	CPPUNIT_ASSERT_NO_THROW(buffer2.allocate(n1));
	CPPUNIT_ASSERT_NO_THROW(buffer1.allocate(n2));
	//reallocation of the lhs
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	CPPUNIT_ASSERT(buffer1.is_allocated());
	CPPUNIT_ASSERT(buffer2.is_allocated());

	Buffer<Float64> buffer3;
	CPPUNIT_ASSERT_NO_THROW(buffer3 = buffer1);
	CPPUNIT_ASSERT(buffer3.is_allocated());
	CPPUNIT_ASSERT(buffer1.is_allocated());

	//checking move assignment
	Buffer<Float64> buffer4;
	CPPUNIT_ASSERT_NO_THROW(buffer4 = std::move(buffer3));
	CPPUNIT_ASSERT(buffer4.is_allocated());
	CPPUNIT_ASSERT(!buffer3.is_allocated());
	CPPUNIT_ASSERT(buffer4.size() == buffer1.size());
}

//------------------------------------------------------------------------------
void BufferTest::testAllocation(){
	Buffer<Float64> dbuffer(n1);

	CPPUNIT_ASSERT(dbuffer.is_allocated());
	CPPUNIT_ASSERT(dbuffer.size() == n1);

	CPPUNIT_ASSERT_NO_THROW(dbuffer.free());
	CPPUNIT_ASSERT(dbuffer.size()==0);
	CPPUNIT_ASSERT(!dbuffer.is_allocated());

	Buffer<Float64> dbuffer2;
	CPPUNIT_ASSERT(dbuffer2.size() == 0);
	CPPUNIT_ASSERT(!dbuffer2.is_allocated());

	CPPUNIT_ASSERT_NO_THROW(dbuffer2.allocate(n2));
	CPPUNIT_ASSERT(dbuffer2.is_allocated());
	CPPUNIT_ASSERT(dbuffer2.size() == n2);

}

//------------------------------------------------------------------------------
void BufferTest::testAccess(){
	Buffer<Float64> dbuffer(1000);

	for(UInt64 i=0;i<1000;i++) dbuffer[i] = (Float64)i;

	for(UInt64 i=0;i<1000;i++){
		CPPUNIT_ASSERT(((Float64)i)==dbuffer[i]);
	}

    Buffer<Int32> ibuffer(4);
    CPPUNIT_ASSERT_NO_THROW(ibuffer.set({1,2,3,4}));
    CPPUNIT_ASSERT(ibuffer[0] = 1);
    CPPUNIT_ASSERT(ibuffer[1] = 2);
    CPPUNIT_ASSERT(ibuffer[2] = 3);
    CPPUNIT_ASSERT(ibuffer[3] = 4);

    CPPUNIT_ASSERT_THROW(ibuffer.set({1,2}),SizeMissmatchError);
    CPPUNIT_ASSERT_THROW(ibuffer.set({1,2,3,4,54,6,7}),SizeMissmatchError);

}

//------------------------------------------------------------------------------
void BufferTest::testComparison(){
	Buffer<Float64> b1(100);
	Buffer<Float64> b2(100);
	b1 = 1.;
	b2 = 2.;

	CPPUNIT_ASSERT(b1 != b2);
	b2 = 1.;
	CPPUNIT_ASSERT(b1 == b2);
}


