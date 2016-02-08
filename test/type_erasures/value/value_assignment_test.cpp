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

#ifdef GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif GCC
#include <boost/test/unit_test.hpp>
#ifdef GCC
#pragma GCC diagnostic pop
#endif GCC
#include <boost/test/floating_point_comparison.hpp>
#include <pni/core/type_erasures.hpp>

#include "types.hpp"
#include "fixture.hpp"

BOOST_AUTO_TEST_SUITE(value_assignment_test)

    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_assignment,T,all_types)
    {
        fixture<T> f;

        value v1(f.value_1);
        value v2;

        v2 = v1;
        BOOST_CHECK_EQUAL(v2.type_id(),v1.type_id());
        BOOST_CHECK_EQUAL(v1.as<T>(),v2.as<T>());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_assignment,T,all_types)
    {
        fixture<T> f;
        value v1(f.value_1);
        value v2 = make_value<uint8>();
        
        v2 = std::move(v1);
        //v1 is invalid here
        BOOST_CHECK(v2.type_id()==type_id_map<T>::type_id);
        BOOST_CHECK_EQUAL(f.value_1,v2.as<T>());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_reset,T,all_types)
    {
        fixture<T> f;
        value v1(f.value_1);

        f.value_1 = f.generator();
        v1 = f.value_1;
        BOOST_CHECK_EQUAL(f.value_1,v1.as<T>());
    }

BOOST_AUTO_TEST_SUITE_END()


