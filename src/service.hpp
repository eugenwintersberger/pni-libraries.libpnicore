/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Dec 8, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
#include <cxxabi.h>
#define USE_GNU_DEMANGLING 1
#endif

#include "Types.hpp"

namespace pni{
namespace core{

#define DEPRECATION_WARNING(oldfunc,newfunc)\
    std::cerr<<"DEPRECATION WARGING:"<<std::endl;\
    std::cerr<<"Function: ";\
    std::cerr<<oldfunc;\
    std::cerr<<" is deprecated!"<<std::endl;\
    std::cerr<<"Use instead: ";\
    std::cerr<<newfunc;\
    std::cerr<<std::endl;



    //-------------------------------------------------------------------------
    /*!
    \brief demangle C++ names

    When using a GNU compiler this function demangles a C++ name as, for
    instance, returned by typeid(..).name(). 
    \param n mangled name
    \return demangled name of the type 
    */
    String demangle_cpp_name(const char *n);



}
}
