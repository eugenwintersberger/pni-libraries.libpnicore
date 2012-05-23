//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "SliceTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(SliceTest);

using namespace pni::utils;

//===========implementation of private test functions==========================
void SliceTest::_construct(size_t start,size_t stop)
{
    Slice s(start,stop);
}

void SliceTest::_construct(size_t start,size_t stop,size_t stride)
{
    Slice s(start,stop,stride);
}

//-----------------------------------------------------------------------------
void SliceTest::setUp()
{
}

//-----------------------------------------------------------------------------
void SliceTest::tearDown()
{
}

//-----------------------------------------------------------------------------
void SliceTest::test_construction()
{
    std::cout<<"void SliceTest::test_construction()--------------------------";
    std::cout<<std::endl;

    CPPUNIT_ASSERT_THROW(_construct(1,0),RangeError);
    CPPUNIT_ASSERT_THROW(_construct(1,1),RangeError);
    CPPUNIT_ASSERT_THROW(_construct(1,10,100),RangeError);
   
    //test construction without stride
    size_t f=1,l=10;
    Slice s(f,l);
    CPPUNIT_ASSERT(s.first() == f);
    CPPUNIT_ASSERT(s.last() == l);
    CPPUNIT_ASSERT(s.stride() == 1);

    //test construction with stride
    size_t stride = 2;
    Slice s1(f,l,stride);
    CPPUNIT_ASSERT(s1.first() == f);
    CPPUNIT_ASSERT(s1.last() == l);
    CPPUNIT_ASSERT(s1.stride() == stride);

    //test copy construction
    Slice s2(s1);
    CPPUNIT_ASSERT(s2.first() == s1.first());
    CPPUNIT_ASSERT(s2.last()  == s1.last());
    CPPUNIT_ASSERT(s2.stride() == s1.stride());

}

//-----------------------------------------------------------------------------
void SliceTest::test_assignment()
{
    std::cout<<"void SliceTest::test_assignment()-----------------------------";
    std::cout<<std::endl;

    size_t f=20,l=100,stride=13;
    Slice s(f,l,stride);

    Slice s1(f,l);

    CPPUNIT_ASSERT_NO_THROW(s1 = s);
    CPPUNIT_ASSERT(s1.first() == s.first());
    CPPUNIT_ASSERT(s1.last() == s.last());
    CPPUNIT_ASSERT(s1.stride() == s.stride());

}

//-----------------------------------------------------------------------------
void SliceTest::test_functions()
{
    std::cout<<"void SliceTest::test_functions()------------------------------";
    std::cout<<std::endl;

    size_t f=20,l=100,stride=13;
    Slice s(f,l,stride);

    CPPUNIT_ASSERT(size(s) == 7);
    CPPUNIT_ASSERT(span(s) == 80);

    Slice s1(1,3,2);
    CPPUNIT_ASSERT(size(s1) == 1);
    CPPUNIT_ASSERT(span(s1) == 2);
    
    
}
