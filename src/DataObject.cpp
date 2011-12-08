/*
 * Implementation of class DataObject
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
 * DataObject is the base class for all data holding objects. The class
 * itself is hardly useful. Concrete functionality must be implemented in its
 * descendants.
 *
 * Created on: May 26, 2011
 *     Author: Eugen Wintersberger
 *
 */


#include "DataObject.hpp"
#include "service.hpp"

namespace pni{
namespace utils{

//==============Implementation of constructors and destructor==================
//implementation of the default constructor
DataObject::DataObject() {
	//nothing to be done

}

//-----------------------------------------------------------------------------
//implementation of the copy constructor
DataObject::DataObject(const DataObject &o){
	_name = o._name;
	_description = o._description;
}

//-----------------------------------------------------------------------------
//implementation of the move constructor
DataObject::DataObject(DataObject &&o){
	_name = std::move(o._name);
	_description = std::move(o._description);
}

//-----------------------------------------------------------------------------
//implementation of a constructor
DataObject::DataObject(const String &n){
	_name = n;
}

//------------------------------------------------------------------------------
//implementation of a constructor
DataObject::DataObject(const String &n,const String &d){
	_name = n;
	_description = d;
}

//------------------------------------------------------------------------------
//implementation of the destructor
DataObject::~DataObject() {
	//empty the string variables
	_name.clear();
	_description.clear();
}

//================Implementation of assignment operators=======================
//implementation of copy assignment
DataObject &DataObject::operator=(const DataObject &o){
	if(this != &o){
		_name = o.name();
		_description = o.description();
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of move assignment
DataObject &DataObject::operator=(DataObject &&o){
	if(this != &o){
		_name = std::move(o._name);
		_description = std::move(o._description);
	}

	return *this;
}

//==============Implementation of object inquiry methods========================


void DataObject::name(const String &n){
	_name = n;
}

String DataObject::name() const{
	return _name;
}

void DataObject::description(const String &d){
	_description = d;
}

String DataObject::description() const{
	return _description;
}

//====================Implementation of output operators========================
std::ostream &operator<<(std::ostream &os,const DataObject &o){
	os<<"DataObject: "<<o._name<<" "<<o._description;
	return os;
}

//end of namespace
}
}
