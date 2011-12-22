/*
 * NumericObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: eugen
 */




#include <boost/python.hpp>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/Types.hpp"


using namespace pni::utils;
using namespace boost::python;

void wrap_numeric_object(){
	//===================Wrapping NumericObject=================================
	String (NumericObject::*get_unit)() const = &NumericObject::unit;
	void   (NumericObject::*set_unit)(const String &) = &NumericObject::unit;
	class_<NumericObject,bases<DataObject> >("NumericObject")
			.def(init<String,String>())
			.def(init<String,String,String>())
			.def(init<NumericObject>())
			.def("type_id",&NumericObject::type_id)
			.add_property("unit",get_unit,set_unit)
			;
}


