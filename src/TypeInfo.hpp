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

	template<typename U> static bool isCompatibleForAssignment(const U &b);
	template<typename U> static bool isCompatibleForDivision(const T &a,const U &b);

};

//checks if a variable of type U can be assigned to one of type T
template<typename T>
template<typename U>
bool TypeInfo<T>::isCompatibleForAssignment(const U &b){
	EXCEPTION_SETUP("template<typename T,typename U> bool isCompatibleForAssignment(const T &a,const U &b)");

	//one cannot assign a complex number to a non-complex float number
	if((!TypeInfo<T>::isComplex())&&(TypeInfo<U>::isComplex())){
		EXCEPTION_INIT(TypeError,"Cannot convert a complex scalar to a non complex type!");
		EXCEPTION_THROW();
	}

	//one cannot assign securely assign a float number to an integer
	if((TypeInfo<T>::isInteger())&&(!TypeInfo<U>::isInteger())){
		EXCEPTION_INIT(TypeError,"Cannot convert a float value to an integer!");
		EXCEPTION_THROW();
	}

	//in general we can assign values only to numbers
	if(TypeInfo<T>::getSize() < TypeInfo<U>::getSize()){
		EXCEPTION_INIT(SizeMissmatchError,"Cannot convert scalar to a smaller type!");
		EXCEPTION_THROW();
	}

	//if we made it until here we have to check for sign
	if((!TypeInfo<T>::isSigned())&&(TypeInfo<U>::isSigned())){
		//we have to check the size of the
		if(b<0){
			EXCEPTION_INIT(RangeError,"Cannot assign a negative number to an unsigned type!");
			EXCEPTION_THROW();
		}
	}

	return true;
}

template<typename T>
template<typename U> bool TypeInfo<T>::isCompatibleForDivision(const T &a,const U &b){
	EXCEPTION_SETUP("template<typename T> template<typename U> bool TypeInfo<T>::isCompatibleForDivision(const T &a,const U &b)");

	//you cannot divide a non-complex number by a complex one
	if((!isComplex())&&(TypeInfo<U>::isComplex())){
		EXCEPTION_INIT(TypeError,"Cannot divide a non-complex number by a complex number!");
		EXCEPTION_THROW();
	}

	//what if we want to divide an integer by a non-integer
	if(isInteger()&&(!TypeInfo<U>::isInteger())){
		EXCEPTION_INIT(TypeError,"Cannot divide an integer by a float!");
		EXCEPTION_THROW();
	}

}



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

	template<typename U> static bool isCompatibleForAssignment(const U &b);
};

//some specialization for complex numbers
template<typename U>
bool TypeInfo<Complex32>::isCompatibleForAssignment(const U &b){
	EXCEPTION_SETUP("template<typename U> bool isCompatibleForAssignment<Complex32,U>(const T &a,const U &b)");

	//in general we can assign values only to numbers
	if(getSize() < TypeInfo<U>::getSize()){
		EXCEPTION_INIT(SizeMissmatchError,"Cannot convert scalar to a smaller type!");
		EXCEPTION_THROW();
	}

	return true;
}


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

	template<typename U> bool isCompatibleForAssignment(const U &v);
};

template<typename U>
bool TypeInfo<Complex64>::isCompatibleForAssignment(const U &b){
	EXCEPTION_SETUP("template<typename U> bool isCompatibleForAssignment<Complex32,U>(const T &a,const U &b)");

	//in general we can assign values only to numbers
	if(getSize() < TypeInfo<U>::getSize()){
		EXCEPTION_INIT(SizeMissmatchError,"Cannot convert scalar to a smaller type!");
		EXCEPTION_THROW();
	}

	return true;
}

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

	template<typename U> static bool isCompatibleForAssignment(const U &b);
};

template<typename U>
bool TypeInfo<Complex128>::isCompatibleForAssignment(const U &b){
	EXCEPTION_SETUP("template<typename U> bool isCompatibleForAssignment<Complex32,U>(const T &a,const U &b)");

	//in general we can assign values only to numbers
	if(getSize() < TypeInfo<U>::getSize()){
		EXCEPTION_INIT(SizeMissmatchError,"Cannot convert scalar to a smaller type!");
		EXCEPTION_THROW();
	}

	return true;
}



//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
