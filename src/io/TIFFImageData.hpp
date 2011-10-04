/*
 * Declaration of class TIFFImageData
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
 * Declaration of class TIFFImageData.
 *
 * Created on: Jun 20, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef TIFFIMAGEDATA_HPP_
#define TIFFIMAGEDATA_HPP_

#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include "../ArrayObject.hpp"

namespace pni {

namespace utils {

//! \ingroup IO
//! \brief image data of a TIFF IFD

//! This class holds the data stored in the image of a TIFF IFD.
//! Each channel (Sample) associated with the pixles of an image is
//! stored in a separate ArrayObject. The class holds a vector
//! on all these ArrayObjects. Thus the channels can be accessed
//! individually.
//!
//! The TIFFImageData class acts as a container for this channel arrays.
//! However, only smart pointers to the channel arrays are stored. This
//! avoids ownership problems during further data processing.
class TIFFImageData {
protected:
	typedef std::vector<ArrayObject::sptr> _channel_list; //!< list type for the channels
	_channel_list _channels;                              //!< channel vector

public:
	typedef std::vector<ArrayObject::sptr>::iterator iterator;    //!< iterator over the channels in a TIFFImageData object
	typedef std::vector<ArrayObject::sptr>::const_iterator const_iterator; //!< const iterator over the channels in a TIFFImageData object
	typedef boost::shared_ptr<TIFFImageData> sptr;  //!< shared pointer to a TIFFImageData object
	//! default constructor
	TIFFImageData();
	//! copy constructor
	TIFFImageData(const TIFFImageData &);
	//! destructor
	virtual ~TIFFImageData();

	//! return the number of channels in the image
	virtual UInt64 getNumberOfChannels() const;
	//! append a channel to the container
	virtual void appendChannel(ArrayObject::sptr ptr);
	//! obtain a shared pointer to a channel array
	virtual ArrayObject::sptr getChannel(UInt64 i);

	//! [] operator to obtain a channel array
	ArrayObject::sptr operator[](UInt64 i);

	//! assignment operator
	TIFFImageData &operator=(const TIFFImageData &o);

	//! get the first channel for iterators
	TIFFImageData::iterator begin();
	//! get the first channel for const_iterators
	TIFFImageData::const_iterator begin() const;
	//! get the last channel for iterators
	TIFFImageData::iterator end();
	//! get the last channel for const_iterators
	TIFFImageData::const_iterator end() const;

	//! ouput operator for command line
	friend std::ostream &operator<<(std::ostream &o,const TIFFImageData &d);

};



}
}
#endif /* TIFFIMAGEDATA_HPP_ */
