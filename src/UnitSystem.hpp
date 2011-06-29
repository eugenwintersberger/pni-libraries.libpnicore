/*
 * UnitSystem.hpp
 *
 *  Created on: Jun 29, 2011
 *      Author: eugen
 */

#ifndef UNITSYSTEM_HPP_
#define UNITSYSTEM_HPP_

extern "C"{
#include <udunits2.h>
}

#include "PNITypes.hpp"

namespace pni{
namespace utils{

//! UnitSystem - describes a system of physical units

//! The object acts as a factory for Unit objects describing
//! a particular physical unit. There is no other way
//! to construct unit objects than to use this class or
//! the copy constructor of a Unit object.
//! A system configuration for the unit system must be
//! provided to configure the system.

//! The class should be implemented as a singleton. This
//! is no problem because access is in fact always reading
//! and therefore there are no threading issues.

//! This class is a wrapper around the UDUnits physical
//! units C API.
class UnitSystem {
private:
	//A unit system cannot be copied or assigned
	//! copy constructor
	UnitSystem(const UnitSystem &o){}
	//! assignment operator
	UnitSystem &operator=(const UnitSystem &o){ return *this; }
protected:
	ut_system *_system;       //!< pointer to the unit system object
	//! method to check for errors during system initialization
	void _system_init_check();
public:
	//! default constructor

	//! This constructor uses the system default configuration
	//! file for initializing the system
	UnitSystem();
	//! standard constructor

	//! Here a custom system configuration file is passed
	//! to the constructor by the String constant fname.
	//! \param &fname name of the system description file
	UnitSystem(const String &fname);
	//! destructor
	virtual ~UnitSystem();

	//! obtain a shared pointer to a unit from a string

	//! Method returns a smart pointer to a Unit object.
	//! The unit is determined from a string which is passed
	//! as an argument to the method.
	//! \param ustr string to parse to determine the unit
	//! \return smart pointer to a Unit object
	virtual Unit::sptr parseUnit(const String &ustr) const;
	//! obtain a unit by name

	//! Method returns a smart pointer to a Unit object
	//! which is determined by the name of the unit
	//! \param uname name of the unit
	//! \return smart pointer to a Unit object
	virtual Unit::sptr getUnitByName(const String &uname) const;
	//! obtain a unit by symbol

	//! Method returns a smart pointer to an instance of a
	//! Unit object determined by the Symbol for this unit.
	//! \param &usym symbol for the unit
	//! \return smart pointer to an instance of class Unit.
	virtual Unit::sptr getUnitBySymbol(const String &usym) const;
};


//end of namespace
}
}

#endif /* UNITSYSTEM_HPP_ */
