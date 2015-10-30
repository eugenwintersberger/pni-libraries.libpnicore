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
//  Created on: Nov 13, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing index map classes
#include <boost/test/unit_test.hpp>
#include <vector>
#include <list>
#include <array>
#include <pni/core/types.hpp>
#include <pni/core/arrays/index_map/c_index_map_imp.hpp>
#include <pni/core/arrays/array_selection.hpp>

using namespace pni::core;


BOOST_AUTO_TEST_SUITE(cindex_implementation_test)
    
    typedef c_index_map_imp map_type; 
    typedef array_selection sel_type;
    typedef std::vector<slice> slice_vector;
    typedef std::vector<size_t> index_type1;
    typedef std::list<size_t> index_type2;

    BOOST_AUTO_TEST_CASE(test_offset)
    {
        shape_t s{100};
        size_t exp_value = 5;
        BOOST_CHECK_EQUAL(map_type::offset(s,index_type1{5}),exp_value);
        BOOST_CHECK_EQUAL(map_type::offset(s,index_type2{5}),exp_value);
        BOOST_CHECK_EQUAL(map_type::offset(s,std::array<size_t,1>{{5}}),exp_value);
        
        s = shape_t{100,23};
        exp_value = 10+5*23;
        BOOST_CHECK_EQUAL(map_type::offset(s,index_type1{5,10}),exp_value);
        BOOST_CHECK_EQUAL(map_type::offset(s,index_type2{5,10}),exp_value);
        BOOST_CHECK_EQUAL(map_type::offset(s,std::array<size_t,2>{{5,10}}),exp_value);

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_selection_offset)
    {
        
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_index_1)
    {
        shape_t index(1),s{100},exp_value{5}; 
        size_t offset = 5;
        map_type::index(s,index,offset);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(),
                                      exp_value.begin(),exp_value.end());
    }

    BOOST_AUTO_TEST_CASE(test_index_2)
    {
        shape_t index(2),s{100,23},exp_value{5,10};
        size_t offset = 10+5*23;
        map_type::index(s,index,offset);
        BOOST_CHECK_EQUAL_COLLECTIONS(index.begin(),index.end(),
                                      exp_value.begin(),exp_value.end());
    }
    


BOOST_AUTO_TEST_SUITE_END()

