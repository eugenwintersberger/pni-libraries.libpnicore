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
#include <pni/core/sbuffer.hpp>

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "data_generator.hpp"
#include "uniform_distribution.hpp"

using namespace pni::core;

template<typename T> class sbuffer_test:public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(sbuffer_test);
        CPPUNIT_TEST(test_constructors);
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
        void test_access();
        void test_iterator();

};

#define N1 1000
#define N2 2000

//-----------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::setUp() { }

//-----------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::tearDown() { }

//------------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create first buffer using the default constructor
    sbuffer<T,N1> b1; //default constructor
    CPPUNIT_ASSERT(b1.size() == N1);
    
    //=====================copy and move constructor=============================
    //using copy constructor
    sbuffer<T,N1> b2(b1);
    CPPUNIT_ASSERT(b1.size() == b2.size());
}

//------------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	//testing here the assignment of equally typed buffers
	sbuffer<T,N1> buffer1;
	sbuffer<T,N1> buffer2;

    data_generator::fill(buffer1.begin(),buffer1.end(),
                         uniform_distribution<T>());
    data_generator::fill(buffer2.begin(),buffer2.end(),
                         uniform_distribution<T>());
   
    buffer1 = buffer2;    

    CPPUNIT_ASSERT(buffer1 == buffer2);

}

//------------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::test_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::vector<T> data(N1);
	sbuffer<T,N1> dbuffer;
   
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

	for(size_t i=0;i<N1;i++) 
        CPPUNIT_ASSERT_NO_THROW(dbuffer[i] = data[i]);

	for(size_t i=0;i<N1;i++)
        check_equality(data[i],dbuffer[i]);

    sbuffer<T,N2> ibuffer;
    data = std::vector<T>(N2);
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT_NO_THROW(ibuffer.at(i) = data[i]);

    for(size_t i=0;i<ibuffer.size();i++)
        check_equality(ibuffer.at(i),data[i]);

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(N2+10),index_error);
}

//------------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::test_comparison()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

	sbuffer<T,100> b1;
	sbuffer<T,100> b2;

    data_generator::fill(b1.begin(),b1.end(),uniform_distribution<T>());
    std::fill(b2.begin(),b2.end(),uniform_distribution<T>()());

	CPPUNIT_ASSERT(!std::equal(b1.begin(),b1.end(),b2.begin()));
    std::copy(b2.begin(),b2.end(),b1.begin());
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename T> void sbuffer_test<T>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::vector<T> data(1000);
    sbuffer<T,1000> b1;
    
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
   
    //writting data via iterator
    typename std::vector<T>::const_iterator diter=data.begin();
    for(auto iter = b1.begin();iter!=b1.end();++iter)
        CPPUNIT_ASSERT_NO_THROW(*iter = *diter++);

    //read data back
    diter = data.begin();
    for(auto iter=b1.begin();iter!=b1.end();++iter)
        check_equality(*iter,*diter++);

}
