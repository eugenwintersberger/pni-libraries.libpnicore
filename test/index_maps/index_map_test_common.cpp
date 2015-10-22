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
//  Created on: Oct 19, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <vector>
#include <list>
#include <pni/core/arrays/index_map/index_maps.hpp>

using namespace pni::core;

typedef boost::mpl::list<std::vector<size_t>,
                         std::vector<ssize_t>,
                         std::vector<unsigned int>,
                         std::list<size_t>,
                         std::list<ssize_t>,
                         std::list<unsigned int>> index_types;

typedef fixed_dim_cindex_map<1> c_index_map_array_1;
typedef fixed_dim_cindex_map<2> c_index_map_array_2;
typedef fixed_dim_cindex_map<3> c_index_map_array_3;

//----------------------define here the first test--------------------
typedef test_params<3,4,5> test1_params;
typedef static_cindex_map<3,4,5> static_map1;

template<typename MAP> 
using test1_template = index_map_test_common<test1_params,MAP,33,1,2,3>;

CPPUNIT_TEST_SUITE_REGISTRATION(test1_template<dynamic_cindex_map>);
CPPUNIT_TEST_SUITE_REGISTRATION(test1_template<c_index_map_array_3>);
CPPUNIT_TEST_SUITE_REGISTRATION(test1_template<static_map1>);

//---------------------define the second test here--------------------
typedef test_params<2,3> test2_params;
typedef static_cindex_map<2,3> static_map2;

template<typename MAP>
using test2_template = index_map_test_common<test2_params,MAP,5,1,2>;

CPPUNIT_TEST_SUITE_REGISTRATION(test2_template<dynamic_cindex_map>);
CPPUNIT_TEST_SUITE_REGISTRATION(test2_template<c_index_map_array_2>);
CPPUNIT_TEST_SUITE_REGISTRATION(test2_template<static_map2>);

//---------------------define the third test here--------------------
typedef test_params<10> test3_params;
typedef static_cindex_map<10> static_map3;

template<typename MAP>
using test3_template = index_map_test_common<test3_params,MAP,3,3>;

CPPUNIT_TEST_SUITE_REGISTRATION(test3_template<dynamic_cindex_map>);
CPPUNIT_TEST_SUITE_REGISTRATION(test3_template<c_index_map_array_1>);
CPPUNIT_TEST_SUITE_REGISTRATION(test3_template<static_map3>);

BOOST_AUTO_TEST_SUITE(index_map_test_common)


BOOST_AUTO_TEST_SUITE_END()
