//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Apr 28, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/arrays.hpp>
#include "../../data_generator.hpp"
#include "../../compare.hpp"
#include <pni/core/type_erasures/array.hpp>
#include <functional>
#include <sstream>

using namespace pni::core;

//-----------------------------------------------------------------------------
template<typename AT> class array_access_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_access_test<AT>);
        CPPUNIT_TEST(test_linear_read_multidim);
        CPPUNIT_TEST(test_linear_write_multidim);
        CPPUNIT_TEST(test_linear_read_at);
        CPPUNIT_TEST(test_linear_write_at);
        CPPUNIT_TEST(test_linear_read_operator);
        CPPUNIT_TEST(test_linear_write_operator);
        CPPUNIT_TEST_SUITE_END();

        typedef AT mdarray_type;
        typedef typename mdarray_type::value_type value_type;
        typedef random_generator<value_type> generator_type;
        generator_type generator;
        typedef array::element_index index_type;
        shape_t _shape;
        mdarray_type _mdarray1;
        mdarray_type _mdarray2;

    public:
        void setUp();
        void tearDown();

        void test_linear_read_at();
        void test_linear_write_at();
        void test_linear_read_operator();
        void test_linear_write_operator();
        void test_linear_read_multidim();
        void test_linear_write_multidim();
};

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::setUp()
{
    _shape = shape_t({3,2});
    _mdarray1 = mdarray_type::create(_shape);
    _mdarray2 = mdarray_type::create(_shape);
    std::generate(_mdarray1.begin(),_mdarray1.end(),generator);
    std::generate(_mdarray2.begin(),_mdarray2.end(),generator);
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::test_linear_read_at()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a(_mdarray1);
    const array &aref = a;

    //reading from the instance itself
    for(size_t i=0;i<a.size();++i)
    {
        compare(a.at(i).as<value_type>(),_mdarray1.at(i));
        compare(aref.at(i).as<value_type>(),_mdarray1.at(i));
    }
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::test_linear_write_at()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a1(_mdarray1);
    array a2(_mdarray2);

    //reading from the instance itself
    for(size_t i=0;i<a1.size();++i)
    {
        CPPUNIT_ASSERT_NO_THROW(a2.at(i) = a1.at(i));
        CPPUNIT_ASSERT_NO_THROW(a1.at(i) = _mdarray2.at(i));
        compare(a1.at(i).as<value_type>(),_mdarray2.at(i));
        compare(a2.at(i).as<value_type>(),_mdarray1.at(i));
    }
}
//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::test_linear_read_operator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a(_mdarray1);
    const array &aref = a;

    //reading from the instance itself
    for(size_t i=0;i<a.size();++i)
    {
        compare(a[i].as<value_type>(),_mdarray1[i]);
        compare(aref[i].as<value_type>(),_mdarray1[i]);
    }
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::test_linear_write_operator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a1(_mdarray1);
    array a2(_mdarray2);

    //reading from the instance itself
    for(size_t i=0;i<a1.size();++i)
    {
        CPPUNIT_ASSERT_NO_THROW(a2[i] = a1[i]);
        CPPUNIT_ASSERT_NO_THROW(a1[i] = _mdarray2[i]);
        compare(a1[i].as<value_type>(),_mdarray2[i]);
        compare(a2[i].as<value_type>(),_mdarray1[i]);
    }
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::test_linear_read_multidim()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a(_mdarray1);
    const array &aref = a;

    //reading from the instance itself
    for(size_t i=0;i<_shape[0];++i)
    {
        for(size_t j=0;j<_shape[1];++j)
        {
            compare(a(index_type{i,j}).as<value_type>(),_mdarray1(i,j));
            compare(aref(index_type{i,j}).as<value_type>(),_mdarray1(i,j));
        }
    }
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_access_test<AT>::test_linear_write_multidim()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a1(_mdarray1);
    array a2(_mdarray2);

    //reading from the instance itself
    for(size_t i=0;i<_shape[0];++i)
    {
        for(size_t j=0;j<_shape[1];++j)
        {
            index_type index{i,j};
            CPPUNIT_ASSERT_NO_THROW(a2(index) = a1(index));
            CPPUNIT_ASSERT_NO_THROW(a1(index) = _mdarray2(i,j));
            compare(a1(index).as<value_type>(),_mdarray2(i,j));
            compare(a2(index).as<value_type>(),_mdarray1(i,j));
        }
    }
}
