/*
 * TIFFIDFEntry.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#ifndef TIFFIDFENTRY_HPP_
#define TIFFIDFENTRY_HPP_

#include "../PNITypes.hpp"

namespace pni{
namespace utils{

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




};

template<typename T>
class IDFEntry{

};

//end of namespace
}
}

#endif /* TIFFIDFENTRY_HPP_ */
