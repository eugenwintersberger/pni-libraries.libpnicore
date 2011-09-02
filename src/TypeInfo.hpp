/*
 * ArrayElementType.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef __TYPEINFO_HPP__
#define __TYPEINFO_HPP

#include <limits>

#include "PNITypes.hpp"

namespace pni{
namespace utils{

//! \ingroup Data-objects
//! \brief type information class

//! class that describes a PNI type as defined in PNITypes.hpp.
//! This template is used to obtain information about types in other
//! classes like arrays and scalars.
template<typename T> class TypeInfo{
public:

	static size_t getSize(){
		return sizeof(T);
	}

	//! return minimum value of the type
	static T getMin(){
		return std::numeric_limits<T>::min();
	}

	//! return maximum value of the type
	static T getMax(){
		return std::numeric_limits<T>::max();
	}

	static bool isSigned(){
		return std::numeric_limits<T>::is_signed;
	}

	static bool isComplex(){
		return false;
	}

	static bool isInteger(){
		return std::numeric_limits<T>::is_integer;
	}


};


//! \ingroup Data-objects
//! \brief PNITypes specialization for 32Bit IEEE floating point complex type
template<> class TypeInfo<Complex32>{
public:

	static size_t getSize(){
		return sizeof(Complex32);
	}

	//! return the minimum value of the Complex32 type
	static Complex32 getMin(){
		return Complex32(std::numeric_limits<Float32>::min(),
				         std::numeric_limits<Float32>::min());
	}

	//! return the maximum value of the Complex32 type
	static Complex32 getMax(){
		return Complex32(std::numeric_limits<Float32>::max(),
				         std::numeric_limits<Float32>::max());
	}

	static bool isSigned(){
		return true;
	}

	static bool isComplex(){
		return true;
	}

	static bool isInteger(){
		return false;
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit IEEE floating point complex type
template<> class TypeInfo<Complex64>{
public:

	static size_t getSize() {
		return sizeof(Complex64);
	}

	//! return the minimum value of the Complex64 type
	static Complex64 getMin(){
		return Complex64(std::numeric_limits<Float64>::min(),
				         std::numeric_limits<Float64>::min());
	}

	//! return the maximum value of the Complex64 type
	static Complex64 getMax(){
		return Complex64(std::numeric_limits<Float64>::max(),
				         std::numeric_limits<Float64>::max());
	}

	static bool isSigned() {
		return true;
	}

	static bool isComplex(){
		return true;
	}

	static bool isInteger(){
		return false;
	}
};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 128Bit IEEE floating point complex type
template<> class TypeInfo<Complex128>{
public:

	static size_t getSize(){
		return sizeof(Complex128);
	}

	//! return the minimum value of the Complex128 type
	static Complex128 getMin(){
		return Complex128(std::numeric_limits<Float128>::min(),
				          std::numeric_limits<Float128>::min());
	}

	//! return the maximum value of the Complex128 type
	static Complex128 getMax(){
		return Complex128(std::numeric_limits<Float128>::max(),
				          std::numeric_limits<Float128>::max());
	}

	static bool isSigned(){
		return true;
	}

	static bool isComplex(){
		return true;
	}

	static bool isInteger(){
		return false;
	}
};


//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
