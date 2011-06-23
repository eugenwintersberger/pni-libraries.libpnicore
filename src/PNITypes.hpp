/*
 * types.hpp
 *
 *  Created on: May 16, 2011
 *      Author: eugen
 */

#ifndef TYPES_HPP_
#define TYPES_HPP_
#include <complex>
#include <string>

//define some standard types
namespace pni{
namespace utils{


//! \addtogroup Data-objects
//! @{
typedef char           Int8;   //!< 8Bit signed integer type
typedef unsigned char  UInt8;  //!< 8Bit unsigned integer type
typedef short          Int16;  //!< 16Bit signed integer type
typedef unsigned short UInt16; //!< 16Bit unsigned integer type
typedef int            Int32;  //!< 32Bit signed integer type
typedef unsigned int   UInt32; //!< 32Bit unsigned integer type
typedef long           Int64;  //!< 64Bit signed integer type
typedef unsigned long  UInt64; //!< 64Bit unsigned integer type

//floating point numbers
typedef double Float64;         //!< 64Bit IEEE floating point type
typedef float Float32;          //!< 32Bit IEEE floating point type
typedef long double Float128;   //!< 128Bit IEEE floating point type

//complex numbers
typedef std::complex<float> Complex32;  //!< 32Bit complex floating point type
typedef std::complex<double> Complex64; //!< 64Bit complex floating point type
typedef std::complex<long double> Complex128; //!< 128Bit complex floating point type

typedef std::string String; //!< String type


//enum types for typecodes

enum PNITypeID {NONE,
				INT8,
				UINT8,
				INT16,
				UINT16,
				INT32,
				UINT32,
				INT64,
				UINT64,
	            FLOAT32,
	            FLOAT64,
	            FLOAT128,
	            COMPLEX32,
	            COMPLEX64,
	            COMPLEX128,
	            STRING
				};

//! @}
//end of namespace
}
}

#endif /* TYPES_HPP_ */
