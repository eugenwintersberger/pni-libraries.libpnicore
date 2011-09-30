/*
 * Implementation of class TIFFFile
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
 * Implementation of class TIFFFile.
 *
 * Created on: Jun 16, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include <iostream>
#include <cmath>

#include "../Exceptions.hpp"

#include "TIFFFile.hpp"
#include "TIFFStripReader.hpp"
#include "TIFFExceptions.hpp"

namespace pni{
namespace utils{


TIFFFile::TIFFFile(){
	_is_little_endian = false;
	_is_big_endian = false;
	_fname = String("");
}

TIFFFile::TIFFFile(const char *n){
	_is_little_endian = false;
	_is_big_endian = false;
	_fname = String(n);

}
TIFFFile::TIFFFile(const String &n){
	_is_little_endian = false;
	_is_big_endian = false;
	_fname = n;
}

TIFFFile::~TIFFFile(){
	_is_little_endian = false;
	_is_big_endian = false;

	_ifd_list.clear();
	//close stream if it is still open
	close();


}

void TIFFFile::setFileName(const String &n){
	_fname = n;

	//close the file if it is still open
	close();
}

void TIFFFile::setFileName(const char *n){
	setFileName(String(n));
}

String TIFFFile::getFileName() const{
	return _fname;
}

void TIFFFile::open(){
	EXCEPTION_SETUP("void TIFFFile::open()");
	Int32 idf_offset;

	//open the file if it is not already opened
	if(!_ifstream.is_open()){
		_ifstream.open(_fname.c_str(),std::ifstream::binary | std::ifstream::in );
		if(_ifstream.fail()){
			EXCEPTION_INIT(FileError,"Cannot open file "+_fname+" for reading");
			EXCEPTION_THROW();
		}
	}

	//in the first step we need to find out if the file is really a
	//TIFF file and how it looks with endieness
	char buffer[2];
	_ifstream.read(buffer,2);
	if((buffer[0]=='I')&&(buffer[1]=='I')) _is_little_endian = true;
	if((buffer[0]=='M')&&(buffer[1]=='M')) _is_big_endian = true;

	UInt16 magic;
	_ifstream.read((char *)(&magic),2);
	if(magic!=42){
		EXCEPTION_INIT(FileError,"File "+_fname+"is not a valid TIFF file!");
		EXCEPTION_THROW();
	}

	//read the first IDF offset
	idf_offset = 0;
	_ifstream.read((char*)(&idf_offset),4);

	//read IDFs from the file
	do{
		TIFFIFD::IFDSptr idf(new TIFFIFD());
		_ifstream.seekg(idf_offset, std::ios::beg);
		_ifstream >> *idf;
		_ifd_list.push_back(idf);
		idf_offset = idf->getNextOffset();
	}while(idf_offset);

	//here we should place some parsing code
}

void TIFFFile::close(){
	if(_ifstream.is_open()) _ifstream.close();
}

UInt64 TIFFFile::getNumberOfIFDs() const{
	return _ifd_list.size();
}

bool TIFFFile::isLittleEndian() const{
	return _is_little_endian;
}

bool TIFFFile::isBigEndian() const{
	return _is_big_endian;
}

TIFFIFD &TIFFFile::operator[](const UInt16 i){
	//need a check here
	return *(_ifd_list[i]);
}


std::ostream &operator<<(std::ostream &o,const TIFFFile &f){
	o<<"TIFF File: "<<f.getFileName()<<std::endl;
	o<<"Byte order: ";
	if(f.isBigEndian()) o<<"big endian"<<std::endl;
	if(f.isLittleEndian()) o<<"little endian"<<std::endl;

	//iterate over all IFDs
	for(TIFFIFD::const_IFDIterator iter = f._ifd_list.begin();iter!=f._ifd_list.end();iter++){
		std::cout<<*(*iter)<<std::endl;
	}

	return o;
}

TIFFImageData::sptr TIFFFile::getData(UInt64 i) const {
	EXCEPTION_SETUP("TIFFImageData::sptr TIFFFile::getData(UInt64 i) const");
	UInt64 uibuffer;
	IFDAbstractEntry::sptr e;
	TIFFIFD &idf = *(_ifd_list[i]);
	TIFFStripReader reader;

	//need to determine the dimension of the image
	try{
		e = idf["ImageWidth"];
	}catch(KeyError &error){
		//raise an exceptions if the ImageWidth entry could not be found
		EXCEPTION_INIT(TIFFReadError,"Error reading TIFF file - ImageWidth entry not found!");
		EXCEPTION_THROW();
	}
	switch(e->getEntryTypeCode()){
	case IDFE_SHORT:
		uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
	case IDFE_LONG:
		uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[0]; break;
	default:
		//raise an exception if the type of the IFD etnry is not known
		EXCEPTION_INIT(TypeError,"Unknown IDF entry type!");
		EXCEPTION_THROW();
	}
	reader.setWidth(uibuffer);


	try{
		e = idf["ImageLength"];
	}catch(KeyError &error){
		EXCEPTION_INIT(TIFFReadError,"Error reading TIFF file - ImageLength entry not found!");
		EXCEPTION_THROW();
	}
	switch(e->getEntryTypeCode()){
	case IDFE_SHORT:
		uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
	case IDFE_LONG:
		uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[0];break;
	default:
		EXCEPTION_INIT(TypeError,"Unknown IDF entry type!");
		EXCEPTION_THROW();
		break;
	}
	reader.setHeight(uibuffer);

	//next task is to determine the data type
	//determine the Bits per Sample
	try{
		e = idf["BitsPerSample"];
	}catch(KeyError &error){
		EXCEPTION_INIT(TIFFReadError,"Error reading TIFF file - BitsPerSample entry not found!");
		EXCEPTION_THROW();
	}
	UInt16 pbs = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];

	//determine the data type used to store the data
	UInt16 dtype = 1;
	try{
		e = idf["SampleFormat"];
		dtype = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];
	}catch(KeyError &error){
		//do nothing here
		dtype = 1;
	}

	//determine the number of samples per image - in other words
	//determines the number of channels
	UInt16 ns = 1;
	try{
		e = idf["SamplesPerPixel"];
		ns = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];
	}catch(KeyError &error){
		ns = 1;
	}
	reader.setNumberOfChannels(ns);

	//determine the number of rows per strip
	UInt16 rps = 1;
	try{
		e = idf["RowsPerStrip"];
		switch(e->getEntryTypeCode()){
		case IDFE_SHORT:
			rps = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
		case IDFE_LONG:
			rps = (*boost::dynamic_pointer_cast<LongEntry>(e))[0]; break;
		default:
			EXCEPTION_INIT(TypeError,"Unknown IFD entry type!");
			EXCEPTION_THROW();
			break;
		}
	}catch(KeyError &error){
		//EXCEPTION_INIT(TIFFReadError,"Error reading TIFF file - RowsPerStrip entry not found!");
		//EXCEPTION_THROW();
		rps = reader.getHeight();
	}

	//from rows per strip and the number image height dim[0] one can determine
	//how many strips are used to assemble the image
	Int64 nstrips = 1;
	nstrips = (UInt64)std::floor((double)(reader.getHeight()+rps-1)/rps);
	reader.setNumberOfStrips((UInt64)nstrips);

	//in the next step we need to determine the strip offsets
	try{
		e = idf["StripOffsets"];
	}catch(KeyError &error){
		EXCEPTION_INIT(TIFFReadError,"Error reading TIFF file - StripOffsets entry not found!");
		EXCEPTION_THROW();
	}
	for(UInt64 i=0;i<(UInt64)nstrips;i++){
		switch(e->getEntryTypeCode()){
		case IDFE_SHORT:
			uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[i]; break;
		case IDFE_LONG:
			uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[i]; break;
		default:
			EXCEPTION_INIT(TypeError,"Unknown IFD entry type!");
			EXCEPTION_THROW();
			break;
		}
		reader.setStripOffset(i,uibuffer);
	}

	//finally we need the byte count for each strip
	try{
		e = idf["StripByteCounts"];
	}catch(KeyError &error){
		EXCEPTION_INIT(TIFFReadError,"Error reading TIFF file - StripByteCounts entry not found!");
		EXCEPTION_THROW();
	}

	for (UInt64 i = 0; i < (UInt64)nstrips; i++) {
		switch (e->getEntryTypeCode()) {
		case IDFE_SHORT:
			uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[i];
			break;
		case IDFE_LONG:
			uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[i];
			break;
		default:
			EXCEPTION_INIT(TypeError,"Unknown IFD entry type!");
			EXCEPTION_THROW();
			break;
		}
		reader.setStripByteCount(i, uibuffer);
	}


	//create new image data object
	TIFFImageData::sptr idata(new TIFFImageData());

	//the reader configuration is done - now we can start with reading
	//data
	switch(pbs){
	case 8:
		switch(dtype){
		case 1: //unsigned data
			reader.read<UInt8>((std::ifstream &)_ifstream,idata); break;
		case 2: //signed data
			reader.read<Int8>((std::ifstream &)_ifstream,idata); break;
		default:
			EXCEPTION_INIT(TypeError,"Unsupported sample format for 8Bit samples!");
			EXCEPTION_THROW();
			break;
		}
		break;
	case 16:
		switch(dtype){
		case 1: //unsigned data
			reader.read<UInt16>((std::ifstream &)_ifstream,idata); break;
		case 2: //signed data
			reader.read<Int16>((std::ifstream &)_ifstream,idata); break;
		default:
			EXCEPTION_INIT(TypeError,"Unsupported sample format for 16Bit samples!");
			EXCEPTION_THROW();
			break;
		}
		break;
	case 32:
		switch(dtype){
		case 1: //unsigned data
			reader.read<UInt32>((std::ifstream &)_ifstream,idata); break;
		case 2: //signed data
			reader.read<Int32>((std::ifstream &)_ifstream,idata); break;
		case 3: //float data
			reader.read<Float32>((std::ifstream &)_ifstream,idata); break;
		default:
			EXCEPTION_INIT(TypeError,"Unsupported sample format for 32Bit samples!");
			EXCEPTION_THROW();
			break;
		}
		break;
	case 64:
		switch(dtype){
		case 1: //unsigned data
			reader.read<UInt64>((std::ifstream &)_ifstream,idata); break;
		case 2: //signed data
			reader.read<Int64>((std::ifstream &)_ifstream,idata); break;
		case 3:
			reader.read<Float64>((std::ifstream &)_ifstream,idata); break;
		default:
			EXCEPTION_INIT(TypeError,"Unsupported sample format for 64Bit samples!");
			EXCEPTION_THROW();
			break;
		}
		break;
	default:
		std::cerr<<"unsupported number of bits per sample!"<<std::endl;
		break;
		//raise an exception here
	}




	return idata;
}

//end of namespace
}
}
