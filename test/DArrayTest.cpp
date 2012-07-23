//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "DArrayTest.hpp"

using namespace pni::utils;

#define DYNAMICARRAY_TEST_REGISTRATION(T,BT,ALLOC)\
static CPPUNIT_NS::AutoRegisterSuite< DArrayTest<T,BT<T,ALLOC> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ );

DYNAMICARRAY_TEST_REGISTRATION(UInt8,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(UInt16,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Int16,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(UInt32,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Int32,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(UInt64,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Int64,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Float32,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Float64,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Float128,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Complex32,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Complex64,DBuffer,NewAllocator);
DYNAMICARRAY_TEST_REGISTRATION(Complex128,DBuffer,NewAllocator);
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



