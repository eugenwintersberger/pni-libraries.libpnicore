//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/current_function.hpp>

#include <pni/utils/DArray.hpp>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/ArrayOperations.hpp>

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
   std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   Shape s{5,10};
   DArray<Float32> a(s);

   auto v1 = a(Slice(1,3),Slice(3,7));
#ifdef NOFOREACH
   auto shape = v1.shape<Shape>();
   for(auto iter = shape.begin();iter!=shape.end();++iter)
   {
       auto v = *iter;
#else
   for(auto v: v1.shape<Shape>()) 
   {
#endif
       std::cout<<v<<std::endl;
   }

   CPPUNIT_ASSERT(v1.shape<Shape>().size() == 2);
   CPPUNIT_ASSERT(v1.shape<Shape>()[0] == 2);
   CPPUNIT_ASSERT(v1.shape<Shape>()[1] == 4);

   auto v2 = a(1,Slice(3,7));
   CPPUNIT_ASSERT(v2.shape<Shape>().size() == 1);
   CPPUNIT_ASSERT(v2.shape<Shape>()[0] == 4);

}

//-----------------------------------------------------------------------------
void ArrayViewTest::test_dataaccess()
{ 
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    Shape s{5,10};
    DArray<Float32> a(s);
    std::fill(a.begin(),a.end(),1.5);

    auto view = a(Slice(0,1),Slice(2,7));
    CPPUNIT_ASSERT(view.shape<Shape>().size() == 1);
    CPPUNIT_ASSERT(view.shape<Shape>()[0] == 5);
    for(size_t i=0;i<view.shape<Shape>()[0];i++)
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
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    DArray<Float32> a(Shape({100,200}));
    std::fill(a.begin(),a.end(),1.24);

    //create the view
    auto v = a(Slice(10,35,2),Slice(100,150,3));

    //check creation 
    CPPUNIT_ASSERT(v.shape<Shape>().size() == 2);
    CPPUNIT_ASSERT(v.shape<Shape>()[1] == 17);
    CPPUNIT_ASSERT(v.shape<Shape>()[0] == 13);

    for(size_t i=0;i<v.size();i++)
        CPPUNIT_ASSERT_NO_THROW(v[i] = i);

    for(size_t i=0;i<v.size();i++)
        CPPUNIT_ASSERT_DOUBLES_EQUAL(v[i],Float32(i),1.e-8);

    size_t cnt = 0;
    for(size_t i=0;i<v.shape<Shape>()[0];i++)
    {
        for(size_t j=0;j<v.shape<Shape>()[1];j++)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(v(i,j),Float32(cnt),1.e-8);
            cnt++;
        }
    }
}

