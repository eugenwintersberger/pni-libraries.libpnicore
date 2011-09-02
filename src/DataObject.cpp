/*
 * DataObject.cpp
 *
 *  Created on: May 26, 2011
 *      Author: eugen
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

const String &DataObject::getName() const{
	return _name;
}

void DataObject::setDescription(const String &d){
	_description = d;
}

const String &DataObject::getDescription() const{
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
