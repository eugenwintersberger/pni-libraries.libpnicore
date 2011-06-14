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

	static const size_t ByteSize = sizeof(T);
	static const bool isSigned = false;

	bool isNegative(const T &v){
		return false;
	}

	T getZeroElement(){
		return 0;
	}
};

template<> class PNITypeInfo<Int8>{
public:
	typedef Int8 Type;
	static const PNITypeID TypeID = INT8;
	static const size_t ByteSize = sizeof(Int8);
	static const bool isSigned = true;

};

template<> class PNITypeInfo<UInt8>{
public:
	typedef UInt8 Type;
	static const PNITypeID TypeID = UINT8;
	static const size_t ByteSize = sizeof(UInt8);
	static const bool isSigned = false;
};

template<> class PNITypeInfo<Int16>{
public:
	typedef Int16 Type;
	static const PNITypeID TypeID = INT16;
	static const size_t ByteSize = sizeof(Int16);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<UInt16>{
public:
	typedef UInt16 Type;
	static const PNITypeID TypeID = UINT16;
	static const size_t ByteSize = sizeof(UInt16);
	static const bool isSigned = false;
};

template<> class PNITypeInfo<Int32>{
public:
	typedef Int32 Type;
	static const PNITypeID TypeID = INT32;
	static const size_t ByteSize = sizeof(Int32);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<UInt32>{
public:
	typedef UInt32 Type;
	static const PNITypeID TypeID = UINT32;
	static const size_t ByteSize = sizeof(UInt32);
	static const bool isSigned = false;
};

template<> class PNITypeInfo<Int64>{
public:
	typedef Int64 Type;
	static const PNITypeID TypeID = INT64;
	static const size_t ByteSize = sizeof(Int64);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<UInt64>{
public:
	typedef UInt64 Type;
	static const PNITypeID TypeID = UINT64;
	static const size_t ByteSize = sizeof(UInt64);
	static const bool isSigned = false;
};

template<> class PNITypeInfo<Float32>{
public:
	typedef Float32 Type;
	static const PNITypeID TypeID = FLOAT32;
	static const size_t ByteSize = sizeof(Float32);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<Float64>{
public:
	typedef Float64 Type;
	static const PNITypeID TypeID = FLOAT64;
	static const size_t ByteSize = sizeof(Float64);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<Float128>{
public:
	typedef Float128 Type;
	static const PNITypeID TypeID = FLOAT128;
	static const size_t ByteSize = sizeof(Float128);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<Complex32>{
public:
	typedef Complex32 Type;
	static const PNITypeID TypeID = COMPLEX32;
	static const size_t ByteSize = sizeof(Complex32);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<Complex64>{
public:
	typedef Complex64 Type;
	static const PNITypeID TypeID = COMPLEX64;
	static const size_t ByteSize = sizeof(Complex64);
	static const bool isSigned = true;
};

template<> class PNITypeInfo<Complex128>{
public:
	typedef Complex128 Type;
	static const PNITypeID TypeID = COMPLEX128;
	static const size_t ByteSize = sizeof(Complex128);
	static const bool isSigned = true;
};

//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
