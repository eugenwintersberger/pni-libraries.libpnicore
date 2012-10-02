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
/* \file */

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

    /*!
    \addtogroup multidim_array_classes
    @{
    */
    typedef DArray<UInt8> U8DArray; //!< 8Bit unsigned integer dynamic array
    typedef DArray<Int8>  I8DArray; //!< 8Bit signed integer dynamic array
    typedef DArray<UInt16> U16DArray; //!< 16Bit unsigned integer dynamic array
    typedef DArray<Int16>  I16DArray; //!< 16Bit signed integer dynamic array
    typedef DArray<UInt32> U32DArray; //!< 32Bit unsigned integer dynamic array
    typedef DArray<Int32>  I32DArray; //!< 32Bit signed integer dynamic array
    typedef DArray<UInt64> U64DArray; //!< 64Bit unsigned integer dynamic array
    typedef DArray<Int64>  I64DArray; //!< 64Bit signed integer dynamic array

    //! 32Bit IEEE floating point dynamic array
    typedef DArray<Float32> F32DArray; 
    //! 64Bit IEEE floating point dynamic array
    typedef DArray<Float64> F64DArray;
    //! 128Bit IEEE floating point dynamic array
    typedef DArray<Float128> F128DArray;

    //! 32Bit IEEE complex floating point dynamic array
    typedef DArray<Complex32> C32DArray;
    //! 64Bit IEEE complex floating point dynamic array
    typedef DArray<Complex64> C64DArray;
    //! 128Bit IEEE complex floating point dynamic array
    typedef DArray<Complex128> C128DArray;
    /*! @}*/

    //define some static arrays
#ifndef NOTMPALIAS
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

    //! standard type for array shapes
    typedef std::vector<size_t> shape_t;

//end of namespace
}
}


#endif
