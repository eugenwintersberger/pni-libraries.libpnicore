/*
 * TIFFStripReader.cpp
 *
 *  Created on: Jun 22, 2011
 *      Author: eugen
 */

#include "../Exceptions.hpp"

#include "TIFFStripReader.hpp"

namespace pni {

namespace utils {

TIFFStripReader::TIFFStripReader() {
	_strip_offsets.clear();
	_strip_byte_counts.clear();
	_nchannels = 0;
	_nstrips = 0;
	_width = 0;
	_height = 0;
}

TIFFStripReader::TIFFStripReader(const TIFFStripReader &o){
	_strip_offsets = o._strip_offsets;
	_strip_byte_counts = o._strip_byte_counts;
	_nchannels = o._nchannels;
	_nstrips = o._nstrips;
	_width = o._width;
	_height = o._height;


}

TIFFStripReader::~TIFFStripReader() {
	_strip_offsets.clear();
	_strip_byte_counts.clear();
	_nchannels = 0;
	_nstrips = 0;
	_width = 0;
	_height = 0;
}


void TIFFStripReader::setStripOffsets(UInt64 offsets[]){
	EXCEPTION_SETUP("void TIFFStripReader::setStripOffsets(UInt64 offsets[])");
	if(_nstrips == 0){
		EXCEPTION_INIT(IndexError,"Number of strips not set or 0!");
		EXCEPTION_THROW();
	}
	for(UInt64 i=0;i<_nstrips;i++){
		_strip_offsets[i] = offsets[i];
	}
}

void TIFFStripReader::setStripOffset(UInt64 i,UInt64 offset){
	EXCEPTION_SETUP("void TIFFStripReader::setStripOffset(UInt64 i,UInt64 offset)");
	if(i>=_nstrips){
		EXCEPTION_INIT(IndexError,"Strip index exceeds number of strip or number of strips not set!");
		EXCEPTION_THROW();
	}
	_strip_offsets[i] = offset;
}

std::vector<UInt64> &TIFFStripReader::getStripOffsets(){
	return _strip_offsets;
}

std::vector<UInt64> TIFFStripReader::getStripOffsets() const{
	return _strip_offsets;
}

UInt64 TIFFStripReader::getStripOffset(UInt64 index) const{
	EXCEPTION_SETUP("UInt64 TIFFStripReader::getStripOffset(UInt64 index) const");
	if(index>=_nstrips){
		EXCEPTION_INIT(IndexError,"Strip index exceeds number of strips or number of strip is not set!");
		EXCEPTION_THROW();
	}
	return _strip_offsets[index];
}

void TIFFStripReader::setStripByteCounts(UInt64 bcounts[]){
	EXCEPTION_SETUP("void TIFFStripReader::setStripByteCounts(UInt64 bcounts[])");
	if(_nstrips==0){
		EXCEPTION_INIT(IndexError,"Number of strips not set!");
		EXCEPTION_THROW();
	}
	for(UInt64 i=0;i<_nstrips;i++) _strip_byte_counts[i] = bcounts[i];
}

void TIFFStripReader::setStripByteCount(UInt64 i,UInt64 bcount){
	EXCEPTION_SETUP("void TIFFStripReader::setStripByteCount(UInt64 i,UInt64 bcount)");
	if(i>=_nstrips){
		EXCEPTION_INIT(IndexError,"Strip index exceeds number of strips or number of strips is not set!");
		EXCEPTION_THROW();
	}
	_strip_byte_counts[i] = bcount;
}

std::vector<UInt64> &TIFFStripReader::getStripByteCounts(){
	return _strip_byte_counts;
}

std::vector<UInt64> TIFFStripReader::getStripByteCounts() const{
	return _strip_byte_counts;
}

UInt64 TIFFStripReader::getStripByteCount(UInt64 index) const{
	if(index>=_nstrips){
		//raise an exception
	}
	return _strip_byte_counts[index];
}

void TIFFStripReader::setNumberOfChannels(UInt64 nc){
	_nchannels = nc;
}

UInt64 TIFFStripReader::getNumberOfChannels() const{
	return _nchannels;
}

void TIFFStripReader::setNumberOfStrips(UInt64 ns){
	_nstrips = ns;
	_strip_byte_counts.resize(ns);
	_strip_offsets.resize(ns);
}

UInt64 TIFFStripReader::getNumberOfStrips() const{
	return _nstrips;
}

void TIFFStripReader::setHeight(UInt64 h){
	_height = h;
}

UInt64 TIFFStripReader::getHeight() const{
	return _height;
}

void TIFFStripReader::setWidth(UInt64 w){
	_width = w;
}

UInt64 TIFFStripReader::getWidth() const{
	return _width;
}

//end of namespace
}
}
