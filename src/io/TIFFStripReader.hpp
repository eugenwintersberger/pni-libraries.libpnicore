/*
 * Declaration of class TIFFStripReader
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
 * Declaration of class TIFFStripReader.
 *
 * Created on: Jun 22, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFSTRIPREADER_HPP_
#define TIFFSTRIPREADER_HPP_

#include <iostream>
#include <fstream>
#include <vector>

#include "TIFFIFD.hpp"
#include "TIFFFile.hpp"
#include "TIFFImageData.hpp"

#include "../Types.hpp"

namespace pni {

namespace utils {

//! \ingroup io_classes
//! \brief reader for strip data in a TIFF file
class TIFFStripReader {
private:
	//here we maybe define a local class for multithreading purposes
protected:
	std::vector<UInt64> _strip_offsets;      //!< array with the file offsets of the strips
	std::vector<UInt64> _strip_byte_counts;  //!< array with byte counts for each strip
	UInt64 _nchannels;  //!< number of channels (samples per pixle)
	UInt64 _nstrips;    //!< total number of strips for the image
	UInt64 _width;      //!< width of the image (in pixles)
	UInt64 _height;     //!< number of scanlines (height of the image)
public:
	//! default constructor
	TIFFStripReader();
	//! copy constructor
	TIFFStripReader(const TIFFStripReader &);
	//! destructor
	virtual ~TIFFStripReader();

	//! set all strip offsets

	//! An array with the offsets for every strip is passed to the
	//! class. The setNumberOfStrips method must be called in advance
	//! of this method to set the number of strips in the file to a
	//! non zero value. Otherwise an IndexError exception will be raised!.
	//! The array must be of appropriate size - otherwise a segmentation fault
	//! will occur.

	//! \param offsets array with file offset values
	virtual void setStripOffsets(UInt64 offsets[]);
	//! set an individual strip offset

	//! The stream offset of strip i will be set to offset.
	//! setNumberOfStrips must have been called in advance otherwise an
	//! IndexError exception will be raised. This exception will be raised
	//! in cases where i exceeds the number of strips for the image too.
	virtual void setStripOffset(UInt64 i,UInt64 offset);
	//! get a vector with the stream offsets of strips
	virtual std::vector<UInt64> &getStripOffsets();
	//! get a vector with stream offsets for the strips
	virtual std::vector<UInt64> getStripOffsets() const;
	//! get an indiviual strip offset

	//! returns the stream offset of strip index. If index exceeds the
	//! total number of strips or the number of strips is not set
	//! an exception will be raised.

	//! \param index index of the strip
	virtual UInt64 getStripOffset(UInt64 index) const;

	//! set the byte count for all strips

	//! Set the number of bytes for each strip. setNumberOfStrips must be
	//! called in advance of this method otherwise an IndexError exception will be
	//! raised. The class has no chance to check the size of the array therefore
	//! it is in the responsibility of the user to allocate enough memory
	//! to avoid segmentation faults.

	//! \param bcounts[] array with byte counts for each strip
	virtual void setStripByteCounts(UInt64 bcounts[]);
	//! set the byte count for an individual strip

	//! Sets the number of bytes to read for strip i. An IndexError exception will
	//! be raised if the number of strips has not been set in advance or if the
	//! strip index i exceeds the total number of strips.

	//! \param i index of the strip
	//! \param bcount number of bytes to read for this strip
	virtual void setStripByteCount(UInt64 i,UInt64 bcount);
	//! return a vector with byte counts for each strip
	virtual std::vector<UInt64> &getStripByteCounts();
	//! return a vector with byte counts for each strip
	virtual std::vector<UInt64> getStripByteCounts() const;
	//! return the byte count for an individual strip

	//! An IndexError exception will be raised if the number of strips has not bee
	//! set or if strip index i exceeds the total number of strips.

	//! \param index index of the strip
	virtual UInt64 getStripByteCount(UInt64 index) const;

	//! set the number of channels (number of samples per pixle)
	virtual void setNumberOfChannels(UInt64 nc);
	//! get the number of channels (number of samples per pixle)
	virtual UInt64 getNumberOfChannels() const;

	//! set the total number of strips
	virtual void setNumberOfStrips(UInt64 ns);
	//! get the total number of strips
	virtual UInt64 getNumberOfStrips() const;

	//! set image height (number of scanlines)
	virtual void setHeight(UInt64 h);
	//! get image height (number of scanlines)
	virtual UInt64 getHeight() const;

	//! set image width (number of pixles)
	virtual void setWidth(UInt64 w);
	//! get image widht (number of pixles)
	virtual UInt64 getWidth() const;

	//! assignment operator
	TIFFStripReader &operator=(const TIFFStripReader &);

	//! template to read image data of various type
	template<typename T> void read(std::ifstream &stream,
			TIFFImageData::sptr idata) {
		UInt64 ssize = sizeof(T);
		T buffer = 0;
		UInt64 ecnt = 0;
		UInt32 dims[2];
		UInt32 ndims = 2;

		dims[0] = _height;
		dims[1] = _width;

		//create arrays
		Shape s(ndims);
		for (UInt32 d=0;d<s.rank();d++) s.dim(d,dims[d]);
		for (UInt64 i = 0; i < _nchannels; i++)
			idata->appendChannel(typename Array<T,Buffer>::sptr(new Array<T,Buffer>(s)));

		//loop over all strips
		for (UInt64 i = 0; i < _nstrips; i++) {
			//place stream object to the strip position
			stream.seekg(_strip_offsets[i], std::ios::beg);

			//for each strip we have to loop over all elements
			UInt64 nruns = _strip_byte_counts[i] / ssize / _nchannels;
			for (UInt64 j = 0; j < nruns; j++) {

				//loop over all channels (samples)
				for (UInt64 k = 0; k < _nchannels; k++) {
					Array<T,Buffer> &a = *boost::dynamic_pointer_cast<Array<T,Buffer> >(idata->getChannel(k));
					stream.read((char*) (&buffer), ssize);
					a[ecnt] = (T) buffer;
				}
				ecnt++;
			}
		}

	}
};



//end of namespace
}
}

#endif /* TIFFSTRIPREADER_HPP_ */
