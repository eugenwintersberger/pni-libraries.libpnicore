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
 * Definition of a dynamic array template.
 *
 * Created on: Jul 19, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "IndexMapBase.hpp"


//-----------------------------------------------------------------------------
IndexMapBase &IndexMapBase::operator=(const IndexMapBase &m)
{
    if(this == &m) return *this;

    _shape = m._shape;
    return *this;
}

//-----------------------------------------------------------------------------
IndexMapBase &IndexMapBase::operator=(IndexMapBase &&m)
{
    if(this == &m) return *this;
    _shape = std::move(m._shape);
    return *this;
}

//-----------------------------------------------------------------------------
size_t IndexMapBase::size() const
{
    size_t s = 1;
    for(auto v: _shape) s*=v;
    return s;
}

