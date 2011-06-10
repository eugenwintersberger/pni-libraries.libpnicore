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
class PNITypeInfo{
private:
public:
	typedef T Type;
	static const PNITypeID TypeID = NONE;
	static const bool isSigned = false;

	static const size_t ByteSize = 0;
	static bool isNegative(const T &v){
		return false;
	}

	static T getZeroElement() const {
		return 0;
	}
};

template<> class PNITypeInfo<Int8>{
public:
	typedef Int8 Type;
	static const PNITypeID TypeID = INT8;

};

template<> class PNITypeInfo<UInt8>{
public:
	typedef UInt8 Type;
	static const PNITypeID TypeID = UINT8;
};

template<> class PNITypeInfo<Int16>{
public:
	typedef Int16 Type;
	static const PNITypeID TypeID = INT16;
};

template<> class PNITypeInfo<UInt16>{
public:
	typedef UInt16 Type;
	static const PNITypeID TypeID = UINT16;
};

template<> class PNITypeInfo<Int32>{
public:
	typedef Int32 Type;
	static const PNITypeID TypeID = INT32;
};

template<> class PNITypeInfo<UInt32>{
public:
	typedef UInt32 Type;
	static const PNITypeID TypeID = UINT32;
};

template<> class PNITypeInfo<Int64>{
public:
	typedef Int64 Type;
	static const PNITypeID TypeID = INT64;
};

template<> class PNITypeInfo<UInt64>{
public:
	typedef UInt64 Type;
	static const PNITypeID TypeID = UINT64;
};

template<> class PNITypeInfo<Float32>{
public:
	typedef Float32 Type;
	static const PNITypeID TypeID = FLOAT32;
};

template<> class PNITypeInfo<Float64>{
public:
	typedef Float64 Type;
	static const PNITypeID TypeID = FLOAT64;
};

template<> class PNITypeInfo<Float128>{
public:
	typedef Float128 Type;
	static const PNITypeID TypeID = FLOAT128;
};

template<> class PNITypeInfo<Complex32>{
public:
	typedef Complex32 Type;
	static const PNITypeID TypeID = COMPLEX32;
};

template<> class PNITypeInfo<Complex64>{
public:
	typedef Complex64 Type;
	static const PNITypeID TypeID = COMPLEX64;
};

template<> class PNITypeInfo<Complex128>{
public:
	typedef Complex128 Type;
	static const PNITypeID TypeID = COMPLEX128;
};

//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
