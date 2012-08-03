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


#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#if (__GNUC__ && __cplusplus && __GNUC__ >= 3)
#include <cxxabi.h>
#define USE_GNU_DEMANGLING 1
#endif

#include "Types.hpp"

namespace pni{
namespace utils{

#define DEPRECATION_WARNING(old_method,new_method) \
	std::cerr<<"Method "+String(old_method)+"is deprecated and will be removed!"<<std::endl;\
	std::cerr<<"use "+String(new_method)+" instead!"<<std::endl;

    String demangle_cpp_name(const char *n);



}
}




#endif /* SERVICE_HPP_ */
