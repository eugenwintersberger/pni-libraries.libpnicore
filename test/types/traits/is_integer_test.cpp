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
// ===========================================================================
//
//  Created on: Jan 7, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing type traits and related functions
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
#include <pni/core/types/types.hpp>
#include <pni/core/types/traits.hpp>
#include <vector>
#include <iostream>
#include "constants.hpp"

using namespace pni::core;

BOOST_AUTO_TEST_SUITE(is_integer_test)
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_integer_types)
    {
        for(auto id: integer_ids) BOOST_CHECK(is_integer(id));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_float_types)
    {
        for(auto id: float_ids) BOOST_CHECK(!is_integer(id));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_complex_types)
    {
        for(auto id: complex_ids) BOOST_CHECK(!is_integer(id));
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_non_numeric_types)
    {
        for(auto id: non_numeric_ids) BOOST_CHECK(!is_integer(id));
    }
    
BOOST_AUTO_TEST_SUITE_END()
