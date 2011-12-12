/*
 * Implementation of class TIFFReader
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
 * Implementation of class TIFFReader.
 *
 * Created on: Jun 15, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "../Exceptions.hpp"
#include "../Array.hpp"
#include "../Types.hpp"
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
