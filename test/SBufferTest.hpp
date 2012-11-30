//unit test for the Buffer class

#ifndef __SBUFFERTEST_HPP__
#define __SBUFFERTEST_HPP__


#include <random>
#include <algorithm>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <pni/utils/SBuffer.hpp>

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::utils;

template<typename T> 
class SBufferTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SBufferTest);
    CPPUNIT_TEST(test_constructors);
    CPPUNIT_TEST(test_access);
    CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_comparison);
    CPPUNIT_TEST(test_iterator);
    CPPUNIT_TEST_SUITE_END();
private:
    UInt64 n1,n2;


public:
    void setUp();
    void tearDown();

    void test_constructors();
    void test_assignment();
    void test_comparison();
    void test_access();
    void test_iterator();

};

#define N1 1000
#define N2 2000

//-----------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::setUp() { }

//-----------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::tearDown() { }

//------------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::test_constructors()
{
    //create first buffer using the default constructor
    SBuffer<T,N1> b1; //default constructor
    CPPUNIT_ASSERT(b1.size() == N1);
    
    //=====================copy and move constructor=============================
    //using copy constructor
    SBuffer<T,N1> b2(b1);
    CPPUNIT_ASSERT(b1.size() == b2.size());

    SBuffer<T,3> b3{1,2,3};
}

//------------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::test_assignment()
{
	//testing here the assignment of equally typed buffers
	SBuffer<T,N1> buffer1;
	SBuffer<T,N1> buffer2;
   
    
    std::fill(buffer1.begin(),buffer1.end(),T(100));
    std::fill(buffer2.begin(),buffer2.end(),T(100));
#ifdef NOFOREACH
    for(auto iter = buffer1.begin();iter!=buffer1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: buffer1)
    {
#endif
        CPPUNIT_ASSERT(v == T(100));
    }

#ifdef NOFOREACH
    for(auto iter=buffer2.begin();iter!=buffer2.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: buffer2)
    {
#endif
        CPPUNIT_ASSERT(v == T(100));
    }

    CPPUNIT_ASSERT(buffer1 == buffer2);

    SBuffer<T,N2> buffer3;

}

//------------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::test_access()
{
	SBuffer<T,N1> dbuffer;

	for(size_t i=0;i<N1;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = T(i));

	for(size_t i=0;i<N1;i++)
		CPPUNIT_ASSERT(T(i)==dbuffer[i]);

    SBuffer<T,N2> ibuffer;
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = T(i));

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == T(i));

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(10000),IndexError);
}

//------------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::test_comparison()
{
	SBuffer<T,100> b1;
	SBuffer<T,100> b2;

    std::fill(b1.begin(),b1.end(),T(1));
    std::fill(b2.begin(),b2.end(),T(2));

	CPPUNIT_ASSERT(b1 != b2);
    std::fill(b2.begin(),b2.end(),T(1));
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T> void SBufferTest<T>::test_iterator()
{
    SBuffer<T,1000> b1;

    auto data = RandomDistribution::uniform<std::vector<T> >(1000);
   
    size_t index = 0;
    std::cout<<"writing data to buffer ..."<<std::endl;
#ifdef NOFOREACH
    for(auto iter = b1.begin();iter!=b1.end();++iter)
    {
        T &v = *iter;
#else
    for(T &v: b1)
    {
#endif
        CPPUNIT_ASSERT_NO_THROW(v = data[index++]);
    }

    //read data back
    index = 0;
    std::cout<<"reading data from buffer ..."<<std::endl;
#ifdef NOFOREACH
    for(auto iter=b1.begin();iter!=b1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: b1)
    {
#endif
        check_equality(v,data[index++]);
    }

}

#endif
