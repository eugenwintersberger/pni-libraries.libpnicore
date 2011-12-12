/*
 * Declaration of class TIFFFile
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
 * Declaration of class TIFFFile.
 *
 * Created on: Jun 16, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFFILE_HPP_
#define TIFFFILE_HPP_

#include <iostream>
#include <fstream>

#include "../Types.hpp"
#include "../ArrayObject.hpp"
#include "../Array.hpp"

#include "TIFFIFD.hpp"
#include "TIFFImageData.hpp"

namespace pni{
namespace utils{

//! \ingroup IO
//! \brief class representing a TIFF file

//! The TIFF file object represents data stored in the Tagged Image File Format.
//! At the moment only reading of uncompressed data is supported. Writing data and
//! using data compression may be added in future.
//!
//! TIFF files are organized in so called Image File Directories (IFDs). Each IFD
//! corresponds to a particular image in the filed. Consequently multiple images
//! can be stored in a single file. The IFD of an image stored in the file
//! contains all the information needed to read the image data from the file.
//! This includes information about the datatype, the number of pixles in each dimension,
//! or information about how the image data is organized within the file.
//! When a TIFF file object is opened all IFDs are read from the file.
//! Thus a TIFFFile object can be considered as a container for the IFDs.
//! The IFDs are represented by TIFFIFD objects.
//!
//! The data that belongs to a particular IFD can be obtaind using the getData
//! method of the TIFFFile class. This method returns an object of type
//! TIFFImageData which holds the entire bunch of data that belongs
//! to an image.
class TIFFFile {
private:
	//the copy constructor is protected - the file cannot be
	//copied (would cause problems with the _ifstream object
	//in the class)
	TIFFFile(const TIFFFile &o){}
	TIFFFile &operator=(const TIFFFile &o){ return *this;}
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

	//! operator to access an individual IFD
	TIFFIFD &operator[](const UInt16 i);
	//! operator to access an individual IFD
	TIFFIFD operator[](const UInt16 i) const;

	//! read image data from IFD i
	TIFFImageData::sptr getData(UInt64 i) const;

	//! output operator for console output
	friend std::ostream &operator<<(std::ostream &o,const TIFFFile &f);

};


//end of namespace
}
}
#endif /* TIFFFILE_HPP_ */
