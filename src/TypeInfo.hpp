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

	template<typename U> static void isCompatibleForAssignment(const T &a,const U &b);

};

//checks if a variable of type U can be assigned to one of type T
template<typename T>
template<typename U>
void TypeInfo<T>::isCompatibleForAssignment(const T& a,const U &b){
	EXCEPTION_SETUP("template<typename T,typename U> bool isCompatibleForAssignment(const T &a,const U &b)");
	static bool target_is_int = TypeInfo<T>::isInteger();
	static bool target_is_complx = TypeInfo<T>::isComplex();
	static bool source_is_int = TypeInfo<U>::isInteger();
	static bool source_is_complx = TypeInfo<U>::isComplex();

	if(target_is_int){
		//in the case the target is an integer type

		//ASSIGNMENT RULE 1 and 2 according to manual
		if(!source_is_int){
			//if the source is not an integer we (float or complex we can break here)
			EXCEPTION_INIT(TypeError,"Cannot assign a float or complex to an integer type!");
			EXCEPTION_THROW();
		}else{
			//the source is an integer value - now things are easy - we only
			//have to check the bounds. By doing so we implicitely check the size
			//now we have to check only ranges
			if((b<TypeInfo<T>::getMin())||(b>TypeInfo<T>::getMax())){
				EXCEPTION_INIT(RangeError,"Assigned variable exceeds type bounds of the target!");
				EXCEPTION_THROW();
			}
		}
	}else{
		//the target is a float or complex
		if(source_is_complx && (!target_is_complx)){
			//the source is complex and the target not - this must not work
			//ASSIGNMENT RULE 2 according to manual
			EXCEPTION_INIT(TypeError,"Cannot assign a complex to a float type!");
			EXCEPTION_THROW();
		}else{
			//now we have to check only ranges
			if((b<TypeInfo<T>::getMin())||(b>TypeInfo<T>::getMax())){
				EXCEPTION_INIT(RangeError,"Assigned variable exceeds type bounds of the target!");
				EXCEPTION_THROW();
			}
		}
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

	template<typename U> static void isCompatibleForAssignment(const Complex32 &a,const U &b);
};

//some specialization for complex numbers
template<typename U>
void TypeInfo<Complex32>::isCompatibleForAssignment(const Complex32 &a,const U &b){
	EXCEPTION_SETUP("template<typename U> bool isCompatibleForAssignment<Complex32,U>(const T &a,const U &b)");

	//need to check only bounds
	if((b<TypeInfo<U>::getMin())||(b>TypeInfo<U>::getMax())){
		EXCEPTION_INIT(RangeError,"Assigned variable exceeds type bounds of the target!");
		EXCEPTION_THROW();
	}


}


//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit IEEE floating point complex type
template<> class TypeInfo<Complex64>{
public:

	static size_t getSize() {
		return sizeof(Complex64);
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

	template<typename U> void isCompatibleForAssignment(const Complex64 &a,const U &v);
};

template<typename U>
void TypeInfo<Complex64>::isCompatibleForAssignment(const Complex64 &a,const U &b){
	EXCEPTION_SETUP("template<typename U> void TypeInfo<Complex64>::isCompatibleForAssignment(const Complex64 &a,const U &b)");

	//need to check only bounds
	if((b<TypeInfo<U>::getMin())||(b>TypeInfo<U>::getMax())){
		EXCEPTION_INIT(RangeError,"Assigned variable exceeds type bounds of the target!");
		EXCEPTION_THROW();
	}
}

//! \ingroup Data-objects
//! \brief PNITypes specialization for 128Bit IEEE floating point complex type
template<> class TypeInfo<Complex128>{
public:

	static size_t getSize(){
		return sizeof(Complex128);
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

	template<typename U> static void isCompatibleForAssignment(const Complex128 &a,const U &b){
		EXCEPTION_SETUP("template<typename U> void TypeInfo<Complex128>::isCompatibleForAssignment(const Complex128 &a,const U &b)");

		//in general we can assign values only to numbers
		if((b<TypeInfo<Complex128>::getMin())||(b>TypeInfo<Complex128>::getMax())){
			EXCEPTION_INIT(RangeError,"Assigned variable exceeds type bounds of the target!");
			EXCEPTION_THROW();
		}
	}
};





//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
