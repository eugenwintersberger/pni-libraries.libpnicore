#include<cppunit/extensions/HelperMacros.h>

#include "TypeInfoTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeInfoTest);

//-----------------------------------------------------------------------------
void TypeInfoTest::test_min_max()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //--------------testing integer types----------------------
    CPPUNIT_ASSERT(TypeInfo<UInt8>::min() == 0 );
    CPPUNIT_ASSERT(TypeInfo<UInt8>::max() == UCHAR_MAX);

    CPPUNIT_ASSERT(TypeInfo<Int8>::min() == SCHAR_MIN);
    CPPUNIT_ASSERT(TypeInfo<Int8>::max() == SCHAR_MAX);

    CPPUNIT_ASSERT(TypeInfo<UInt16>::min() == 0);
    CPPUNIT_ASSERT(TypeInfo<UInt16>::max() == USHRT_MAX);

    CPPUNIT_ASSERT(TypeInfo<Int16>::min() == SHRT_MIN);
    CPPUNIT_ASSERT(TypeInfo<Int16>::max() == SHRT_MAX);

    CPPUNIT_ASSERT(TypeInfo<UInt32>::min() == 0);
    CPPUNIT_ASSERT(TypeInfo<UInt32>::max() == UINT_MAX);

    CPPUNIT_ASSERT(TypeInfo<Int32>::min() == INT_MIN);
    CPPUNIT_ASSERT(TypeInfo<Int32>::max() == INT_MAX);

    CPPUNIT_ASSERT(TypeInfo<UInt64>::min() == 0);
    CPPUNIT_ASSERT(TypeInfo<UInt64>::max() == ULONG_MAX);

    CPPUNIT_ASSERT(TypeInfo<Int64>::min() == LONG_MIN);
    CPPUNIT_ASSERT(TypeInfo<Int64>::max() == LONG_MAX);

    //---------------------testing floating point type----------
    CPPUNIT_ASSERT(TypeInfo<Float32>::min() == -FLT_MAX);
    CPPUNIT_ASSERT(TypeInfo<Float32>::max() == +FLT_MAX);

    CPPUNIT_ASSERT(TypeInfo<Float64>::min() == -DBL_MAX);
    CPPUNIT_ASSERT(TypeInfo<Float64>::max() == +DBL_MAX);

    CPPUNIT_ASSERT(TypeInfo<Float128>::min() == -LDBL_MAX);
    CPPUNIT_ASSERT(TypeInfo<Float128>::max() == +LDBL_MAX);

    //------------------testing floating point numbers----------
    CPPUNIT_ASSERT(TypeInfo<Complex32>::min() == -FLT_MAX);
    CPPUNIT_ASSERT(TypeInfo<Complex32>::max() == +FLT_MAX);

    CPPUNIT_ASSERT(TypeInfo<Complex64>::min() == -DBL_MAX);
    CPPUNIT_ASSERT(TypeInfo<Complex64>::max() == +DBL_MAX);

    CPPUNIT_ASSERT(TypeInfo<Complex128>::min() == -LDBL_MAX);
    CPPUNIT_ASSERT(TypeInfo<Complex128>::max() == +LDBL_MAX);

    //------------------special types---------------------------
    CPPUNIT_ASSERT(TypeInfo<Bool>::min() == false);
    CPPUNIT_ASSERT(TypeInfo<Bool>::max() == true);

}

