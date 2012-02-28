/*
 * Declaration of class DataObject
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
 * DataObject is the base class for all data holding objects. The class
 * itself is hardly useful. Concrete functionality must be implemented in its
 * descendants.
 *
 * Created on: May 26, 2011
 *     Author: Eugen Wintersberger
 *
 */

#ifndef __DATAOBJECT_HPP_
#define __DATAOBJECT_HPP_

#include<memory>
#include<iostream>
#include<string>

#include "Types.hpp"

namespace pni{
namespace utils{

//! \ingroup data_classes
//! \brief base class for all data holding objects

//! This class is the basement for all data holding classes in the pni::utils
//! namespace. It holds the basic information each data object must provide:
//! a name and a description.
class DataObject {
private:
	String _name;         //!< name of the data object
	String _description;  //!< description of the object
public:
	typedef std::shared_ptr<DataObject> sptr; //!< shared pointer to a data object
	//! default constructor
	DataObject();
	//! copy constructor
	DataObject(const DataObject &);
	//! move constructor
	DataObject(DataObject &&o);
	//! constructor

	//! This constructor sets only the name of the DataObject class.
	//! \param n object name as String
	DataObject(const String &n);
	//! constructor

	//! Constructor setting name and description of an object
	//! \param n object name as String
	//! \param d object description as String
	DataObject(const String &n,const String &d);
	//! destructor
	virtual ~DataObject();
	//! copy assignment operator

	//! Assignment operator setting the values of an existing object
	//! to the value of an already existing one.
	DataObject &operator=(const DataObject &o);
	//! move assignment operator
	DataObject &operator=(DataObject &&o);
	//! set name

	//! Set the name of the object.
	//! \param n name of the object
	virtual void name(const String &n);
	//! get name

	//! Returns the name of the object.
	//! \return object name
	virtual String name() const;
	//! set description

	//! Set the description for the.
	//! \param d object's description
	virtual void description(const String &d);
	//! get description

	//! Gets the description of the object.
	//! \return object description
	virtual String description() const;
	//! print object

	//! Prints object data to an output stream.
	//! \param os output stream
	//! \param o object to print
	//! \return output stream
	friend std::ostream &operator<<(std::ostream &os,const DataObject &o);
};


//end of namespace
}
}


#endif /* DATAOBJECT_HPP_ */
