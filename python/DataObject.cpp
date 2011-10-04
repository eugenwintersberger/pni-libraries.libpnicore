/*
 * DataObject.cpp
 *
 *  Created on: Oct 4, 2011
 *      Author: eugen
 */

#include <boost/python.hpp>


#include "../src/DataObject.hpp"
#include "../src/NumericObject.hpp"
#include "../src/ArrayObject.hpp"
#include "../src/PNITypes.hpp"

using namespace pni::utils;
using namespace boost::python;

BOOST_PYTHON_MODULE(pniutils)
{

	class_<DataObject>("DataObject")
			.add_property("name", &DataObject::getName,&DataObject::setName)
			.add_property("description",&DataObject::getDescription,&DataObject::setDescription)
			;

	class_<NumericObject,bases<DataObject> >("NumericObject")
			.add_property("unit",&NumericObject::getUnit,&NumericObject::setUnit)
			;

}




