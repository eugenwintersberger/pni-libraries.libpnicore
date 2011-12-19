/*
 * Declaration of class CBFReader
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
 * CBFReader is the base class for readers for the CBF format and a descendant
 * of Reader (see Reader.hpp).
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef CBFREADER_HPP_
#define CBFREADER_HPP_

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>

#include "../Types.hpp"
#include "../DataObject.hpp"

#include "Reader.hpp"
#include "CBFHeader.hpp"


#define CIF_BINARY_SECTION "--CIF-BINARY-FORMAT-SECTION--"
#define CIF_HEADER_CONVENTION "_array_data.header_convention"
#define CIF_HEADER_CONVENTION_SLS "\"SLS_1.0\""
#define CIF_HEADER_CONVENTION_SLS_11 "\"SLS/DECTRIS_1.1\""

namespace pni{
namespace utils{

//! \ingroup io_classes
//! \brief base clase for CBF readers

//! CBFReader is the base class for all readers of data stored in binary CIF format.
//! Although CBF is standardized by the ICUR the guys from Dectris (the vendor of the Pilatus
//! detector) use a kind of dialect which must be treated in a slightly different way.
//! The field _header_convention in the class indicates whether or not the header is
//! in standard CBF format or in the Dectris dialect.
//!
//! Reading a CBF file is a two step process:
//! - the header is read and the information stored there kept in in a CIFBinaryHeader object
//! - the binary data is read from the stream using a CBFBinStreamReader object
//! The header information contains enough information to decide which binary reader to use
//! and to construct the data objects which will hold the data read from the file.
//! From such a point of view the header object can be consideres as a factory for the binary
//! readers and the array objects holding the data.
class CBFReader: public Reader {
private:
	//like all other readers the CBFReader must not be
	//copied or assigned
	CBFReader(const CBFReader &r){}
	CBFReader &operator=(const CBFReader &r){return *this;}
protected:
	String _header_convention_;  //!< string defining the header convention
	char buffer_[1024]; 		 //!< buffer for what ever purpose
	CIFBinaryHeader *_binheader; //!< header object
public:
	//! default constructor
	CBFReader();
	//! standard constructor

	//! The name of the CBFFile is passed as a C string.
	CBFReader(const char* filename);
	//! standard constructor

	//! The name of the CBFFile is passed as a String object.
	CBFReader(const String &fname);
	//! destructor
	virtual ~CBFReader();

	//! read data from the file

	//! Data is read from the CBF file and returned as a general
	//! DataObject. This DataObject is typically an instance of Array<T>
	//! - at least in the case of CBF files.
	virtual DataObject::sptr read();
	virtual DataObject::sptr read(const UInt64 &i);
};

}
}

#endif /* CBFREADER_HPP_ */
