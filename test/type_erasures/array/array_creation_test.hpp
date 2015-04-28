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
#include <pni/core/error.hpp>
#include <pni/core/type_erasures/array.hpp>
#include <functional>
#include <sstream>

#include "../../data_generator.hpp"
#include "../../compare.hpp"

using namespace pni::core;

//-----------------------------------------------------------------------------
template<typename AT> class array_creation_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_creation_test<AT>);
        CPPUNIT_TEST(test_default);
        CPPUNIT_TEST(test_from_mdarray_copy);
        CPPUNIT_TEST(test_from_mdarray_move);
        CPPUNIT_TEST(test_from_view_copy);
        CPPUNIT_TEST(test_from_view_move);
        CPPUNIT_TEST(test_move);
        CPPUNIT_TEST(test_copy);
        CPPUNIT_TEST_SUITE_END();

        typedef AT mdarray_type;
        typedef typename mdarray_type::value_type value_type;
        typedef random_generator<value_type> generator_type;
        shape_t _shape;
        mdarray_type _mdarray1;
        mdarray_type _mdarray2;
        std::vector<value_type> _data;

    public:
        void setUp();
        void tearDown();
      
        //test default constructed instance of array
        void test_default();
        //test construction from an mdarray instance
        void test_from_mdarray_copy();
        void test_from_mdarray_move();
        //test construction from a view
        void test_from_view_copy();
        void test_from_view_move();
        //test move construction 
        void test_move();
        //test copy construction
        void test_copy();
};

//-----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::setUp()
{
    _shape = shape_t({3,2});
    _mdarray1 = mdarray_type::create(_shape);
    _mdarray2 = mdarray_type::create(_shape);

    std::generate(_mdarray1.begin(),_mdarray1.end(),generator_type());
    std::generate(_mdarray2.begin(),_mdarray2.end(),generator_type());
}

//-----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::tearDown() { }

//----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_default()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array a;
    CPPUNIT_ASSERT_THROW(a.type_id(),memory_not_allocated_error);
    CPPUNIT_ASSERT_THROW(a.size(),memory_not_allocated_error);
    CPPUNIT_ASSERT_THROW(a.rank(), memory_not_allocated_error);
}

//-----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_from_mdarray_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array a(_mdarray1);
    
    CPPUNIT_ASSERT(a.type_id() == _mdarray1.type_id);
    CPPUNIT_ASSERT(a.rank() == _mdarray1.rank());
    CPPUNIT_ASSERT(a.size() == _mdarray2.size());
    auto s = a.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),_shape.begin()));
    
    //check equality of data
    for(size_t i=0;i<a.size(); ++i) 
        compare(a[i].as<value_type>(),_mdarray1[i]);
}

//----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_from_mdarray_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::copy(_mdarray1.begin(),_mdarray1.end(),_mdarray2.begin());

    array a(std::move(_mdarray1));
  
    //cannot do this check because the static arrays will always have a size
    //CPPUNIT_ASSERT(_mdarray1.size() == 0);
    CPPUNIT_ASSERT(a.rank() == 2);
    CPPUNIT_ASSERT(a.size() == 6);
    auto s = a.shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),_shape.begin()));
    
    //check equality of data
    for(size_t i=0;i<a.size(); ++i) 
        compare(a[i].as<value_type>(),_mdarray2[i]);

}

//----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_from_view_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    auto view = _mdarray1(slice(0,3),1);
    array a(view);

    CPPUNIT_ASSERT(a.type_id() == view.type_id);
    CPPUNIT_ASSERT(a.size() == view.size());
    CPPUNIT_ASSERT(a.rank() == view.rank());
    auto sa = a.shape<shape_t>();
    auto sv = view.template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(sa.begin(),sa.end(),sv.begin()));

    //check data
    for(size_t i=0;i<a.size();++i)
        compare(a[i].as<value_type>(),view[i]);
}

//----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_from_view_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto view = _mdarray1(slice(0,3),1);
    array a(_mdarray1(slice(0,3),1));

    CPPUNIT_ASSERT(a.type_id() == view.type_id);
    CPPUNIT_ASSERT(a.size() == view.size());
    CPPUNIT_ASSERT(a.rank() == view.rank());
    auto sa = a.shape<shape_t>();
    auto sv = view.template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(sa.begin(),sa.end(),sv.begin()));

    //check data
    for(size_t i=0;i<a.size();++i)
        compare(a[i].as<value_type>(),view[i]);

}

//----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_copy()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;

    array a1(_mdarray1);
    array a2(a1);

    CPPUNIT_ASSERT(a1.size() == a2.size());
    CPPUNIT_ASSERT(a1.type_id() == a2.type_id());
    CPPUNIT_ASSERT(a1.rank() == a2.rank());

    for(size_t i=0;i<a1.size();++i)
    {
        compare(a1[i].as<value_type>(),a2[i].as<value_type>());
        compare(a1[i].as<value_type>(),_mdarray1[i]);
        compare(a2[i].as<value_type>(),_mdarray1[i]);
    }

}

//----------------------------------------------------------------------------
template<typename AT> void array_creation_test<AT>::test_move()
{
    std::cerr<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    array a1(_mdarray1);
    array a2(std::move(a1));

    CPPUNIT_ASSERT_THROW(a1.type_id(),memory_not_allocated_error);

    CPPUNIT_ASSERT(a2.size() == _mdarray1.size());
    CPPUNIT_ASSERT(a2.type_id() == _mdarray1.type_id);
    CPPUNIT_ASSERT(a2.rank() == _mdarray1.rank());

    for(size_t i=0;i<a2.size();++i)
    {
        compare(a2[i].as<value_type>(),_mdarray1[i]);
    }

}
