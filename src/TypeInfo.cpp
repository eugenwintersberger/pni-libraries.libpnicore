/*
 * TypeInfo.cpp
 *
 *  Created on: Sep 7, 2011
 *      Author: eugen
 */

#include "TypeInfo.hpp"

namespace pni{
namespace utils{

template<>
void TypeInfo<Complex128>::isCompatibleForAssignment<Complex32>(const Complex128 &a,const Complex32 &b){
	EXCEPTION_SETUP("template<> void TypeInfo<Complex128>::isCompatibleForAssignment(const Complex128 &a,const Complex32 &b)");

	if((b.real() < TypeInfo<Complex128>::getMin())||
	   (b.imag() < TypeInfo<Complex128>::getMin())||
	   (b.real() > TypeInfo<Complex128>::getMax())||
	   (b.real() > TypeInfo<Complex128>::getMax())
	){
		EXCEPTION_INIT(RangeError,"Assigned variable exceeds type bounds of the target!");
		EXCEPTION_THROW();
	}

}

}
}


