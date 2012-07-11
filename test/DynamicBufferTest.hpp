//unit test for the Buffer class

#ifndef __DYNAMICBUFFERTEST_HPP
#define __DYNAMICBUFFERTEST_HPP__


#include<random>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "DynamicBuffer.hpp"
#include "NewAllocator.hpp"

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::utils;

template<typename T,typename Allocator> 
class DynamicBufferTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(DynamicBufferTest);
    CPPUNIT_TEST(test_constructors);
    CPPUNIT_TEST(test_allocation);
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
    void test_allocation();
    void test_access();
    void test_iterator();

};

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::setUp()
{
    this->n1 = 1000;
    this->n2 = 2000;
}

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::tearDown()
{ }

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::test_constructors()
{
    //create first buffer using the default constructor
    DynamicBuffer<T,Allocator> b1; //default constructor
    CPPUNIT_ASSERT(!b1.size());
    
    //create the second constructor with the standard constructor
    //allocating memory
    DynamicBuffer<T,Allocator> b2(this->n2);
    CPPUNIT_ASSERT(b2.size());

    //construct from a initializier list
    DynamicBuffer<T,Allocator> ibuffer = {T(1),T(6),T(12)};
    CPPUNIT_ASSERT(ibuffer[0] == T(1));
    CPPUNIT_ASSERT(ibuffer[1] == T(6));
    CPPUNIT_ASSERT(ibuffer[2] == T(12));


    //test constructor with vector
    std::vector<T> vec = {3,9,1};
    DynamicBuffer<T,Allocator> vbuffer(vec);
    CPPUNIT_ASSERT(vbuffer.size());
    CPPUNIT_ASSERT(vbuffer.size() == 3);
    CPPUNIT_ASSERT(vbuffer[0] == T(3));
    CPPUNIT_ASSERT(vbuffer[1] == T(9));
    CPPUNIT_ASSERT(vbuffer[2] == T(1));


    //=====================copy and move constructor=============================
    //using copy constructor
    DynamicBuffer<T,Allocator> b3(b2);
    CPPUNIT_ASSERT(b2.size());
    CPPUNIT_ASSERT(b3.size());
    CPPUNIT_ASSERT(b3.size() == b2.size());

    //using the move constructor
    DynamicBuffer<T,Allocator> b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.size());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.size());
}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::test_assignment()
{
	//testing here the assignment of equally typed buffers
	DynamicBuffer<T,Allocator> buffer1;
	DynamicBuffer<T,Allocator> buffer2;

	//check first for some standard problems
	//nothing happens - both are not allocated
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	//now the lhs is not allocated and the rhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2.allocate(this->n1));
    CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
    //now the rhs is not allocate dnad the lhs is
    CPPUNIT_ASSERT_NO_THROW(buffer1.free());
    CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);

    //booth buffers are allocated
	CPPUNIT_ASSERT_NO_THROW(buffer2.allocate(this->n1));
	CPPUNIT_ASSERT_NO_THROW(buffer1.allocate(this->n2));
    CPPUNIT_ASSERT(buffer1.size() != buffer2.size());
	//reallocation of the lhs
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	CPPUNIT_ASSERT(buffer1.size());
	CPPUNIT_ASSERT(buffer2.size());
    CPPUNIT_ASSERT(buffer1.size() == buffer2.size());

	DynamicBuffer<T,Allocator> buffer3;
	CPPUNIT_ASSERT_NO_THROW(buffer3 = buffer1);
	CPPUNIT_ASSERT(buffer3.size());
	CPPUNIT_ASSERT(buffer1.size());
    CPPUNIT_ASSERT(buffer3.size() == buffer1.size());

	//checking move assignment - moveing an  allocated
    //buffer to an not allocated one
	DynamicBuffer<T,Allocator> buffer4;
	CPPUNIT_ASSERT_NO_THROW(buffer4 = std::move(buffer3));
	CPPUNIT_ASSERT(buffer4.size());
	CPPUNIT_ASSERT(!buffer3.size());
	CPPUNIT_ASSERT(buffer4.size() == buffer1.size());

    //buffer3 is not allocated now - moving a not allocated buffer to an
    //allocated one
    CPPUNIT_ASSERT_NO_THROW(buffer4 = std::move(buffer3));
    CPPUNIT_ASSERT(!buffer4.size());
    CPPUNIT_ASSERT(!buffer3.size());
    CPPUNIT_ASSERT(buffer4.size() == 0);
    CPPUNIT_ASSERT(buffer3.size() == 0);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::test_allocation()
{
	DynamicBuffer<T,Allocator> dbuffer(this->n1);
	CPPUNIT_ASSERT(dbuffer.size() == this->n1);

	CPPUNIT_ASSERT_NO_THROW(dbuffer.free());
	CPPUNIT_ASSERT(dbuffer.size()==0);

	DynamicBuffer<T,Allocator> dbuffer2;
	CPPUNIT_ASSERT(dbuffer2.size() == 0);

	CPPUNIT_ASSERT_NO_THROW(dbuffer2.allocate(n2));
	CPPUNIT_ASSERT(dbuffer2.size() == n2);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::test_access()
{
	DynamicBuffer<T,Allocator> dbuffer(1000);

	for(size_t i=0;i<1000;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = T(i));

	for(size_t i=0;i<1000;i++){
		CPPUNIT_ASSERT(T(i)==dbuffer[i]);
	}

    DynamicBuffer<T,Allocator> ibuffer(4);
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = T(i));

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == T(i));

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(100),IndexError);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::test_comparison()
{
	DynamicBuffer<T,Allocator> b1(100);
	DynamicBuffer<T,Allocator> b2(100);

	b1 = T(1);
	b2 = T(2);

	CPPUNIT_ASSERT(b1 != b2);
	b2 = T(1);
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DynamicBufferTest<T,Allocator>::test_iterator()
{
    std::cout<<"void BufferTest<BTYPE>::test_iterator()----------------------";
    std::cout<<std::endl;
    DynamicBuffer<T,Allocator> b1(1000);

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
