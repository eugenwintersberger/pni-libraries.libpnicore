/*
 * Implementation of class ScalarObject
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
 * ScalarObject is the base class for all numerical scalar quantities.
 *
 * Created on: Jun 9, 2011
 *     Author: Eugen Wintersberger
 *
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
