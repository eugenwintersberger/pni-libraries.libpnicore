//!
//! (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Dec 27, 2012
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>

#include <pni/core/configuration/configuration.hpp>

namespace pni{
namespace core{

    //--------------------------------------------------------------------------
    std::ostream &configuration::print(std::ostream &o) const
    {
        return o<<_visible_opts;
    }

    //--------------------------------------------------------------------------
    configuration::configuration():
        _vmap(popts::variables_map()),
        _visible_opts(popts::options_description()),
        _hidden_opts(popts::options_description()),
        _oargs(popts::positional_options_description())
    {
        //set command line options
        //_visible_opts.add_options()
         //       ("help,h","print help message")
          //      ;
    }

    //--------------------------------------------------------------------------
    configuration::configuration(configuration &&c):
        _vmap(std::move(c._vmap)),
        _visible_opts(std::move(c._visible_opts)),
        _hidden_opts(std::move(c._hidden_opts)),
        _oargs(std::move(c._oargs))
    {

    }

    //--------------------------------------------------------------------------
    bool configuration::has_option(const string &name) const
    {
        if(_vmap.count(name)) return true;
        return false;
    }

    //--------------------------------------------------------------------------
    void configuration::add_option(const config_option<Bool> &opt,bool visible)
    {
        typedef boost::shared_ptr<popts::option_description> option_sptr;
        //assemble the name of the option
        string oname = opt.long_name();

        if(!opt.short_name().empty())
            oname += ","+opt.short_name();

        //assemble the sematnic value
        auto value =
            popts::bool_switch(const_cast<bool*>(opt.external_reference()));
        if(opt.has_default())
            value->default_value(opt.default_value());

        option_sptr option_ptr (new popts::option_description(oname.c_str(),
                                value,opt.description().c_str()));

        //finally we cann add the option
        if(visible)
            _visible_opts.add(option_ptr);
        else
            _hidden_opts.add(option_ptr);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const configuration &c)
    {
        return c.print(o);
    }

//end of namespace
}
}
