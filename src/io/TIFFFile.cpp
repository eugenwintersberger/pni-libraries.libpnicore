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
		_ifstream.seekg(idf_offset, std::ios::beg);
		TIFFIDF idf;
		_ifstream >> idf;
		std::cout << idf;
		_idf_list.push_back(idf);
		idf_offset = idf.getNextOffset();
	}while(idf_offset);

	//here we should place some parsing code
}

void TIFFFile::close(){
	if(_ifstream.is_open()) _ifstream.close();
}

UInt64 TIFFFile::getNumberOfIFDs() const{

	return 0;
}

bool TIFFFile::isLittleEndian() const{
	return _is_little_endian;
}

bool TIFFFile::isBigEndian() const{
	return _is_big_endian;
}

std::ostream &operator<<(std::ostream &o,const TIFFFile &f){
	o<<"TIFF File: "<<f.getFileName()<<std::endl;
	o<<"Byte order: ";
	if(f.isBigEndian()) o<<"big endian"<<std::endl;
	if(f.isLittleEndian()) o<<"little endian"<<std::endl;

	return o;
}

//end of namespace
}
}
