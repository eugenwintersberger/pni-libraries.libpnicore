/*
 * Reader.cpp
 *
 *  Created on: May 26, 2011
 *      Author: eugen
 */

#include "Reader.hpp"

namespace pni{
namespace utils{


Reader::Reader() {
	//we do not have to do something here
}

Reader::Reader(const std::string &fname){
	_fname = fname;
}

Reader::Reader(const char *fname){
	//call the proper constructor here
	Reader(std::string(fname));
}


Reader::~Reader() {
	//close the stream if it is open and release
	//memory for the filename

	if(_istream.is_open()) _istream.close();
	_fname.clear();
}

void Reader::open(){
	EXCEPTION_SETUP("void Reader::open()");
	//before we open a file we have to check if the stream is already open
	//and close it if this is the case
	if(_istream.is_open()) _istream.close();

	_istream.open(_fname.c_str());

	if(_istream.fail()){
		EXCEPTION_INIT(FileError,"Error opening file");
		EXCEPTION_THROW();
	}
}

void Reader::close(){
	if(_istream.is_open()) _istream.close();
}

void Reader::setFileName(const std::string &s){
	//close the file before changing the file name
	close();
	_fname = s;
}

void Reader::setFileName(const char *s){
	setFileName(std::string(s));
}

DataObject *Reader::read(){
	EXCEPTION_SETUP("void Reader::read(DataObject &o)");
	EXCEPTION_INIT(NotImplementedError,"This method must be overridden by child classes!");
	EXCEPTION_THROW();
}



}}
