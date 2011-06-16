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

#include "TIFFIDF.hpp"

namespace pni{
namespace utils{


class TIFFFile {
private:
	//the copy constructor is protected - the file cannot be
	//copied
	TIFFFile(const TIFFFile &o){}
protected:
	bool _is_little_endian;  //!<true if file is little endian
	bool _is_big_endian;     //!<true if file is big endian
	String _fname;           //!<name of the file
	std::ifstream _ifstream;  //!<input stream to read the file
	IDFList _idf_list;       //!< list of IDFs in a file
public:
	TIFFFile();
	TIFFFile(const char *n);
	TIFFFile(const String &n);
	virtual ~TIFFFile();

	virtual void setFileName(const String &n);
	virtual void setFileName(const char *n);
	virtual String getFileName() const;

	virtual void open();
	virtual void close();

	virtual UInt64 getNumberOfIFDs() const;
	virtual bool isLittleEndian() const;
	virtual bool isBigEndian() const;

	friend std::ostream &operator<<(std::ostream &o,const TIFFFile &f);

};

//end of namespace
}
}
#endif /* TIFFFILE_HPP_ */
