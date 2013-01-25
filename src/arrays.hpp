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
 * Created on: Aug 5, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <vector>
#include "DArray.hpp"
#include "SArray.hpp"
#include "NumArray.hpp"
#include "types.hpp"
#include "Slice.hpp"


namespace pni{
namespace core{

    /*!
    \addtogroup multidim_array_classes
    @{
    */
    typedef DArray<uint8> U8DArray; //!< 8Bit unsigned integer dynamic array
    typedef DArray<int8>  I8DArray; //!< 8Bit signed integer dynamic array
    typedef DArray<uint16> U16DArray; //!< 16Bit unsigned integer dynamic array
    typedef DArray<int16>  I16DArray; //!< 16Bit signed integer dynamic array
    typedef DArray<uint32> U32DArray; //!< 32Bit unsigned integer dynamic array
    typedef DArray<int32>  I32DArray; //!< 32Bit signed integer dynamic array
    typedef DArray<uint64> U64DArray; //!< 64Bit unsigned integer dynamic array
    typedef DArray<int64>  I64DArray; //!< 64Bit signed integer dynamic array

    //! 32Bit IEEE floating point dynamic array
    typedef DArray<float32> F32DArray; 
    //! 64Bit IEEE floating point dynamic array
    typedef DArray<float64> F64DArray;
    //! 128Bit IEEE floating point dynamic array
    typedef DArray<float128> F128DArray;

    //! 32Bit IEEE complex floating point dynamic array
    typedef DArray<complex32> C32DArray;
    //! 64Bit IEEE complex floating point dynamic array
    typedef DArray<complex64> C64DArray;
    //! 128Bit IEEE complex floating point dynamic array
    typedef DArray<complex128> C128DArray;
    /*! @}*/

    //define some static arrays
#ifndef NOTMPALIAS
    template<size_t ...DIMS> using U8SArray = SArray<uint8,DIMS...>;
    template<size_t ...DIMS> using I8SArray = SArray<int8,DIMS...>;
    template<size_t ...DIMS> using U16SArray = SArray<uint16,DIMS...>;
    template<size_t ...DIMS> using I16SArray = SArray<int16,DIMS...>;
    template<size_t ...DIMS> using U32SArray = SArray<uint32,DIMS...>;
    template<size_t ...DIMS> using I32SArray = SArray<int32,DIMS...>;
    template<size_t ...DIMS> using U64SArray = SArray<uint64,DIMS...>;
    template<size_t ...DIMS> using I64SArray = SArray<int64,DIMS...>;

    template<size_t ...DIMS> using F32SArray = SArray<float32,DIMS...>;
    template<size_t ...DIMS> using F64SArray = SArray<float64,DIMS...>;
    template<size_t ...DIMS> using F128SArray = SArray<float128,DIMS...>;
    
    template<size_t ...DIMS> using C32SArray = SArray<complex32,DIMS...>;
    template<size_t ...DIMS> using C64SArray = SArray<complex64,DIMS...>;
    template<size_t ...DIMS> using C128SArray = SArray<complex128,DIMS...>;
#endif

    /*! \addtogroup numeric_array_classes
      @{
     */
    //define some numeric arrays based on a dynamic array
    //! 8Bit unsinged integer numeric array with a dynamic container array
    typedef NumArray<U8DArray> NU8DArray;
    //! 8Bit signed integer numeric array with a dynamic container array
    typedef NumArray<I8DArray> NI8DArray;
    //! 16Bit unsigned integer numeric array with a dynamic container array
    typedef NumArray<U16DArray> NU16DArray;
    //! 16Bit signed integer numeric array with a dynamic container array
    typedef NumArray<I16DArray> NI16DArray;
    //! 32Bit unsigned integer numeric array with a dynamic container array
    typedef NumArray<U32DArray> NU32DArray;
    //! 32Bit singed integer numeric array with a dynamic container array
    typedef NumArray<I32DArray> NI32DArray;
    //! 64Bit unsigned integer numeric array with a dynamic container array
    typedef NumArray<U64DArray> NU64DArray;
    //! 64Bit signed integer numeric array with a dynamic container array
    typedef NumArray<I64DArray> NI64DArray;
   
    //! 32Bit IEEE floating point numeric array with a dynamic container type
    typedef NumArray<F32DArray> NF32DArray;
    //! 64Bit IEEE floating point numeric array with a dynamic container type
    typedef NumArray<F64DArray> NF64DArray;
    //! 128Bit IEEE floating point numeric array with a dynamic container type
    typedef NumArray<F128DArray> NF128DArray;
   
    //! 32Bit IEEE complex floating point numeric array with a dynamic container type
    typedef NumArray<C32DArray> NC32DArray;
    //! 64Bit IEEE complex floating point numeric array with a dynamic container type
    typedef NumArray<C64DArray> NC64DArray;
    //! 128Bit IEEE complex floating point numeric array with a dynamic container type
    typedef NumArray<C128DArray> NC128DArray;
    /*! @} */

    //define some numeric array templates based on static arrays
#ifndef NOTMPALIAS
    template<size_t ...DIMS> using NU8SArray = NumArray<U8SArray<DIMS...> >;
    template<size_t ...DIMS> using NI8SArray = NumArray<I8SArray<DIMS...> >;
    template<size_t ...DIMS> using NU16SArray = NumArray<U16SArray<DIMS...> >;
    template<size_t ...DIMS> using NI16SArray = NumArray<I16SArray<DIMS...> >;
    template<size_t ...DIMS> using NU32SArray = NumArray<U32SArray<DIMS...> >;
    template<size_t ...DIMS> using NI32SArray = NumArray<I32SArray<DIMS...> >;
    template<size_t ...DIMS> using NU64SArray = NumArray<U64SArray<DIMS...> >;
    template<size_t ...DIMS> using NI64SArray = NumArray<I64SArray<DIMS...> >;

    template<size_t ...DIMS> using NF32SArray = NumArray<F32SArray<DIMS...> >;
    template<size_t ...DIMS> using NF64SArray = NumArray<F64SArray<DIMS...> >;
    template<size_t ...DIMS> using NF128SArray = NumArray<F128SArray<DIMS...> >;

    template<size_t ...DIMS> using NC32SArray = NumArray<C32SArray<DIMS...> >;
    template<size_t ...DIMS> using NC64SArray = NumArray<C64SArray<DIMS...> >;
    template<size_t ...DIMS> using NC128SArray = NumArray<C128SArray<DIMS...> >;
#endif


//end of namespace
}
}
