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
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/SArray.hpp>

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::core;

template<typename T>
class SArrayTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(SArrayTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_multiindex_access_const);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST(test_view);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_multiindex_access_const();
        void test_typeinfo();
        void test_stl();
        void test_view();
};

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::setUp(){ }

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //testing the default constructor
    SArray<T,2,3> a1;
    CPPUNIT_ASSERT(a1.rank() == 2);
    CPPUNIT_ASSERT(a1.size() == 6);

    //testing initializer list constructor
    SArray<T,2,3> a2{1,2,3,4,5,6};
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.size() == 6);

    //testing copy constructor
    SArray<T,2,3> a3(a2);
    CPPUNIT_ASSERT(a3.rank() == a2.rank());
    CPPUNIT_ASSERT(a3.size() == a2.size());
}

//------------------------------------------------------------------------------ 
template<typename T> void SArrayTest<T>::test_linear_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    SArray<T,2,3> a1{1,2,3,4,5,6};
    std::vector<T> v1{1,2,3,4,5,6};
   
    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        a1[i] = T(i);

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        check_equality(T(i),a1[i]);

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        a1.at(i) = T(i);

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        check_equality(T(i),a1.at(i));

    CPPUNIT_ASSERT_THROW(a1.at(a1.size()+10),IndexError);

}

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    SArray<T,2,3> a1;

    //--------------------check standard iterator----------------
	//access via [] operator
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    //----------------------testing write data---------------------------------
    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin(); iter!=a1.end();iter++)
    {
        T &v = *iter;
#else
    for(T &v: a1)
    {
#endif
        v = data[index++];
    }
   
    //-----------------------test reading data---------------------------------
    index = 0;
#ifdef NOFOREACH
    for(auto iter=a1.begin();iter!=a1.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto &v: a1)
    {
#endif
        check_equality(v,data[index++]);
    }


    //-------------------check const iterator-----------------------------

    index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto v: a1)
    {
#endif
        check_equality(v,data[index++]); 
    }
}

//-----------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_multiindex_access()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    SArray<T,2,3> a1;
    
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            a1(i,j) = data[i*3+j];

    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            check_equality(a1(i,j),data[i*3+j]);

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            a1(index) = data[i*3+j];
        }
    }

    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            check_equality(a1(index),data[i*3+j]);
        }
    }
}

//-----------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_multiindex_access_const()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto data =RandomDistribution::uniform<std::vector<T> >(6);
    const SArray<T,2,3> a1(data);
    

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            check_equality(a1(i,j),data[i*3+j]);

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            check_equality(a1(index),data[i*3+j]);
        }
    }
}


//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_view()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    SArray<T,10,3> v;
    std::vector<Slice> s{Slice(0),Slice(0,3,1)};

    for(size_t i=0;i<10;i++)
    {
        auto view = v(std::vector<Slice>{Slice(i),Slice(0,3,1)});
        std::fill(view.begin(),view.end(),T(i));
    }
    
    for(size_t i=0;i<10;i++)
    {
        //for reading we use a different construction here
        auto view = v(i,Slice(0,3,1));
#ifdef NOFOREACH
        for(auto iter = view.begin();iter!=view.end();++iter)
        {
            auto v = *iter;
#else
        for(auto v: view)
        {
#endif
            check_equality(v,T(i));
        }
    }

    //check construction of a static array from a view
    auto view = v(2,Slice(0,3));
    SArray<T,3> c(view);

    for(auto viter=view.begin(),citer=c.begin();viter!=view.end();
            ++viter,++citer)
    {
        check_equality(*viter,*citer);
    }

   
}
//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_typeinfo()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    TypeID id1 = SArray<T,2,3>::type_id;
    TypeID id2 = TypeIDMap<T>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}
