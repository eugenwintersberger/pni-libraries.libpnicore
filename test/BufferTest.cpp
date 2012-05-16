//implementation for the Buffer test

#include "BufferTest.hpp"

//register the test at the test suite
//CPPUNIT_TEST_SUITE_REGISTRATION(  );
//CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest<Int8,Buffer,NewAllocator>);

#define BUFFER_TEST_REGISTRATION(BTYPE,VTYPE,ALLOC)\
static CPPUNIT_NS::AutoRegisterSuite< BufferTest<BTYPE<VTYPE,ALLOC> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ );

BUFFER_TEST_REGISTRATION(Buffer,Int8,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,UInt8,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Int16,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,UInt16,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Int32,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,UInt32,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Int64,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,UInt64,NewAllocator);

BUFFER_TEST_REGISTRATION(Buffer,Float32,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Float64,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Float128,NewAllocator);

BUFFER_TEST_REGISTRATION(Buffer,Complex32,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Complex64,NewAllocator);
BUFFER_TEST_REGISTRATION(Buffer,Complex128,NewAllocator);

BUFFER_TEST_REGISTRATION(Buffer,Binary,NewAllocator);

BUFFER_TEST_REGISTRATION(RefBuffer,Int8,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,UInt8,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Int16,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,UInt16,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Int32,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,UInt32,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Int64,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,UInt64,NewAllocator);

BUFFER_TEST_REGISTRATION(RefBuffer,Float32,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Float64,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Float128,NewAllocator);

BUFFER_TEST_REGISTRATION(RefBuffer,Complex32,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Complex64,NewAllocator);
BUFFER_TEST_REGISTRATION(RefBuffer,Complex128,NewAllocator);

BUFFER_TEST_REGISTRATION(RefBuffer,Binary,NewAllocator);
