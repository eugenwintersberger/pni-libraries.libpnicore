/*
 * Declaration of template class TypeInfo
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
 * class provides information about native data types. This class provides
 * similar information to PNITypeInfo. In order to avoid redundancies one
 * of the two classes will vanish in future.
 *
 * Created on: Sep 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

/*
 * ArrayElementType.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef __TYPEINFO_HPP__
#define __TYPEINFO_HPP__

#include <limits>

#include "Types.hpp"
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

	static bool is_negative(T value){
		if (value < 0) return true;
		return false;
	}

	static const size_t size = sizeof(T);
	static const bool is_integer = std::numeric_limits<T>::is_integer;
	static const bool is_signed = std::numeric_limits<T>::is_signed;
	static const bool is_complex = false;

	//! return minimum value of the type
	static T min(){
		//in the case of integers we can use min
		if (std::numeric_limits<T>::is_integer){
			return std::numeric_limits<T>::min();
		}else{
			//for floating point numbers this is a bit different
			//min would yield here the value of the smallest possible number
			return -std::numeric_limits<T>::max();
		}
	}

	//! return maximum value of the type
	static T max(){
		return std::numeric_limits<T>::max();
	}

};


//! \cond NO_API_DOC
template<> class TypeInfo<Complex32>{
public:

	typedef Complex32 Type;
	typedef Float32 BaseType;

	static const size_t size = sizeof(Complex32);
	static const bool is_integer = std::numeric_limits<Float32>::is_integer;
	static const bool is_signed = std::numeric_limits<Float32>::is_signed;
	static const bool is_complex = true;

	static bool is_negative(Complex32 value){
		return false;
	}


	//! return the minimum value of the Complex32 type
	static Float32 min(){
		return -std::numeric_limits<Float32>::max();
	}

	//! return the maximum value of the Complex32 type
	static Float32 max(){
		return std::numeric_limits<Float32>::max();
	}

};
//! \endcond



//! \ingroup Data-objects
//! \brief PNITypes specialization for 64Bit IEEE floating point complex type
template<> class TypeInfo<Complex64>{
public:

	typedef Complex64 Type;
	typedef Float64 BaseType;

	static const size_t size = sizeof(Complex64);
	static const bool is_integer = std::numeric_limits<Float64>::is_integer;
	static const bool is_signed = std::numeric_limits<Float64>::is_signed;
	static const bool is_complex = true;



	static bool is_negative(Complex64 value){
		return false;
	}

	//! return the minimum value of the Complex64 type
	static Float64 min(){
		return -std::numeric_limits<Float64>::max();
	}

	//! return the maximum value of the Complex64 type
	static Float64 max(){
		return std::numeric_limits<Float64>::max();
	}

};

//! \ingroup Data-objects
//! \brief PNITypes specialization for 128Bit IEEE floating point complex type
template<> class TypeInfo<Complex128>{
public:
	typedef Complex128 Type;
	typedef Float128 BaseType;

	static const size_t size = sizeof(Complex128);
	static const bool is_integer = std::numeric_limits<Float128>::is_integer;
	static const bool is_signed = std::numeric_limits<Float128>::is_signed;
	static const bool is_complex = true;


	static bool is_negative(){
		return false;
	}

	//! return the minimum value of the Complex128 type
	static Float128 min(){
		return -std::numeric_limits<Float128>::max();
	}

	//! return the maximum value of the Complex128 type
	static Float128 max(){
		return std::numeric_limits<Float128>::max();
	}
};

//end of namespace
}
}


#endif /* ARRAYELEMENTTYPE_HPP_ */
