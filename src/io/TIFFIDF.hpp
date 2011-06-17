/*
 * TIFFIDF.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#ifndef TIFFIDF_HPP_
#define TIFFIDF_HPP_

#include <vector>
#include <fstream>
#include <iostream>

#include "../PNITypes.hpp"

#include "TIFFIDFAbstractEntry.hpp"
#include "TIFFIDFEntry.hpp"

namespace pni{
namespace utils{

//IDF Entry type codes
#define ENTRY_TYPE_BYTE 1
#define ENTRY_TYPE_ASCII 2
#define ENTRY_TYPE_SHORT 3
#define ENTRY_TYPE_LONG 4
#define ENTRY_TYPE_RATIONAL 5
#define ENTRY_TYPE_SBYTE 6
#define ENTRY_TYPE_UNDEFINED 7
#define ENTRY_TYPE_SSHORT 8
#define ENTRY_TYPE_SLONG 9
#define ENTRY_TYPE_SRATIONAL 10
#define ENTRY_TYPE_FLOAT 11
#define ENTRY_TYPE_DOUBLE 12


class TIFFIDF {
protected:
	Int32 _idf_offset;  //!< starting offset of the IDF
	Int32 _idf_next_offset; //!< offset to the next IDF (0 if this is the last);
	UInt16 _number_of_idf_entries; //!< number of IDF entries
	typedef std::vector<IDFAbstractEntry *> _IDFEntryList;
	typedef _IDFEntryList::iterator _iterator;
	typedef _IDFEntryList::const_iterator _const_iterator;
	_IDFEntryList _entry_list;
public:
	TIFFIDF();
	TIFFIDF(const TIFFIDF &o);
	virtual ~TIFFIDF();

	virtual bool isLastIDF() const;
	virtual Int32 getNextOffset() const;
	virtual Int32 getOffset() const;
	virtual void setOffset(const Int32 &o);

	IDFAbstractEntry *operator[](const UInt16 i);
	IDFAbstractEntry *operator[](const String &n);

	friend std::ifstream &operator>>(std::ifstream &i,TIFFIDF &idf);
	friend std::ostream &operator<<(std::ostream &o,const TIFFIDF &idf);
};

typedef std::vector<TIFFIDF> IDFList;

//end of namespace
}
}


#endif /* TIFFIDF_HPP_ */
