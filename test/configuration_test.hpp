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
 *  Created on: Dec 27, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<pni/utils/config/configuration.hpp>


using namespace pni::utils;

class configuration_test: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(configuration_test);
        CPPUNIT_TEST(test_configfile);
        CPPUNIT_TEST_SUITE_END();
        configuration conf_file;
    public:
        void setUp();
        void tearDown();

        void test_configfile();

};
