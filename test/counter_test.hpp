/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jan 8, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/counter.hpp>
#include <functional>

using namespace pni::core;

template<typename T> class counter_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(counter_test<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_increment);
        CPPUNIT_TEST(test_decrement);
        CPPUNIT_TEST_SUITE_END();

        size_t _value1;
        size_t _value2;
        void _set_value1(size_t v);
        void _set_value2(size_t v);
    public:
        void setUp();
        void tearDown();

        void test_construction();
        void test_increment();
        void test_decrement();
};

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::_set_value1(size_t v)
{
    std::cout<<"execute callback 1: "<<this->_value1<<" -> "<<v<<std::endl;
    this->_value1 = v;
}

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::_set_value2(size_t v)
{
    std::cout<<"execute callback 2: "<<this->_value2<<" -> "<<v<<std::endl;
    this->_value2 = v;
}

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::setUp()
{
}

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::tearDown()
{

}

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //default construction
    counter<T> c;
    CPPUNIT_ASSERT(c.start() == T(0));
    CPPUNIT_ASSERT(c.value() == c.start());
    CPPUNIT_ASSERT(c.stop() == T(0));
    CPPUNIT_ASSERT(c.inc() == T(0));

    //standard constructor
    c = counter<T>(T(0),T(10),T(2));
    CPPUNIT_ASSERT(c.start() == T(0));
    CPPUNIT_ASSERT(c.value() == c.start());
    CPPUNIT_ASSERT(c.stop() == T(10));
    CPPUNIT_ASSERT(c.inc() == T(2));

    //testing factory functions
    c = create_counter(T(100));
    CPPUNIT_ASSERT(c.start() == T(0));
    CPPUNIT_ASSERT(c.value() == c.start());
    CPPUNIT_ASSERT(c.stop() == T(100));
    CPPUNIT_ASSERT(c.inc() == T(1));

    c = create_counter(T(5),T(100));
    CPPUNIT_ASSERT(c.start() == T(5));
    CPPUNIT_ASSERT(c.value() == c.start());
    CPPUNIT_ASSERT(c.stop() == T(100));
    CPPUNIT_ASSERT(c.inc() == T(1));

    c = create_counter<T>(T(7),20,T(3));
    CPPUNIT_ASSERT(c.start() == T(7));
    CPPUNIT_ASSERT(c.value() == c.start());
    CPPUNIT_ASSERT(c.stop() == T(7)+20*T(3));
    CPPUNIT_ASSERT(c.inc() == T(3));

}

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::test_increment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    counter<T> c(T(0),T(30));

    for(size_t i=0;i<30;i++)
    {
        CPPUNIT_ASSERT(c.value() == T(i));
        c.increment();
    }
    CPPUNIT_ASSERT(c.value() == T(30));
    //the next call to increment should trigger an overflow and reset the
    //counter
    c.increment(true);
    CPPUNIT_ASSERT(c.value() == c.start());

    //test with callback functions
    c = counter<T>(T(0),T(2));
    this->_value1 = 10;
    this->_value2 = 20;
    c.register_overflow_callback(std::bind(&counter_test<T>::_set_value1,this,1));
    c.register_overflow_callback(std::bind(&counter_test<T>::_set_value2,this,2));
    c.increment(); 
    CPPUNIT_ASSERT(c.value() == 1);
    c.increment();
    CPPUNIT_ASSERT(c.value() == 2);
    c.increment();
    CPPUNIT_ASSERT(this->_value1 == 1);
    CPPUNIT_ASSERT(this->_value2 == 2);

}

//-----------------------------------------------------------------------------
template<typename T> void counter_test<T>::test_decrement()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    counter<T> c(T(0),T(30));
    c.value(T(30));
    CPPUNIT_ASSERT(c.value() == T(30));

    for(size_t i=30;i>0;i--)
    {
        std::cout<<c.value()<<"\t"<<T(i)<<std::endl;
        CPPUNIT_ASSERT(c.value() == T(i));
        c.decrement();
    }
    CPPUNIT_ASSERT(c.value() == T(0));
    //the next call to increment should trigger an underflow and reset the
    //counter
    c.decrement(true);
    CPPUNIT_ASSERT(c.value() == c.start());

    //test with callback functions
    c = counter<T>(T(0),T(2));
    c.value(2);
    this->_value1 = 10;
    this->_value2 = 20;
    c.register_underflow_callback(std::bind(&counter_test<T>::_set_value1,this,1));
    c.register_underflow_callback(std::bind(&counter_test<T>::_set_value2,this,2));
    c.decrement(); 
    CPPUNIT_ASSERT(c.value() == 1);
    c.decrement();
    CPPUNIT_ASSERT(c.value() == 0);
    c.decrement();
    CPPUNIT_ASSERT(this->_value1 == 1);
    CPPUNIT_ASSERT(this->_value2 == 2);

}

