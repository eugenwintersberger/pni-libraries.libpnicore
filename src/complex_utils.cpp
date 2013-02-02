/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * A couple of utility operators and function for complex numbers.
 *
 * Created on: Sep 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

#include "complex_utils.hpp"

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    bool operator==(const complex32 &a,const complex64 &b)
    {
        complex64 _a(a.real(),a.imag());

        return (_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex32 &a,const complex128 &b)
    {
        complex64 _a(a.real(),a.imag());

        return (_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex64 &a,const complex32 &b)
    {
        complex64 _b(b.real(),b.imag());
        return (a == _b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex64 &a,const complex128 &b)
    {
        complex128 _a(a.real(),a.imag());
        return(_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex128 &a,const complex32 &b)
    {
        complex128 _b(b.real(),b.imag());
        return(_b == a);
    }

    //-------------------------------------------------------------------------
    bool operator==(const complex128 &a,const complex64 &b)
    {
        complex128 _b(b.real(),b.imag());
        return(_b == a);
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex32 &a,const complex64 &b)
    {
        if(a == b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex32 &a,const complex128 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex64 &a,const complex32 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex64 &a,const complex128 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex128 &a,const complex32 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const complex128 &a,const complex64 &b)
    {
        if(a==b) return false;
        return true;
    }
}
}




