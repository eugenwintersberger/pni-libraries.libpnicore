/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jan 17, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "arrays/common.hpp"
#include <pni/core/arrays.hpp>

using namespace pni::core;

//---------------general factory for dynamic arrays-----------------------------
template<typename ATYPE> struct array_factory
{
    typedef typename ATYPE::storage_type storage_type;
    typedef typename ATYPE::value_type value_type;
    typedef typename ATYPE::map_type map_type;

    template<typename CTYPE> static ATYPE create(const CTYPE &s)
    {
        map_type map=map_utils<map_type>::create(s);
        return ATYPE(std::move(map),storage_type(map.size()));
    }

};


//------------------static arrays----------------------------------------------
template<typename T,size_t ...DIMS> 
struct array_factory<static_array<T,DIMS...> >
{
    public:
        template<typename CTYPE> static sarray<T,DIMS...> create(const CTYPE &s)
        {
            return sarray<T,DIMS...>();
        }
};

template<typename T> class array_factory<scalar<T> >
{
    public:
        template<typename CTYPE> static scalar<T> create(const CTYPE &s)
        {
            return scalar<T>();
        }
};



