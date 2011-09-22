/*
 * NumericObject.cpp
 *
 *  Created on: Jun 10, 2011
 *      Author: eugen
 */

#include "NumericObject.hpp"
#include "Exceptions.hpp"


namespace pni{
namespace utils{


NumericObject::NumericObject():DataObject(){
	_unit = String("");
}

NumericObject::NumericObject(const NumericObject &o)
			  :DataObject(o){
	_unit = o._unit;
}

NumericObject::NumericObject(const String &u):DataObject(){
	_unit = u;
}



NumericObject::NumericObject(const String &n,const String &u):DataObject(n){
	_unit = u;
}


NumericObject::NumericObject(const String &n,const String &u,const String &d):DataObject(n,d){
	_unit = u;
}


NumericObject::~NumericObject(){

}

String NumericObject::getUnit() const {
	return _unit;
}


void NumericObject::setUnit(const String &u){
	_unit = u;
}

PNITypeID NumericObject::getTypeID() const{
	return NONE;
}

NumericObject &NumericObject::operator=(const NumericObject &o){
	if (this != &o) {
		DataObject &this_object = (DataObject &)(*this);
		DataObject &that_object = (DataObject &)o;
		this_object = that_object;

		setUnit(o.getUnit());
	}

	return *this;
}

void *NumericObject::getVoidPtr(){
	EXCEPTION_SETUP("void *NumericObject::getVoidPtr()");

	EXCEPTION_INIT(NotImplementedError,"This method must be implemented by a child class!");
	EXCEPTION_THROW();

	return NULL;
}

const void *NumericObject::getVoidPtr() const{
	EXCEPTION_SETUP("const void *NumericObject::getVoidPtr() const");

	EXCEPTION_INIT(NotImplementedError,"This method must be implemented by a child class!");
	EXCEPTION_THROW();

	return NULL;
}

//end of namespace
}
}
