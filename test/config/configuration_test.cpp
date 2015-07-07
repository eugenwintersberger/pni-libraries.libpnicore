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
// ============================================================================
//
//  Created on: Dec 27, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <vector>
#include <list>

#include <pni/core/configuration/config_parser.hpp>
#include <pni/core/configuration/cli_args.hpp>
#include "configuration_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(configuration_test);

//-----------------------------------------------------------------------------
void configuration_test::setUp()
{
    conf_file.add_option(config_option<size_t>("pnicore.nthreads","",
                         "number of threads"));

    conf_cli.add_option(config_option<size_t>("nthreads","n","number of threads",3));
    conf_cli.add_option(config_option<std::vector<size_t>>("nruns","r","number of runs"));
}

//-----------------------------------------------------------------------------
void configuration_test::tearDown()
{


}

//-----------------------------------------------------------------------------
void configuration_test::test_configfile()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    parse(conf_file,"config/pni.cfg");
    CPPUNIT_ASSERT(conf_file.value<size_t>("pnicore.nthreads")==4);

    configuration c = std::move(conf_file);
    CPPUNIT_ASSERT(c.value<size_t>("pnicore.nthreads")==4);

}

//-----------------------------------------------------------------------------
void configuration_test::test_configcli()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    std::vector<string> args{"-n4","-r1","-r4","-r10"};

    parse(conf_cli,args);
    std::cout<<conf_cli<<std::endl;

    CPPUNIT_ASSERT(conf_cli.value<size_t>("nthreads")==4);

    auto o = conf_cli.value<std::vector<size_t>>("nruns");
    CPPUNIT_ASSERT(o.size() == 3);
    CPPUNIT_ASSERT(o[0] == 1);
    CPPUNIT_ASSERT(o[1] == 4);
    CPPUNIT_ASSERT(o[2] == 10);

    configuration conf;
    CPPUNIT_ASSERT_THROW(
    conf.add_option(config_option<std::vector<string>>("names","n",
                "user names",std::vector<string>{})),
    index_error);

    CPPUNIT_ASSERT_NO_THROW(
    conf.add_option(config_option<std::vector<string>>("names","n",
            "user names",std::vector<string>{"me"})));

}

//-----------------------------------------------------------------------------
void configuration_test::test_libconfig()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //CPPUNIT_ASSERT(pnicore_config.n_arithmetic_threads() == 4);
}
