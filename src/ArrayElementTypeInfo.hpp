/*
 * ArrayElementType.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef ARRAYELEMENTTYPE_HPP_
#define ARRAYELEMENTTYPE_HPP_

#include "PNITypes.hpp"

namespace pni{
namespace utils{


template<typename T>
class ArrayElementTypeInfo{
private:
public:
	typedef T ElementType;
	static const PNITypeID ElementTypeID = NONE;
};

template<> class ArrayElementTypeInfo<Int8>{
public:
	typedef Int8 ElementType;
	static const PNITypeID ElementTypeID = INT8;
};

template<> class ArrayElementTypeInfo<UInt8>{
public:
	typedef UInt8 ElementType;
	static const PNITypeID ElementTypeID = UINT8;
};

template<> class ArrayElementTypeInfo<Int16>{
public:
	typedef Int16 ElementType;
	static const PNITypeID ElementTypeID = INT16;
};

template<> class ArrayElementTypeInfo<UInt16>{
public:
	typedef UInt16 ElementType;
	static const PNITypeID ElementTypeID = UINT16;
};

template<> class ArrayElementTypeInfo<Int32>{
public:
	typedef Int32 ElementType;
	static const PNITypeID ElementTypeID = INT32;
};

template<> class ArrayElementTypeInfo<UInt32>{
public:
	typedef UInt32 ElementType;
	static const PNITypeID ElementTypeID = UINT32;
};

template<> class ArrayElementTypeInfo<Int64>{
public:
	typedef Int64 ElementType;
	static const PNITypeID ElementTypeID = INT64;
};

template<> class ArrayElementTypeInfo<UInt64>{
public:
	typedef UInt64 ElementType;
	static const PNITypeID ElementTypeID = UINT64;
};

template<> class ArrayElementTypeInfo<Float32>{
public:
	typedef Float32 ElementType;
	static const PNITypeID ElementTypeID = FLOAT32;
};

template<> class ArrayElementTypeInfo<Float64>{
public:
	typedef Float64 ElementType;
	static const PNITypeID ElementTypeID = FLOAT64;
};

template<> class ArrayElementTypeInfo<Float128>{
public:
	typedef Float128 ElementType;
	static const PNITypeID ElementTypeID = FLOAT128;
};

template<> class ArrayElementTypeInfo<Complex32>{
public:
	typedef Complex32 ElementType;
	static const PNITypeID ElementTypeID = COMPLEX32;
};

template<> class ArrayElementTypeInfo<Complex64>{
public:
	typedef Complex64 ElementType;
	static const PNITypeID ElementTypeID = COMPLEX64;
};

template<> class ArrayElementTypeInfo<Complex128>{
public:
	typedef Complex128 ElementType;
	static const PNITypeID ElementTypeID = COMPLEX128;
};

//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
