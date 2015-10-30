//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Oct 29, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/core/arrays.hpp>

#include "array_types.hpp"
#include "../data_generator.hpp"
#include "../compiler_verion.hpp"

#if GCC_VERSION > 40800
BOOST_AUTO_TEST_SUITE(static_mdarray_test)
    
    typedef all_static_arrays<2,3,5> array_types;

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_default_constructor,AT,array_types)
    {
        AT a;
        BOOST_CHECK_EQUAL(a.size(),30);
        BOOST_CHECK_EQUAL(a.rank(),3);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_constructor,AT,array_types)
    {

    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_constructor,AT,array_types)
    {

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment,AT,array_types)
    {

    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_assignment,AT,array_types)
    {

    }

BOOST_AUTO_TEST_SUITE_END()
#endif

