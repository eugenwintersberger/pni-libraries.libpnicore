/*
 * Declaration of class template CBFBinReaderByteOffset
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
 * Declaration of class template CBFBinReaderByteOffset - reads CBF files
 * with ByteOffset compression.
 *
 * Created on: Apr 19, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef CBFBOREADERS_HPP_
#define CBFBOREADERS_HPP_


#include "CBFBinStreamReader.hpp"
#include "../Exceptions.hpp"
#include "../Buffer.hpp"


namespace pni{
namespace utils{

//! \ingroup io_classes
//! \brief CBF reader for byte-offset compressed data

//! This template provides a reader object for binary data stored in CBF files
//! using the Byte-Offset compression. The template parameter determines the
//! datatype used to store the data.
template<typename T> class CBFBinReaderByteOffset: public CBFBinStreamReader {
public:
	//! default constructor
	CBFBinReaderByteOffset();
	//! standard constructor
	CBFBinReaderByteOffset(unsigned long);
	//! destructor
	virtual ~CBFBinReaderByteOffset();

	//! reading data from the file

	//! This is the concrete implementation of the read method provided
	//! by the CBFBinStreamReader base class.
	virtual void read();




};

template<typename T> CBFBinReaderByteOffset<T>::CBFBinReaderByteOffset() :
	CBFBinStreamReader() {
}

template<typename T> CBFBinReaderByteOffset<T>::CBFBinReaderByteOffset(
		unsigned long n) :
	CBFBinStreamReader(n) {
	elemsize_ = sizeof(T);
}
;

template<typename T> CBFBinReaderByteOffset<T>::~CBFBinReaderByteOffset() {
}

template<typename T> void CBFBinReaderByteOffset<T>::read() {
	//unsigned long i;
	unsigned long ecnt; // element counter
	T buffer;
	Buffer<T> &dbuffer = (Buffer<T> &)(*_buffer);

	buffer = 0;
	ecnt = 0;

	//initialize all data values with 0
	dbuffer = 0;

	//std::cout << "start with reading binary data ..." << std::endl;
	while ((!_stream->eof()) && (ecnt != nelements_)) {

		_stream->read((char *) (&buffer), 1);
		if (((unsigned char) buffer) != 0x80){
			//this byte is a valid offset
			dbuffer[ecnt] += (char) buffer;
			//now we have to increment the element counter
			ecnt++;
			if (ecnt >= nelements_)
				break;
			dbuffer[ecnt] = dbuffer[ecnt - 1];
			//reset the buffer so that all bits are set to 0
			buffer = 0;
			continue;
		}

		_stream->read((char *) (&buffer), 2);
		if (((unsigned short) buffer) != 0x8000) {
			dbuffer[ecnt] += (short) buffer;
			//increase the element counter
			ecnt++;
			if (ecnt >= nelements_)
				break;
			dbuffer[ecnt] = dbuffer[ecnt - 1];
			//reset the buffer so that all bits are set to 0
			buffer = 0;
			continue;
		}

		_stream->read((char*) (&buffer), 4);
		if (((unsigned int) buffer) != 0x800000) {
			dbuffer[ecnt] += (int) buffer;
			//increase the element counter
			ecnt++;
			if (ecnt >= nelements_)
				break;
			dbuffer[ecnt] = dbuffer[ecnt - 1];
			buffer = 0;
			continue;
		}

	}
	//std::cout << "read " << ecnt << " elements to the data buffer" << std::endl;
}

//standard reader actually supported
typedef CBFBinReaderByteOffset<short> CBFBinStreamBOInt16;
typedef CBFBinReaderByteOffset<int> CBFBinStreamBOInt32;

//end of namespaces
}
}


#endif /* CBFBOREADERS_HPP_ */
