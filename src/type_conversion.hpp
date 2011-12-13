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
