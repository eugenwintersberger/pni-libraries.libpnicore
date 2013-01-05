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
 * Service routings for internal use only
 *
 * Created on: Aug 3, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include "service.hpp"

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    String demangle_cpp_name(const char *n)
    {
#if USE_GNU_DEMANGLING
        char *rname;
        std::size_t len;
        int stat;
        rname = abi::__cxa_demangle(n,NULL,&len,&stat);

        if(rname!=NULL)
        {
            String out(rname);
            std::free(rname);
            return out;
        }

        return String("Cannot Demangle name of symbol ")+String(n);
#else
        return String(n);
#endif
    }

//end of namespace
}
}
