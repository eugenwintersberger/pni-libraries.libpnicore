//implementation of IndexMapBaseTest

#include<cppunit/extensions/HelperMacros.h>

#include "IndexMapBaseTest.hpp"
#include <list>

CPPUNIT_TEST_SUITE_REGISTRATION(IndexMapBaseTest);


//-----------------------------------------------------------------------------
void IndexMapBaseTest::setUp()
{}

//-----------------------------------------------------------------------------
void IndexMapBaseTest::tearDown()
{}

//-----------------------------------------------------------------------------
void IndexMapBaseTest::test_construction()
{
    //default construction
    IndexMapBase im1;

    CPPUNIT_ASSERT(im1.size()==0);
    CPPUNIT_ASSERT(im1.rank()==0);

    //construction from initializer list
    IndexMapBase im2{1,2,3,4,5};
    CPPUNIT_ASSERT(im2.size()==2*3*4*5);
    CPPUNIT_ASSERT(im2.rank()==5);

    //construction from a container
    std::list<size_t> s{3,2,5,6};
    IndexMapBase im3(s);
    CPPUNIT_ASSERT(im3.size()==3*2*5*6);
    CPPUNIT_ASSERT(im3.rank()==4);

    //copy construction
    IndexMapBase im4(im3);
    CPPUNIT_ASSERT(im4.size() == im3.size());
    CPPUNIT_ASSERT(im4.rank() == im3.rank());
    CPPUNIT_ASSERT(std::equal(im4.shape().begin(),im4.shape().end(),
                              im3.shape().begin()));

    //move construction
    IndexMapBase im5 = std::move(im3);
    CPPUNIT_ASSERT(im3.size() == 0);
    CPPUNIT_ASSERT(im3.rank() == 0);

    CPPUNIT_ASSERT(im4.size() == im5.size());
    CPPUNIT_ASSERT(im4.rank() == im5.rank());
    CPPUNIT_ASSERT(std::equal(im4.shape().begin(),im4.shape().end(),
                              im5.shape().begin()));

}

//-----------------------------------------------------------------------------
void IndexMapBaseTest::test_assignment()
{
    IndexMapBase im1{2,3,4,5};
    IndexMapBase im2,im3;

    im2 = im1;
    CPPUNIT_ASSERT(im2.rank() == im1.rank());
    CPPUNIT_ASSERT(im2.size() == im1.size());
    CPPUNIT_ASSERT(std::equal(im1.shape().begin(),im1.shape().end(),
                              im2.shape().begin()));

    im3 = std::move(im1);
    CPPUNIT_ASSERT(im1.size() == 0);
    CPPUNIT_ASSERT(im1.rank() == 0);
    CPPUNIT_ASSERT(im3.rank() == im2.rank());
    CPPUNIT_ASSERT(im3.size() == im2.size());
    CPPUNIT_ASSERT(std::equal(im2.shape().begin(),im2.shape().end(),
                              im3.shape().begin()));
}

//-----------------------------------------------------------------------------
void IndexMapBaseTest::test_access()
{
    std::vector<size_t> s{3,2,5,7};
    IndexMapBase im1(s);

    //this is trivial
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),im1.shape().begin()));
    //try a copy
    auto ls = im1.shape<std::list<size_t> >();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),ls.begin()));

    //in the end we reset the map with a new shape
    std::list<size_t> ns{8,1,4};
    CPPUNIT_ASSERT_NO_THROW(im1.shape(ns));
    CPPUNIT_ASSERT(im1.rank() == 3);
    CPPUNIT_ASSERT(im1.size() == 8*4);
    CPPUNIT_ASSERT(std::equal(ns.begin(),ns.end(),im1.shape().begin()));


}
