/*
 * ComplexUtils.cpp
 *
 *  Created on: Sep 9, 2011
 *      Author: Eugen Wintersberger
 */


#include "ComplexUtils.hpp"

namespace pni{
namespace utils{


bool operator==(const Complex32 &a,const Complex64 &b){
	Complex64 _a(a.real(),a.imag());

	return (_a == b);
}

bool operator==(const Complex32 &a,const Complex128 &b){
	Complex64 _a(a.real(),a.imag());

	return (_a == b);
}

bool operator==(const Complex64 &a,const Complex32 &b){
	Complex64 _b(b.real(),b.imag());
	return (a == _b);
}

bool operator==(const Complex64 &a,const Complex128 &b){
	Complex128 _a(a.real(),a.imag());
	return(_a == b);
}

bool operator==(const Complex128 &a,const Complex32 &b){
	Complex128 _b(b.real(),b.imag());
	return(_b == a);
}
bool operator==(const Complex128 &a,const Complex64 &b){
	Complex128 _b(b.real(),b.imag());
	return(_b == a);
}


bool operator!=(const Complex32 &a,const Complex64 &b){
	if(a == b) return false;
	return true;
}

bool operator!=(const Complex32 &a,const Complex128 &b){
	if(a==b) return false;
	return true;
}

bool operator!=(const Complex64 &a,const Complex32 &b){
	if(a==b) return false;
	return true;
}
bool operator!=(const Complex64 &a,const Complex128 &b){
	if(a==b) return false;
	return true;
}

bool operator!=(const Complex128 &a,const Complex32 &b){
	if(a==b) return false;
	return true;
}
bool operator!=(const Complex128 &a,const Complex64 &b){
	if(a==b) return false;
	return true;
}


}
}




