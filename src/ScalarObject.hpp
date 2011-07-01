/*
 * ScalarObject.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef SCALAROBJECT_HPP_
#define SCALAROBJECT_HPP_

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "PNITypes.hpp"
#include "NumericObject.hpp"

namespace pni{
namespace utils{

//! \ingroup Data-objects
//! \brief base class for numeric scalar templates

//! This class represents a single numeric value. In many cases it would be sufficient
//! to store such a value in a simple variable using a native type rather than an entire
//! object. However, in this case on would loose all the advantages of a NumericObject
//! type like name, description, and most important, the physical unit.
class ScalarObject:public NumericObject {
public:
	//public types
	typedef boost::shared_ptr<ScalarObject> sptr; //!< shared pointer on a scalar object
	typedef std::vector<ScalarObject> list;       //!< list of scalar objects
	typedef std::vector<sptr> ptrlist;            //!< list of shared pointers to scalar objects

	//! default constructor
	ScalarObject();
	//! copy constructor
	ScalarObject(const ScalarObject &o);
	//! constructor

	//! Constructor setting name and unit of a scalar
	//! \param n name of the scalar as String object
	//! \param u unit of the scalar as String object
	ScalarObject(const String &n,const String &u):NumericObject(n,u){}
	//! constructor

	//! Constructor setting name and unit of a scalar
	//! \param n name of the scalar as character array
	//! \param u unit of the scalar as character array
	ScalarObject(const char *n,const char *u):NumericObject(n,u){}
	//! constructor

	//! Constructor setting name, unit, and description of a scalar
	//! \param n name of the scalar as String object
	//! \param u unit of the scalar as String object
	//! \param d description of the scalar as String object
	ScalarObject(const String &n,const String &u,const String &d):NumericObject(n,u,d){}
	//! constructor

	//! Constructor setting name, unit, and description of a scalar
	//! \param n name of the scalar as character array
	//! \param u unit of the scalar as character array
	//! \param d description of the scalar as character array
	ScalarObject(const char *n,const char *u,const char *d):NumericObject(n,u,d){}
	//! destructor
	virtual ~ScalarObject();

	//! assignment operator
	ScalarObject &operator=(const ScalarObject &o);

	//! output operator for console output
	friend std::ostream &operator<<(std::ostream &o,const ScalarObject &s);

	//! get void pointer to the data value
	virtual void *getVoidPtr(){ return NULL; }
};


//end of namespace
}
}


#endif /* SCALAROBJECT_HPP_ */
