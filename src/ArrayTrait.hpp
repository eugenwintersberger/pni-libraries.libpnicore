/*
 * Declaration of the ArrayTrait<T> template
 *
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


#ifndef ARRAYTRAIT_HPP_
#define ARRAYTRAIT_HPP_

#include "PNITypes.hpp"

namespace pni{
namespace utils{

//! \addtogroup Data-objects
//! @{

//! \brief template for Array operation return types

//! This particular template is used to determine the return type of
//! accumulative array operations as a function of the array's element
//! type. This should handle the problem that for very "small" data types
//! like 8Bit integer values accumulative operations over large arrays
//! most probably would lead to overflows.
//! Several specializations of this template should avoid this problem.
//! In the default case the return type of the accululative operations
//! is the same as that of the array's element.
template<typename T> class ArrayType{
public:
	typedef T Type; //!< data type for accumulative operations
};

//! template specialization for 8 Bit signed integer
template<> class ArrayType<Int8>{
public:
	typedef Int64 Type; //!< result type for Int8 array operations
};

//! template specialization for 16 Bit signed integer
template<> class ArrayType<Int16>{
public:
	typedef Int64 Type; //!< result type for Int16 array operations
};

//! template specialization for 32 Bit signed integer
template<> class ArrayType<Int32>{
public:
	typedef Int64 Type; //!< result type for Int32 array operations
};

//! template specialization for 64 Bit signed integer
template<> class ArrayType<Int64>{
public:
	typedef Int64 Type; //!< result type for Int64 array operations
};

//! template specialization for 8Bit unsigned integer
template<> class ArrayType<UInt8>{
public:
	typedef UInt64 Type; //!< result type for UInt8 array operations
};

//! template specialization for 16Bit unsigned integer
template<> class ArrayType<UInt16>{
public:
	typedef UInt64 Type; //!< result type for UInt16 array operations
};

//! template specialization for 32Bit unsigned integer
template<> class ArrayType<UInt32>{
public:
	typedef UInt64 Type; //!< result type for UInt32 array operations
};

//! template specialization for 64Bit unsigned integer
template<> class ArrayType<UInt64>{
public:
	typedef UInt64 Type; //!< result type for UInt64 array operations
};

//! template specialization for 32Bit IEEE floating point numbers
template<> class ArrayType<Float32>{
public:
	typedef Float128 Type; //!< result type for Float32 array operations
};

//! template specialization for 64Bit IEEE floating point numbers
template<> class ArrayType<Float64>{
public:
	typedef Float128 Type; //!< result type for Float64 array operations
};

//! template specialization for 128Bit IEEE floating point numbers
template<> class ArrayType<Float128>{
public:
	typedef Float128 Type; //!< result type for Float128 point numbers
};

//! template specialization for 32Bit IEEE complex floating point numbers
template<> class ArrayType<Complex32>{
public:
	typedef Complex128 Type; //!< result type for Complex32 array operations
};

//! template specialization for 64Bit IEEE complex floating point numbers
template<> class ArrayType<Complex64>{
public:
	typedef Complex128 Type; //!< result type for Complex64 array operations
};

//! template specialization for 128Bit IEEE complex floating point numbers
template<> class ArrayType<Complex128>{
public:
	typedef Complex128 Type; //!< result type for Complex128 array operations
};

//! @}
}
}


#endif /* ARRAYTRAIT_HPP_ */