//-----------------------------------------------------------------------------
void ArrayViewTest::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl; 
    //create random data
    Shape frame_shape{1024,2048};

    auto data = RandomDistribution::uniform<DBuffer<Float32> >(1024*2048);
    DArray<Float32> frame(frame_shape,data);
    auto roi = frame(Slice(512,732,2),Slice(1024,1077,3));

    CPPUNIT_ASSERT(roi.shape<Shape>()[0] == 110);
    CPPUNIT_ASSERT(roi.shape<Shape>()[1] == 18);

    //check if selection worked
    for(size_t i=0;i<roi.shape<Shape>()[0];i++)
        for(size_t j=0;j<roi.shape<Shape>()[1];j++)
        {
            Float32 v1 = frame(512+i*2,1024+j*3);
            Float32 v2 = roi(i,j);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(v1,v2,1e-8);
        }

    //create a new array holding the roi data
    DArray<Float32> roi2(roi);

    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = roi2.begin();iter!=roi2.end();iter++)
    {
        const Float32 &v = *iter;
#else
    for(auto v: roi2)
    {
#endif
        CPPUNIT_ASSERT_DOUBLES_EQUAL(v,roi[index++],1.e-8);
    }


    DArray<Float32> roi3(roi);
    auto rs1 = roi3.shape<Shape>();
    auto rs2 = roi.shape<Shape>();
    CPPUNIT_ASSERT(roi3.size() == roi.size());
    CPPUNIT_ASSERT(std::equal(rs1.begin(),rs1.end(),rs2.begin()));
    index = 0;

#ifdef NOFOREACH
    for(auto iter = roi3.begin();iter!=roi3.end();iter++)
    {
        const Float32 &v = *iter;
#else
    for(auto v: roi3)
    {
#endif
        CPPUNIT_ASSERT_DOUBLES_EQUAL(v,roi[index++],1.e-8);
    }
    

}

//-----------------------------------------------------------------------------
void ArrayViewTest::test_operations()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create random data
    Shape frame_shape{10,10};
    std::vector<Float32> data(10*10);

    size_t index=0;
#ifdef NOFOREACH
    for(auto iter=data.begin();iter!=data.end();iter++)
    {
        Float32 &v = *iter;
#else
    for(Float32 &v: data)
    {
#endif 
        v = index++;
    }
    CPPUNIT_ASSERT_DOUBLES_EQUAL(data[0],0,1.e-8);

    DArray<Float32> frame(frame_shape,DArray<Float32>::storage_type(data));
    auto roi = frame(Slice(1,10,2),Slice(2,9,3));

#ifdef NOFOREACH
    for(auto iter=roi.begin();iter!=roi.end();iter++)
    {
        const Float32 &v = *iter;
#else
    for(auto v: roi) 
    {
#endif
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(sum(roi),825,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(max(roi),98,1.e-8);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(min(roi),12.,1.e-8);
   
    //copy data to reuse it for several tests
    DArray<Float32> test1(roi);
    DArray<Float32> test2(roi);
    CPPUNIT_ASSERT(test1 == test2);

    //check clipping 
    test2(0,0) = 30; test2(0,1) = 30; test2(0,2) = 30;
    test2(4,0) = 90; test2(4,1) = 90; test2(4,2) = 90;
    clip(test1,30,90);
    for(size_t i=0;i<test1.size();i++)
        std::cout<<roi[i]<<"\t"<<test1[i]<<"\t"<<test2[i]<<std::endl;
    CPPUNIT_ASSERT(test1 == test2);

    //testing clip with a particular value
    test1 = DArray<Float32>(roi);
    test2 = DArray<Float32>(roi);
    test2(0,0) = 666; test2(0,1) = 666; test2(0,2) = 666;
    test2(4,0) = 42; test2(4,1) = 42; test2(4,2) = 42;
    clip(test1,30,90,666,42);
    CPPUNIT_ASSERT(test1 == test2);

    //testing min clip
    test1 = DArray<Float32>(roi);
    test2 = DArray<Float32>(roi);
    test2(0,0) = 30; test2(0,1) = 30; test2(0,2) = 30;
    min_clip(test1,30);
    CPPUNIT_ASSERT(test1 == test2);

    test1 = DArray<Float32>(roi);
    test2 = DArray<Float32>(roi);
    test2(0,0) = 666; test2(0,1) = 666; test2(0,2) = 666;
    min_clip(test1,30,666);
    CPPUNIT_ASSERT(test1 == test2);

    //testing min clip
    test1 = DArray<Float32>(roi);
    test2 = DArray<Float32>(roi);
    test2(4,0) = 90; test2(4,1) = 90; test2(4,2) = 90;
    max_clip(test1,90);
    CPPUNIT_ASSERT(test1 == test2);

    test1 = DArray<Float32>(roi);
    test2 = DArray<Float32>(roi);
    test2(4,0) = 42; test2(4,1) = 42; test2(4,2) = 42;
    max_clip(test1,90,42);
    CPPUNIT_ASSERT(test1 == test2);

    //testing min and max offset
    CPPUNIT_ASSERT(max_offset(roi) == roi.size()-1);
    CPPUNIT_ASSERT(min_offset(roi) == 0);

    //testing min and max index
    std::vector<size_t> eindex{4,2};
    auto maxi = max_index<std::vector<size_t> >(roi);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(roi(maxi),98.,1.e-8);
    CPPUNIT_ASSERT(maxi[0] == eindex[0]);
    CPPUNIT_ASSERT(maxi[1] == eindex[1]);
   
    eindex[0] = 0; eindex[1] = 0;
    auto mini = min_index<std::vector<size_t> >(roi);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(roi(mini),12.,1.e-8);
    CPPUNIT_ASSERT(mini[0] == eindex[0]);
    CPPUNIT_ASSERT(mini[1] == eindex[1]);
}
