/*
 * Declaration of class UnitConverter
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
 * Declaration of class UnitConverter which converts a numerical value from
 * one unit to another.
 *
 * Created on: Jun 29, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef UNITCONVERTER_HPP_
#define UNITCONVERTER_HPP_

extern "C"{
#include <udunits2.h>
}

#import "Unit.hpp"

namespace pni {
namespace utils {

class UnitConverter {
protected:
	Unit _u1;
	Unit _u2;
	cv_converter *_conv;
public:
	UnitConverter();
	UnitConverter(const Unit &u1,const Unit &u2);
	virtual ~UnitConverter();

	//single value unit conversion
	template<typename T> double operator()(const T &value);

};

template<typename T> T UnitConverter::operator()(const T &value){
	return (T)cv_converter_double(_conv,(double)value);
}

template<> Float64 UnitConverter::operator<Float64>()(const Float64 &v){
	return cv_converter_double(_conv,v);
}

template<> Float32 UnitConverter::operator<Float32>()(const Float32 &v){
	return cv_converter_float(_conv,v);
}



}
}

#endif /* UNITCONVERTER_HPP_ */
