/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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

#include <pni/core/config/library_config.hpp>

namespace pni{
namespace core{

  
    //-------------------------------------------------------------------------
    void library_config::_setup_configuration()
    {
        conf.add_option(config_option<size_t>("nthreads","",
                        "number of threads",&_nthreads));
    }

    //-------------------------------------------------------------------------
    library_config::library_config() {}

    //-------------------------------------------------------------------------
    library_config::library_config(const string &fname)
    {
        _setup_configuration();
        parse(conf,fname);
    }

    //-------------------------------------------------------------------------
    library_config::~library_config(){}

    //-------------------------------------------------------------------------
    size_t library_config::n_arithmetic_threads() const
    {
        return _nthreads;
    }

//end of namespace
}
}


