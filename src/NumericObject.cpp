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
#include "service.hpp"


namespace pni{
namespace utils{

//==================Implementation of constructors and destructor==============
//implementation of the default constructor
NumericObject::NumericObject():DataObject(){
	_unit = String("");
}

//-----------------------------------------------------------------------------
//implementation of the copy constructor
NumericObject::NumericObject(const NumericObject &o)
			  :DataObject(o){
	_unit = o._unit;
}

//-----------------------------------------------------------------------------
//implementation of the move constructor
NumericObject::NumericObject(NumericObject &&o):DataObject(std::move(o)){
	_unit = std::move(o._unit);
}

//------------------------------------------------------------------------------
//constructor
NumericObject::NumericObject(const String &n,const String &u):DataObject(n){
	_unit = u;
}

//------------------------------------------------------------------------------
//constructor
NumericObject::NumericObject(const String &n,const String &u,const String &d)
:DataObject(n,d){
	_unit = u;
}

//------------------------------------------------------------------------------
//implementation of the destructor
NumericObject::~NumericObject(){

}

//==============Implementation of assignment operators=========================
NumericObject &NumericObject::operator=(const NumericObject &o){
	if (this != &o) {
		(DataObject &)(*this) = (DataObject &)o;

		unit(o.unit());
	}

	return *this;
}

NumericObject &NumericObject::operator=(NumericObject &&o){
	if(this != &o){
		(DataObject &)(*this) = std::move((DataObject &)o);
		_unit = std::move(o._unit);
	}

	return *this;
}
//================Implementation of inquiry methods============================


String NumericObject::unit() const {
	return _unit;
}


void NumericObject::unit(const String &u){
	_unit = u;
}


PNITypeID NumericObject::type_id() const {
	return PNITypeID::NONE;
}


void *NumericObject::void_ptr(){
	EXCEPTION_SETUP("void *NumericObject::void_ptr()");

	EXCEPTION_INIT(NotImplementedError,"This method must be implemented by a child class!");
	EXCEPTION_THROW();

	return nullptr;

}

const void *NumericObject::void_ptr() const {
	EXCEPTION_SETUP("const void *NumericObject::void_ptr() const");

	EXCEPTION_INIT(NotImplementedError,"This method must be implemented by a child class!");
	EXCEPTION_THROW();

	return nullptr;

}

//end of namespace
}
}
