/*
 * Implementation exception classes
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
 * Implementation of the exception classes declared in Exceptions.hpp.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger
 *
 */

#include<iostream>
#include<string>

#include "Exceptions.hpp"

namespace pni{
namespace utils{

//============Implementation of constructors and destructor=====================
Exception::Exception(const String &n){
    _name = n;
}
     
//------------------------------------------------------------------------------
Exception::Exception(const String &n,const String &i){
    _name = n;
    _issuer = i;
}

//------------------------------------------------------------------------------
Exception::Exception(const String &n,const String &i,const String &d)
{
    _name = n;
    _issuer = i;
    _description = d;
}

//==========Implementation of output methods and operator=======================
std::ostream &Exception::print(std::ostream &o) const {
	o<<this->name()<<" by:  "<<this->issuer()<<std::endl;
	o<<this->description()<<std::endl;

	return o;
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &ostr,const Exception &ex){
    return ex.print(ostr);
}

//=========Implementation of the output operators for other errors==============

std::ostream &operator<<(std::ostream &o,const MemoryAllocationError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const ShapeMissmatchError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const SizeMissmatchError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const IndexError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const FileError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const TypeError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const RangeError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const NotImplementedError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const MemoryAccessError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const ProcessingError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const AssignmentError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const IteratorError &e){
	return e.print(o);
}
//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const KeyError &e){
	return e.print(o);
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const MemoryNotAllocatedError &e)
{
    return e.print(o);
}

//end of namespace
}
}
