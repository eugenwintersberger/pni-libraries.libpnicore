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
 * Trait to determine the comparison type for two numeric types.
 *
 * Created on: May 6, 2012
 *     Author: Eugen Wintersberger
 *
 */

#pragma once

#include "types.hpp"

namespace pni{
namespace core{

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
    COMPTYPETRAITSINGLE(uint8,uint8);
    COMPTYPETRAIT(uint8,int8,int16);
    COMPTYPETRAIT(uint8,uint16,uint16);
    COMPTYPETRAIT(uint8,int16,int16);
    COMPTYPETRAIT(uint8,uint32,uint32);
    COMPTYPETRAIT(uint8,int32,int32);
    COMPTYPETRAIT(uint8,uint64,uint64);
    COMPTYPETRAIT(uint8,int64,int64);
    COMPTYPETRAIT(uint8,float32,float32);
    COMPTYPETRAIT(uint8,float64,float64);
    COMPTYPETRAIT(uint8,float128,float128);
    
    COMPTYPETRAITSINGLE(int8,int8);
    COMPTYPETRAIT(int8,uint16,int16);
    COMPTYPETRAIT(int8,int16,int16);
    COMPTYPETRAIT(int8,uint32,int64);
    COMPTYPETRAIT(int8,int32,int32);
    COMPTYPETRAIT(int8,uint64,int64);
    COMPTYPETRAIT(int8,int64,int64);
    COMPTYPETRAIT(int8,float32,float32);
    COMPTYPETRAIT(int8,float64,float64);
    COMPTYPETRAIT(int8,float128,float128);
    
    COMPTYPETRAITSINGLE(uint16,uint16);
    COMPTYPETRAIT(uint16,int16,int16);
    COMPTYPETRAIT(uint16,uint32,uint32);
    COMPTYPETRAIT(uint16,int32,int32);
    COMPTYPETRAIT(uint16,uint64,uint64);
    COMPTYPETRAIT(uint16,int64,int64);
    COMPTYPETRAIT(uint16,float32,float32);
    COMPTYPETRAIT(uint16,float64,float64);
    COMPTYPETRAIT(uint16,float128,float128);
    
    COMPTYPETRAITSINGLE(int16,int16);
    COMPTYPETRAIT(int16,uint32,int64);
    COMPTYPETRAIT(int16,int32,int32);
    COMPTYPETRAIT(int16,uint64,int64);
    COMPTYPETRAIT(int16,int64,int64);
    COMPTYPETRAIT(int16,float32,float32);
    COMPTYPETRAIT(int16,float64,float64);
    COMPTYPETRAIT(int16,float128,float128);

    COMPTYPETRAITSINGLE(uint32,uint32);
    COMPTYPETRAIT(uint32,int32,int32);
    COMPTYPETRAIT(uint32,uint64,uint64);
    COMPTYPETRAIT(uint32,int64,int64);
    COMPTYPETRAIT(uint32,float32,float32);
    COMPTYPETRAIT(uint32,float64,float64);
    COMPTYPETRAIT(uint32,float128,float128);
    
    COMPTYPETRAITSINGLE(int32,int32);
    COMPTYPETRAIT(int32,uint64,int64);
    COMPTYPETRAIT(int32,int64,int64);
    COMPTYPETRAIT(int32,float32,float32);
    COMPTYPETRAIT(int32,float64,float64);
    COMPTYPETRAIT(int32,float128,float128);
    
    COMPTYPETRAITSINGLE(uint64,uint64);
    COMPTYPETRAIT(uint64,int64,int64);
    COMPTYPETRAIT(uint64,float32,float32);
    COMPTYPETRAIT(uint64,float64,float64);
    COMPTYPETRAIT(uint64,float128,float128);

    COMPTYPETRAITSINGLE(int64,int64);
    COMPTYPETRAIT(int64,float32,float32);
    COMPTYPETRAIT(int64,float64,float64);
    COMPTYPETRAIT(int64,float128,float128);

    COMPTYPETRAITSINGLE(float32,float32);
    COMPTYPETRAIT(float32,float64,float64);
    COMPTYPETRAIT(float32,float128,float128);

    COMPTYPETRAITSINGLE(float64,float64);
    COMPTYPETRAIT(float64,float128,float128);
    COMPTYPETRAITSINGLE(float128,float128);

    COMPTYPETRAITSINGLE(complex32,complex32);
    COMPTYPETRAIT(complex32,complex64,complex64);
    COMPTYPETRAIT(complex32,complex128,complex128);

    COMPTYPETRAITSINGLE(complex64,complex64);
    COMPTYPETRAIT(complex64,complex128,complex128);
    COMPTYPETRAITSINGLE(complex128,complex128);
    //! \endcond
//end off namespace
}
}

