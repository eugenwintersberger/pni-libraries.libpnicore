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

#include <pni/core/Array.hpp>

template<typename ATYPE> class array_factory
{
    public:
        template<typename CTYPE> static ATYPE create(const CTYPE &s)
        {
            return ATYPE(s);
        }
};

template<typename T,size_t ...DIMS> class array_factory<SArray<T,DIMS...> >
{
    public:
        static SArray<T,DIMS...> create(shape_t &s)
        {
            return SArray<T,DIMS...>();
        }
};

template<typename T> class array_factory<Scalar<T> >
{
    public:
        static Scalar<T> create(shape_t &s)
        {
            return Scalar<T>();
        }
};



