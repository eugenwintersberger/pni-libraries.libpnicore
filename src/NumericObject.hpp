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

//! \ingroup Data-objects
//! base class for numerical objects

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
	//! constructor

	//! Constructor setting only the physical unit of the object.
	//! \param u unit as string
	NumericObject(const String &u);
	//! constructor

	//! Constructor setting only the physical unit of the object.
	//! \param u unit as character array
	NumericObject(const char *u);
	//! constructor

	//! Constructor setting name and unit of the object.
	//! \param n object name as String
	//! \param u object unit as String
	NumericObject(const String &n,const String &u);
	//! constructor

	//! Constructor setting name and physical unit of the object.
	//! \param n object name as character array
	//! \param u object unit as character array
	NumericObject(const char *n,const char *u);
	//! constructor

	//! This constructor sets the object's name, physical unit, and description.
	//! \param n object name as String
	//! \param u object unit as String
	//! \param d object description as String
	NumericObject(const String &n,const String &u,const String &d);
	//! constructor

	//! This constructor sets the object's name, physical unit, and description.
	//! \param n object name as character array
	//! \param u object unit as character array
	//! \param d object description as character array
	NumericObject(const char *n,const char *u,const char *d);
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
	//! set the physical unit

	//! Set the physical unit of the object.
	//! \param u unit as String
	virtual void setUnit(const String &u);
	//! get the ID of the data type

	//! This virtual function is overloaded by the concrete implementations
	//! of numerical types. It returns the ID of the type used to store
	//! the data.
	//! \return PNITypeID ID value of the type
	virtual PNITypeID getTypeID() const;

	//! assignment operator
	NumericObject &operator=(const NumericObject &o);
};


//end of namespace
}
}

#endif /* NUMERICOBJECT_HPP_ */
