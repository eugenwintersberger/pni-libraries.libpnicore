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
 *  Created on: Jan 12, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include "EqualityCheck.hpp"
#include "array_factory.hpp"
#include "data_factory.hpp"
#include <pni/core/array.hpp>
#include <functional>
#include <sstream>

using namespace pni::core;

//-----------------------------------------------------------------------------
template<typename OT> class array_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_test<OT>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_copy_and_move);
        CPPUNIT_TEST(test_io);
        CPPUNIT_TEST(test_inquery);
        CPPUNIT_TEST(test_element_access);
        CPPUNIT_TEST(test_at_access);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST_SUITE_END();

        shape_t _shape;
        OT _object1;
        OT _object2;
        std::vector<typename OT::value_type> _data;

    public:
        void setUp();
        void tearDown();

        void test_construction();
        void test_copy_and_move();
        void test_io();
        void test_inquery();
        void test_element_access();
        void test_at_access();
        void test_iterator();
};

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::setUp()
{
    _shape = shape_t({3,2});
    data_factory<typename OT::value_type>::create(3*2,_data);
    _object1 = array_factory<OT>::create(_shape);
    _object2 = array_factory<OT>::create(_shape);
}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array o1(_object1);
    array o2(std::move(_object2));

    CPPUNIT_ASSERT(o1.rank() == _object1.rank());
    CPPUNIT_ASSERT(o1.size() == _object1.size());
    CPPUNIT_ASSERT(o1.type_id() == OT::type_id);

    //check the shape
    shape_t do1s = o1.shape();
    shape_t o1s = _object1.template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(do1s.begin(),do1s.end(),o1s.begin()));
}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_copy_and_move()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array o1(_object1);

    array o2(o1);
    CPPUNIT_ASSERT(o2.rank() == _object1.rank());
    CPPUNIT_ASSERT(o2.size() == _object1.size());
    CPPUNIT_ASSERT(o2.type_id() == OT::type_id);

    array o3(o1);

    array o4(std::move(o3));
    CPPUNIT_ASSERT(o4.rank() == _object1.rank());
    CPPUNIT_ASSERT(o4.size() == _object1.size());
    CPPUNIT_ASSERT(o4.type_id() == OT::type_id);

    CPPUNIT_ASSERT_THROW(o3.rank(),MemoryNotAllocatedError);
    CPPUNIT_ASSERT_THROW(o3.size(),MemoryNotAllocatedError);

}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_io()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array o(_object1);
    std::stringstream s("1 2 3 4 5 6");

    s>>o;
    std::cout<<o<<std::endl;
}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_element_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array o(_object1);

    //write data to array
    for(size_t i=0;i<o.size();++i)
        CPPUNIT_ASSERT_NO_THROW(o[i] = _data[i]);

    //reading data back
    for(size_t i=0;i<o.size();++i)
        check_equality(_data[i],o[i].as<typename OT::value_type>());

}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_iterator()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array o(_object1);
 
    size_t index = 0;
    for(array::iterator iter = o.begin();iter!=o.end();++iter)
        CPPUNIT_ASSERT_NO_THROW(*iter = _data[index++]);

    std::cout<<o<<std::endl;

    index =0;
    for(auto iter = o.begin();iter!=o.end();++iter)
        check_equality(iter->as<typename OT::value_type>(),
                       _data[index++]); 
}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_at_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array o(_object1);

    //write data to array
    for(size_t i=0;i<o.size();++i)
        CPPUNIT_ASSERT_NO_THROW(o.at(i) = _data[i]);

    //reading data back
    for(size_t i=0;i<o.size();++i)
        check_equality(_data[i],
                       o.at(i).as<typename OT::value_type>());

}

//-----------------------------------------------------------------------------
template<typename OT> void array_test<OT>::test_inquery()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    array o(_object1);
    CPPUNIT_ASSERT(o.type_name() == typeid(OT).name());
}


