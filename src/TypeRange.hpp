/*
 * Declaration of template class TypeRange
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * This template performs range checks if a value of a particular type
 * lies in the range of an other type.
 *
 * Created on: Sep 8, 2011
 *     Author: Eugen Wintersberger
 *
 */

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
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();
	static bool t_issigned = TypeInfo<A>::is_signed;
	static bool s_issigned = TypeInfo<B>::is_signed;

	//a brute force check: 0 fits for all types
	if(v == 0) return true;

	//if v is negative and A is an unsigned type - this will fail.
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

	if((v.real() < t_min) || (v.real() > t_max) ||
	   (v.imag() < t_min) || (v.imag() > t_max)) return false;

	return true;
}

template<typename A>
bool TypeRange<A>::checkRange(const Complex32 &v){
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();

	if((v.real() < t_min) || (v.real() > t_max) ||
	   (v.imag() < t_min) || (v.imag() > t_max)) return false;

	return true;
}

template<typename A>
bool TypeRange<A>::checkRange(const Complex64 &v){
	static typename TypeInfo<A>::BaseType t_min = TypeInfo<A>::getMin();
	static typename TypeInfo<A>::BaseType t_max = TypeInfo<A>::getMax();

	if((v.real() < t_min) || (v.real() > t_max) ||
	   (v.imag() < t_min) || (v.imag() > t_max)) return false;

	return true;
}

//end of namespace
}
}


#endif /* TYPERANGE_HPP_ */
