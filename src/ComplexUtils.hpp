/*
 * ComplexUtils.hpp
 *
 *  Created on: Sep 9, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef COMPLEXUTILS_HPP_
#define COMPLEXUTILS_HPP_

#include "PNITypes.hpp"
#include "TypeInfo.hpp"

using namespace pni::utils;

namespace pni{
namespace utils{

template<typename C,typename O> C __convert(const O &v){
	if(TypeInfo<O>::is_complex){
		return C(v.real(),v.imag());
	}

	return C(v);
};

bool operator==(const Complex32 &a,const Complex64 &b);
bool operator==(const Complex32 &a,const Complex128 &b);

bool operator==(const Complex64 &a,const Complex32 &b);
bool operator==(const Complex64 &a,const Complex128 &b);

bool operator==(const Complex128 &a,const Complex32 &b);
bool operator==(const Complex128 &a,const Complex64 &b);


bool operator!=(const Complex32 &a,const Complex64 &b);
bool operator!=(const Complex32 &a,const Complex128 &b);

bool operator!=(const Complex64 &a,const Complex32 &b);
bool operator!=(const Complex64 &a,const Complex128 &b);

bool operator!=(const Complex128 &a,const Complex32 &b);
bool operator!=(const Complex128 &a,const Complex64 &b);

//end of namespace
}
}




#endif /* COMPLEXUTILS_HPP_ */
