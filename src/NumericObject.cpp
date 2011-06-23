/*
 * NumericObject.cpp
 *
 *  Created on: Jun 10, 2011
 *      Author: eugen
 */

#include "NumericObject.hpp"


namespace pni{
namespace utils{


NumericObject::NumericObject():DataObject(){
	_unit = String("NONE");
}

NumericObject::NumericObject(const NumericObject &o){
	_name = o._name;
	_description = o._description;
	_unit = o._unit;
}

NumericObject::NumericObject(const String &u):DataObject(){
	_unit = u;
}

NumericObject::NumericObject(const char *u):DataObject(){
	_unit = String(u);
}

NumericObject::NumericObject(const String &n,const String &u):DataObject(n){
	_unit = u;
}

NumericObject::NumericObject(const char *n,const char *u):DataObject(n){
	_unit = String(u);
}

NumericObject::NumericObject(const String &n,const String &u,const String &d):DataObject(n,d){
	_unit = u;
}

NumericObject::NumericObject(const char *n,const char *u,const char *d):DataObject(n,d){
	_unit = String(u);
}

NumericObject::~NumericObject(){

}

String NumericObject::getUnit() const {
	return _unit;
}

void NumericObject::setUnit(const char *u){
	_unit = String(u);
}

void NumericObject::setUnit(const String &u){
	_unit = u;
}

PNITypeID NumericObject::getTypeID() const{
	return NONE;
}

NumericObject &NumericObject::operator=(const NumericObject &o){
	if (this != &o) {
		_name = o._name;
		_description = o._description;
		_unit = o._unit;
	}

	return *this;
}

//end of namespace
}
}
