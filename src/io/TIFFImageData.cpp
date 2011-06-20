/*
 * TIFFImageData.cpp
 *
 *  Created on: Jun 20, 2011
 *      Author: eugen
 */

#include "TIFFImageData.hpp"

namespace pni {

namespace utils {

TIFFImageData::TIFFImageData(){
	_channels.clear();
}

TIFFImageData::TIFFImageData(const TIFFImageData &o){
	_channels = o._channels;
}

TIFFImageData::~TIFFImageData(){
	_channels.clear();
}

UInt64 TIFFImageData::getNumberOfChannels() const {
	return _channels.size();
}

void TIFFImageData::appendChannel(ArrayObject::sptr ptr){
	_channels.push_back(ptr);
}

ArrayObject::sptr TIFFImageData::getChannel(UInt64 i){
	return _channels[i];
}

ArrayObject::sptr TIFFImageData::operator[](UInt64 i){
	return _channels[i];
}

TIFFImageData &TIFFImageData::operator=(const TIFFImageData &o){
	if(this != &o){
		_channels.clear();
		_channels = o._channels;
	}

	return *this;
}

TIFFImageData::iterator TIFFImageData::begin(){
	return _channels.begin();
}

TIFFImageData::iterator TIFFImageData::end(){
	return _channels.end();
}





}

}
