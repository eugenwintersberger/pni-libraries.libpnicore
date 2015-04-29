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
template<typename AT> class array_iterator_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_iterator_test<AT>);
        CPPUNIT_TEST(test_foreach);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST(test_const_iterator);
        CPPUNIT_TEST_SUITE_END();

        typedef AT mdarray_type;
        typedef typename mdarray_type::value_type value_type;
        typedef random_generator<value_type> generator_type;
        generator_type _generator;
        shape_t _shape;
        mdarray_type _mdarray1;
        mdarray_type _mdarray2;

    public:
        void setUp();
        void tearDown();

        void test_iterator();
        void test_foreach();
        void test_const_iterator();
};

//-----------------------------------------------------------------------------
template<typename AT> 
void array_iterator_test<AT>::setUp()
{
    _shape = shape_t({3,2});
    _mdarray1 = mdarray_type::create(_shape);
    _mdarray2 = mdarray_type::create(_shape);
    std::generate(_mdarray1.begin(),_mdarray1.end(),_generator);
    std::generate(_mdarray2.begin(),_mdarray2.end(),_generator);
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_iterator_test<AT>::tearDown() { }


//-----------------------------------------------------------------------------
template<typename AT> 
void array_iterator_test<AT>::test_iterator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array a1(_mdarray1);
    array a2(_mdarray2);
 
    size_t index = 0;
    auto iter1 = a1.begin();
    auto iter2 = a2.begin();
    for(;iter1!=a1.end();++iter1,++iter2,++index)
    {
        CPPUNIT_ASSERT_NO_THROW(*iter2 = *iter1);
        CPPUNIT_ASSERT_NO_THROW(*iter1 = _mdarray2[index]);
        compare((*iter1).as<value_type>(),_mdarray2[index]);
        compare((*iter2).as<value_type>(),_mdarray1[index]);

        value v(to_value(*iter1));
        compare(v.as<value_type>(),_mdarray2[index]);
    }
}

//-----------------------------------------------------------------------------
template<typename AT>
void array_iterator_test<AT>::test_const_iterator()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a1(_mdarray1);
    const array &r = a1;

    size_t index = 0;
    auto iter = r.begin();
    for(;iter!=r.end();++iter,++index)
    {
        compare((*iter).as<value_type>(),_mdarray1[index]);

        value v(*iter);
        compare(v.as<value_type>(),_mdarray1[index]);
    }
}

//-----------------------------------------------------------------------------
template<typename AT> 
void array_iterator_test<AT>::test_foreach()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array a1(_mdarray1);
 
    size_t index = 0;
    for(auto v: a1)
        CPPUNIT_ASSERT_NO_THROW(v = _mdarray1[index++]);


    index = 0;
    for(auto v: a1)
        compare(v.as<value_type>(),_mdarray1[index++]); 

}
