/*
 * Implementation of class Unit
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
 * This header file contains the declaration of class Unit which represents
 * a single unit from a UDUNITS unit system.
 *
 * Created on: Jun 29, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "Unit.hpp"

namespace pni {
namespace utils {

Unit::Unit(const Unit &o){
	_unit = ut_clone(o._unit);

}

Unit::~Unit() {
	if (_unit != NULL){
		ut_free(_unit);
	}
}

Unit &Unit::operator=(const Unit &u){
	if ( this != &u ){
		//free the original unit
		ut_free(_unit);
		//clone the assigned unit
		_unit = ut_clone(u._unit);
	}

	return *this;
}

String Unit::getName() const {
	const char *buffer;
	ut_status stat;

	buffer = ut_get_name(_unit,UT_UTF8);
	//check here for errors
	ut_status = ut_get_status();
	switch(ut_status){
	case UT_SUCCESS:
		return String(buffer);
	case UT_BAD_ARG:
		std::cerr<<
	}
	return String(buffer);
}

String Unit::getSymbol() const {
	const char *buffer;
	bufffer = ut_get_symbol(_unit,UT_UTF8);
	//check here for errors

	return String(buffer);
}

void Unit::setScale(const Float64 &s){
	ut_unit *tmp;

	tmp = ut_scale(s,_unit);
	//need to check here if everything was ok

	//everything was fine so we can reset the
	//original unit pointer
	ut_free(_unit);
	_unit = tmp;
}

Unit &Unit::operator*=(const Float64 &s){
	setScale(s);
	return *this;
}

void Unit::setOffset(const Float64 &o){
	ut_unit *tmp;
	tmp = ut_offset(_unit,o);
	//check here if everything was ok

	//everything was fine - reset the original
	//unit pointer
	ut_free(_unit);
	_unit = tmp;
}

Unit &Unit::operator += (const Float64 &o){
	setOffset(o);
	return *this;
}

Unit operator*(const Float64 &s,const Unit &u){
	Unit result = u;
	result.setScale(s);
	return result;
}

Unit operator*(const Unit &u,const Float64 &s){
	return s*u;
}

Unit operator*(const Unit &a,const Unit &b){
	Unit result;
	ut_status stat;
	result._unit = ut_multiply(a._unit,b._unit);
	//check here for erros
	return result;
}

Unit operator/(const Float64 &s,const Unit &u){
	Unit result;
	result._unit = ut_invert(u._unit);
	//check for errors

	result *= s;
	//check for errors

	return result;
}

Unit operator/(const Unit &u,const Float64 &s){
	return (1/s)*u;
}

Unit operator/(const Unit &a,const Unit &b){
	Unit result;
	result._unit = ut_divide(a._unit,b._unit);
	//check for errors

	return result;
}

bool operator == (const Unit &a,const Unit &b){
	//check if units belong to the same system
	if (ut_same_system(a._unit,b._unit)){
		//check if units are equal
		if(!ut_compare(a._unit,b._unit)){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

bool operator != (const Unit &a,const Unit &b){
	if(a==b){
		return false;
	}else{
		return true;
	}
}

ostream &operator<<(ostream &o,const Unit &u){
	o<<"Unit: "<<u.getName()<<" ("<<u.getSymbol()<<")";
	return o;
}


//end of namespace
}
}
