//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "ArrayFactory.hpp"
#include "Buffer.hpp"
#include "Shape.hpp"
#include "ArrayViewTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(ArrayViewTest);

using namespace pni::utils;

void ArrayViewTest::setUp()
{
}

void ArrayViewTest::tearDown()
{
}

//-----------------------------------------------------------------------------
void ArrayViewTest::testConstruction()
{
   Shape s{5,10};
   auto a = ArrayFactory<Float32>::create(s);

   auto v1 = a(Slice(1,3),Slice(3,7));
   CPPUNIT_ASSERT(v1.shape().rank() == 2);
   CPPUNIT_ASSERT(v1.shape()[0] == 2);
   CPPUNIT_ASSERT(v1.shape()[1] == 4);

   auto v2 = a(Slice(1,2),Slice(3,7));
   CPPUNIT_ASSERT(v2.shape().rank() == 1);
   CPPUNIT_ASSERT(v2.shape()[0] == 4);

}

//-----------------------------------------------------------------------------
void ArrayViewTest::test_dataaccess()
{
    std::cout<<"void ArrayViewTest::test_dataaccess()......................";
    std::cout<<std::endl;
    Shape s{5,10};
    auto a = ArrayFactory<Float32>::create(s);
    a = 1.5;

    auto view = a(Slice(0,1),Slice(2,7));
    CPPUNIT_ASSERT(view.shape().rank() == 1);
    CPPUNIT_ASSERT(view.shape()[0] == 5);
    for(size_t i=0;i<view.shape()[0];i++)
        CPPUNIT_ASSERT_NO_THROW(view(i) = Float32(i));

    for(size_t j=0;j<s[0];j++)
    {
        for(size_t i=0;i<s[1];i++) std::cout<<a(j,i)<<" ";
        std::cout<<std::endl;
    }

    for(size_t i=0;i<10;i++)
    {
        if((i<2)||(i>6)) CPPUNIT_ASSERT_DOUBLES_EQUAL(a(0,i),1.5,1.e-8);
        else 
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a(0,i),Float32(i-2),1.e-8);
    }

   
}

//-----------------------------------------------------------------------------
void ArrayViewTest::test_linearaccess()
{
    std::cout<<"void ArrayViewTest::test_linearaccess()-----------------------";
    std::cout<<std::endl;

    auto a = ArrayFactory<Float32>::create({100,200});
    a = 1.24;

    //create the view
    auto v = a(Slice(10,35,2),Slice(100,150,3));

    //check creation 
    std::cout<<v.shape()<<std::endl;
    CPPUNIT_ASSERT(v.shape().rank() == 2);
    CPPUNIT_ASSERT(v.shape()[1] == 16);
    CPPUNIT_ASSERT(v.shape()[0] == 12);

    for(size_t i=0;i<v.size();i++)
        CPPUNIT_ASSERT_NO_THROW(v[i] = i);

    for(size_t i=0;i<v.size();i++)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(v[i],Float32(i),1.e-8);

    size_t cnt = 0;
    for(size_t i=0;i<v.shape()[0];i++)
    {
        for(size_t j=0;j<v.shape()[1];j++)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(v(i,j),Float32(cnt),1.e-8);
            cnt++;
        }
    }
}
