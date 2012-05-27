//implementation for the Buffer test

#include "BufferTest.hpp"

//register the test at the test suite
//CPPUNIT_TEST_SUITE_REGISTRATION(  );
//CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest<Int8,Buffer,NewAllocator>);

#define BUFFER_TEST_REGISTRATION(VTYPE,ALLOC)\
static CPPUNIT_NS::AutoRegisterSuite< BufferTest<VTYPE,ALLOC> >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ );

BUFFER_TEST_REGISTRATION(Int8,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt8,NewAllocator);
BUFFER_TEST_REGISTRATION(Int16,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt16,NewAllocator);
BUFFER_TEST_REGISTRATION(Int32,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt32,NewAllocator);
BUFFER_TEST_REGISTRATION(Int64,NewAllocator);
BUFFER_TEST_REGISTRATION(UInt64,NewAllocator);

BUFFER_TEST_REGISTRATION(Float32,NewAllocator);
BUFFER_TEST_REGISTRATION(Float64,NewAllocator);
BUFFER_TEST_REGISTRATION(Float128,NewAllocator);

BUFFER_TEST_REGISTRATION(Complex32,NewAllocator);
BUFFER_TEST_REGISTRATION(Complex64,NewAllocator);
BUFFER_TEST_REGISTRATION(Complex128,NewAllocator);

BUFFER_TEST_REGISTRATION(Binary,NewAllocator);

