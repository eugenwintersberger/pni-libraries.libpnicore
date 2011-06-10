/*
 * NumericObject.hpp
 *
 *  Created on: Jun 10, 2011
 *      Author: eugen
 */

#ifndef NUMERICOBJECT_HPP_
#define NUMERICOBJECT_HPP_

#include "DataObject.hpp"
#include "PNITypes.hpp"
#include "PNITypeInfo.hpp"

namespace pni{
namespace utils{

//! numeric object - base class for numerical objects

//! NumericObject is the base class for all objects in the
//! PNI utility name space that hold numeric data. As a descendant of
//! DataObject it inherits its ancestors properties "name" and "description".
//! NumericObjects adds the property "unit" which describes the physical
//! unit of a numeric object. In addition the NumericObject
//! implements introspection methods to obtain types and other information
//! about numeric objects.

class NumericObject:public DataObject {
protected:
	String _unit; //!< string holding the physical unit of the object
public:
	//! default constructor
	NumericObject();
	//! copy constructor
	NumericObject(const NumericObject &);
	//! constructor with unit as string argument
	NumericObject(const String &u);
	//! constructor with unit as char* argument
	NumericObject(const char *u);
	//! full constructor for a data object with name and unit
	NumericObject(const String &n,const String &u);
	NumericObject(const char *n,const char *u);
	//! full constructor for a DataObject
	NumericObject(const String &n,const String &d,const String &u);
	NumericObject(const char *n,const char *d,const char *u);
	//! destructor
	virtual ~NumericObject();

	//! get the physical Unit

	//! Returns a copy of the unit string of the object.
	//! \return - the unit as String object
	virtual String getUnit() const;
	//! set the physical unit

	//! Set the physical unit string
	//! \param u char* to the unit string.
	virtual void setUnit(const char *u);
	virtual void setUnit(const String &u);

	virtual PNITypeID getTypeID() const;
};


//end of namespace
}
}

#endif /* NUMERICOBJECT_HPP_ */
