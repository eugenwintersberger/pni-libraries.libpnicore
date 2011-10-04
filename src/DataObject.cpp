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

namespace pni{
namespace utils{

DataObject::DataObject() {
	//nothing to be done

}

DataObject::DataObject(const DataObject &o){
	_name = o._name;
	_description = o._description;
}

DataObject::DataObject(const std::string &n){
	_name = n;
}

DataObject::DataObject(const std::string &n,const std::string &d){
	_name = n;
	_description = d;
}

DataObject::~DataObject() {
	//empty the string variables
	_name.clear();
	_description.clear();
}

void DataObject::setName(const std::string &n){
	_name = n;
}

String DataObject::getName() const{
	return _name;
}

void DataObject::setDescription(const String &d){
	_description = d;
}

String DataObject::getDescription() const{
	return _description;
}

DataObject &DataObject::operator=(const DataObject &o){
	if(this != &o){
		_name = o._name;
		_description = o._description;
	}

	return *this;
}

std::ostream &operator<<(std::ostream &os,const DataObject &o){
	os<<"DataObject: "<<o._name<<" "<<o._description;
	return os;
}

//end of namespace
}
}
