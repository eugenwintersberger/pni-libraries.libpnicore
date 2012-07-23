//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "NumArrayTest.hpp"

using namespace pni::utils;

#define NUMARRAY_TEST_REGISTRATION(ATYPE,VTYPE)\
static CPPUNIT_NS::AutoRegisterSuite< NumArrayTest<ATYPE<VTYPE> >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ );

NUMARRAY_TEST_REGISTRATION(DArray,UInt8);
NUMARRAY_TEST_REGISTRATION(DArray,Int8);
/*
NUMARRAY_TEST_REGISTRATION(UInt16,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Int16,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(UInt32,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Int32,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(UInt64,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Int64,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Float32,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Float64,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Float128,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Complex32,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Complex64,Buffer,NewAllocator);
NUMARRAY_TEST_REGISTRATION(Complex128,Buffer,NewAllocator);
*/
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



