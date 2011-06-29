/*
 * UnitSystem.cpp
 *
 *  Created on: Jun 29, 2011
 *      Author: eugen
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
