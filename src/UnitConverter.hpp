/*
 * UnitConverter.hpp
 *
 *  Created on: Jun 29, 2011
 *      Author: eugen
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
