/*
 * ArrayTrait.hpp
 *
 *  Created on: Jun 3, 2011
 *      Author: eugen
 */

#ifndef ARRAYTRAIT_HPP_
#define ARRAYTRAIT_HPP_

#include "PNITypes.hpp"

namespace pni{
namespace utils{


//! template for Array operation return types

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
	typedef T Type;
};


//! template specialization for 8 Bit signed integer
template<> class ArrayType<Int8>{
public:
	typedef Int64 Type;
};

//! template specialization for 16 Byte signed integer
template<> class ArrayType<Int16>{
public:
	typedef Int64 Type;
};

//! template specialization for 32 Byte signed integer
template<> class ArrayType<Int32>{
public:
	typedef Int64 Type;
};

//! template specialization for 64 Byte signed integer
template<> class ArrayType<Int64>{
public:
	typedef Int64 Type;
};

template<> class ArrayType<UInt8>{
public:
	typedef UInt64 Type;
};

template<> class ArrayType<UInt16>{
public:
	typedef UInt64 Type;
};

template<> class ArrayType<UInt32>{
public:
	typedef UInt64 Type;
};

template<> class ArrayType<UInt64>{
public:
	typedef UInt64 Type;
};

template<> class ArrayType<Float32>{
public:
	typedef Float128 Type;
};

template<> class ArrayType<Float64>{
public:
	typedef Float128 Type;
};

template<> class ArrayType<Float128>{
public:
	typedef Float128 Type;
};

template<> class ArrayType<Complex32>{
public:
	typedef Complex128 Type;
};

template<> class ArrayType<Complex64>{
public:
	typedef Complex128 Type;
};

template<> class ArrayType<Complex128>{
public:
	typedef Complex128 Type;
};

}
}


#endif /* ARRAYTRAIT_HPP_ */
