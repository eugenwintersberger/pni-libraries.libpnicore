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
#include <boost/shared_ptr.hpp>

#include "../PNITypes.hpp"
#include "../Array.hpp"

#include "TIFFIFDAbstractEntry.hpp"
#include "TIFFIFDEntry.hpp"

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

//! \ingroup IO
//! \brief TIFFIFD - Image File Directory class

//! This class describes an Image File Directory (IFD) block in a TIFF file.
//! Each IFD is associated with a single image. An IFD can be considered as a
//! container for IFD entries. Each of this entries has a particular type and
//! one or several values of this type. The entries can be obtained
//! using the [] operator together with an integer index as its argument.
//! Each entry has a unique tag. The TIFF specification defines a group of
//! standard entries with defines names. Such entries can be obtained using the []
//! operator along with a string holding the name of an entrie as defines by the
//! TIFF standard.
//!
//! The type of an entry is usually not standardized. Therefore
class TIFFIFD {
protected:
	Int32 _idf_offset;             //!< starting offset of the IFD
	Int32 _idf_next_offset;        //!< offset to the next IFD in the file (0 if this is the last)
	UInt16 _number_of_idf_entries; //!< number of IFD entries
	IFDAbstractEntry::list _entry_list; //!< list of IFD entries
public:
	//some data types that can be useful for IFDs
	typedef boost::shared_ptr<TIFFIFD> IFDSptr;        //!< shared pointer to an IDF entry
	typedef std::vector<IFDSptr>       IFDList;        //!< vector to IDF entries
	typedef IFDList::iterator       IFDIterator;       //!< iterator over IDF entries in IDFList
	typedef IFDList::const_iterator const_IFDIterator; //!< const. iterator over IDF entries in IDF List

	//! default constructor
	TIFFIFD();
	//! copy constructor
	TIFFIFD(const TIFFIFD &o);
	//! destructor
	virtual ~TIFFIFD();

	//! overloaded assignment operator
	TIFFIFD &operator = (const TIFFIFD &o);

	//! get number of IFD entries
	virtual UInt16 getNumberOfEntries() const;

	//! return true if this is the last IFD
	virtual bool isLastIDF() const;
	//! return the offset of the next IFD in the file
	virtual Int32 getNextOffset() const;
	//! return the offset of this IFD in the file
	virtual Int32 getOffset() const;
	//! set the offset of this IFD in the file
	virtual void setOffset(const Int32 &o);

	//! operator to obtain an entry by index

	//! This woks for all entries stored in the IFD also for those
	//! not defined by the TIFF specification. If the index requested
	//! exceeds the number of entries stored in the IFD an exception
	//! will be raised.

	//! \param i unsigned integer with the index of the entry
	//! \return smart pointer to an IFDAbstractEntry object
	IFDAbstractEntry::sptr operator[](const UInt16 i);
	//! operator to obtain an entry by its name

	//! This operator works only for entries which are defined in the
	//! TIFF specification. If the requested entry is not available
	//! an exception will be raised.

	//! \param n a string with the name of the entry
	//! \return smart pointer to an IFDAbstractEntry
	IFDAbstractEntry::sptr operator[](const String &n);

	//! overloaded ifstream operator for stream reading

	//! this operator can be used to read an IFD from the binary file stream.
	//! Unlike other >> operators this resets the position of the stream object
	//! to its original value after being applied to an IFD object. The reason
	//! for this behavior is that TIFF files are not organized sequentially.
	//! Thus the standard behavior would not make too much sense.
	friend std::ifstream &operator>>(std::ifstream &i,TIFFIFD &idf);

	//! overloaded ostream operator for standard output

	//! Thiss operator can be used to dump the content of an IFD to standard out.
	friend std::ostream &operator<<(std::ostream &o,const TIFFIFD &idf);
};


//end of namespace
}
}


#endif /* TIFFIDF_HPP_ */
