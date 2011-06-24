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

ScalarObject::ScalarObject(const ScalarObject &o){
	_name = o._name;
	_description = o._description;
	_unit = o._unit;
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

std::ostream &operator<<(std::ostream &o,const ScalarObject &s){
	o<<s._name<<"["<<s._description<<"]"<<" in units of ("<<s._unit<<")";
	return o;
}

//end of namespace
}
}
