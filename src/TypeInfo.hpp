/*
 * ArrayElementType.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef __TYPEINFO_HPP__
#define __TYPEINFO_HPP

#include <limits>

#include "PNITypes.hpp"
#include "Exceptions.hpp"

namespace pni{
namespace utils{

//! \ingroup Data-objects
//! \brief type information class

//! class that describes a PNI type as defined in PNITypes.hpp.
//! This template is used to obtain information about types in other
//! classes like arrays and scalars.
template<typename T> class TypeInfo{
public:
	typedef T Type;
	typedef T BaseType;

	static size_t getSize(){
		return sizeof(T);
	}

	static bool isNegative(T value){
		if (value < 0) return true;
		return false;
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

	typedef Complex32 Type;
	typedef Float32 BaseType;

	static bool isNegative(Complex32 value){
		return false;
	}

	static size_t getSize(){
		return sizeof(Complex32);
	}

	//! return the minimum value of the Complex32 type
	static Float32 getMin(){
		return std::numeric_limits<Float32>::min();
	}

	//! return the maximum value of the Complex32 type
	static Float32 getMax(){
		return std::numeric_limits<Float32>::max();
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

	typedef Complex64 Type;
	typedef Float64 BaseType;

	static size_t getSize() {
		return sizeof(Complex64);
	}

	static bool isNegative(Complex64 value){
		return false;
	}

	//! return the minimum value of the Complex64 type
	static Float64 getMin(){
		return std::numeric_limits<Float64>::min();
	}

	//! return the maximum value of the Complex64 type
	static Float64 getMax(){
		return std::numeric_limits<Float64>::max();
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
	typedef Complex128 Type;
	typedef Float128 BaseType;

	static size_t getSize(){
		return sizeof(Complex128);
	}

	static bool isNegative(){
		return false;
	}

	//! return the minimum value of the Complex128 type
	static Float128 getMin(){
		return std::numeric_limits<Float128>::min();
	}

	//! return the maximum value of the Complex128 type
	static Float128 getMax(){
		return std::numeric_limits<Float128>::max();
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
