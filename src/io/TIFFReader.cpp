/*
 * TIFFReader.cpp
 *
 *  Created on: Jun 15, 2011
 *      Author: eugen
 */

#include "../Exceptions.hpp"
#include "../Array.hpp"
#include "../PNITypes.hpp"
#include "../Buffer.hpp"
#include "TIFFReader.hpp"

namespace pni{
namespace utils{


TIFFReader::TIFFReader() {
}

TIFFReader::~TIFFReader() {
	_file.close();
}

void TIFFReader::open(){
	_file.open();
}

void TIFFReader::close(){
	_file.close();
}

void TIFFReader::setFileName(const String &n){
	_file.setFileName(n);
}

void TIFFReader::setFileName(const char *n){
	_file.setFileName(n);
}

DataObject::sptr TIFFReader::read(){
	TIFFImageData::sptr idata;

	//read the first image from the stack
	idata = _file.getData(0);

	return boost::dynamic_pointer_cast<DataObject>(idata->getChannel(0));
}

DataObject::sptr TIFFReader::read(const UInt64 &i){
	TIFFImageData::sptr idata;

	idata = _file.getData(i);
	return boost::dynamic_pointer_cast<DataObject>(idata->getChannel(0));
}


//end of namespace
}
}
