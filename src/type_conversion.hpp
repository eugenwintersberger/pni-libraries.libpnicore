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
 * type_conversion.hpp
 *
 *  Created on: Dec 10, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef TYPE_CONVERSION_HPP_
#define TYPE_CONVERSION_HPP_

#include <limits>
#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

using namespace boost::numeric;

#include "Exceptions.hpp"
#include "TypeInfo.hpp"


namespace pni{
namespace utils{

//! \ingroup type_classes
//! \brief general conversion strategy template

//! This template implements a generic type conversion between two types.
//! The type conversion is done from type U to T. There are some special cases
//! in the case where one or both of the types are complex. The core of the
//! convert method is the boost::numeric_cast template function for type
//! conversion.
//! \sa class ConversionStrategy<T,U,true,false>
//! \sa class ConversionStrategy<T,U,true,true>
template<typename T, typename U,bool t_complex,bool u_complex>
class ConversionStrategy{
public:
	static T convert(const U &u){
		EXCEPTION_SETUP("T ConversionStrategy<u_complex,t_complex,T,U>::convert(const U &u)");
		T value;

		try{
			value = boost::numeric_cast<T>(u);
		}catch(negative_overflow &error){
			EXCEPTION_INIT(RangeError,"Cannot assign value doe to negative overflow!");
			EXCEPTION_THROW();
		}catch(positive_overflow &error){
			EXCEPTION_INIT(RangeError,"Cannot assign value due to positive overflow!");
			EXCEPTION_THROW();
		}catch(...){
			EXCEPTION_INIT(TypeError,"Something went wrong!");
			EXCEPTION_THROW();
		}
		return value;
	}
};

//! \ingroup type_classes
//! \brief specialization of the type conversion template

//! This is a specialization of ConversionStrategy template for the case
//! that the target type T is complex. In this case the rhs object
//! of the conversion operation (which is of type U) is converted to the
//! base type of T and assigned to the real part of the complex value.
template<typename T,typename U> class ConversionStrategy<T,U,true,false>{
public:
	static T convert(const U &u){
		EXCEPTION_SETUP("template<typename T,typename U> T ConversionStrategy<false,true,T,U>::convert(const U &u)");
		typedef typename TypeInfo<T>::BaseType TBaseType;
		T value;
		try{
			value = std::complex<TBaseType>(boost::numeric_cast<TBaseType>(u),0);
		}catch(negative_overflow &error){
			EXCEPTION_INIT(RangeError,"Cannot convert type due to negative overflow!");
			EXCEPTION_THROW();
		}catch(positive_overflow &error){
			EXCEPTION_INIT(RangeError,"Cannot convert type due to positive overflow!");
			EXCEPTION_THROW();
		}catch(...){
			EXCEPTION_INIT(TypeError,"Type conversion failed!");
			EXCEPTION_THROW();
		}

		return value;
	}
};

//! \ingroup type_classes
//! \brief specialization of the type conversion template

//! A specialization of the ConversionStrategy template for the case that
//! both types are complex. In this case the conversion is straight forwared.
template<typename T,typename U> class ConversionStrategy<T,U,true,true>{
public:
	static T convert(const U &u){
		EXCEPTION_SETUP("template<typename T,typename U> T ConversionStrategy<true,true,T,U>::convert(const U &u)");
		typedef typename TypeInfo<T>::BaseType TBaseType;
		TBaseType real;
		TBaseType imag;
		try{
			real = boost::numeric_cast<TBaseType>(u.real());
			imag = boost::numeric_cast<TBaseType>(u.imag());
		}catch(negative_overflow &error){
			EXCEPTION_INIT(RangeError,"Cannot convert type due to negative overflow!");
			EXCEPTION_THROW();
		}catch(positive_overflow &error){
			EXCEPTION_INIT(RangeError,"Cannot convert type due to positive overflow!");
			EXCEPTION_THROW();
		}catch(...){
			EXCEPTION_INIT(TypeError,"Type conversion failed!");
			EXCEPTION_THROW();
		}

		return std::complex<TBaseType>(real,imag);
	}
};

//! ingroup type_classes
//! \brief type conversion function template

//! This function template finally performs the type conversion. Several
//! static asserts are performed which ensure the two cases of conversions
//! will not even compile: conversion from a floating point number fo an
//! integer value and conversion from a complex value to a non-complex type.
template<typename T,typename U> T convert_type(const U &u){
	EXCEPTION_SETUP("template<typename T,typename U> T convert_type(const U &u)");
	//static assert of the source type is float and T is an integer type
	//this avoids conversion from float to integer as supported by the
	//C++ standard.
	BOOST_STATIC_ASSERT(!((!std::numeric_limits<U>::is_integer)&&(std::numeric_limits<T>::is_integer)));

	//need to check for complex types - you cannot convert a complex type
	//to a non-complex type
	BOOST_STATIC_ASSERT(!((!TypeInfo<T>::is_complex)&&(TypeInfo<U>::is_complex)));

	T value = ConversionStrategy<T,U,TypeInfo<T>::is_complex,TypeInfo<U>::is_complex >::convert(u);

	return value;

}


//end of namespace
}
}




#endif /* TYPE_CONVERSION_HPP_ */
