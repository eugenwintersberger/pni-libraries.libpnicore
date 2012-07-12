//unit test for the Buffer class

#ifndef __REFBUFFERTEST_HPP__
#define __REFBUFFERTEST_HPP__


#include<random>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "StaticBuffer.hpp"

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include <algorithm>

using namespace pni::utils;

template<typename T> 
class StaticBufferTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(StaticBufferTest);
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
template<typename T> void StaticBufferTest<T>::setUp() { }

//-----------------------------------------------------------------------------
template<typename T> void StaticBufferTest<T>::tearDown() { }

//------------------------------------------------------------------------------
template<typename T> void StaticBufferTest<T>::test_constructors()
{
    //create first buffer using the default constructor
    StaticBuffer<T,N1> b1; //default constructor
    CPPUNIT_ASSERT(b1.size() == N1);
    
    //=====================copy and move constructor=============================
    //using copy constructor
    StaticBuffer<T,N1> b2(b1);
    CPPUNIT_ASSERT(b1.size() == b2.size());

    StaticBuffer<T,3> b3{1,2,3};
}

//------------------------------------------------------------------------------
template<typename T> void StaticBufferTest<T>::test_assignment()
{
	//testing here the assignment of equally typed buffers
	StaticBuffer<T,N1> buffer1;
	StaticBuffer<T,N1> buffer2;
   
    
    std::fill(buffer1.begin(),buffer1.end(),T(100));
    std::fill(buffer2.begin(),buffer2.end(),T(100));

    for(auto v: buffer1) CPPUNIT_ASSERT(v == T(100));
    for(auto v: buffer2) CPPUNIT_ASSERT(v == T(100));

    CPPUNIT_ASSERT(buffer1 == buffer2);

    StaticBuffer<T,N2> buffer3;

}

//------------------------------------------------------------------------------
template<typename T> void StaticBufferTest<T>::test_access()
{
	StaticBuffer<T,N1> dbuffer;

	for(size_t i=0;i<N1;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = T(i));

	for(size_t i=0;i<N1;i++)
		CPPUNIT_ASSERT(T(i)==dbuffer[i]);

    StaticBuffer<T,N2> ibuffer;
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = T(i));

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == T(i));

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(10000),IndexError);
}

//------------------------------------------------------------------------------
template<typename T> void StaticBufferTest<T>::test_comparison()
{
	StaticBuffer<T,100> b1;
	StaticBuffer<T,100> b2;

    std::fill(b1.begin(),b1.end(),T(1));
    std::fill(b2.begin(),b2.end(),T(2));

	CPPUNIT_ASSERT(b1 != b2);
    std::fill(b2.begin(),b2.end(),T(1));
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T> void StaticBufferTest<T>::test_iterator()
{
    StaticBuffer<T,1000> b1;

    auto data = RandomDistribution::uniform<std::vector<T> >(1000);
   
    size_t index = 0;
    std::cout<<"writing data to buffer ..."<<std::endl;
    for(T &v: b1)
        CPPUNIT_ASSERT_NO_THROW(v = data[index++]);

    //read data back
    index = 0;
    std::cout<<"reading data from buffer ..."<<std::endl;
    for(auto v: b1)
        check_equality(v,data[index++]);

}

#endif
