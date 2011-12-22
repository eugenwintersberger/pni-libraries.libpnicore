/*
 * DataObject.cpp
 *
 *  Created on: Dec 22, 2011
 *      Author: Eugen Wintersberger
 */




#include <boost/python.hpp>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/Types.hpp"


using namespace pni::utils;
using namespace boost::python;

void wrap_data_object(){
	//===================Wrapping DataObject====================================
	String (DataObject::*get_name)() const = &DataObject::name;
	void   (DataObject::*set_name)(const String &) = &DataObject::name;
	String (DataObject::*get_description)() const = &DataObject::description;
	void   (DataObject::*set_description)(const String &) = &DataObject::description;
	class_<DataObject>("DataObject")
			.def(init<String>())
			.def(init<String,String>())
			.def(init<DataObject>())
			.add_property("name", get_name,set_name)
			.add_property("description",get_description,set_description)
			;
}

