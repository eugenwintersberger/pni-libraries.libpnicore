/*
 * TIFFIDFAbstractEntry.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: eugen
 */

#ifndef TIFFIDFABSTRACTENTRY_HPP_
#define TIFFIDFABSTRACTENTRY_HPP_

#include "../PNITypes.hpp"

namespace pni{
namespace utils{

enum IDFEntryTypeCode {IDFE_BYTE,IDFE_ASCII,IDFE_SHORT,IDFE_LONG,IDFE_RATIONAL,
	                   IDFE_SBYTE,IDFE_UNDEFINED,IDFE_SSHORT,
                       IDFE_SLONG,IDFE_SRATIONAL,IDFE_FLOAT,IDFE_DOUBLE};


class IDFAbstractEntry{
protected:
	String _name;   //!<name of the entry
	UInt32 _cnt;    //!<number of elements
public:
	//! default constructor
	IDFAbstractEntry();
	//! copy constructor
	IDFAbstractEntry(const IDFAbstractEntry &o);
	//! standard constructor
	IDFAbstractEntry(const String &n,const UInt32 cnt);
	//! destructor
	virtual ~IDFAbstractEntry();

	//! set the name of the entry

	//! \param n name as String value
	virtual void setName(const String &n);
	//! get the name of the entry

	//! \return a String value with the name
	virtual String getName() const;
	//! get the number of elements in the entry

	//! \return a UInt32 value with the number of elements
	virtual UInt32 getCount() const;

	virtual IDFEntryTypeCode getEntryTypeCode() const{
		return IDFE_UNDEFINED;
	}

	friend std::ostream &operator<<(std::ostream &o,const IDFAbstractEntry &e);

};

//end of namespace
}
}


#endif /* TIFFIDFABSTRACTENTRY_HPP_ */
