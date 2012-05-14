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
 * Implementation of the Slice type
 *
 * Created on: May 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "Slice.hpp"

namespace pni{
namespace utils{
    
    //==========implementation of constructors and destructor==================

    Slice::Slice(size_t first,size_t last,size_t stride):
        _first(first),
        _last(last),
        _stride(stride)
    {}

    //-------------------------------------------------------------------------
    Slice::Slice(const std::initializer_list<size_t> &l)
    {
        if(l.size()<2)
        {
            //throw an exception here
        }

        _first = l[0];
        _last  = l[1];
        if(l.size()>=3) _stride = l[2];
        else _stride = 1;
    }


    //=============implementation of assignment operators======================
    Slice &Slice::operator=(const Slice &s)
    {
        if(this == &s) return *this;
        _first = s._first;
        _last  = s._last;
        _stride = s._stride;
        return *this;
    }

    //==========implementation of non-member functions=========================
    size_t size(const Slice &s)
    {
        return (s.last() - s.first())*s.stride();
    }


//end of namespace
}
}
