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
 *std::vector<T> along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jan 8, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/core/index_iterator.hpp>
#include <pni/core/index_map/index_maps.hpp>
#include <functional>

using namespace pni::core;

template<typename IT> class index_iterator_test : public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(index_iterator_test<IT>);
        CPPUNIT_TEST(test_forward);
        CPPUNIT_TEST_SUITE_END();
        void print_index(const IT &i);
    public:
        void setUp();
        void tearDown();

        void test_forward();
};

//-----------------------------------------------------------------------------
template<typename IT> 
void index_iterator_test<IT>::print_index(const IT &i)
{
    for(auto iter = i.begin();iter!=i.end();++iter)
        std::cout<<*iter<<" ";

    std::cout<<std::endl;
}

//-----------------------------------------------------------------------------
template<typename IT> void index_iterator_test<IT>::setUp()
{}

//-----------------------------------------------------------------------------
template<typename IT> void index_iterator_test<IT>::tearDown()
{}

//-----------------------------------------------------------------------------
template<typename IT> void index_iterator_test<IT>::test_forward()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef index_iterator<IT,dynamic_cindex_map> iterator_t;

    for(auto iter = iterator_t::begin(shape_t{2,4});
             iter!= iterator_t::end(shape_t{2,4});
             ++iter)
        print_index(*iter);
}

