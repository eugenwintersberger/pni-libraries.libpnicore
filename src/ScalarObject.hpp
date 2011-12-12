/*
 * Delcaration of class ScalarObject
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
 * ScalarObject is the base class for all numerical scalar quantities.
 *
 * Created on: Jun 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

#ifndef SCALAROBJECT_HPP_
#define SCALAROBJECT_HPP_

#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Types.hpp"
#include "NumericObject.hpp"

namespace pni{
namespace utils{

//! \ingroup Data-objects
//! \brief base class for numeric scalar templates

//! This class represents a single numeric value. In many cases it would be
//! sufficient to store such a value in a simple variable using a native type
//! rather than an entire object. However, in this case on would loose all the
//! advantages of a NumericObject type like name, description, and most
//! important, the physical unit.
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
	//! move constructor
	ScalarObject(ScalarObject &&o);
	//! move constructor
	//! constructor

	//! Constructor setting name and unit of a scalar
	//! \param n name of the scalar as String object
	//! \param u unit of the scalar as String object
	ScalarObject(const String &n,const String &u):NumericObject(n,u){}
	//! constructor

	//! Constructor setting name, unit, and description of a scalar
	//! \param n name of the scalar as String object
	//! \param u unit of the scalar as String object
	//! \param d description of the scalar as String object
	ScalarObject(const String &n,const String &u,const String &d):NumericObject(n,u,d){}
	//! destructor
	virtual ~ScalarObject();

	//! assignment operator
	ScalarObject &operator=(const ScalarObject &o);
	//! move assignment
	ScalarObject &operator=(ScalarObject &&o);

	//! output operator for console output
	friend std::ostream &operator<<(std::ostream &o,const ScalarObject &s);

};


//end of namespace
}
}


#endif /* SCALAROBJECT_HPP_ */
