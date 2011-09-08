/*
 * TypeRange.hpp
 *
 *  Created on: Sep 8, 2011
 *      Author: eugen
 */

#ifndef TYPERANGE_HPP_
#define TYPERANGE_HPP_

#include "PNITypes.hpp"
#include "TypeCompat.hpp"

namespace pni{
namespace utils{


template<typename A> class TypeRange{
private:

public:
	template<typename B> static bool checkRange(const B &v);
	static bool checkRange(const Complex128 &v);
	static bool checkRange(const Complex32 &v);
	static bool checkRange(const Complex64 &v);

};

template<typename A>
template<typename B> bool TypeRange<A>::checkRange(const B &v){
	//static size_t t_size = TypeInfo<A>::getSize();
	//static size_t s_size = TypeInfo<B>::getSize();
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();
	static bool t_issigned = TypeInfo<A>::isSigned();
	static bool s_issigned = TypeInfo<B>::isSigned();

	//a brute force check: 0 fits for all types
	if(v == 0) return true;

	if(TypeInfo<B>::isNegative(v) && (!t_issigned)){
		return false;
	}

	if(t_issigned && s_issigned){
		if((v < t_min) || (v > t_max)) return false;
	}else{
		if(v>t_max) return false;
	}
	return true;

}

template<typename A>
bool TypeRange<A>::checkRange(const Complex128 &v){
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();

	if((v.real() < t_min) || (v.real() > t_max)) return false;

	return true;
}

template<typename A>
bool TypeRange<A>::checkRange(const Complex32 &v){
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();

	if((v.real() < t_min) || (v.real() > t_max)) return false;

	return true;
}

template<typename A>
bool TypeRange<A>::checkRange(const Complex64 &v){
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();

	if((v.real() < t_min) || (v.real() > t_max)) return false;

	return true;
}

//end of namespace
}
}


#endif /* TYPERANGE_HPP_ */
