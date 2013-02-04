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


    std::vector<string> cliargs2vector(int argc,char **argv)
    {
        std::vector<string> args; 

        for(size_t i=1;i<argc;i++)
            args.push_back(string(argv[i]));

        return args;
    }

    //-------------------------------------------------------------------------
    void parse(configuration &config,const std::vector<string> &args)
    {
        //merging hidden and visible options to a single option description
        popts::options_description total_opts;
        total_opts.add(config.visible_options());
        total_opts.add(config.hidden_options());

        //run the parser
        popts::store(popts::command_line_parser(args).
                     options(total_opts).
                     positional(config.arguments()).run(),
                     const_cast<popts::variables_map&>(config.map()));

        //notify the variable map that we are done
        popts::notify(const_cast<popts::variables_map&>(config.map()));
       
    }
  
    //-------------------------------------------------------------------------
    void parse(configuration &c,const string &s)
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
