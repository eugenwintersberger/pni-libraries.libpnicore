/*
 * TIFFFile.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#ifndef TIFFFILE_HPP_
#define TIFFFILE_HPP_

#include <iostream>
#include <fstream>

#include "../PNITypes.hpp"
#include "../ArrayObject.hpp"
#include "../Array.hpp"

#include "TIFFIFD.hpp"
#include "TIFFImageData.hpp"

namespace pni{
namespace utils{

//! TIFFFile - class representing a TIFF file

class TIFFFile {
private:
	//the copy constructor is protected - the file cannot be
	//copied
	TIFFFile(const TIFFFile &o){}


protected:
	bool   _is_little_endian;    //!<true if file is little endian
	bool   _is_big_endian;       //!<true if file is big endian
	String _fname;               //!<name of the file
	std::ifstream    _ifstream;  //!<input stream to read the file
	TIFFIFD::IFDList _ifd_list;  //!< list of IDFs in a file
public:
	//! default constructor
	TIFFFile();
	//! standard constructor
	TIFFFile(const char *n);
	//! standard constructor
	TIFFFile(const String &n);
	//! destructor
	virtual ~TIFFFile();

	//! set the filename as String object
	virtual void setFileName(const String &n);
	//! set the filename as C string
	virtual void setFileName(const char *n);
	//! return the filename as String object
	virtual String getFileName() const;

	//! open the file
	virtual void open();
	//! close the file
	virtual void close();

	//! return the number of IFDs in the file
	virtual UInt64 getNumberOfIFDs() const;
	//! true if data is stored as little endian
	virtual bool isLittleEndian() const;
	//! true if data is stored as big endian
	virtual bool isBigEndian() const;

	//need an operator to access the IFDs
	TIFFIFD &operator[](const UInt16 i);
	TIFFIFD operator[](const UInt16 i) const;

	TIFFImageData::sptr getData(UInt64 i) const;

	friend std::ostream &operator<<(std::ostream &o,const TIFFFile &f);

};

//end of namespace
}
}
#endif /* TIFFFILE_HPP_ */
