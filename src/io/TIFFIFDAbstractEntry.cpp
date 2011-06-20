/*
 * TIFFIDFAbstractEntry.cpp
 *
 *  Created on: Jun 17, 2011
 *      Author: Eugen Wintersberger
 */

#include <iostream>

#include "TIFFIFDAbstractEntry.hpp"

namespace pni{
namespace utils{


IFDAbstractEntry::IFDAbstractEntry() {
	_name = "";
	_cnt = 0;
}


IFDAbstractEntry::IFDAbstractEntry(const IFDAbstractEntry &o) {
	_name = o._name;
	_cnt = o._cnt;
}

IFDAbstractEntry::IFDAbstractEntry(const String &n,const UInt32 cnt) {
	_name = n;
	_cnt = cnt;
}

IFDAbstractEntry::~IFDAbstractEntry() {
}

void IFDAbstractEntry::setName(const String &n) {
	_name = n;
}

String IFDAbstractEntry::getName() const {
	return _name;
}

UInt32 IFDAbstractEntry::getCount() const {
	return _cnt;
}

std::ostream &operator<<(std::ostream &o,const IFDAbstractEntry &e){

	o<<e._name<<" count = "<<e._cnt;
	return o;
}

//end of namespace
}
}
