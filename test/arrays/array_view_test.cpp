//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
//  Created on: May 14, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <pni/core/arrays.hpp>
#include "../data_generator.hpp"
#include "array_types.hpp"
#include <boost/mpl/joint_view.hpp>
#include <iostream>
#include "../compiler_version.hpp"

using namespace pni::core;

#define NX 100
#define NY 125

typedef  boost::mpl::joint_view<dynamic_arrays,
#if GCC_VERSION > 40800
                                boost::mpl::joint_view<
                                fixed_dim_arrays<2>,
                                static_arrays<100,125>
                                >
#else 
                                fixed_dim_arrays<2>
#endif
                                > all_array_types;

template<typename AT> struct array_view_test_fixture
{
    typedef AT                            array_type;
    typedef array_view<AT>                view_type;
    typedef typename AT::value_type       value_type;
    typedef random_generator<value_type>  generator_type;
    typedef std::vector<slice>            slice_vector;
    typedef typename array_type::map_type map_type;
    typedef array_selection               selection_type;

    generator_type generator;
    shape_t shape;
    array_type a;

    array_view_test_fixture():
        generator(),
        shape({NX,NY}),
        a(array_type::create(shape))
    {
        std::generate(a.begin(),a.end(),generator); 
    }
};

BOOST_AUTO_TEST_SUITE(array_view_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_construction,AT,all_array_types)
    {
        typedef array_view_test_fixture<AT> fixture_type; 
        typedef typename fixture_type::view_type view_type;
        typedef typename fixture_type::selection_type selection_type;
        typedef typename fixture_type::slice_vector slice_vector;


        fixture_type fixture;
       
        slice_vector slices{slice(0,3),slice(3,7)};
        view_type v1(fixture.a,selection_type::create(slices));

    }

BOOST_AUTO_TEST_SUITE_END()

