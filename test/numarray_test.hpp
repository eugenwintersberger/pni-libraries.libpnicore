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
 *  Created on: Jul 23, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <boost/current_function.hpp>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/numarray.hpp>
#include <pni/core/darray.hpp>
#include <pni/core/sarray.hpp>

#include "data_generator.hpp"
#include "uniform_distribution.hpp"
#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "BufferHelper.hpp"

using namespace pni::core;

template<typename ATYPE,typename TAGTYPE,template<typename> class IPAT,bool MT_BINARY_ARITHMETICS>
class numarray_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(numarray_test);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST(test_unary_add);
        CPPUNIT_TEST(test_unary_sub);
        CPPUNIT_TEST(test_unary_mult);
        CPPUNIT_TEST(test_unary_div);
        CPPUNIT_TEST(test_view);
        CPPUNIT_TEST_SUITE_END();
    private:
        //---------------------------------------------------------------------
        template<typename T,typename ST,typename MT>
        void create_array(darray<T,ST,MT> &a)
        {
            a = darray<T,ST,MT>(std::vector<size_t>{3,4});
        }

        //---------------------------------------------------------------------
        template<typename AT> AT create_array()
        {
            AT result;
            create_array(result);
            return result;
        }
        
    public:
        typedef numarray<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS> narray_t;
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_typeinfo();
        void test_unary_add();
        void test_unary_sub();
        void test_unary_mult();
        void test_unary_div();
       void test_view();
};

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::setUp(){ }

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::tearDown(){ } 

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //default construction
    narray_t a1(create_array<ATYPE>());
    CPPUNIT_ASSERT(a1.size() == 12);
    CPPUNIT_ASSERT(a1.rank() == 2);

    //copy construction
    narray_t a2(a1);
    CPPUNIT_ASSERT(a2.rank() == a1.rank());
    CPPUNIT_ASSERT(a2.size() == a1.size());
}

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    narray_t a1(create_array<ATYPE>());
    size_t i;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();++iter)
    {
        typename ATYPE::value_type &a = *iter;
#else
    for(typename ATYPE::value_type  &a: a1) 
    {
#endif
        a = typename ATYPE::value_type(i);
    }
   
    //copy assignment
    narray_t a2(create_array<ATYPE>());
    a2 = a1;
    CPPUNIT_ASSERT(a2.rank() == a1.rank());
    CPPUNIT_ASSERT(a2.size() == a2.size());
    CPPUNIT_ASSERT(std::equal(a1.begin(),a1.end(),a2.begin()));
}

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_linear_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a1(create_array<ATYPE>());

    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1[i] = value_type(i));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(value_type(i),a1[i]));

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1.at(i) = value_type(i));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(value_type(i),a1.at(i)));

    CPPUNIT_ASSERT_THROW(a1.at(a1.size() + 100),index_error);

    //--------------testing insert---------------------------------------------
    value_type value(100);
    CPPUNIT_ASSERT_NO_THROW(a1.insert(0,value));
    CPPUNIT_ASSERT_THROW(a1.insert(2*a1.size(),value),index_error);

    //--------------testing front----------------------------------------------
    CPPUNIT_ASSERT_NO_THROW(a1.front()=value);
    check_equality(a1.front(),value);

    CPPUNIT_ASSERT_NO_THROW(a1.back() = value);
    check_equality(a1.back(),value);

}

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a1(create_array<ATYPE>());

    //--------------------check standard iterator----------------
	//access via [] operator
    auto data = RandomDistribution::uniform<std::vector<value_type> >(a1.size());

    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();++iter)
    {
        value_type &v = *iter;
#else
    for(value_type &v: a1)
    {
#endif 
        v = data[index++];
    }
    
    index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();++iter)
    {
        auto &v = *iter;
#else
    for(auto &v: a1) 
    {
#endif
        check_equality(v,data[index++]);
    }


    //-------------------check const iterator-----------------------------
    const narray_t &a = a1;

    index = 0;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,data[index++]); 
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_multiindex_access()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    typedef std::vector<size_t> stype;
    std::cout<<"void NumArrayTest<T,STORAGE>::test_multiindex_access()";
    std::cout<<std::endl;

    narray_t a1(create_array<ATYPE>());
    auto s1 = a1.template shape<std::vector<size_t> >();
    auto data = RandomDistribution::uniform<std::vector<value_type> >(a1.size());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
        {
            CPPUNIT_ASSERT_NO_THROW(a1(i,j) = 
                    data[a1.template shape<stype>()[0]*i+j]);
        }
            

    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(i,j),
                        data[a1.template shape<stype>()[0]*i+j]));

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(a1(index) = 
                    data[a1.template shape<stype>()[0]*i+j]);
        }
    }

    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(index),
                        data[a1.template shape<stype>()[0]*i+j]));
        }
    }

    //check some exceptions 
}

//------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_typeinfo()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    type_id_t id1 = narray_t::type_id;
    type_id_t id2 = type_id_map<typename ATYPE::value_type>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}

//-------------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_unary_add()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(1));

    //add a scalar
    a += value_type(1);
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif
        check_equality(v,value_type(2));
    }

    //add a array
    narray_t b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(3));

    a += b;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(5));
    }

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(10));
    a += c;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(15));
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_unary_sub()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(15));

    //add a scalar
    a -= value_type(1);
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(14));
    }

    //add a array
    narray_t b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(3));

    a -= b;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(11));
    }

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(10));
    a -= c;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(1));
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_unary_mult()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(1));

    //add a scalar
    a *= value_type(2);
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(2));
    }

    //add a array
    narray_t b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(3));

    a *= b;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(6));
    }

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(10));
    a *= c;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(60));
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_unary_div()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(12));

    //add a scalar
    a /= value_type(2);
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(12/2));
    }

    //add a array
    narray_t b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(2));

    a /= b;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(12/2/2));
    }

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(2));
    a /= c;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a) 
    {
#endif 
        check_equality(v,value_type(value_type(12)/value_type(2)/
                                  value_type(2)/value_type(2)));
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE,
         typename TAGTYPE,
         template<typename> class IPAT,
         bool MT_BINARY_ARITHMETICS> 
void numarray_test<ATYPE,TAGTYPE,IPAT,MT_BINARY_ARITHMETICS>::test_view()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef typename narray_t::value_type value_type;
    narray_t a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(12));

    auto view = a(size_t(0),slice(0,4));

    view += value_type(1.32);

}
