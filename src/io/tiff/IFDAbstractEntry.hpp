/*
 * Declaration of class TIFFIFDAbstractEntry
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
 * Declaration of class TIFFIFDAbstractEntry.
 *
 * Created on: Jun 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFIDFABSTRACTENTRY_HPP_
#define TIFFIDFABSTRACTENTRY_HPP_

#include <memory>
#include <vector>

#include "../Types.hpp"

namespace pni{
namespace utils{

//! \ingroup io_classes
//! typecodes to identify the type of an IFD entry
enum IFDEntryTypeCode {IDFE_BYTE,       //!< ID of an unsigned 8Bit integer type
	     	 	 	   IDFE_ASCII,      //!< ID of a string type (NUL terminated)
	     	 	 	   IDFE_SHORT,      //!< ID of an unsigned 16Bit integer type
	     	 	 	   IDFE_LONG,       //!< ID of an unsigned 32Bit integer type
	     	 	 	   IDFE_RATIONAL,   //!< ID of a unsigned 32Bit rational type (see the Rational template)
	                   IDFE_SBYTE,      //!< ID of a signed 8Bit integer type
	                   IDFE_UNDEFINED,  //!< ID of an undefined data type
	                   IDFE_SSHORT,     //!< ID of a signed 16Bit integer type
                       IDFE_SLONG,      //!< ID of a signed 32Bit integer type
                       IDFE_SRATIONAL,  //!< ID of a signed 32Bit rational type (see the Rational template)
                       IDFE_FLOAT,      //!< ID of a 32Bit IEEE float type
                       IDFE_DOUBLE      //!< ID of a 64Bit IEEE float type
					  };

//! \ingroup io_classes
//! \brief abstract IFD entry

//! The IFDAbstractEntry class describes the basic properties of an IFD entry.
//! These are the name of the entry (if it has a defined name) and the number
//! of elements stored in the entry. This class acts as a base class for
//! the concrete IFDEntry classes which are implemented as templates
//! (see IFDEntry).
class IFDAbstractEntry{
protected:
	String _name;   //!<name of the entry
	UInt32 _cnt;    //!<number of elements
public:
	typedef std::shared_ptr<IFDAbstractEntry> sptr; //!< a shared pointer to an abstract entry
	typedef std::vector<sptr> list;                   //!< type for IFDAbstractEntry lists
	typedef list::iterator iterator;                  //!< iterator over an IFDAbstractEntry list
	typedef list::const_iterator const_iterator;      //!< const iterator over an IFDAbstractEntry list

	//! default constructor
	IFDAbstractEntry();
	//! copy constructor
	IFDAbstractEntry(const IFDAbstractEntry &o);
	//! standard constructor
	IFDAbstractEntry(const String &n,const UInt32 cnt);
	//! destructor
	virtual ~IFDAbstractEntry();

	//! set the name of the entry

	//! \param n name as String value
	virtual void setName(const String &n);
	//! get the name of the entry

	//! \return a String value with the name
	virtual String getName() const;
	//! get the number of elements in the entry

	//! \return a UInt32 value with the number of elements
	virtual UInt32 getCount() const;

	//! virtual function to obtain the entry type code

	//! This method is overloaded by the different specializations
	//! of the IDFEntry template.
	virtual IFDEntryTypeCode getEntryTypeCode() const{
		return IDFE_UNDEFINED;
	}

	//! ouput operator for console output
	friend std::ostream &operator<<(std::ostream &o,const IFDAbstractEntry &e);

};

//end of namespace
}
}


#endif /* TIFFIDFABSTRACTENTRY_HPP_ */
