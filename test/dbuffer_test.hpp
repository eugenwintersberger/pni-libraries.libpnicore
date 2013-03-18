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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <pni/core/dbuffer.hpp>
#include <pni/core/new_allocator.hpp>

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "data_generator.hpp"
#include "uniform_distribution.hpp"

using namespace pni::core;

template<typename T,typename Allocator> 
class dbuffer_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(dbuffer_test);
        CPPUNIT_TEST(test_constructors);
        CPPUNIT_TEST(test_allocation);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST_SUITE_END();
    private:
        size_t n1,n2;
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
void dbuffer_test<T,Allocator>::setUp()
{
    this->n1 = 1000;
    this->n2 = 2000;
}

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void dbuffer_test<T,Allocator>::tearDown()
{ }

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void dbuffer_test<T,Allocator>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    //create first buffer using the default constructor
    dbuffer<T,Allocator> b1; //default constructor
    CPPUNIT_ASSERT(!b1.size());
    
    //create the second constructor with the standard constructor
    //allocating memory
    dbuffer<T,Allocator> b2(this->n2);
    data_generator::fill(b2.begin(),b2.end(),uniform_distribution<T>());
    CPPUNIT_ASSERT(b2.size());

    //construct from a initializier list
    T v1 = uniform_distribution<T>()();
    T v2 = uniform_distribution<T>()();
    T v3 = uniform_distribution<T>()();
    dbuffer<T,Allocator> ibuffer{v1,v2,v3};
    check_equality(ibuffer[0],v1);
    check_equality(ibuffer[1],v2);
    check_equality(ibuffer[2],v3);


    //=====================copy and move constructor=============================
    //using copy constructor
    dbuffer<T,Allocator> b3(b2);
    CPPUNIT_ASSERT(b2.size());
    CPPUNIT_ASSERT(b3.size());
    CPPUNIT_ASSERT(b3.size() == b2.size());
    for(size_t i=0;i<b3.size();++i)
        check_equality(b2[i],b3[i]);

    //using the move constructor
    dbuffer<T,Allocator> b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.size());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.size());
    for(size_t i=0;i<b4.size();++i)
        check_equality(b4[i],b3[i]);
}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void dbuffer_test<T,Allocator>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	//testing here the assignment of equally typed buffers
	dbuffer<T,Allocator> buffer1;
	dbuffer<T,Allocator> buffer2;

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

	dbuffer<T,Allocator> buffer3;
	CPPUNIT_ASSERT_NO_THROW(buffer3 = buffer1);
	CPPUNIT_ASSERT(buffer3.size());
	CPPUNIT_ASSERT(buffer1.size());
    CPPUNIT_ASSERT(buffer3.size() == buffer1.size());

	//checking move assignment - moveing an  allocated
    //buffer to an not allocated one
	dbuffer<T,Allocator> buffer4;
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
void dbuffer_test<T,Allocator>::test_allocation()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
	dbuffer<T,Allocator> b1(this->n1);
	CPPUNIT_ASSERT(b1.size() == this->n1);

	CPPUNIT_ASSERT_NO_THROW(b1.free());
	CPPUNIT_ASSERT(b1.size()==0);

	dbuffer<T,Allocator> b2;
	CPPUNIT_ASSERT(b2.size() == 0);

	CPPUNIT_ASSERT_NO_THROW(b2.allocate(n2));
	CPPUNIT_ASSERT(b2.size() == n2);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void dbuffer_test<T,Allocator>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	dbuffer<T,Allocator> buffer(1000);
    std::vector<T> data(buffer.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

	for(size_t i=0;i<1000;i++) 
        CPPUNIT_ASSERT_NO_THROW(buffer[i] = data[i]);

	for(size_t i=0;i<1000;i++)
		check_equality(data[i],buffer[i]);

    dbuffer<T,Allocator> ibuffer(4);
    data = std::vector<T>(ibuffer.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = data[i]);

    for(size_t i=0;i<ibuffer.size();i++)
        check_equality(ibuffer.at(i),data[i]);

    dbuffer<T,Allocator> jbuffer(4);
    data = std::vector<T>(jbuffer.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
    for(size_t i=0;i<jbuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(jbuffer.insert(i,data[i]));

    for(size_t i=0;i<jbuffer.size();i++)
        check_equality(jbuffer[i],data[i]);

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(100),index_error);
    CPPUNIT_ASSERT_THROW(ibuffer.insert(100,uniform_distribution<T>()()),index_error);

}

//------------------------------------------------------------------------------
template<typename T,typename Allocator> 
void dbuffer_test<T,Allocator>::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	dbuffer<T,Allocator> b1(100);
	dbuffer<T,Allocator> b2(100);

    data_generator::fill(b1.begin(),b1.end(),uniform_distribution<T>());
    std::fill(b2.begin(),b2.end(),uniform_distribution<T>()());

	CPPUNIT_ASSERT(b1 != b2);
    std::copy(b2.begin(),b2.end(),b1.begin());
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T,typename Allocator> 
void dbuffer_test<T,Allocator>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    dbuffer<T,Allocator> b1(1000);
    std::vector<T> data(b1.size());

    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    std::copy(data.begin(),data.end(),b1.begin());

    //read data back
    auto diter = data.begin();
    for(auto iter = b1.begin();iter!=b1.end();++iter)
        check_equality(*iter,*diter++);
}
