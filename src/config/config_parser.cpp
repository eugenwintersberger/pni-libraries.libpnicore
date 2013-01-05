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
 * Created on: Dec 27, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include <fstream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "config_parser.hpp"

namespace popts = boost::program_options;

namespace pni{
namespace core{


    void parse(configuration &c,int argc,const char **argv)
    {
        //merging hidden and visible options to a single option description
        popts::options_description total_opts;
        total_opts.add(c.visible_options());
        total_opts.add(c.hidden_options());

        //run the parser
        popts::store(popts::command_line_parser(argc,argv).
                     options(total_opts).
                     positional(c.arguments()).run(),
                     const_cast<popts::variables_map&>(c.map()));

        //notify the variable map that we are done
        popts::notify(const_cast<popts::variables_map&>(c.map()));
       
        /*
        if(has_option("help"))
            throw cli_help_request(EXCEPTION_RECORD,"help was requested!");
        */
    }
  
    //-------------------------------------------------------------------------
    void parse(configuration &c,const String &s)
    {
        std::ifstream cstream(s);

        popts::options_description total_opts;
        total_opts.add(c.visible_options());
        total_opts.add(c.hidden_options());

        //run the parser
        popts::store(popts::parse_config_file(cstream,total_opts),
                     const_cast<popts::variables_map&>(c.map()));

        cstream.close();

        //notify the variable map that we are done
        popts::notify(const_cast<popts::variables_map&>(c.map()));
    }



//end of namespace
}
}
