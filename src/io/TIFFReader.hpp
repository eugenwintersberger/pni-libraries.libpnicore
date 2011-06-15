/*
 * TIFFReader.hpp
 *
 *  Created on: Jun 15, 2011
 *      Author: eugen
 */

#ifndef TIFFREADER_HPP_
#define TIFFREADER_HPP_


#include "Reader.hpp"

extern "C"{
#include <tiffio.h>
}

namespace pni{
namespace utils{


class TIFFReader:public Reader {
private:
	TIFFReader(const TIFFReader &){}
protected:
	TIFF *_tiff;
public:
	TIFFReader();
	virtual ~TIFFReader();

	virtual void open();
	virtual void close();
	virtual DataObject *read();
};

//end of namespace
}
}

#endif /* TIFFREADER_HPP_ */
