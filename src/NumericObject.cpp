/*
 * Implementation of class NumericObject
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of class NumericObject which acts as a base class for all
 * objects storing numeric data. It extends DataObject with a physical unit.
 *
 * Created on: Jun 10, 2011
 *     Author: Eugen Wintersberger
 *
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
