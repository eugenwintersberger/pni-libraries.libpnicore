/*
 * cbfboreaders.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#ifndef CBFBOREADERS_HPP_
#define CBFBOREADERS_HPP_

#include <boost/shared_ptr.hpp>

#include "CBFBinStreamReader.hpp"
#include "../Exceptions.hpp"
#include "../Buffer.hpp"


namespace pni{
namespace utils{

//! \ingroup IO
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
	Buffer<T> &dbuffer = *boost::dynamic_pointer_cast<Buffer<T> >(_buffer);

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
