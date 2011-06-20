/*
 * TIFFFile.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#include <iostream>

#include "../Exceptions.hpp"

#include "TIFFFile.hpp"

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
	Int32 idf_offset;

	//open the file if it is not already opened
	if(!_ifstream.is_open()){
		_ifstream.open(_fname.c_str(),std::ifstream::binary | std::ifstream::in );
		if(_ifstream.fail()){
			FileError e;
			e.setSource("TIFFFile::open");
			e.setDescription(String("Cannot open file ")+_fname+String(" for reading"));
			throw e;
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
		FileError e;
		e.setSource("TIFFFile::open");
		e.setDescription(String("File ")+_fname+String("is not a valid TIFF file!"));
		throw e;
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
	UInt64 dims[2];
	IFDAbstractEntry::sptr e;
	TIFFIFD &idf = *(_ifd_list[i]);
	//ArrayObject *a;

	//need to determine the dimension of the image
	e = idf["ImageWidth"];
	switch(e->getEntryTypeCode()){
	case IDFE_SHORT:
		dims[1] = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
	case IDFE_LONG:
		dims[1] = (*boost::dynamic_pointer_cast<LongEntry>(e))[0]; break;
	default:
		std::cerr<<"Unknown image width!"<<std::endl;
		dims[1] = 0;
	}

	e = idf["ImageLength"];
	switch(e->getEntryTypeCode()){
	case IDFE_SHORT:
		dims[0] = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0]; break;
	case IDFE_LONG:
		dims[0] = (*boost::dynamic_pointer_cast<LongEntry>(e))[0];break;
	default:
		std::cerr<<"Unkown image length!"<<std::endl;
		dims[0] = 0;
	}

	std::cout<<dims[0]<<" x "<<dims[1]<<std::endl;

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

	//determine the number of samples per image
	UInt16 ns;
	e = idf["SamplesPerPixel"];
	ns = 1;
	if(e!=NULL) ns = (*boost::dynamic_pointer_cast<ShortEntry>(e))[0];

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
			std::cerr<<"Numb of rows per strip is of unknown type!"<<std::endl;
		}
	}



	//with the value of dtype and pbs one can determine the data type
	//used to store the data

	//create new image data object
	TIFFImageData::sptr idata(new TIFFImageData());

	//first loop over each strip
	UInt64 strip_index;
	for(strip_index = 0;strip_index < nstrips;)



	return idata;
}

//end of namespace
}
}
