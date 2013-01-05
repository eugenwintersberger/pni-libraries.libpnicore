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

#include "ComplexUtils.hpp"

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    bool operator==(const Complex32 &a,const Complex64 &b)
    {
        Complex64 _a(a.real(),a.imag());

        return (_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const Complex32 &a,const Complex128 &b)
    {
        Complex64 _a(a.real(),a.imag());

        return (_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const Complex64 &a,const Complex32 &b)
    {
        Complex64 _b(b.real(),b.imag());
        return (a == _b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const Complex64 &a,const Complex128 &b)
    {
        Complex128 _a(a.real(),a.imag());
        return(_a == b);
    }

    //-------------------------------------------------------------------------
    bool operator==(const Complex128 &a,const Complex32 &b)
    {
        Complex128 _b(b.real(),b.imag());
        return(_b == a);
    }

    //-------------------------------------------------------------------------
    bool operator==(const Complex128 &a,const Complex64 &b)
    {
        Complex128 _b(b.real(),b.imag());
        return(_b == a);
    }

    //-------------------------------------------------------------------------
    bool operator!=(const Complex32 &a,const Complex64 &b)
    {
        if(a == b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const Complex32 &a,const Complex128 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const Complex64 &a,const Complex32 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const Complex64 &a,const Complex128 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const Complex128 &a,const Complex32 &b)
    {
        if(a==b) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool operator!=(const Complex128 &a,const Complex64 &b)
    {
        if(a==b) return false;
        return true;
    }
}
}




