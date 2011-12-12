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

template<typename T,typename U> T convert_type(const U &u){
	EXCEPTION_SETUP("template<typename T,typename U> T convert_type(const U &u)");
	//static assert of the source type is float and T is an integer type
	//this avoids conversion from float to integer as supported by the
	//C++ standard.
	std::cout<<"original template function"<<std::endl;
	BOOST_STATIC_ASSERT(!((!std::numeric_limits<U>::is_integer)&&(std::numeric_limits<T>::is_integer)));

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
		EXCEPTION_INIT(RangeError,"Something went wrong!");
		EXCEPTION_THROW();
	}

	return value;

}

//need to handle the special case of complex numbers
#define COMPLEX_CONVERT_TYPE(target_base,source_base)\
template<> std::complex<target_base> convert_type(const std::complex<source_base> &u){\
	std::cout<<"overloaded function for complex number!"<<std::endl;\
	target_base real;\
	target_base imag;\
	real = convert_type<target_base>(u.real());\
	imag = convert_type<target_base>(u.imag());\
	return std::complex<target_base>(real,imag);\
}


//end of namespace
}
}




#endif /* TYPE_CONVERSION_HPP_ */
