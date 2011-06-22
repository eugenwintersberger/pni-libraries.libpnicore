/*
 * TIFFStripReader.hpp
 *
 *  Created on: Jun 22, 2011
 *      Author: eugen
 */

#ifndef TIFFSTRIPREADER_HPP_
#define TIFFSTRIPREADER_HPP_

#include <iostream>
#include <fstream>
#include <vector>

#include "TIFFIFD.hpp"
#include "TIFFFile.hpp"
#include "TIFFImageData.hpp"

#include "../PNITypes.hpp"

namespace pni {

namespace utils {

class TIFFStripReader {
private:
	//here we maybe define a local class for multithreading purposes
protected:
	std::vector<UInt64> _strip_offsets;
	std::vector<UInt64> _strip_byte_counts;
	UInt64 _nchannels;
	UInt64 _nstrips;
	UInt64 _width;
	UInt64 _height;
public:
	TIFFStripReader();
	TIFFStripReader(const TIFFStripReader &);
	virtual ~TIFFStripReader();

	virtual void setStripOffsets(UInt64 offsets[]);
	virtual void setStripOffset(UInt64 i,UInt64 offset);
	virtual std::vector<UInt64> &getStripOffsets();
	virtual std::vector<UInt64> getStripOffsets() const;
	virtual UInt64 getStripOffset(UInt64 index) const;

	virtual void setStripByteCounts(UInt64 bcounts[]);
	virtual void setStripByteCount(UInt64 i,UInt64 bcount);
	virtual std::vector<UInt64> &getStripByteCounts();
	virtual std::vector<UInt64> getStripByteCounts() const;
	virtual UInt64 getStripByteCount(UInt64 index) const;

	virtual void setNumberOfChannels(UInt64 nc);
	virtual UInt64 getNumberOfChannels() const;

	virtual void setNumberOfStrips(UInt64 ns);
	virtual UInt64 getNumberOfStrips() const;

	virtual void setHeight(UInt64 h);
	virtual UInt64 getHeight() const;

	virtual void setWidth(UInt64 w);
	virtual UInt64 getWidth() const;

	TIFFStripReader &operator=(const TIFFStripReader &);


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
		for (UInt64 i = 0; i < _nchannels; i++)
			idata->appendChannel(typename Array<T>::sptr(new Array<T>(ndims, dims)));

		//loop over all strips
		for (UInt64 i = 0; i < _nstrips; i++) {
			//place stream object to the strip position
			stream.seekg(_strip_offsets[i], std::ios::beg);

			//for each strip we have to loop over all elements
			UInt64 nruns = _strip_byte_counts[i] / ssize / _nchannels;
			for (UInt64 j = 0; j < nruns; j++) {

				//loop over all channels (samples)
				for (UInt64 k = 0; k < _nchannels; k++) {
					Array<T> &a = *boost::dynamic_pointer_cast<Array<T> >(idata->getChannel(k));
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
