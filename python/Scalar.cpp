/*
 * Scalar.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */

#include <boost/python.hpp>

#include "../src/Types.hpp"
#include "../src/ScalarObject.hpp"
#include "../src/Scalar.hpp"

#include "OperatorDefines.hpp"


using namespace pni::utils;
using namespace boost::python;

//=================Macro for instantiating a scalar object----------------------
#define SCALAR_TEMPLATE(type,name) \
		void (Scalar<type>::*(name ## _set_value))(const Scalar<type> &) = &Scalar<type>::value;\
		void (Scalar<type>::*(name ## _set_value_pod))(const type &) = &Scalar<type>::value;\
		type (Scalar<type>::*(name ## _get_value))() const = &Scalar<type>::value;\
		class_<Scalar<type>,bases<ScalarObject> >(#name)\
				.def(init<Scalar<type> >())\
				.def(init<type,String,String,String>())\
				.def(init<String,String,String>())\
				.def("value",(name ## _set_value))\
				.def("value",(name ## _get_value))\
				.def("value",(name ## _set_value_pod))\
				.add_property("type_id",&Scalar<type>::type_id)\
				.def(self == self)\
				EQUALITY_TOTAL(Scalar)\
				.def(self != self)\
				INEQUALITY_TOTAL(Scalar)\
				.def(self + self)\
				BINARY_ADD_TOTAL(Scalar)\
				.def(self - self)\
				BINARY_SUB_TOTAL(Scalar)\
				.def(self / self)\
				BINARY_DIV_TOTAL(Scalar)\
				.def(self * self)\
				BINARY_MULT_TOTAL(Scalar)\
				;

void wrap_scalar(){
	//==========================Wrapping ScalarObject===========================
	class_<ScalarObject,bases<NumericObject> >("ScalarObject")
			.def(init<ScalarObject>())
			.def(init<>())
			.def(init<String,String>())
			.def(init<String,String,String>())
			;

	//==================Wrapping scalar templates===============================
	SCALAR_TEMPLATE(UInt8,UInt8Scalar);
	SCALAR_TEMPLATE(Int8,Int8Scalar);
	SCALAR_TEMPLATE(UInt16,UInt16Scalar);
	SCALAR_TEMPLATE(Int16,Int16Scalar);
	SCALAR_TEMPLATE(UInt32,UInt32Scalar);
	SCALAR_TEMPLATE(Int32,Int32Scalar);
	SCALAR_TEMPLATE(UInt64,UInt64Scalar);
	SCALAR_TEMPLATE(Int64,Int64Scalar);
	SCALAR_TEMPLATE(Float32,Float32Scalar);
	SCALAR_TEMPLATE(Float64,Float64Scalar);
	SCALAR_TEMPLATE(Float128,Float128Scalar);

}
