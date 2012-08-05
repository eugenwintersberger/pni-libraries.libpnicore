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
 * Created on: 5.08.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include <vector>
#include "DArray.hpp"
#include "SArray.hpp"
#include "NumArray.hpp"
#include "Types.hpp"
#include "Slice.hpp"


namespace pni{
namespace utils{

    //define some dynamic arrays
    typedef DArray<UInt8> U8DArray;
    typedef DArray<Int8>  I8Darray;
    typedef DArray<UInt16> U16DArray;
    typedef DArray<Int16>  I16DArray;
    typedef DArray<UInt32> U32DArray;
    typedef DArray<Int32>  I32DArray;
    typedef DArray<UInt64> U64DArray;
    typedef DArray<Int64>  I64DArray;

    typedef DArray<Float32> F32DArray;
    typedef DArray<Float64> F64DArray;
    typedef DArray<Float128> F128DArray;

    typedef DArray<Complex32> C32DArray;
    typedef DArray<Complex64> C64DArray;
    typedef DArray<Complex128> C128DArray;

    //define some static arrays
    template<size_t ...DIMS> using U8SArray = SArray<UInt8,DIMS...>;
    template<size_t ...DIMS> using I8SArray = SArray<Int8,DIMS...>;
    template<size_t ...DIMS> using U16SArray = SArray<UInt16,DIMS...>;
    template<size_t ...DIMS> using I16SArray = SArray<Int16,DIMS...>;
    template<size_t ...DIMS> using U32SArray = SArray<UInt32,DIMS...>;
    template<size_t ...DIMS> using I32SArray = SArray<Int32,DIMS...>;
    template<size_t ...DIMS> using U64SArray = SArray<UInt64,DIMS...>;
    template<size_t ...DIMS> using I64SArray = SArray<Int64,DIMS...>;

    template<size_t ...DIMS> using F32SArray = SArray<Float32,DIMS...>;
    template<size_t ...DIMS> using F64SArray = SArray<Float64,DIMS...>;
    template<size_t ...DIMS> using F128SArray = SArray<Float128,DIMS...>;
    
    template<size_t ...DIMS> using C32SArray = SArray<Complex32,DIMS...>;
    template<size_t ...DIMS> using C64SArray = SArray<Complex64,DIMS...>;
    template<size_t ...DIMS> using C128SArray = SArray<Complex128,DIMS...>;


    //define some numeric arrays based on a dynamic array
    typedef NumArray<U8DArray> NU8DArray;
    typedef NumArray<I8DArray> NI8DArray;
    typedef NumArray<U16DArray> NU16DArray;
    typedef NumArray<I16DArray> NI16DArray;
    typedef NumArray<U32DArray> NU32DArray;
    typedef NumArray<I32DArray> NI32DArray;
    typedef NumArray<U64DArray> NU64DArray;
    typedef NumArray<I64DArray> NI64DArray;
    
    typedef NumArray<F32DArray> NF32DArray;
    typedef NumArray<F64DArray> NF64DArray;
    typedef NumArray<F128DArray> NF128DArray;
    
    typedef NumArray<C32DArray> NC32DArray;
    typedef NumArray<C64DArray> NC64DArray;
    typedef NumArray<C128DArray> NC128DArray;

    //define some numeric array templates based on static arrays
    template<size_t ...DIMS> using NU8SArray = NumArray<U8SArray<DIMS...> >;
    template<size_t ...DIMS> using NI8SArray = NumArray<I8SArray<DIMS...> >;
    template<size_t ...DIMS> using NU16SArray = NumArray<U16SArray<DIMS...> >;
    template<size_t ...DIMS> using NI16SArray = NumArray<I16SArray<DIMS...> >;
    template<size_t ...DIMS> using NU32SArray = NumArray<U32SArray<DIMS...> >;
    template<size_t ...DIMS> using NI32SArray = NumArray<I32SArray<DIMS...> >;
    template<size_t ...DIMS> using NU64SArray = NumArray<U64SArray<DIMS...> >;
    template<size_t ...DIMS> using NI64SArray = NumArray<I64SArray<DIMS...> >;

    template<size_t ...DIMS> using NF32SArray = NumArray<F32SArray<DIMS...> >;
    template<size_t ...DIMS> using NF64SArray = NumArray<F64SARray<DIMS...> >;
    template<size_t ...DIMS> using NF128SArray = NumArray<F128SArray<DIMS...> >;

    template<size_t ...DIMS> using NC32SArray = NumArray<C32SArray<DIMS...> >;
    template<size_t ...DIMS> using NC64SArray = NumArray<C64SArray<DIMS...> >;
    template<size_t ...DIMS> using NC128SArray = NumArray<C128SArray<DIMS...> >;

    //shape type
    typedef std::vector<size_t> shape_t;

//end of namespace
}
}


#endif
