/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 19, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <boost/current_function.hpp>
#include <random>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <pni/core/DBuffer.hpp>
#include <pni/core/NewAllocator.hpp>

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::core;

template<typename T,typename Allocator> 
class DBufferTest:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(DBufferTest);
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
void DBufferTest<T,Allocator>::setUp()
{
    this->n1 = 1000;
    this->n2 = 2000;
}

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DBufferTest<T,Allocator>::tearDown()
{ }

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DBufferTest<T,Allocator>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    //create first buffer using the default constructor
    DBuffer<T,Allocator> b1; //default constructor
    CPPUNIT_ASSERT(!b1.size());
    
    //create the second constructor with the standard constructor
    //allocating memory
    DBuffer<T,Allocator> b2(this->n2);
    CPPUNIT_ASSERT(b2.size());

    //construct from a initializier list
    DBuffer<T,Allocator> ibuffer{T(1),T(6),T(12)};
    CPPUNIT_ASSERT(ibuffer[0] == T(1));
    CPPUNIT_ASSERT(ibuffer[1] == T(6));
    CPPUNIT_ASSERT(ibuffer[2] == T(12));


    //=====================copy and move constructor=============================
    //using copy constructor
    DBuffer<T,Allocator> b3(b2);
    CPPUNIT_ASSERT(b2.size());
    CPPUNIT_ASSERT(b3.size());
    CPPUNIT_ASSERT(b3.size() == b2.size());

    //using the move constructor
    DBuffer<T,Allocator> b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.size());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.size());
}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DBufferTest<T,Allocator>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	//testing here the assignment of equally typed buffers
	DBuffer<T,Allocator> buffer1;
	DBuffer<T,Allocator> buffer2;

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

	DBuffer<T,Allocator> buffer3;
	CPPUNIT_ASSERT_NO_THROW(buffer3 = buffer1);
	CPPUNIT_ASSERT(buffer3.size());
	CPPUNIT_ASSERT(buffer1.size());
    CPPUNIT_ASSERT(buffer3.size() == buffer1.size());

	//checking move assignment - moveing an  allocated
    //buffer to an not allocated one
	DBuffer<T,Allocator> buffer4;
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
void DBufferTest<T,Allocator>::test_allocation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	DBuffer<T,Allocator> dbuffer(this->n1);
	CPPUNIT_ASSERT(dbuffer.size() == this->n1);

	CPPUNIT_ASSERT_NO_THROW(dbuffer.free());
	CPPUNIT_ASSERT(dbuffer.size()==0);

	DBuffer<T,Allocator> dbuffer2;
	CPPUNIT_ASSERT(dbuffer2.size() == 0);

	CPPUNIT_ASSERT_NO_THROW(dbuffer2.allocate(n2));
	CPPUNIT_ASSERT(dbuffer2.size() == n2);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DBufferTest<T,Allocator>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	DBuffer<T,Allocator> dbuffer(1000);

	for(size_t i=0;i<1000;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = T(i));

	for(size_t i=0;i<1000;i++){
		CPPUNIT_ASSERT(T(i)==dbuffer[i]);
	}

    DBuffer<T,Allocator> ibuffer(4);
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = T(i));

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == T(i));

    DBuffer<T,Allocator> jbuffer(4);
    for(size_t i=0;i<jbuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(jbuffer.insert(i,T(i)));

    for(size_t i=0;i<jbuffer.size();i++)
        CPPUNIT_ASSERT(jbuffer[i] == T(i));

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(100),IndexError);
    CPPUNIT_ASSERT_THROW(ibuffer.insert(100,1),IndexError);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DBufferTest<T,Allocator>::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	DBuffer<T,Allocator> b1(100);
	DBuffer<T,Allocator> b2(100);

    std::fill(b1.begin(),b1.end(),T(1));
    std::fill(b2.begin(),b2.end(),T(2));

	CPPUNIT_ASSERT(b1 != b2);
    std::fill(b2.begin(),b2.end(),T(1));
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void DBufferTest<T,Allocator>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    DBuffer<T,Allocator> b1(1000);

    auto data = RandomDistribution::uniform<std::vector<T> >(1000);

    std::copy(data.begin(),data.end(),b1.begin());

    //read data back
    size_t index = 0;
    std::cout<<"reading data from buffer ..."<<std::endl;
#ifdef NOFOREACH
    for(auto iter = b1.begin();iter!=b1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: b1)
    {
#endif
        check_equality(v,data[index++]);
    }
}
