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
	UInt32 shape[2];
	uint32 w,h;
	uint32 *raster;
	UInt64 i,j;

	//determine the dimension of the image
	TIFFGetField(_tiff,TIFFTAG_IMAGEWIDTH,&w);
	TIFFGetField(_tiff,TIFFTAG_IMAGELENGTH,&h);
	shape[0] = (UInt64)h;
	shape[1] = (UInt64)w;

	//fetch some tags to obtain information about the
	//image data
	UInt16 sperpix,bpersamp,dtype;
	TIFFGetField(_tiff,TIFFTAG_SAMPLESPERPIXEL,&sperpix);
	TIFFGetField(_tiff,TIFFTAG_BITSPERSAMPLE,&bpersamp);
	TIFFGetField(_tiff,TIFFTAG_DATATYPE,&dtype);
	std::cout<<"Samples per pixel: "<<sperpix<<std::endl;
	std::cout<<"Bits per sample: "<<bpersamp<<std::endl;

	if(TIFFIsByteSwapped(_tiff)){
		std::cout<<"byte swapped data"<<std::endl;
	}


	raster = (uint32 *)_TIFFmalloc(w*h*sizeof(uint32));
	TIFFReadRGBAImage(_tiff, w, h,raster, 0);
	UInt32Array *array = new UInt32Array(2, shape);
	for(i=0;i<h*w;i++){
		(*array)[i] = (UInt32)raster[i];
	}

	std::cout<<array->Min()<<" "<<array->Max()<<std::endl;

	_TIFFfree(raster);
	return (DataObject *)array;

}


//end of namespace
}
}
