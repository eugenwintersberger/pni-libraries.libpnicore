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


//some type traits neede for the array operations
template<typename T> class ArrayType{
public:
	typedef T Type;
};

template<> class ArrayType<Int8>{
public:
	typedef Int64 Type;
};

template<> class ArrayType<Int16>{
public:
	typedef Int64 Type;
};

template<> class ArrayType<Int32>{
public:
	typedef Int64 Type;
};

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
