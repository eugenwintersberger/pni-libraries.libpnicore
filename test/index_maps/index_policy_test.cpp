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
 *  Created on: Oct 23, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>
#include <pni/core/c_index_policy.hpp>
#include "index_policy_test.hpp"

typedef index_test_params<3,4,5> test_params_1;

template<typename POL> using policy_test_1 = index_policy_test<test_params_1,POL,33,1,2,3>;

CPPUNIT_TEST_SUITE_REGISTRATION(policy_test_1<c_index_policy>);
