/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Oct 19, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include "index_map_test_common.hpp"
#include <list>

typedef index_test_params<3,4,5> test_params_1;
typedef static_cindex_map<3,4,5> static_map1;

template<typename IMAP> using test1_template = index_map_test_common<test_params_1,IMAP,33,1,2,3>;

CPPUNIT_TEST_SUITE_REGISTRATION(test1_template<cindex_map>);
CPPUNIT_TEST_SUITE_REGISTRATION(test1_template<static_map1>);


