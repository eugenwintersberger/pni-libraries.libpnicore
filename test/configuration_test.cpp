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

#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <vector>
#include <list>

#include <pni/utils/config/config_parser.hpp>
#include <pni/utils/config/cli_args.hpp>
#include "configuration_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(configuration_test);

//-----------------------------------------------------------------------------
void configuration_test::setUp()
{
    conf_file.add_option(config_option<size_t>("pniutils.nthreads","",
                         "number of threads"));

    conf_cli.add_option(config_option<size_t>("nthreads","n","number of threads"));
}

//-----------------------------------------------------------------------------
void configuration_test::tearDown()
{


}

//-----------------------------------------------------------------------------
void configuration_test::test_configfile()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    parse(conf_file,"pni.cfg");
    CPPUNIT_ASSERT(conf_file.value<size_t>("pniutils.nthreads")==4);
}

//-----------------------------------------------------------------------------
void configuration_test::test_configcli()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    std::vector<String> argv{"-n4"};
    cli_args args(argv);
    std::cout<<args<<std::endl;

    parse(conf_cli,args.argc(),args.argv());
    std::cout<<conf_cli<<std::endl;

    CPPUNIT_ASSERT(conf_cli.value<size_t>("nthreads")==4);

}
