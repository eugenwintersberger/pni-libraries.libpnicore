#include<cppunit/extensions/HelperMacros.h>
#include<limits>

#include "TypeInfoTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(TypeInfoTest);

//-----------------------------------------------------------------------------
void TypeInfoTest::test_min_max()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //--------------testing integer types----------------------
    CPPUNIT_ASSERT(TypeInfo<UInt8>::min() == std::numeric_limits<UInt8>::min() );
    CPPUNIT_ASSERT(TypeInfo<UInt8>::max() == std::numeric_limits<UInt8>::max() );

    CPPUNIT_ASSERT(TypeInfo<Int8>::min() == std::numeric_limits<Int8>::min());
    CPPUNIT_ASSERT(TypeInfo<Int8>::max() == std::numeric_limits<Int8>::max());

    CPPUNIT_ASSERT(TypeInfo<UInt16>::min() == std::numeric_limits<UInt16>::min());
    CPPUNIT_ASSERT(TypeInfo<UInt16>::max() == std::numeric_limits<UInt16>::max());

    CPPUNIT_ASSERT(TypeInfo<Int16>::min() == std::numeric_limits<Int16>::min());
    CPPUNIT_ASSERT(TypeInfo<Int16>::max() == std::numeric_limits<Int16>::max());

    CPPUNIT_ASSERT(TypeInfo<UInt32>::min() == std::numeric_limits<UInt32>::min());
    CPPUNIT_ASSERT(TypeInfo<UInt32>::max() == std::numeric_limits<UInt32>::max());

    CPPUNIT_ASSERT(TypeInfo<Int32>::min() == std::numeric_limits<Int32>::min());
    CPPUNIT_ASSERT(TypeInfo<Int32>::max() == std::numeric_limits<Int32>::max());

    CPPUNIT_ASSERT(TypeInfo<Int64>::min() == std::numeric_limits<Int64>::min());
    CPPUNIT_ASSERT(TypeInfo<Int64>::max() == std::numeric_limits<Int64>::max());

    CPPUNIT_ASSERT(TypeInfo<UInt64>::min() == std::numeric_limits<UInt64>::min());
    CPPUNIT_ASSERT(TypeInfo<UInt64>::max() == std::numeric_limits<UInt64>::max());


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

