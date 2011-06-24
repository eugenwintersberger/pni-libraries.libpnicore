/*
 * ArrayElementType.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef ARRAYELEMENTTYPE_HPP_
#define ARRAYELEMENTTYPE_HPP_

#include <limits>

#include "PNITypes.hpp"

namespace pni{
namespace utils{

//! \ingroup Data-objects
//! \brief type information class

//! class that describes a PNI type as defined in PNITypes.hpp.
//! This template is used to obtain information about types in other
//! classes like arrays and scalars.
template<typename T>
class PNITypeInfo{
private:
public:
	//! a type used to define objects
	typedef T Type;
	//! ID of the type
	static const PNITypeID TypeID = NONE;
	//! size of the type in bytes
	static const size_t ByteSize = sizeof(T);
	//! sign flag - tells if the type is signed
	static const bool isSigned = false;

	//! returns true if a value is negative

	//! This method is useful for types that do not provide
	//! simple mechanisms to determine the sign of a value.
	bool isNegative(const T &v){
		return false;
	}

	//! return minimum value of the type
	static T min(){
		return getZeroElement();
	}

	//! return maximum value of the type
	static T max(){
		return getZeroElement();
	}

	//! return the zero element of a type
	static T getZeroElement(){
		return 0;
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 8Bit signed integer
template<> class PNITypeInfo<Int8>{
public:
	typedef Int8 Type; //!< type
	static const PNITypeID TypeID = INT8;  //!< typecode
	static const size_t ByteSize = sizeof(Int8); //!< size in memory
	static const bool isSigned = true;    //!< type supports signed values

	//! return minimum value of the Int8 type
	static Int8 min(){
		return std::numeric_limits<Int8>::min();
	}

	//! return maximum value of the Int8 type
	static Int8 max(){
		return std::numeric_limits<Int8>::max();
	}

};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 8Bit unsigned integer
template<> class PNITypeInfo<UInt8>{
public:
	typedef UInt8 Type; //!< type
	static const PNITypeID TypeID = UINT8; //!< typecode
	static const size_t ByteSize = sizeof(UInt8); //!< size in bytes
	static const bool isSigned = false; //!< types does not support signed values

	//! return the minimum value of the UInt8 type
	static UInt8 min(){
		return std::numeric_limits<UInt8>::min();
	}

	//! return the maximum value of the UInt8 type
	static UInt8 max(){
		return std::numeric_limits<UInt8>::max();
	}

};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 16Bit signed integer
template<> class PNITypeInfo<Int16>{
public:
	typedef Int16 Type; //!< type
	static const PNITypeID TypeID = INT16; //!< typecode
	static const size_t ByteSize = sizeof(Int16); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Int16 type
	static Int16 min(){
		return std::numeric_limits<Int16>::min();
	}

	//! return the maximum value of the Int16 type
	static Int16 max(){
		return std::numeric_limits<Int16>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 16Bit unsigned integer
template<> class PNITypeInfo<UInt16>{
public:
	typedef UInt16 Type; //!< type
	static const PNITypeID TypeID = UINT16; //!< typecode
	static const size_t ByteSize = sizeof(UInt16); //!< size in bytes
	static const bool isSigned = false; //!< type does not support signed values

	//! return the minimum value of the UInt16 type
	static UInt16 min(){
		return std::numeric_limits<UInt16>::min();
	}

	//! return the maximum value of the UInt16 type
	static UInt16 max(){
		return std::numeric_limits<UInt16>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 32Bit signed integer
template<> class PNITypeInfo<Int32>{
public:
	typedef Int32 Type; //!< type
	static const PNITypeID TypeID = INT32; //!< typecode
	static const size_t ByteSize = sizeof(Int32); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Int32 type
	static Int32 min(){
		return std::numeric_limits<Int32>::min();
	}

	//! return the maximum value of the Int32 type
	static Int32 max(){
		return std::numeric_limits<Int32>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 32Bit unsigned integer
template<> class PNITypeInfo<UInt32>{
public:
	typedef UInt32 Type; //!< type
	static const PNITypeID TypeID = UINT32; //!< typecode
	static const size_t ByteSize = sizeof(UInt32); //!< size in bytes
	static const bool isSigned = false; //!< type does not support signed values

	//! return the minimum value of the UInt32 type
	static UInt32 min(){
		return std::numeric_limits<UInt32>::min();
	}

	//! return the maximum value of the UInt32 type
	static UInt32 max(){
		return std::numeric_limits<UInt32>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit signed integer
template<> class PNITypeInfo<Int64>{
public:
	typedef Int64 Type; //!< type
	static const PNITypeID TypeID = INT64; //!< typecode
	static const size_t ByteSize = sizeof(Int64); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Int64 type
	static Int64 min(){
		return std::numeric_limits<Int64>::min();
	}

	//! return the maximum value of the Int64 type
	static Int64 max(){
		return std::numeric_limits<Int64>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit unsigned integer
template<> class PNITypeInfo<UInt64>{
public:
	typedef UInt64 Type; //!< type
	static const PNITypeID TypeID = UINT64; //!< typecode
	static const size_t ByteSize = sizeof(UInt64); //!< size in bytes
	static const bool isSigned = false; //!< type does not support signed values

	//! return the minimum value of the UInt64 type
	static UInt64 min(){
		return std::numeric_limits<UInt64>::min();
	}

	//! return the maximum value of the UInt64 type
	static UInt64 max(){
		return std::numeric_limits<UInt64>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 32Bit IEEE floating point type
template<> class PNITypeInfo<Float32>{
public:
	typedef Float32 Type; //!< type
	static const PNITypeID TypeID = FLOAT32; //!< typecode
	static const size_t ByteSize = sizeof(Float32); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Float32 type
	static Float32 min(){
		return std::numeric_limits<Float32>::min();
	}

	//! return the maximum value of the Float32 type
	static Float32 max(){
		return std::numeric_limits<Float32>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit IEEE floating point type
template<> class PNITypeInfo<Float64>{
public:
	typedef Float64 Type; //!< type
	static const PNITypeID TypeID = FLOAT64; //!< typecode
	static const size_t ByteSize = sizeof(Float64); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Float64 type
	static Float64 min(){
		return std::numeric_limits<Float64>::min();
	}

	//! return the maximum value of the Float64 type
	static Float64 max(){
		return std::numeric_limits<Float64>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 128Bit IEEE floating point type
template<> class PNITypeInfo<Float128>{
public:
	typedef Float128 Type; //!< type
	static const PNITypeID TypeID = FLOAT128; //!< typecode
	static const size_t ByteSize = sizeof(Float128); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Float128 type
	static Float128 min(){
		return std::numeric_limits<Float128>::min();
	}

	//! return the maximum value of the Float128 type
	static Float128 max(){
		return std::numeric_limits<Float128>::max();
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 32Bit IEEE floating point complex type
template<> class PNITypeInfo<Complex32>{
public:
	typedef Complex32 Type; //!< type
	static const PNITypeID TypeID = COMPLEX32; //!< typecode
	static const size_t ByteSize = sizeof(Complex32); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Complex32 type
	static Complex32 min(){
		return Complex32(std::numeric_limits<Float32>::min(),
				         std::numeric_limits<Float32>::min());
	}

	//! return the maximum value of the Complex32 type
	static Complex32 max(){
		return Complex32(std::numeric_limits<Float32>::max(),
				         std::numeric_limits<Float32>::max());
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit IEEE floating point complex type
template<> class PNITypeInfo<Complex64>{
public:
	typedef Complex64 Type; //!< type
	static const PNITypeID TypeID = COMPLEX64; //!< typecode
	static const size_t ByteSize = sizeof(Complex64); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Complex64 type
	static Complex64 min(){
		return Complex64(std::numeric_limits<Float64>::min(),
				         std::numeric_limits<Float64>::min());
	}

	//! return the maximum value of the Complex64 type
	static Complex64 max(){
		return Complex64(std::numeric_limits<Float64>::max(),
				         std::numeric_limits<Float64>::max());
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 128Bit IEEE floating point complex type
template<> class PNITypeInfo<Complex128>{
public:
	typedef Complex128 Type; //!< type
	static const PNITypeID TypeID = COMPLEX128; //!< typecode
	static const size_t ByteSize = sizeof(Complex128); //!< size in bytes
	static const bool isSigned = true; //!< type supports signed values

	//! return the minimum value of the Complex128 type
	static Complex128 min(){
		return Complex128(std::numeric_limits<Float128>::min(),
				          std::numeric_limits<Float128>::min());
	}

	//! return the maximum value of the Complex128 type
	static Complex128 max(){
		return Complex128(std::numeric_limits<Float128>::max(),
				          std::numeric_limits<Float128>::max());
	}
};


//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
