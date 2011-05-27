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


template<typename T> class CBFBinReaderByteOffset: public CBFBinStreamReader {
private:
	boost::shared_ptr<Buffer<T> > _buffer;
public:
	CBFBinReaderByteOffset();
	CBFBinReaderByteOffset(unsigned long);
	virtual ~CBFBinReaderByteOffset();

	virtual void read();
	virtual boost::shared_ptr<Buffer<T> > &getBuffer(){
		return _buffer;
	}

	virtual void setBuffer(boost::shared_ptr<BufferObject > buffer){
		_buffer = boost::shared_static_cast<Buffer<T> >(buffer);
	}

};

template<typename T> CBFBinReaderByteOffset<T>::CBFBinReaderByteOffset() :
	CBFBinStreamReader() {
	_buffer.reset();
}

template<typename T> CBFBinReaderByteOffset<T>::CBFBinReaderByteOffset(
		unsigned long n) :
	CBFBinStreamReader(n) {
	elemsize_ = sizeof(T);
	_buffer.reset();
}
;

template<typename T> CBFBinReaderByteOffset<T>::~CBFBinReaderByteOffset() {
	_buffer.reset();
}

template<typename T> void CBFBinReaderByteOffset<T>::read() {
	//unsigned long i;
	unsigned long ecnt; // element counter
	T buffer;

	buffer = 0;
	ecnt = 0;

	//initialize all data values with 0
	*_buffer = 0;

	std::cout << "start with reading binary data ..." << std::endl;
	while ((!_stream->eof()) && (ecnt != nelements_)) {

		_stream->read((char *) (&buffer), 1);
		if (((unsigned char) buffer) != 0x80) {
			//this byte is a valid offset
			(*_buffer)[ecnt] += (char) buffer;
			//now we have to increment the element counter
			ecnt++;
			if (ecnt >= nelements_)
				break;
			(*_buffer)[ecnt] = (*_buffer)[ecnt - 1];
			//reset the buffer so that all bits are set to 0
			buffer = 0;
			continue;
		}

		_stream->read((char *) (&buffer), 2);
		if (((unsigned short) buffer) != 0x8000) {
			(*_buffer)[ecnt] += (short) buffer;
			//increase the element counter
			ecnt++;
			if (ecnt >= nelements_)
				break;
			(*_buffer)[ecnt] = (*_buffer)[ecnt - 1];
			//reset the buffer so that all bits are set to 0
			buffer = 0;
			continue;
		}

		_stream->read((char*) (&buffer), 4);
		if (((unsigned int) buffer) != 0x800000) {
			(*_buffer)[ecnt] += (int) buffer;
			//increase the element counter
			ecnt++;
			if (ecnt >= nelements_)
				break;
			(*_buffer)[ecnt] = (*_buffer)[ecnt - 1];
			buffer = 0;
			continue;
		}

	}
	std::cout << "read " << ecnt << " elements to the data buffer" << std::endl;
}

typedef CBFBinReaderByteOffset<short> CBFBinStreamBOInt16;
typedef CBFBinReaderByteOffset<int> CBFBinStreamBOInt32;

//end of namespaces
}
}


#endif /* CBFBOREADERS_HPP_ */
