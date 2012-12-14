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
 * Trait to determine the comparison type for two numeric types.
 *
 * Created on: May 6, 2012
 *     Author: Eugen Wintersberger
 *
 */

#pragma once

#include "Types.hpp"

namespace pni{
namespace utils{

    /*!
    \ingroup type_classes
    \brief comparison trait

    This trait is used to determine the intermediate type to which two values of
    types A and B are converted in order to compare them. 
    In principle this looks like this
    \code
    Float64 a = 100.;
    UInt16 b = 17;
    typedef typename ComparisonTrait<Float64,UInt16>::CompType comp_t;
    //do some comparison
    if(comp_t(a) > comp_t(b))
    {
        //....code omitted ...
    }
    \endcode
    Thus it can be ensured that only types that are comparable are used for the
    comparison operation.
    */
    template<typename A,typename B> class ComparisonTrait;

#define COMPTYPETRAITSINGLE(A,CT)\
    template<> class ComparisonTrait<A,A>\
    {\
        public:\
               typedef CT CompType;\
    }

#define COMPTYPETRAIT(A,B,CT)\
    template<> class ComparisonTrait<A,B>\
    {\
        public:\
               typedef CT CompType;\
    };\
    template<> class ComparisonTrait<B,A>\
    {\
        public:\
               typedef CT CompType;\
    }

    //! \cond no_doc
    COMPTYPETRAITSINGLE(UInt8,UInt8);
    COMPTYPETRAIT(UInt8,Int8,Int16);
    COMPTYPETRAIT(UInt8,UInt16,UInt16);
    COMPTYPETRAIT(UInt8,Int16,Int16);
    COMPTYPETRAIT(UInt8,UInt32,UInt32);
    COMPTYPETRAIT(UInt8,Int32,Int32);
    COMPTYPETRAIT(UInt8,UInt64,UInt64);
    COMPTYPETRAIT(UInt8,Int64,Int64);
    COMPTYPETRAIT(UInt8,Float32,Float32);
    COMPTYPETRAIT(UInt8,Float64,Float64);
    COMPTYPETRAIT(UInt8,Float128,Float128);
    
    COMPTYPETRAITSINGLE(Int8,Int8);
    COMPTYPETRAIT(Int8,UInt16,Int16);
    COMPTYPETRAIT(Int8,Int16,Int16);
    COMPTYPETRAIT(Int8,UInt32,Int64);
    COMPTYPETRAIT(Int8,Int32,Int32);
    COMPTYPETRAIT(Int8,UInt64,Int64);
    COMPTYPETRAIT(Int8,Int64,Int64);
    COMPTYPETRAIT(Int8,Float32,Float32);
    COMPTYPETRAIT(Int8,Float64,Float64);
    COMPTYPETRAIT(Int8,Float128,Float128);
    
    COMPTYPETRAITSINGLE(UInt16,UInt16);
    COMPTYPETRAIT(UInt16,Int16,Int16);
    COMPTYPETRAIT(UInt16,UInt32,UInt32);
    COMPTYPETRAIT(UInt16,Int32,Int32);
    COMPTYPETRAIT(UInt16,UInt64,UInt64);
    COMPTYPETRAIT(UInt16,Int64,Int64);
    COMPTYPETRAIT(UInt16,Float32,Float32);
    COMPTYPETRAIT(UInt16,Float64,Float64);
    COMPTYPETRAIT(UInt16,Float128,Float128);
    
    COMPTYPETRAITSINGLE(Int16,Int16);
    COMPTYPETRAIT(Int16,UInt32,Int64);
    COMPTYPETRAIT(Int16,Int32,Int32);
    COMPTYPETRAIT(Int16,UInt64,Int64);
    COMPTYPETRAIT(Int16,Int64,Int64);
    COMPTYPETRAIT(Int16,Float32,Float32);
    COMPTYPETRAIT(Int16,Float64,Float64);
    COMPTYPETRAIT(Int16,Float128,Float128);

    COMPTYPETRAITSINGLE(UInt32,UInt32);
    COMPTYPETRAIT(UInt32,Int32,Int32);
    COMPTYPETRAIT(UInt32,UInt64,UInt64);
    COMPTYPETRAIT(UInt32,Int64,Int64);
    COMPTYPETRAIT(UInt32,Float32,Float32);
    COMPTYPETRAIT(UInt32,Float64,Float64);
    COMPTYPETRAIT(UInt32,Float128,Float128);
    
    COMPTYPETRAITSINGLE(Int32,Int32);
    COMPTYPETRAIT(Int32,UInt64,Int64);
    COMPTYPETRAIT(Int32,Int64,Int64);
    COMPTYPETRAIT(Int32,Float32,Float32);
    COMPTYPETRAIT(Int32,Float64,Float64);
    COMPTYPETRAIT(Int32,Float128,Float128);
    
    COMPTYPETRAITSINGLE(UInt64,UInt64);
    COMPTYPETRAIT(UInt64,Int64,Int64);
    COMPTYPETRAIT(UInt64,Float32,Float32);
    COMPTYPETRAIT(UInt64,Float64,Float64);
    COMPTYPETRAIT(UInt64,Float128,Float128);

    COMPTYPETRAITSINGLE(Int64,Int64);
    COMPTYPETRAIT(Int64,Float32,Float32);
    COMPTYPETRAIT(Int64,Float64,Float64);
    COMPTYPETRAIT(Int64,Float128,Float128);

    COMPTYPETRAITSINGLE(Float32,Float32);
    COMPTYPETRAIT(Float32,Float64,Float64);
    COMPTYPETRAIT(Float32,Float128,Float128);

    COMPTYPETRAITSINGLE(Float64,Float64);
    COMPTYPETRAIT(Float64,Float128,Float128);
    COMPTYPETRAITSINGLE(Float128,Float128);

    COMPTYPETRAITSINGLE(Complex32,Complex32);
    COMPTYPETRAIT(Complex32,Complex64,Complex64);
    COMPTYPETRAIT(Complex32,Complex128,Complex128);

    COMPTYPETRAITSINGLE(Complex64,Complex64);
    COMPTYPETRAIT(Complex64,Complex128,Complex128);
    COMPTYPETRAITSINGLE(Complex128,Complex128);
    //! \endcond
//end off namespace
}
}

