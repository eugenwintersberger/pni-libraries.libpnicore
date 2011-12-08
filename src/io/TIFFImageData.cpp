/*
 * Implementation of class TIFFImageData
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
 * Implementation of class TIFFImageData.
 *
 * Created on: Jun 20, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "../Array.hpp"

#include "TIFFImageData.hpp"

namespace pni {
namespace utils {

//------------------------------------------------------------------------------
TIFFImageData::TIFFImageData(){
	_channels.clear();
}

//------------------------------------------------------------------------------
TIFFImageData::TIFFImageData(const TIFFImageData &o){
	_channels = o._channels;
}

//------------------------------------------------------------------------------
TIFFImageData::~TIFFImageData(){
	_channels.clear();
}

//------------------------------------------------------------------------------
UInt64 TIFFImageData::getNumberOfChannels() const {
	return _channels.size();
}

//------------------------------------------------------------------------------
void TIFFImageData::appendChannel(ArrayObject::sptr ptr){
	_channels.push_back(ptr);
}

//------------------------------------------------------------------------------
ArrayObject::sptr TIFFImageData::getChannel(UInt64 i){
	return _channels[i];
}

//------------------------------------------------------------------------------
ArrayObject::sptr TIFFImageData::operator[](UInt64 i){
	return _channels[i];
}

//------------------------------------------------------------------------------
TIFFImageData &TIFFImageData::operator=(const TIFFImageData &o){
	if(this != &o){
		_channels.clear();
		_channels = o._channels;
	}

	return *this;
}

//------------------------------------------------------------------------------
TIFFImageData::iterator TIFFImageData::begin(){
	return _channels.begin();
}

//------------------------------------------------------------------------------
TIFFImageData::const_iterator TIFFImageData::begin() const {
	return _channels.begin();
}

//------------------------------------------------------------------------------
TIFFImageData::iterator TIFFImageData::end(){
	return _channels.end();
}

//------------------------------------------------------------------------------
TIFFImageData::const_iterator TIFFImageData::end() const {
	return _channels.end();
}

//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const TIFFImageData &d){
	o<<"TIFF image data with "<<d._channels.size()<<" samples per pixle"<<std::endl;

	TIFFImageData::const_iterator iter;
	for(iter = d.begin();iter!=d.end();iter++){
		ArrayObject &a = *boost::dynamic_pointer_cast<ArrayObject>(*iter);
		switch(a.type_id()){
		case PNITypeID::UINT8:
			o<<*boost::dynamic_pointer_cast<UInt8Array>(*iter)<<std::endl; break;
		case PNITypeID::INT8:
			o<<*boost::dynamic_pointer_cast<Int8Array>(*iter)<<std::endl; break;
		case PNITypeID::UINT16:
			o<<*boost::dynamic_pointer_cast<UInt16Array>(*iter)<<std::endl; break;
		case PNITypeID::INT16:
			o<<*boost::dynamic_pointer_cast<Int16Array>(*iter)<<std::endl; break;
		case PNITypeID::UINT32:
			o<<*boost::dynamic_pointer_cast<UInt32Array>(*iter)<<std::endl; break;
		case PNITypeID::INT32:
			o<<*boost::dynamic_pointer_cast<Int32Array>(*iter)<<std::endl; break;
		case PNITypeID::FLOAT32:
			o<<*boost::dynamic_pointer_cast<Float32Array>(*iter)<<std::endl; break;
		case PNITypeID::FLOAT64:
			o<<*boost::dynamic_pointer_cast<Float64Array>(*iter)<<std::endl; break;
		default:
			std::cerr<<"Array of unknown Type"<<std::endl;
		}
	}

	return o;
}



//end of namespace
}
}
