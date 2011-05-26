/*
 * Reader.hpp
 *
 *  Created on: May 26, 2011
 *      Author: eugen
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

//! Reader - base class for file reader objects

//! The Reader class is the basement for all data readers.
//! It provides the basic functionality for opening and closing data streams.
//! Due to its abstract nature it is hardly useful for direcet instantiation.
//! However it acts as a basement for all other reader objects.
//! The copy constructor is not public, thus such objects cannot be copied
//! which should avoid confusion on the file sytem level if systems do not
//! support parallel read.

class Reader{
private:
	Reader(const Reader &r){} //readers cannot be copied
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

	virtual DataObject *read();
};



}
}


#endif /* READER_HPP_ */
