/*
 * Implementation of class TIFFIFDAbstractEntry
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
 * Implementation of class TIFFIFDAbstractEntry.
 *
 * Created on: Jun 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include <iostream>

#include "TIFFIFDAbstractEntry.hpp"

namespace pni{
namespace utils{

//------------------------------------------------------------------------------
IFDAbstractEntry::IFDAbstractEntry() {
	_name = "";
	_cnt = 0;
}

//------------------------------------------------------------------------------
IFDAbstractEntry::IFDAbstractEntry(const IFDAbstractEntry &o) {
	_name = o._name;
	_cnt = o._cnt;
}

//------------------------------------------------------------------------------
IFDAbstractEntry::IFDAbstractEntry(const String &n,const UInt32 cnt) {
	_name = n;
	_cnt = cnt;
}

//------------------------------------------------------------------------------
IFDAbstractEntry::~IFDAbstractEntry() {
}

void IFDAbstractEntry::setName(const String &n) {
	_name = n;
}

//------------------------------------------------------------------------------
String IFDAbstractEntry::getName() const {
	return _name;
}

//------------------------------------------------------------------------------
UInt32 IFDAbstractEntry::getCount() const {
	return _cnt;
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const IFDAbstractEntry &e){

	o<<e._name<<" count = "<<e._cnt;
	return o;
}

//end of namespace
}
}
