/*
 * Declaration of class TIFFReader
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
 * Declaration of class TIFFReader.
 *
 * Created on: Jun 15, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFREADER_HPP_
#define TIFFREADER_HPP_


#include "Reader.hpp"
#include "TIFFFile.hpp"
#include "TIFFImageData.hpp"



namespace pni{
namespace utils{

//! \ingroup io_classes
//! \brief TIFF file reader

//! TIFFReader is an implementation of the Reader class for reading TIFF
//! image files.
class TIFFReader:public Reader {
private:
	//like all other derivatives of Reader the TIFFReader
	//cannot be copied or assigned to.
	TIFFReader(const TIFFReader &){}
	TIFFReader &operator=(const TIFFReader &o){return *this;}
protected:
	TIFFFile _file;
public:
	//! default constructor
	TIFFReader();
	//! destructor
	virtual ~TIFFReader();

	//! set the filename
	virtual void setFileName(const String &n);
	//! set the filename
	virtual void setFileName(const char *n);

	//! open the file
	virtual void open();
	//! close the file
	virtual void close();
	//! read data
	virtual DataObject::sptr read();
	//! read data
	virtual DataObject::sptr read(const UInt64 &i);
};

//end of namespace
}
}

#endif /* TIFFREADER_HPP_ */
