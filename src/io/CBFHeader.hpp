/*
 * cbfheader.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#ifndef CBFHEADER_HPP_
#define CBFHEADER_HPP_

#include "CBFBinStreamReader.hpp"
#include "../DataObject.hpp"
#include "../Array.hpp"
#include "../PNITypes.hpp"

namespace pni{
namespace utils{


#define CIF_DATA_TYPE_KEY  "X-Binary-Element-Type"
#define CIF_DATA_SIGNED_INT32  "\"signed 32-bit integer\""
#define UNSIGNED_INT_8 1
#define SIGNED_INT_8 2
#define UNSIGNED_INT_16 3
#define SIGNED_INT_16 4
#define UNSIGNED_INT_32 5
#define SIGNED_INT_32 6
#define UNSIGNED_INT_64 7
#define SIGNED_INT_64 8

#define CIF_DATA_BYTE_ORDER_KEY  "X-Binary-Element-Byte-Order"
#define BYTE_ORDER_LITTLE_ENDIAN 1
#define BYTE_ORDER_BIG_ENDIAN 2

#define CIF_DATA_CONVERSION_KEY  "conversions"
#define CIF_DATA_CONVERSION_BO_VALUE  "\"x-CBF_BYTE_OFFSET\""
#define CONVERSION_BYTE_OFFSET 1

#define CIF_DATA_1FAST_DIM_KEY  "X-Binary-Size-Fastest-Dimension"
#define CIF_DATA_2FAST_DIM_KEY  "X-Binary-Size-Second-Dimension"
#define CIF_DATA_3FAST_DIM_KEY  "X-Binary-Size-Third-Dimension"
#define CIF_DATA_NELEMENTS_KEY  "X-Binary-Number-of-Elements"

//! \ingroup IO
//! Header of a binary CIF file

//! CIFBinaryHeader represents the header structure of a binary CIF file. The structure
//! of such a header differs slightly from that of a pure ASCII CIF file.
//!
//! A few words should be left about how the dimensions of the data are stored. A CBF
//! file can store data of rank 1, 2, or 3. In the very beginning we do not know
//! how many dimension are present in the data file that is parsed.
//! The number of elements along each of the probable 3 dimension is stored
//! in the member variable _dims[3]. In the CBF header stream the dimension
//! 1,2, and 3 are denoted by "third fastest dimension", "second fastest dimension", and
//! "fastest dimension". The values of this header tags are stored as followd in the
//! _dims field:
//! 	- _dims[2] - fastest dimension
//! 	- _dims[1] - second fastest dimension
//! 	- _dims[0] - third fastest dimension
//!
//! This follows the rule of how arrays are stored in the Array template - the last index
//! varies fastest.
//!
//! The CBFBinaryHeader classes act also as factories for the stream reader objects which
//! are responsible for reading and decompressing the binary data stream associated with the
//! header. In addition, these classes also act as factories for numeric arrays
//! whose type is determined by the header entries in the CBF file.
class CIFBinaryHeader{
private:
	//maybe one should hide the copy constructor and the
	//assignment operator.
protected:
	UInt32 _conversion_id; //!< which type of compression used
	UInt32 _byte_order;    //!< byte order of the data
	UInt64 _nofelements;   //!< number of elements stored
	UInt64 _dims[3];       //!< number of dimension along each direction
	UInt32 _data_type;     //!< datatype used to store the data
	UInt32 _ndims;         //!< rank of the data stored

public:
	//! default constructor
	CIFBinaryHeader() {}
	//! standard constructor

	//! The standard constructor takes a stream of an CBF file as an argument
	//! from which it reads all the information needed to continue with the
	//! reading process.

	//! \param &s - a reference to a file stream
	CIFBinaryHeader(std::ifstream &s) {}
	//! destructor
	virtual ~CIFBinaryHeader() {}

	//! output operator
	friend std::ostream &operator<<(std::ostream &o, const CIFBinaryHeader &h);

	//! return a binary stream reader
	virtual CBFBinStreamReader *createBinaryReader() {
		return NULL;
	}

	//! create an array of appropriate type

	//! This method creates an array according to the data type
	//! described in the header.
	virtual ArrayObject *createArray();

	//! get the number of elements

	//! return the number of elements stored in the data section
	//! to which the header belongs.
	UInt64 getNumberOfElements() const {
		return _nofelements;
	}

	//! get the number of dimension

	//! return the number of dimension (the rank) of the data stored
	//! in the data section the header is associated with.
	unsigned int getNumberOfDimensions() const {
		return _ndims;
	}

	//! get the dimension

	//! return a pointer to the number of elements along each dimension
	//! of the data.
	const unsigned long *getDimensions() const {
		return _dims;
	}
};

//! \ingroup IO
//! Dectris Pilatus CBF header class

//! As usual Dectris is not following all the CIF conventions strictly. As a descendant of
//! CIFBinaryHeader this class provides a custom constructor for extracting the header
//! information and an overloaded version of the reader creation factory method.
class PCIFBinaryHeader: public CIFBinaryHeader {
public:
	//! default constructor;
	PCIFBinaryHeader() {
	}
	//! standard constructor
	PCIFBinaryHeader(std::ifstream &stream);

	virtual CBFBinStreamReader *createBinaryReader();
};

//end of namespace
}
}


#endif /* CBFHEADER_HPP_ */
