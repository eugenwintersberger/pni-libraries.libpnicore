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

    //============implementation of private methods============================
    void Slice::_check_start_stop(const String &o) const
    {
        if(_first >= _last)
        {
            std::stringstream ss;
            ss<<"Last index ("<<_last<<") is equal or exceeds first ("<<_first<<")!";

            RangeError error;
            error.issuer(o);
            error.description(ss.str());
            throw error;
        }
    }

    //-------------------------------------------------------------------------
    void Slice::_check_stride(const String &o) const
    {
        if(span(*this)<_stride)
        {
            std::stringstream ss;
            ss<<"Stride ("<<_stride<<") is larger than span ("<<span(*this);
            ss<<")!";
            RangeError error;
            error.issuer(o);
            error.description(ss.str());
            throw error;
        }
    }
    
    //==========implementation of constructors and destructor==================

    Slice::Slice(size_t first,size_t last,size_t stride):
        _first(first),
        _last(last),
        _stride(stride)
    {
        _check_start_stop("Slice::Slice(size_t first,size_t last,"
                          "size_t stride)");
        _check_stride("Slice::Slice(size_t first,size_t last,"
                      "size_t stride)");
    }

    //-------------------------------------------------------------------------
    Slice::Slice(const std::initializer_list<size_t> &l)
    {
        if(l.size()<2)
        {
            //throw an exception here
        }

        _stride = 1;
        size_t cnt=0;
        for(auto v: l)
        {
            if(cnt == 0) _first = v;
            if(cnt == 1) _last = v;
            if(cnt == 2) _stride = v ;

            cnt++;
        }

        _check_start_stop("Slice::Slice(const "
                          "std::initializer_list<size_t> &l)");
        _check_stride("Slice::Slice(const "
                      "std::initializer_list<size_t> &l)");
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
        return (s.last() - s.first())/s.stride();
    }

    //-------------------------------------------------------------------------
    size_t span(const Slice &s)
    {
        return (s.last()-s.first());
    }


//end of namespace
}
}
