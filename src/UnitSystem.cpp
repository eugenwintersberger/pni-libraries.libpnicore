/*
 * Implementation of class UnitSystem
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
 * Declaration of class UnitSystem which is an interface to a UDUNITS unit
 * system.
 *
 * Created on: Jun 29, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "UnitSystem.hpp"

namespace pni{
namespace utils{

void UnitSystem::_system_init_check(){
	int stat = ut_get_status();

	if ((stat == UT_OPEN_ARG) ||
		(stat == UT_OPEN_ENV) ||
		(stat == UT_OPEN_DEFAULT)){
		std::cerr<<"Cannot open unit system XML file!"<<std::endl;
		//raise exception here
	}

	if((stat == UT_OS)){
		std::cerr<<"OS error during system XML open!"<<std::endl;
		//raise an exception
	}

	if((stat == UT_PARSE)){
		std::cerr<<"Parser error for system XML file!"<<std::endl;
		//raise an exception
	}

}

UnitSystem::UnitSystem() {
	//here we may need a default path
	_system = ut_read_xml(NULL);
	_system_init_check();

}

UnitSystem::UnitSystem(const String &n){
	_system = ut_read_xml(n.c_str());
	_system_init_check();
}

UnitSystem::~UnitSystem() {
	if(_system != NULL) ut_free_system(_system);
}




//end of namespace
}
}
