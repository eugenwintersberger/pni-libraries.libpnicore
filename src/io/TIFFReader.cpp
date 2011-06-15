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
	// TODO Auto-generated constructor stub
	_tiff = NULL;

}

TIFFReader::~TIFFReader() {
	// TODO Auto-generated destructor stub
}

void TIFFReader::open(){
	_tiff = TIFFOpen(_fname.c_str(),"r");
	if(_tiff==NULL){
		//something went wrong
		FileError e;
		e.setSource("TIFFReader::open");
		e.setDescription(pni::utils::String("cannot open file ")+_fname+pni::utils::String(" for reading"));
		throw e;
	}
}

void TIFFReader::close(){
	if(_tiff!=NULL) TIFFClose(_tiff);
}

DataObject *TIFFReader::read(){
	UInt32Array *array;
	UInt32 shape[2];
	uint32 w,h;

	//determine the dimension of the image
	TIFFGetField(_tiff,TIFFTAG_IMAGEWIDTH,&w);
	TIFFGetField(_tiff,TIFFTAG_IMAGELENGTH,&h);
	shape[0] = (UInt64)h;
	shape[1] = (UInt64)w;


	//allocate array memory
	array = new UInt32Array(2,shape);
	Buffer<UInt32>::sptr buffer = boost::static_pointer_cast<Buffer<UInt32> >(array->getBuffer());

	TIFFReadRGBAImage(_tiff,w,h,buffer->getPtr(),0);

	//in the end we have to return the array data
	return array;
}


//end of namespace
}
}
