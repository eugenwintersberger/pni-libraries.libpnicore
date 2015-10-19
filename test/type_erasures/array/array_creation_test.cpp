//!
//! (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//!  Created on: Apr 28, 2015
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing the array type earsure
#include <boost/test/unit_test.hpp>
#include <pni/core/type_erasures.hpp>

#include "array_types.hpp"
#include "fixture.hpp"

using namespace pni::core;




BOOST_AUTO_TEST_SUITE(array_creation)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_default)
    {
        array a;
        BOOST_CHECK_THROW(a.type_id(),memory_not_allocated_error);
        BOOST_CHECK_THROW(a.size(),memory_not_allocated_error);
        BOOST_CHECK_THROW(a.rank(), memory_not_allocated_error);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_mdarray_copy,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;
        
        array a(f.mdarray_1);
    
        BOOST_CHECK_EQUAL(a.type_id(),f.mdarray_1.type_id);
        BOOST_CHECK_EQUAL(a.rank(),f.mdarray_1.rank());
        BOOST_CHECK_EQUAL(a.size(),f.mdarray_1.size());

        auto s = a.shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(),s.end(),
                                      f.shape.begin(),f.shape.end());

        for(size_t index=0;index<a.size();++index)
        {
            BOOST_CHECK_EQUAL(a[index].as<value_type>(),f.mdarray_1[index]);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_mdarray_move,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;
        std::copy(f.mdarray_1.begin(),f.mdarray_1.end(),f.mdarray_2.begin());
        
        array a(std::move(f.mdarray_1));
        BOOST_CHECK_EQUAL(a.type_id(),f.mdarray_1.type_id);
        BOOST_CHECK_EQUAL(a.rank(),f.mdarray_2.rank());
    
        for(size_t index=0;index<a.size();++index)
        {
            BOOST_CHECK_EQUAL(a[index].as<value_type>(),f.mdarray_2[index]);
        }

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_view_copy,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        auto view = f.mdarray_1(slice(0,3),1);
        array a(view);

        BOOST_CHECK(a.type_id() == view.type_id);
        BOOST_CHECK_EQUAL(a.size(),view.size());
        BOOST_CHECK_EQUAL(a.rank(),view.rank());
        auto sa = a.shape<shape_t>();
        auto sv = view.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(sa.begin(),sa.end(),sv.begin(),sv.end());
        
        for(size_t index=0;index<a.size();++index)
        {
            BOOST_CHECK_EQUAL(a[index].as<value_type>(),view[index]);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_view_move,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        auto view = f.mdarray_1(slice(0,3),1);
        array a(f.mdarray_1(slice(0,3),1));

        BOOST_CHECK(a.type_id() == view.type_id);
        BOOST_CHECK_EQUAL(a.size(),view.size());
        BOOST_CHECK_EQUAL(a.rank(),view.rank());
        auto sa = a.shape<shape_t>();
        auto sv = view.template shape<shape_t>();
        BOOST_CHECK_EQUAL_COLLECTIONS(sa.begin(),sa.end(),sv.begin(),sv.end());
        
        for(size_t index=0;index<a.size();++index)
        {
            BOOST_CHECK_EQUAL(a[index].as<value_type>(),view[index]);
        }
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_construction,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a1(f.mdarray_1);
        array a2(a1);

        BOOST_CHECK_EQUAL(a1.size(),a2.size());
        BOOST_CHECK_EQUAL(a1.type_id(),a2.type_id());
        BOOST_CHECK_EQUAL(a1.rank(),a2.rank());

        for(size_t i=0;i<a1.size();++i)
        {
            BOOST_CHECK_EQUAL(a1[i].as<value_type>(),a2[i].as<value_type>());
            BOOST_CHECK_EQUAL(a1[i].as<value_type>(),f.mdarray_1[i]);
            BOOST_CHECK_EQUAL(a2[i].as<value_type>(),f.mdarray_1[i]);
        }

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_construction,AT,all_array_types)
    {
        typedef typename md_array_trait<AT>::value_type value_type;
        fixture<AT> f;

        array a1(f.mdarray_1);
        array a2(std::move(a1));

        BOOST_CHECK_THROW(a1.type_id(),memory_not_allocated_error);

        BOOST_CHECK_EQUAL(a2.size(),f.mdarray_1.size());
        BOOST_CHECK_EQUAL(a2.type_id(),f.mdarray_1.type_id);
        BOOST_CHECK_EQUAL(a2.rank(),f.mdarray_1.rank());

        for(size_t i=0;i<a2.size();++i)
        {
            BOOST_CHECK_EQUAL(a2[i].as<value_type>(),f.mdarray_1[i]);
        }
    }
BOOST_AUTO_TEST_SUITE_END()
