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
 *  Created on: Jul 20, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/arrays.hpp>
#include <pni/core/darray.hpp>

#include "data_generator.hpp"
#include "uniform_distribution.hpp"
#include "EqualityCheck.hpp"
#include "BufferHelper.hpp"

using namespace pni::core;

/*!
\brief darray template test

\tparam T data type
\tparam STORAGE storage container
*/
template<typename T,typename STORAGE>
class darray_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(darray_test);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_multiindex_access_const);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST_SUITE_END();
    private:
        shape_t s1,s2;
        size_t r1,r2;
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_multiindex_access_const();
        void test_typeinfo();
        void test_unary_addition();
        void test_unary_subtraction();
};

//------------------------------------------------------------------------------
template<typename T,typename STORAGE> void darray_test<T,STORAGE>::setUp()
{
    s1 = {3,4};
    s2 = {2,3,5};
}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE> void darray_test<T,STORAGE>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    //test default construction
    darray<T,STORAGE> a1;
    CPPUNIT_ASSERT(a1.size() == 0);
    CPPUNIT_ASSERT(a1.rank() == 0);

    //default construction
    darray<T,STORAGE> a2(s1,STORAGE(12));
    CPPUNIT_ASSERT(a2.size() == 12);
    CPPUNIT_ASSERT(a2.rank() == 2);

    //copy construction
    darray<T,STORAGE> a3(a2);
    CPPUNIT_ASSERT(a2.rank() == a3.rank());
    CPPUNIT_ASSERT(a2.size() == a3.size());

    //move construction
    darray<T,STORAGE> a4 = std::move(a2);
    CPPUNIT_ASSERT(a2.size() == 0);
    CPPUNIT_ASSERT(a2.rank() == 0);
    CPPUNIT_ASSERT(a4.size() == a3.size());
    CPPUNIT_ASSERT(a4.rank() == a3.rank());

}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    darray<T,STORAGE> a1(s1,STORAGE(12));
    data_generator::fill(a1.begin(),a1.end(),uniform_distribution<T>());
   
    //copy assignment
    darray<T,STORAGE> a2;
    a2 = a1;
    CPPUNIT_ASSERT(a2.rank() == a1.rank());
    CPPUNIT_ASSERT(a2.size() == a2.size());
    CPPUNIT_ASSERT(std::equal(a1.begin(),a1.end(),a2.begin()));
    
    //move assignment operator
    darray<T,STORAGE> a3;
    a3 = std::move(a1); 
    CPPUNIT_ASSERT(a3.rank() == a2.rank());
    CPPUNIT_ASSERT(a3.size() == a2.size());
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.size() == 0);

    CPPUNIT_ASSERT(std::equal(a3.begin(),a3.end(),a2.begin()));

}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_linear_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    darray<T,STORAGE> a1(s1,STORAGE(12));
    std::vector<T> data(a1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1[i] = T(data[i]));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(data[i],a1[i]));

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1.at(i) = T(data[i]));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(data[i],a1.at(i)));

    CPPUNIT_ASSERT_THROW(a1.at(a1.size() + 100),index_error);
   
    //-------------------testing insert-----------------------------------------
    T value = uniform_distribution<T>()();
    CPPUNIT_ASSERT_THROW(a1.insert(2*a1.size(),value),index_error);
    CPPUNIT_ASSERT_NO_THROW(a1.insert(0,value));
    check_equality(a1.at(0),value);

    //------------------check front---------------------------------------------
    a1.front() = data.back();
    check_equality(a1.front(),data.back());
    
    //------------------check back----------------------------------------------
    a1.back() = data.front();
    check_equality(a1.back(),data.front());
    
    darray<T,STORAGE> a2;
    CPPUNIT_ASSERT_NO_THROW(a2.back());
    CPPUNIT_ASSERT_NO_THROW(a2.front());
    //this would cause a segmentation fault. Maybe we should add some check here
    //at least for the standard methods (not for [])
    //CPPUNIT_ASSERT_NO_THROW(a2.back()=value);

}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    darray<T,STORAGE> a1(s1,STORAGE(12));
    std::vector<T> data(a1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    //--------------------check standard iterator----------------
    auto diter = data.begin();
    for(auto iter = a1.begin();iter!=a1.end();++iter)
        *iter = *diter++;

    diter = data.begin();
    for(auto iter = a1.begin();iter!=a1.end();++iter)
        check_equality(*iter,*diter++);

    //-------------------check const iterator-----------------------------
    const darray<T,STORAGE> &a = a1;

    diter = data.begin();
    for(auto iter = a.begin();iter!=a.end();++iter)
        check_equality(*iter,*diter++); 
}

//-----------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_multiindex_access()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    darray<T,STORAGE> a1(s1,STORAGE(12));
    std::vector<T> data(a1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
        {
            CPPUNIT_ASSERT_NO_THROW(a1(i,j) = data[a1.shape()[1]*i+j]);
        }
            

    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(i,j),data[a1.shape()[1]*i+j]));

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(a1(index) = data[a1.shape()[1]*i+j]);
        }
    }

    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(index),data[a1.shape()[1]*i+j]));
        }
    }

    //check some exceptions 
}

//-----------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_multiindex_access_const()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    STORAGE data(12);
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
    const darray<T,STORAGE> a1(s1,data);
    CPPUNIT_ASSERT(a1.shape()[0] == s1[0]);
    CPPUNIT_ASSERT(a1.shape()[1] == s1[1]);

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(i,j),data[a1.shape()[1]*i+j]));
        }
    }

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(index),data[a1.shape()[1]*i+j]));
        }

    }
    
    //check some exceptions 
    
}
//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void darray_test<T,STORAGE>::test_typeinfo()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    type_id_t id1 = darray<T,STORAGE>::type_id;
    type_id_t id2 = type_id_map<T>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}
