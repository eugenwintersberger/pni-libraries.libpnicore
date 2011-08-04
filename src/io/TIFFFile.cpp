/*
 * TIFFFile.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#include <iostream>
#include <cmath>

#include "../Exceptions.hpp"

#include "TIFFFile.hpp"
#include "TIFFStripReader.hpp"

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
	UInt64 uibuffer;
	IFDAbstractEntry::sptr e;
	TIFFIFD &idf = *(_ifd_list[i]);
	TIFFStripReader reader;

	//need to determine the dimension of the image
	e = idf["ImageWidth"];
	switch(e->getEntryTypeCode()){
	case IDFE_SHORT:
		uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
	case IDFE_LONG:
		uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[0]; break;
	default:
		std::cerr<<"Unknown image width!"<<std::endl;
		uibuffer = 0;
	}
	reader.setWidth(uibuffer);

	e = idf["ImageLength"];
	switch(e->getEntryTypeCode()){
	case IDFE_SHORT:
		uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
	case IDFE_LONG:
		uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[0];break;
	default:
		std::cerr<<"Unkown image length!"<<std::endl;
		uibuffer = 0;
	}
	reader.setHeight(uibuffer);

	//next task is to determine the data type
	//determine the Bits per Sample
	e = idf["BitsPerSample"];
	UInt16 pbs = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];

	//determine the data type used to store the data
	e = idf["SampleFormat"];
	UInt16 dtype;
	if(e != NULL){
		dtype = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];
	}else{
		dtype = 1;
	}

	//determine the number of samples per image - in other words
	//determines the number of channels
	UInt16 ns;
	e = idf["SamplesPerPixel"];
	ns = 1;
	if(e!=NULL) ns = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];
	reader.setNumberOfChannels(ns);

	//determine the number of rows per strip
	UInt16 rps = 1;
	e = idf["RowsPerStrip"];
	if(e!=NULL){
		switch(e->getEntryTypeCode()){
		case IDFE_SHORT:
			rps = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
		case IDFE_LONG:
			rps = (*boost::dynamic_pointer_cast<LongEntry>(e))[0]; break;
		default:
			std::cerr<<"Number of rows per strip is of unknown type!"<<std::endl;
		}
	}

	//from rows per strip and the number image height dim[0] one can determine
	//how many strips are used to assemble the image
	Int64 nstrips = 1;
	nstrips = (UInt64)std::floor((double)(reader.getHeight()+rps-1)/rps);
	reader.setNumberOfStrips((UInt64)nstrips);

	//in the next step we need to determine the strip offsets
	e = idf["StripOffsets"];
	if(e==NULL){
		//raise an exception if there are no strip offsets
	}
	for(UInt64 i=0;i<(UInt64)nstrips;i++){
		switch(e->getEntryTypeCode()){
		case IDFE_SHORT:
			uibuffer = (*boost::dynamic_pointer_cast<ShortEntry>(e))[i]; break;
		case IDFE_LONG:
			uibuffer = (*boost::dynamic_pointer_cast<LongEntry>(e))[i]; break;
		default:
			std::cerr<<"Strip offset uses unknown type!"<<std::endl;
		}
		reader.setStripOffset(i,uibuffer);
	}

	//finally we need the byte count for each strip
	e = idf["StripByteCounts"];
	if(e==NULL){
		//raise an exception here
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
			std::cerr << "Strip offset uses unknown type!" << std::endl;
			//raise an exception here
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
			std::cerr<<"unsupported sample format for 8Bit samples!"<<std::endl;
			//raise an exception here
		}
		break;
	case 16:
		switch(dtype){
		case 1: //unsigned data
			reader.read<UInt16>((std::ifstream &)_ifstream,idata); break;
		case 2: //signed data
			reader.read<Int16>((std::ifstream &)_ifstream,idata); break;
		default:
			std::cerr<<"unsupported sample format for 16 bit samples!"<<std::endl;
			//raise an exception here
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
			std::cerr<<"unsupported sample format for 32Bit samples!"<<std::endl;
			//raise an exception here
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
			std::cerr<<"unsupported sample format for 64Bit samples!"<<std::endl;
			//raise an exception here
		}
		break;
	default:
		std::cerr<<"unsupported number of bits per sample!"<<std::endl;
		//raise an exception here
	}




	return idata;
}

//end of namespace
}
}
