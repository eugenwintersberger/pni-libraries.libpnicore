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
#include "darray.hpp"
#include "sarray.hpp"
#include "numarray.hpp"
#include "types.hpp"
#include "slice.hpp"


namespace pni{
namespace core{

    /*!
    \addtogroup multidim_array_classes
    @{
    */
    typedef darray<uint8> u8darray; //!< 8Bit unsigned integer dynamic array
    typedef darray<int8>  i8darray; //!< 8Bit signed integer dynamic array
    typedef darray<uint16> u16darray; //!< 16Bit unsigned integer dynamic array
    typedef darray<int16>  i16darray; //!< 16Bit signed integer dynamic array
    typedef darray<uint32> u32darray; //!< 32Bit unsigned integer dynamic array
    typedef darray<int32>  i32darray; //!< 32Bit signed integer dynamic array
    typedef darray<uint64> u64darray; //!< 64Bit unsigned integer dynamic array
    typedef darray<int64>  i64darray; //!< 64Bit signed integer dynamic array

    //! 32Bit IEEE floating point dynamic array
    typedef darray<float32> f32darray; 
    //! 64Bit IEEE floating oint dynamic array
    typedef darray<float64> f64darray;
    //! 128Bit IEEE floating point dynamic array
    typedef darray<float128> f128darray;

    //! 32Bit IEEE complex floating point dynamic array
    typedef darray<complex32> c32darray;
    //! 64Bit IEEE complex floating point dynamic array
    typedef darray<complex64> c64darray;
    //! 128Bit IEEE complex floating point dynamic array
    typedef darray<complex128> c128darray;
    /*! @}*/

    //define some static arrays
#ifndef NOTMPALIAS
    template<size_t ...DIMS> using u8sarray = sarray<uint8,DIMS...>;
    template<size_t ...DIMS> using i8sarray = sarray<int8,DIMS...>;
    template<size_t ...DIMS> using u16sarray = sarray<uint16,DIMS...>;
    template<size_t ...DIMS> using i16sarray = sarray<int16,DIMS...>;
    template<size_t ...DIMS> using u32sarray = sarray<uint32,DIMS...>;
    template<size_t ...DIMS> using i32sarray = sarray<int32,DIMS...>;
    template<size_t ...DIMS> using u64sarray = sarray<uint64,DIMS...>;
    template<size_t ...DIMS> using i64sarray = sarray<int64,DIMS...>;

    template<size_t ...DIMS> using f32sarray = sarray<float32,DIMS...>;
    template<size_t ...DIMS> using f64sarray = sarray<float64,DIMS...>;
    template<size_t ...DIMS> using f128sarray = sarray<float128,DIMS...>;
    
    template<size_t ...DIMS> using c32sarray = sarray<complex32,DIMS...>;
    template<size_t ...DIMS> using c64sarray = sarray<complex64,DIMS...>;
    template<size_t ...DIMS> using c128sarray = sarray<complex128,DIMS...>;
#endif

    /*! \addtogroup numeric_array_classes
      @{
     */
    //define some numeric arrays based on a dynamic array
    //! 8Bit unsinged integer numeric array with a dynamic container array
    typedef numarray<u8darray> nu8darray;
    //! 8Bit signed integer numeric array with a dynamic container array
    typedef numarray<i8darray> ni8darray;
    //! 16Bit unsigned integer numeric array with a dynamic container array
    typedef numarray<u16darray> nu16darray;
    //! 16Bit signed integer numeric array with a dynamic container array
    typedef numarray<i16darray> ni16darray;
    //! 32Bit unsigned integer numeric array with a dynamic container array
    typedef numarray<u32darray> nu32darray;
    //! 32Bit singed integer numeric array with a dynamic container array
    typedef numarray<i32darray> ni32darray;
    //! 64Bit unsigned integer numeric array with a dynamic container array
    typedef numarray<u64darray> nu64darray;
    //! 64Bit signed integer numeric array with a dynamic container array
    typedef numarray<i64darray> ni64darray;
   
    //! 32Bit IEEE floating point numeric array with a dynamic container type
    typedef numarray<f32darray> nf32darray;
    //! 64Bit IEEE floating point numeric array with a dynamic container type
    typedef numarray<f64darray> nf64darray;
    //! 128Bit IEEE floating point numeric array with a dynamic container type
    typedef numarray<f128darray> nf128darray;
   
    //! 32Bit IEEE complex floating point numeric array with a dynamic container type
    typedef numarray<c32darray> nc32darray;
    //! 64Bit IEEE complex floating point numeric array with a dynamic container type
    typedef numarray<c64darray> nc64darray;
    //! 128Bit IEEE complex floating point numeric array with a dynamic container type
    typedef numarray<c128darray> nc128darray;
    /*! @} */

    //define some numeric array templates based on static arrays
#ifndef NOTMPALIAS
    template<size_t ...DIMS> using nu8sarray = numarray<u8sarray<DIMS...> >;
    template<size_t ...DIMS> using ni8sarray = numarray<i8sarray<DIMS...> >;
    template<size_t ...DIMS> using nu16sarray = numarray<u16sarray<DIMS...> >;
    template<size_t ...DIMS> using ni16sarray = numarray<i16sarray<DIMS...> >;
    template<size_t ...DIMS> using nu32sarray = numarray<u32sarray<DIMS...> >;
    template<size_t ...DIMS> using ni32sarray = numarray<i32sarray<DIMS...> >;
    template<size_t ...DIMS> using nu64sarray = numarray<u64sarray<DIMS...> >;
    template<size_t ...DIMS> using ni64sarray = numarray<i64sarray<DIMS...> >;

    template<size_t ...DIMS> using nf32sarray = numarray<f32sarray<DIMS...> >;
    template<size_t ...DIMS> using nf64sarray = numarray<f64sarray<DIMS...> >;
    template<size_t ...DIMS> using nf128sarray = numarray<f128sarray<DIMS...> >;

    template<size_t ...DIMS> using nc32sarray = numarray<c32sarray<DIMS...> >;
    template<size_t ...DIMS> using nc64sarray = numarray<c64sarray<DIMS...> >;
    template<size_t ...DIMS> using nc128sarray = numarray<c128sarray<DIMS...> >;
#endif


//end of namespace
}
}
