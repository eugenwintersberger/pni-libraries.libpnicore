/*
 * Declaration of class Reader
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
 * Class Reader is the base class for all readers which retrieve data from
 * files and other sources.
 *
 * Created on: May 26, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#ifndef READER_HPP_
#define READER_HPP_

#include<iostream>
#include<fstream>
#include<string>

#include "../Exceptions.hpp"
#include "../DataObject.hpp"

namespace pni{
namespace utils {

//! \defgroup IO
//! The pni::utils namespace contains classes primarily for reading data stored in  various
//! file formats. These classes are described here in the IO module.

//! \ingroup IO
//! \brief base class for file reader objects

//! The Reader class is the basement for all data readers.
//! It provides the basic functionality for opening and closing data streams.
//! Due to its abstract nature it is hardly useful for direcet instantiation.
//! However it acts as a basement for all other reader objects.
//! The copy constructor is not public, thus such objects cannot be copied
//! which should avoid confusion on the file sytem level if systems do not
//! support parallel read.
//!
//! The reader object holds a stream as a member variable. Since stream objects
//! must not be copied or assigned to the copy constructor and assignment operator
//! are defined as private and cannot be used outside the class.
class Reader{
private:
	//reader classes cannot be copied - the reason for this is
	//that stream objects must not be copied (due to standard
	//definitions). Thus no copy constructor will be provided.
	//The same is valid for assignment of streams. Therefore
	//Reader objects must not be assigned.
	Reader(const Reader &r){}
	//the return statement is here only for syntactical reasons
	//to avoid compiler warnings
	Reader &operator=(const Reader &o){return *this;}
protected:
	std::ifstream _istream; //!< input stream for the data
	std::string   _fname;   //!< string with the name of the file from which to read data
public:
	//! default constructor
	Reader();
	//! standard constructor taking the filename as string object
	Reader(const std::string &fname);
	//! standard constructor taking the filename as pointer to char
	Reader(const char *fname);
	//! destructor
	virtual ~Reader();

	//! set the filename as string object

	//! This method sets a new filename. If this method is invoked while a
	//! file is already open this file will be closed. However, this method
	//! does  not open the new file immediately - an explicit call to the open method
	//! is required instead.

	//! \param fname name of the file to open
	virtual void setFileName(const std::string &fname);
	//! set the filename as pointer to char *

	//! Calls setFilename(const std::string &fname). See there for more information.

	//! \param fname name of the new file as pointer to char
	virtual void setFileName(const char *fname);

	//! opens the file

	//! This method opens the file with the name stored in the class field _fname.
	//! In cases of errors an exception of type FileError will be raised.
	virtual void open();

	//! closes the file
	virtual void close();

	//! read data from a file
	virtual DataObject::sptr read();
	virtual DataObject::sptr read(const UInt64 &i);
};



}
}


#endif /* READER_HPP_ */
