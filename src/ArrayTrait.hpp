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
 * This trait should determine the return type of special array operations.
 *
 * Created on: Jun 3, 2011
 *     Author: Eugen Wintersberger
 *
 */


#pragma once

#include "Types.hpp"

namespace pni{
namespace utils{

    /*!
    \ingroup type_classes
    \brief template for Array operation return types

    This particular template is used to determine the return type of
    accumulative array operations as a function of the array's element type.
    This should handle the problem that for very "small" data types like 8Bit
    integer values accumulative operations over large arrays most probably would
    lead to overflows.  Several specializations of this template should avoid
    this problem.  In the default case the return type of the accululative
    operations is the same as that of the array's element.
    */
    template<typename T> class ArrayType
    {
        public:
            //! data type for accumulative operations
            typedef T Type; 
    };

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Int8>
    {
        public:
            //! result type for Int8 array operations
            typedef Int64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Int16>
    {
        public:
            //! result type for Int16 array operations
            typedef Int64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Int32>
    {
        public:
            //! result type for Int32 array operations
            typedef Int64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Int64>
    {
        public:
            //! result type for Int64 array operations
            typedef Int64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<UInt8>
    {
        public:
            //! result type for UInt8 array operations
            typedef UInt64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<UInt16>
    {
        public:
            //! result type for UInt16 array operations
            typedef UInt64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<UInt32>
    {
        public:
            //! result type for UInt32 array operations
            typedef UInt64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<UInt64>
    {
        public:
            //! result type for UInt64 array operations
            typedef UInt64 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Float32>
    {
        public:
            //! result type for Float32 array operations
            typedef Float128 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Float64>
    {
        public:
            //! result type for Float64 array operations
            typedef Float128 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Float128>
    {
        public:
            //! result type for Float128 point numbers
            typedef Float128 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Complex32>
    {
        public:
            //! result type for Complex32 array operations
            typedef Complex128 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Complex64>
    {
        public:
            //! result type for Complex64 array operations
            typedef Complex128 Type; 
    };
    //! \endcond NO_API_DOC

    //-------------------------------------------------------------------------
    //! \cond NO_API_DOC
    template<> class ArrayType<Complex128>
    {
        public:
            //! result type for Complex128 array operations
            typedef Complex128 Type; 
    };
    //! \endcond NO_API_DOC

}
}
