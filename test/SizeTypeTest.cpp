/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: May 31, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <boost/current_function.hpp>
#include "SizeTypeTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(SizeTypeTest);

void SizeTypeTest::test_size()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    size_t s = SizeType<100>::size;
    CPPUNIT_ASSERT(s == 100);
    s = SizeType<100,2,4>::size;
    CPPUNIT_ASSERT(s == 800);
}
