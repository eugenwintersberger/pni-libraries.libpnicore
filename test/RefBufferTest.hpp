//unit test for the Buffer class

#ifndef __REFBUFFERTEST_HPP__
#define __REFBUFFERTEST_HPP__


#include<random>
#include<algorithm>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "RefBuffer.hpp"
#include "NewAllocator.hpp"

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::utils;

template<typename T> 
class RefBufferTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(RefBufferTest);
    CPPUNIT_TEST(test_constructors);
    CPPUNIT_TEST(test_access);
    CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_comparison);
    CPPUNIT_TEST(test_iterator);
    CPPUNIT_TEST_SUITE_END();
private:
    UInt64 n1,n2,n3;
    T *ptr1;
    T *ptr2;
    T *ptr3;

public:
    void setUp();
    void tearDown();

    void test_constructors();
    void test_assignment();
    void test_comparison();
    void test_access();
    void test_iterator();

};

//-----------------------------------------------------------------------------
template<typename T> void RefBufferTest<T>::setUp()
{
    this->n1 = 1000;
    this->n3 = 1000;
    this->n2 = 2000;
    this->ptr1 = new T[this->n1];
    this->ptr2 = new T[this->n2];
    this->ptr3 = new T[this->n3];
}

//-----------------------------------------------------------------------------
template<typename T> void RefBufferTest<T>::tearDown()
{ 
    if(this->ptr1) delete [] this->ptr1;
    if(this->ptr2) delete [] this->ptr2;
    if(this->ptr3) delete [] this->ptr3;
}

//------------------------------------------------------------------------------
template<typename T> void RefBufferTest<T>::test_constructors()
{
    //create first buffer using the default constructor
    RefBuffer<T> b1; //default constructor
    CPPUNIT_ASSERT(!b1.size());
    
    //create the second constructor with the standard constructor
    //allocating memory
    RefBuffer<T> b2(this->n2,this->ptr2);
    CPPUNIT_ASSERT(b2.size() == this->n2);


    //=====================copy and move constructor=============================
    //using copy constructor
    RefBuffer<T> b3(b2);
    CPPUNIT_ASSERT(b2.size());
    CPPUNIT_ASSERT(b3.size());
    CPPUNIT_ASSERT(b3.size() == b2.size());

    //using the move constructor
    RefBuffer<T> b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.size());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.size());
}

//------------------------------------------------------------------------------
template<typename T> void RefBufferTest<T>::test_assignment()
{
	//testing here the assignment of equally typed buffers
	RefBuffer<T> buffer1;
	RefBuffer<T> buffer2;

    CPPUNIT_ASSERT(buffer1 == buffer2);

	//now the lhs is not allocated and the rhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2 = RefBuffer<T>(this->n2,this->ptr2));
    CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
    //now the rhs is not allocate dnad the lhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);

    //booth buffers are allocated
	CPPUNIT_ASSERT_NO_THROW(buffer2 = RefBuffer<T>(this->n2,this->ptr2));
	CPPUNIT_ASSERT_NO_THROW(buffer1 = RefBuffer<T>(this->n1,this->ptr1));
    CPPUNIT_ASSERT(buffer2.size() == this->n2);
    CPPUNIT_ASSERT(buffer1.size() == this->n1);
    CPPUNIT_ASSERT(buffer1.size() != buffer2.size());
	//copy assignment
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	CPPUNIT_ASSERT(buffer1.size());
	CPPUNIT_ASSERT(buffer2.size());
    CPPUNIT_ASSERT(buffer1.size() == buffer2.size());


	//checking move assignment - moveing an  allocated
    //buffer to an not allocated one
    RefBuffer<T> buffer3 = buffer1;
	RefBuffer<T> buffer4;
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
template<typename T> void RefBufferTest<T>::test_access()
{
	RefBuffer<T> dbuffer(this->n1,this->ptr1);

	for(size_t i=0;i<this->n1;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = T(i));

	for(size_t i=0;i<this->n1;i++)
		CPPUNIT_ASSERT(T(i)==dbuffer[i]);

    RefBuffer<T> ibuffer(this->n2,this->ptr2);
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = T(i));

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == T(i));

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(this->n2+2),IndexError);
}

//------------------------------------------------------------------------------
template<typename T> void RefBufferTest<T>::test_comparison()
{
	RefBuffer<T> b1(this->n1,this->ptr1);
	RefBuffer<T> b2(this->n3,this->ptr3);

    std::fill(b1.begin(),b1.end(),T(1));
    std::fill(b2.begin(),b2.end(),T(2));

	CPPUNIT_ASSERT(b1 != b2);

    std::fill(b2.begin(),b2.end(),T(1));
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T> void RefBufferTest<T>::test_iterator()
{
    RefBuffer<T> b1(this->n1,this->ptr1);

    auto data = RandomDistribution::uniform<std::vector<T> >(this->n1);

    //copy data
    std::copy(data.begin(),data.end(),b1.begin());
   
    //read data back
    size_t index = 0;
    std::cout<<"reading data from buffer ..."<<std::endl;
    for(auto v: b1)
        check_equality(v,data[index++]);
}

#endif
