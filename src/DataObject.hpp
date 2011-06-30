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
	//! constructor

	//! Constructor setting only the name of the object using a
	//! C-type string.
	//! \param n object name as character array
	DataObject(const char *n);
	//! constructor

	//! Constructor setting name and description of an object using
	//! C-type strings.
	//! \param n object name as character array
	//! \param d object description as character array
	DataObject(const char *n,const char *d);
	//! destructor
	virtual ~DataObject();

	//! set the name of the object as String object
	virtual void setName(const String &n);
	//! set the name of the object as pointer to char
	virtual void setName(const char *n);
	//! get the name of the data object
	virtual const String &getName() const;

	//! set the object's description as String object
	virtual void setDescription(const String &d);
	//! set the object's description as pointer to char
	virtual void setDescription(const char *d);
	//! return the description of the object as String
	virtual const String &getDescription() const;

	//! overloaded assignment operator
	DataObject &operator=(const DataObject &o);
	//! overloaded output operator
	friend std::ostream &operator<<(std::ostream &os,const DataObject &o);

};


//end of namespace
}
}


#endif /* DATAOBJECT_HPP_ */
