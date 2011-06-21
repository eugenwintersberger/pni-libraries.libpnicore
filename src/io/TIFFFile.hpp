/*
 * TIFFFile.hpp
 *
 *  Created on: Jun 16, 2011
 *      Author: eugen
 */

#ifndef TIFFFILE_HPP_
#define TIFFFILE_HPP_

#include <iostream>
#include <fstream>

#include "../PNITypes.hpp"
#include "../ArrayObject.hpp"
#include "../Array.hpp"

#include "TIFFIFD.hpp"
#include "TIFFImageData.hpp"

namespace pni{
namespace utils{

//! TIFFFile - class representing a TIFF file

class TIFFFile {
private:
	//the copy constructor is protected - the file cannot be
	//copied
	TIFFFile(const TIFFFile &o){}

	template<typename T> void _read_strip_data(UInt64 nchans,UInt64 dims[],UInt64 nstrips,Int32 strip_offsets[],
		    UInt64 strip_byte_count[],TIFFImageData::sptr &data);
	template<typename T> void _read_tile_data();
protected:
	bool   _is_little_endian;    //!<true if file is little endian
	bool   _is_big_endian;       //!<true if file is big endian
	String _fname;               //!<name of the file
	std::ifstream    _ifstream;  //!<input stream to read the file
	TIFFIFD::IFDList _ifd_list;  //!< list of IDFs in a file
public:
	//! default constructor
	TIFFFile();
	//! standard constructor
	TIFFFile(const char *n);
	//! standard constructor
	TIFFFile(const String &n);
	//! destructor
	virtual ~TIFFFile();

	//! set the filename as String object
	virtual void setFileName(const String &n);
	//! set the filename as C string
	virtual void setFileName(const char *n);
	//! return the filename as String object
	virtual String getFileName() const;

	//! open the file
	virtual void open();
	//! close the file
	virtual void close();

	//! return the number of IFDs in the file
	virtual UInt64 getNumberOfIFDs() const;
	//! true if data is stored as little endian
	virtual bool isLittleEndian() const;
	//! true if data is stored as big endian
	virtual bool isBigEndian() const;

	//need an operator to access the IFDs
	TIFFIFD &operator[](const UInt16 i);
	TIFFIFD operator[](const UInt16 i) const;

	TIFFImageData::sptr getData(UInt64 i) const;

	friend std::ostream &operator<<(std::ostream &o,const TIFFFile &f);

};

template<typename T> void TIFFFile::_read_tile_data(){

}


template<typename T> void TIFFFile::_read_strip_data(UInt64 nchans,UInt64 dims[],UInt64 nstrips,Int32 strip_offsets[],
		    UInt64 strip_byte_count[],TIFFImageData::sptr &data){
	UInt64 width,height;
	UInt64 ssize = sizeof(T);
	UInt64 nsamps = data->getNumberOfChannels();
	T buffer = 0;
	UInt64 ecnt = 0;

	height = dims[0];
	width = dims[1];

	//create arrays
	for(UInt64 i=0;i<nchans;i++) data->appendChannel(Array<T>::sptr(new Array<T>(2,dims)));

	//loop over all strips
	for(UInt64 i=0;i<nstrips;i++){
		//place stream object to the strip position
		_ifstream.seekg(strip_offsets[i],std::ios::beg);

		//for each strip we have to loop over all elements
		UInt64 nruns = strip_byte_count[i]/ssize/nsamps;
		for(UInt64 j=0;j<nruns;j++){

			//loop over all channels (samples)
			for(UInt64 k=0;k<nsamps;k++){
				Array<T> &a = *data->getChannel(k);
				_ifstream.read((char*)(&buffer),ssize);
				a[ecnt] = (T)buffer;
			}
			ecnt++;
		}
	}
}

//end of namespace
}
}
#endif /* TIFFFILE_HPP_ */
