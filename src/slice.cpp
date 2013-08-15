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
 * Implementation of the Slice type
 *
 * Created on: May 14, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/core/slice.hpp>
#include <iostream>

namespace pni{
namespace core{

    //============implementation of private methods============================
    void slice::_check_start_stop(const exception_record &o) const
    {
        if(_first >= _last)
        {
            std::stringstream ss;
            ss<<"Last index ("<<_last<<") is equal or exceeds first ("<<_first<<")!";
            throw range_error(o,ss.str());
        }
    }

    //-------------------------------------------------------------------------
    void slice::_check_stride(const exception_record &o) const
    {
        if(span(*this)<_stride)
        {
            std::stringstream ss;
            ss<<"Stride ("<<_stride<<") is larger than span ("<<span(*this);
            ss<<")!";
            throw range_error(o,ss.str());
        }
    }
    
    //==========implementation of constructors and destructor==================

    slice::slice(size_t first,size_t last,size_t stride):
        _first(first),
        _last(last),
        _stride(stride)
    {
        _check_start_stop(EXCEPTION_RECORD);
        _check_stride(EXCEPTION_RECORD);
    }

    //-------------------------------------------------------------------------
    slice::slice(const std::initializer_list<size_t> &l)
    {
        if(l.size()<2)
        {
            //throw an exception here
        }

        _stride = 1;
        size_t cnt=0;
#ifdef NOFOREACH
        for(auto iter = l.begin(); iter != l.end(); iter++)
        {
            size_t v = *iter;
#else
        for(auto v: l)
        {
#endif
            if(cnt == 0) _first = v;
            if(cnt == 1) _last = v;
            if(cnt == 2) _stride = v ;

            cnt++;
        }

        _check_start_stop(EXCEPTION_RECORD);
        _check_stride(EXCEPTION_RECORD);
    }

    //-------------------------------------------------------------------------
    slice::slice(size_t i):
        _first(i),
        _last(i+1),
        _stride(1)
    {
        _check_start_stop(EXCEPTION_RECORD);
        _check_stride(EXCEPTION_RECORD);
    }


    //=============implementation of assignment operators======================
    slice &slice::operator=(const slice &s)
    {
        if(this == &s) return *this;
        _first = s._first;
        _last  = s._last;
        _stride = s._stride;
        return *this;
    }

    //==========implementation of non-member functions=========================
    std::ostream &operator<<(std::ostream &o,const slice &s)
    {
        o<<s.first()<<":"<<s.last();
        if(s.stride()!=1) o<<":"<<s.stride();
        return o;
    }
    
    //-------------------------------------------------------------------------
    size_t size(const slice &s)
    {
        return (span(s)+s.stride()-1)/s.stride();
    }

    //-------------------------------------------------------------------------
    size_t span(const slice &s)
    {
        return (s.last()-s.first());
    }



//end of namespace
}
}
