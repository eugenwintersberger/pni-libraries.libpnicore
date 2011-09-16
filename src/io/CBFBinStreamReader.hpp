/*
 * cbfbinstreamreader.hpp
 *
 *  Created on: Apr 20, 2011
 *      Author: eugen
 */

#ifndef CBFBINSTREAMREADER_HPP_
#define CBFBINSTREAMREADER_HPP_

#include<iostream>
#include<boost/shared_ptr.hpp>

#include "../Buffer.hpp"
#include "../PNITypes.hpp"

namespace pni{
namespace utils{

//! \ingroup IO
//! \brief binary CBF data reader

//! This is the base class for all binary CBF reades. The aim of all this
//! classes is to decode the binary data stream in a CBF file and
//! store it to a buffer for further processing.
//! The buffer is passed to the class as a shared pointer of type BufferObject.
//! The reader class is not very intelligent - the
//! buffer object must be provided by the code that wants to use this reader class.
//! In addition the CBFBinReaderByteOffset class does not resize the buffer object
//! if necessary. The buffer must have the appropriate size when it is passed
//! to the reader class. This might be changed in future but works quite fine for now.
class CBFBinStreamReader {
private:
	//neither copying nor assignemnt is allowed!
	CBFBinStreamReader(const CBFBinStreamReader &o){}
	CBFBinStreamReader &operator=(const CBFBinStreamReader &o){return *this;}
protected:
	UInt64 nelements_;          //!< total number of elements to read
	UInt32 elemsize_;           //!< size of each element in bytes (depends on the type)
	std::ifstream *_stream;     //!< stream from which to read the data
	BufferObject* _buffer;      //!< buffer object which holds the data read from the stream
public:
	//! default constructor
	CBFBinStreamReader();
	//! constructor

	//! \param n number of elements to read from the stream.
	CBFBinStreamReader(unsigned long n);
	//! destructor
	virtual ~CBFBinStreamReader();
	//! set the stream from which to read

	//! since streams cannot be copied or assigned a pointer is used
	//! to access the stream from which data should be read.

	//! \param *s pointer to the stream to read from
	virtual void setStream(std::ifstream *s) {
		_stream = s;
	}

	//! read data from the stream - dummy version
	virtual void read() {
		std::cout << "call base reader - does nothing!" << std::endl;
	}
	;

	//! set the data buffer to which to write the data
	virtual void setBuffer(const BufferObject &buffer){
		_buffer = &(BufferObject &)buffer;
	}

	//! get the buffer object that stores the data
	virtual BufferObject* getBuffer(){
		return _buffer;
	}

};

//end of namespace
}
}

#endif /* CBFBINSTREAMREADER_HPP_ */
