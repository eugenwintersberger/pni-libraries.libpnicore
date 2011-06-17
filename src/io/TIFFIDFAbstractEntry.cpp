/*
 * TIFFIDFAbstractEntry.cpp
 *
 *  Created on: Jun 17, 2011
 *      Author: Eugen Wintersberger
 */

#include <iostream>

#include "TIFFIDFAbstractEntry.hpp"

namespace pni{
namespace utils{


IDFAbstractEntry::IDFAbstractEntry() {
	_name = "";
	_cnt = 0;
}


IDFAbstractEntry::IDFAbstractEntry(const IDFAbstractEntry &o) {
	_name = o._name;
	_cnt = o._cnt;
}

IDFAbstractEntry::IDFAbstractEntry(const String &n,const UInt32 cnt) {
	_name = n;
	_cnt = cnt;
}

IDFAbstractEntry::~IDFAbstractEntry() {
}

void IDFAbstractEntry::setName(const String &n) {
	_name = n;
}

String IDFAbstractEntry::getName() const {
	return _name;
}

UInt32 IDFAbstractEntry::getCount() const {
	return _cnt;
}

std::ostream &operator<<(std::ostream &o,const IDFAbstractEntry &e){

	o<<e._name<<" count = "<<e._cnt;
	return o;
}

//end of namespace
}
}
