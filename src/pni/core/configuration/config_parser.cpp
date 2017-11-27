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
// ===========================================================================
//
// Created on: Dec 27, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <fstream>
#include <pni/core/configuration/config_parser.hpp>

namespace popts = boost::program_options;

namespace pni{
namespace core{


    //-------------------------------------------------------------------------
    std::vector<string> cliargs2vector(int argc,char **argv)
    {
        std::vector<string> args; 

        for(size_t i=1;(ssize_t)i<argc;i++)
            args.push_back(string(argv[i]));

        return args;
    }

    //-------------------------------------------------------------------------
    std::vector<string> parse(configuration &config,
                              const std::vector<string> &args,
                              bool unregistered)
    {
        //merging hidden and visible options to a single option description
        popts::options_description total_opts;
        total_opts.add(config.visible_options());
        total_opts.add(config.hidden_options());

        //run the parser
        popts::parsed_options parsed_opts(&total_opts);
        
        auto p = popts::command_line_parser(args);
        p.options(total_opts);

        //if there are any positional arguments - add them
        if(config.arguments().max_total_count()) 
            p.positional(config.arguments());

        //if we allow for unregistered options
        if(unregistered) p.allow_unregistered();

        try
        {
            parsed_opts = p.run();

            //store the parsed options
            popts::store(parsed_opts,const_cast<popts::variables_map&>(config.map()));

        }
        catch(popts::unknown_option &error)
        {
            throw cli_option_error(EXCEPTION_RECORD,
                    "Unknown option ["+error.get_option_name()+"]!");
        }
        catch(popts::required_option &error)
        {
            throw cli_option_error(EXCEPTION_RECORD,
                    "Missing required option ["+error.get_option_name()+"]!");
        }
        catch(popts::multiple_occurrences &error)
        {
            throw cli_option_error(EXCEPTION_RECORD,
                    "Multiple occurrence of option ["
                    +error.get_option_name()+"]!");
        }
        catch(popts::invalid_option_value &error)
        {
            throw cli_option_error(EXCEPTION_RECORD,
                    "Invalid value for option ["+error.get_option_name()+"]!");
        }


        //notify the variable map that we are done
        popts::notify(const_cast<popts::variables_map&>(config.map()));

        return
            popts::collect_unrecognized(parsed_opts.options,popts::include_positional);

       
    }
  
    //-------------------------------------------------------------------------
    void parse(configuration &c,const string &s)
    {
        std::ifstream cstream(s.c_str());

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
