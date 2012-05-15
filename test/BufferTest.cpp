//implementation for the Buffer test

#include<cppunit/extensions/HelperMacros.h>

#include "BufferTest.hpp"

//register the test at the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest<UInt8,Buffer,NewAllocator>);
//CPPUNIT_TEST_SUITE_REGISTRATION(BufferTest<Int8,Buffer,NewAllocator>);






