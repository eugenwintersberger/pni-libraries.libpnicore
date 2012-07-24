//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "NumArrayTest.hpp"

using namespace pni::utils;

#define NUMARRAY_TEST_REGISTRATION(ATYPE,VTYPE)\
static CPPUNIT_NS::AutoRegisterSuite< NumArrayTest<ATYPE<VTYPE> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ );

NUMARRAY_TEST_REGISTRATION(DArray,UInt8);
NUMARRAY_TEST_REGISTRATION(DArray,Int8);
NUMARRAY_TEST_REGISTRATION(DArray,UInt16);
NUMARRAY_TEST_REGISTRATION(DArray,Int16);
NUMARRAY_TEST_REGISTRATION(DArray,UInt32);
NUMARRAY_TEST_REGISTRATION(DArray,Int32);
NUMARRAY_TEST_REGISTRATION(DArray,UInt64);
NUMARRAY_TEST_REGISTRATION(DArray,Int64);
NUMARRAY_TEST_REGISTRATION(DArray,Float32);
NUMARRAY_TEST_REGISTRATION(DArray,Float64);
NUMARRAY_TEST_REGISTRATION(DArray,Float128);
NUMARRAY_TEST_REGISTRATION(DArray,Complex32);
NUMARRAY_TEST_REGISTRATION(DArray,Complex64);
NUMARRAY_TEST_REGISTRATION(DArray,Complex128);
/*
ARRAY_TEST_REGISTRATION(UInt8,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int8,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(UInt16,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int16,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(UInt32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(UInt64,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Int64,RefBuffer,NewAllocator);

ARRAY_TEST_REGISTRATION(Float32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Float64,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Float128,RefBuffer,NewAllocator);

ARRAY_TEST_REGISTRATION(Complex32,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Complex64,RefBuffer,NewAllocator);
ARRAY_TEST_REGISTRATION(Complex128,RefBuffer,NewAllocator);
*/



