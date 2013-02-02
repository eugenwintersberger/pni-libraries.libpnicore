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
 *  Created on: May 31, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/current_function.hpp>
#include "size_type_test.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(size_type_test);

void size_type_test::test_size()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    size_t s = size_type<100>::size;
    CPPUNIT_ASSERT(s == 100);
    s = size_type<100,2,4>::size;
    CPPUNIT_ASSERT(s == 800);
    s = size_type<2,4>::size;
    CPPUNIT_ASSERT(s == 8);
}
