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

//=================Implementation of constructors and destructor===============
//implementation of the default constructor
ScalarObject::ScalarObject():NumericObject() {

}

//-----------------------------------------------------------------------------
//implementation of the copy constructor
ScalarObject::ScalarObject(const ScalarObject &o):NumericObject(o){

}

//-----------------------------------------------------------------------------
//implementation of the move constructor
ScalarObject::ScalarObject(ScalarObject &&o):NumericObject(std::move(o)){

}

//------------------------------------------------------------------------------
//implementation of the destructor
ScalarObject::~ScalarObject() {
	// TODO Auto-generated destructor stub
}

//================Implementation of assignment operators========================
//implementation of the copy assignment operator
ScalarObject &ScalarObject::operator=(const ScalarObject &o){
	if(this != &o){
		(NumericObject &)(*this) = (NumericObject &)o;
	}

	return *this;
}

//------------------------------------------------------------------------------
//implementation of the move assignment operator
ScalarObject &ScalarObject::operator=(ScalarObject &&o){
	if(this != &o){
		(NumericObject &)(*this) = std::move((NumericObject &)o);
	}
	return *this;
}

//====================Implementation of output operators========================
std::ostream &operator<<(std::ostream &o,const ScalarObject &s){
	o<<s.name()<<"["<<s.description()<<"]"<<" in units of ("<<s.unit()<<")";
	return o;
}

//end of namespace
}
}
