/*
 * ScalarObject.cpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#include "ScalarObject.hpp"

namespace pni{
namespace utils{


ScalarObject::ScalarObject():NumericObject() {
	// TODO Auto-generated constructor stub

}

ScalarObject::~ScalarObject() {
	// TODO Auto-generated destructor stub
}

ScalarObject &ScalarObject::operator=(const ScalarObject &o){
	if(this != &o){
		_name = o._name;
		_unit = o._unit;
		_description = o._description;
	}

	return *this;
}

//end of namespace
}
}
