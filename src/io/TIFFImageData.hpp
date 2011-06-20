/*
 * TIFFImageData.hpp
 *
 *  Created on: Jun 20, 2011
 *      Author: eugen
 */

#ifndef TIFFIMAGEDATA_HPP_
#define TIFFIMAGEDATA_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>

#include "../ArrayObject.hpp"

namespace pni {

namespace utils {

class TIFFImageData {
protected:
	typedef std::vector<ArrayObject::sptr> _channel_list;
	_channel_list _channels;

public:
	typedef std::vector<ArrayObject::sptr>::iterator iterator;
	typedef std::vector<ArrayObject::sptr>::const_iterator const_iterator;
	typedef boost::shared_ptr<TIFFImageData> sptr;
	TIFFImageData();
	TIFFImageData(const TIFFImageData &);
	virtual ~TIFFImageData();

	virtual UInt64 getNumberOfChannels() const;
	virtual void appendChannel(ArrayObject::sptr ptr);
	virtual ArrayObject::sptr getChannel(UInt64 i);

	ArrayObject::sptr operator[](UInt64 i);

	TIFFImageData &operator=(const TIFFImageData &o);

	TIFFImageData::iterator begin();
	TIFFImageData::iterator end();

};



}
}
#endif /* TIFFIMAGEDATA_HPP_ */
