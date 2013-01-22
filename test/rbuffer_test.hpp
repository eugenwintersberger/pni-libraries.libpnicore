/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 19, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once


#include <boost/current_function.hpp>
#include <random>
#include <algorithm>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <pni/core/RBuffer.hpp>
#include <pni/core/NewAllocator.hpp>

#include "data_generator.hpp"
#include "uniform_distribution.hpp"
#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::core;

template<typename T> class rbuffer_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(rbuffer_test);
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
template<typename T> void rbuffer_test<T>::setUp()
{
    this->n1 = 1000;
    this->n3 = 1000;
    this->n2 = 2000;
    this->ptr1 = new T[this->n1];
    this->ptr2 = new T[this->n2];
    this->ptr3 = new T[this->n3];
}

//-----------------------------------------------------------------------------
template<typename T> void rbuffer_test<T>::tearDown()
{ 
    if(this->ptr1) delete [] this->ptr1;
    if(this->ptr2) delete [] this->ptr2;
    if(this->ptr3) delete [] this->ptr3;
}

//------------------------------------------------------------------------------
template<typename T> void rbuffer_test<T>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create first buffer using the default constructor
    RBuffer<T> b1; //default constructor
    CPPUNIT_ASSERT(!b1.size());
    
    //create the second constructor with the standard constructor
    //allocating memory
    RBuffer<T> b2(this->n2,this->ptr2);
    CPPUNIT_ASSERT(b2.size() == this->n2);
    data_generator::fill(b2.begin(),b2.end(),uniform_distribution<T>());


    //=====================copy and move constructor=============================
    //using copy constructor
    RBuffer<T> b3(b2);
    CPPUNIT_ASSERT(b2.size());
    CPPUNIT_ASSERT(b3.size());
    CPPUNIT_ASSERT(b3.size() == b2.size());
    CPPUNIT_ASSERT(std::equal(b2.begin(),b2.end(),b3.begin()));

    //using the move constructor
    RBuffer<T> b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.size());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.size());
    CPPUNIT_ASSERT(std::equal(b4.begin(),b4.end(),b3.begin()));
}

//------------------------------------------------------------------------------
template<typename T> void rbuffer_test<T>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	//testing here the assignment of equally typed buffers
	RBuffer<T> buffer1;
	RBuffer<T> buffer2;

    CPPUNIT_ASSERT(buffer1 == buffer2);

	//now the lhs is not allocated and the rhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2 = RBuffer<T>(this->n2,this->ptr2));
    CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
    //now the rhs is not allocate dnad the lhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);

    //booth buffers are allocated
	CPPUNIT_ASSERT_NO_THROW(buffer2 = RBuffer<T>(this->n2,this->ptr2));
	CPPUNIT_ASSERT_NO_THROW(buffer1 = RBuffer<T>(this->n1,this->ptr1));
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
    RBuffer<T> buffer3 = buffer1;
	RBuffer<T> buffer4;
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
template<typename T> void rbuffer_test<T>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	RBuffer<T> dbuffer(this->n1,this->ptr1);
    std::vector<T> data(dbuffer.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

	for(size_t i=0;i<this->n1;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = data[i]);

	for(size_t i=0;i<this->n1;i++)
        check_equality(data[i],dbuffer[i]);

    RBuffer<T> ibuffer(this->n2,this->ptr2);
    data = std::vector<T>(ibuffer.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = data[i]);

    for(size_t i=0;i<ibuffer.size();i++)
        check_equality(ibuffer.at(i),data[i]);

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(this->n2+2),IndexError);
}

//------------------------------------------------------------------------------
template<typename T> void rbuffer_test<T>::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	RBuffer<T> b1(this->n1,this->ptr1);
	RBuffer<T> b2(this->n3,this->ptr3);
    data_generator::fill(b1.begin(),b1.end(),uniform_distribution<T>());
    std::fill(b2.begin(),b2.end(),uniform_distribution<T>()());

	CPPUNIT_ASSERT(!std::equal(b1.begin(),b1.end(),b2.begin()));
    std::copy(b1.begin(),b1.end(),b2.begin());
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T> void rbuffer_test<T>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    RBuffer<T> b1(this->n1,this->ptr1);
    std::vector<T> data(b1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    //copy data
    std::copy(data.begin(),data.end(),b1.begin());
   
    //read data back
    auto diter = data.begin();
    for(auto iter = b1.begin();iter!=b1.end();++iter)
        check_equality(*iter,*diter++);
}

