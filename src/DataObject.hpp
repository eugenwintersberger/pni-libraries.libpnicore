/*
 * DataObject.hpp
 *
 *  Created on: May 26, 2011
 *      Author: eugen
 */

#ifndef DATAOBJECT_HPP_
#define DATAOBJECT_HPP_

#include<iostream>
#include<string>
#include<boost/shared_ptr.hpp>

#include "PNITypes.hpp"

namespace pni{
namespace utils{

//! \defgroup Data-objects
//! Data holding objects in memory

//! \ingroup Data-objects
//! \brief base class for all data holding objects

//! This class is the basement for all data holding classes in the pni::utils
//! namespace. It holds the basic information each data object must provide:
//! a name and a description.
class DataObject {
protected:
	String _name;         //!< name of the data object
	String _description;  //!< description of the object
public:
	typedef boost::shared_ptr<DataObject> sptr; //!< shared pointer to a data object
	//! default constructor
	DataObject();
	//! copy constructor
	DataObject(const DataObject &);
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

	//! set name

	//! Set the name of the object.
	//! \param n name of the object
	virtual void setName(const String &n);

	//! get name

	//! Returns the name of the object.
	//! \return object name
	virtual const String &getName() const;

	//! set description

	//! Set the description for the.
	//! \param d object's description
	virtual void setDescription(const String &d);

	//! get description

	//! Gets the description of the object.
	//! \return object description
	virtual const String &getDescription() const;

	//! assignment operator

	//! Assignment operator setting the values of an existing object
	//! to the value of an already existing one.
	DataObject &operator=(const DataObject &o);

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
