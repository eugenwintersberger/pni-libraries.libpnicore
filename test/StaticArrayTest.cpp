//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "Buffer.hpp"
#include "Shape.hpp"
#include "ArrayTest.hpp"
#include "ArrayView.hpp"
#include "Slice.hpp"

using namespace pni::utils;

#define STATICARRAY_TEST_REGISTRATION(T)\
static CPPUNIT_NS::AutoRegisterSuite< StaticArrayTest<T> >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ );

STATICARRAY_TEST_REGISTRATION(UInt8);
STATICARRAY_TEST_REGISTRATION(Int8);
STATICARRAY_TEST_REGISTRATION(UInt16);
STATICARRAY_TEST_REGISTRATION(Int16);
STATICARRAY_TEST_REGISTRATION(UInt32);
STATICARRAY_TEST_REGISTRATION(Int32);
STATICARRAY_TEST_REGISTRATION(UInt64);
STATICARRAY_TEST_REGISTRATION(Int64);

STATICARRAY_TEST_REGISTRATION(Float32);
STATICARRAY_TEST_REGISTRATION(Float64);
STATICARRAY_TEST_REGISTRATION(Float128);

STATICARRAY_TEST_REGISTRATION(Complex32);
STATICARRAY_TEST_REGISTRATION(Complex64);
STATICARRAY_TEST_REGISTRATION(Complex128);

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



