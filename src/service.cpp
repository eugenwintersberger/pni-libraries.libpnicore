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
 * Service routings for internal use only
 *
 * Created on: Aug 3, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include <pni/core/service.hpp>

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    string demangle_cpp_name(const char *n)
    {
#if USE_GNU_DEMANGLING
        char *rname;
        std::size_t len;
        int stat;
        rname = abi::__cxa_demangle(n,NULL,&len,&stat);

        if(rname!=NULL)
        {
            string out(rname);
            std::free(rname);
            return out;
        }

        return string("Cannot Demangle name of symbol ")+string(n);
#else
        return string(n);
#endif
    }

//end of namespace
}
}
