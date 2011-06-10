/*
 * NumericObject.cpp
 *
 *  Created on: Jun 10, 2011
 *      Author: eugen
 */

#include "NumericObject.hpp"


namespace pni{
namespace utils{


NumericObject::NumericObject(){
	_unit = String("NONE");
}

NumericObject::NumericObject(const NumericObject &o):DataObject(o){
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

NumericObject::NumericObject(const String &n,const String &d,const String &u):DataObject(n,d){
	_unit = u;
}

NumericObject::NumericObject(const char *n,const char *d,const char *u):DataObject(n,d){
	_unit = String(u);
}

NumericObject::~NumericObject(){

}

String NumericObject::getUnit() const{
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

//end of namespace
}
}
