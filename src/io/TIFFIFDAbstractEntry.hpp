/*
 * TIFFIDFAbstractEntry.hpp
 *
 *  Created on: Jun 17, 2011
 *      Author: eugen
 */

#ifndef TIFFIDFABSTRACTENTRY_HPP_
#define TIFFIDFABSTRACTENTRY_HPP_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "../PNITypes.hpp"

namespace pni{
namespace utils{

enum IDFEntryTypeCode {IDFE_BYTE,IDFE_ASCII,IDFE_SHORT,IDFE_LONG,IDFE_RATIONAL,
	                   IDFE_SBYTE,IDFE_UNDEFINED,IDFE_SSHORT,
                       IDFE_SLONG,IDFE_SRATIONAL,IDFE_FLOAT,IDFE_DOUBLE};


class IFDAbstractEntry{
protected:
	String _name;   //!<name of the entry
	UInt32 _cnt;    //!<number of elements
public:
	typedef boost::shared_ptr<IFDAbstractEntry> sptr; //!< a shared pointer to an abstract entry
	typedef std::vector<sptr> list;
	typedef list::iterator iterator;
	typedef list::const_iterator const_iterator;
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

	virtual IDFEntryTypeCode getEntryTypeCode() const{
		return IDFE_UNDEFINED;
	}

	friend std::ostream &operator<<(std::ostream &o,const IFDAbstractEntry &e);

};

//end of namespace
}
}


#endif /* TIFFIDFABSTRACTENTRY_HPP_ */
