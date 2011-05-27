//implementation for the Buffer test

#include<cppunit/extensions/HelperMacros.h>

#include "libpniutils_buffer.hpp"
#include "Buffer.hpp"

//register the test at the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest);

void BufferTest::setUp(){
}

void BufferTest::tearDown(){


}

void BufferTest::testAllocation(){
	pni::utils::Buffer<double> dbuffer;
	unsigned long n;

	n = 100;
	dbuffer.allocate(n);
	CPPUNIT_ASSERT(dbuffer.getSize()==n);
	CPPUNIT_ASSERT(dbuffer.getMemSize()==(sizeof(double)*n));

	for(unsigned long i=0;i<n;i++) dbuffer[i] = (double)i;

	n = 100000000;
	dbuffer.resize(n);
	CPPUNIT_ASSERT(dbuffer.getSize()==n);
	CPPUNIT_ASSERT(dbuffer.getMemSize()==(sizeof(double)*n));

	for(unsigned long i=0;i<n;i++) dbuffer[i] = (double)i;

}

void BufferTest::testAccess(){
	pni::utils::Buffer<double> dbuffer(1000);

	for(unsigned long i=0;i<1000;i++) dbuffer[i] = (double)i;

	for(unsigned long i=0;i<1000;i++){
		CPPUNIT_ASSERT(((double)i)==dbuffer[i]);
	}
}
