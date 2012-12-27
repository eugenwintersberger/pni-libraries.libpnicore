/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Dec, 27 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "cli_args.hpp"

namespace pni{
namespace utils{


    //--------------------------------------------------------------------------
    cli_args::~cli_args()
    {
        for(size_t i = 0;i<_argc;++i)
            if(_argv[i]) delete [] _argv[i];

        if(_argv) delete [] _argv;
        _argc = 0;
        _argv = nullptr;
    }

    //--------------------------------------------------------------------------
    const char **cli_args::argv() const
    {
        return (const char **)_argv;
    }

    //--------------------------------------------------------------------------
    int cli_args::argc() const
    {
        return _argc;
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const cli_args &args)
    {
        for(size_t i=0;i<args.argc();i++) o<<args.argv()[i]<<std::endl;

        return o;
    }

//end of namespace
}
}
