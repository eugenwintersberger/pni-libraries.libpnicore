/*
 * TIFFReader.hpp
 *
 *  Created on: Jun 15, 2011
 *      Author: eugen
 */

#ifndef TIFFREADER_HPP_
#define TIFFREADER_HPP_

#include <boost/shared_ptr.hpp>

#include "Reader.hpp"
#include "TIFFFile.hpp"
#include "TIFFImageData.hpp"



namespace pni{
namespace utils{


class TIFFReader:public Reader {
private:
	//like all other derivatives of Reader the TIFFReader
	//cannot be copied or assigned to.
	TIFFReader(const TIFFReader &){}
	TIFFReader &operator=(const TIFFReader &o){return *this;}
protected:
	TIFFFile _file;
public:
	TIFFReader();
	virtual ~TIFFReader();

	virtual void setFileName(const String &n);
	virtual void setFileName(const char *n);

	virtual void open();
	virtual void close();
	virtual DataObject::sptr read();
	virtual DataObject::sptr read(const UInt64 &i);
};

//end of namespace
}
}

#endif /* TIFFREADER_HPP_ */
