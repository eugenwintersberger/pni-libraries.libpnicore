/*
 * Definition of standard types
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
 * Architecture independant definition of native data types.
 *
 * Created on: May 16, 2011
 *     Author: Eugen Wintersberger
 *
 */

#include <complex>
#include <string>

#ifndef PNITYPES_HPP_
#define PNITYPES_HPP_


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

typedef UInt8 Binary; //!< data type for binary data
typedef bool Bool;    //!< data type for boolean expressions


//! type codes for PNI data types
enum class PNITypeID {NONE,   //!< no data type
				INT8,   //!< signed 8Bit integer
				UINT8,  //!< unsigned 8Bit integer
				INT16,  //!< signed 16Bit integer
				UINT16, //!< unsigned 16Bit integer
				INT32,  //!< signed 32Bit integer
				UINT32, //!< unsigned 32Bit integer
				INT64,  //!< signed 64Bit integer
				UINT64, //!< unsigned 64Bit integer
	            FLOAT32,  //!< 32Bit IEEE floating point
	            FLOAT64,  //!< 64Bit IEEE floating point
	            FLOAT128, //!< 128Bit IEEE floating point
	            COMPLEX32,  //!< 32Bit IEEE floating point complex
	            COMPLEX64,  //!< 64Bit IEEE floating point complex
	            COMPLEX128, //!< 128Bit IEEE floating point complex
	            STRING,      //!< String type
	            BINARY,      //!< binary data
	            BOOLEAN      //!< boolean data
				};

//! classes of data types provided by the PNI utility library
enum class PNITypeClass { NONE,       //!< unspecified type
	                INTEGER,    //!< integer type
 	                FLOAT,      //!< floating point type
	                BINARY,     //!< binary data type
	                BOOL,       //!< boolean data type
	                COMPLEX     //!< complex data type
				    };



//! @}
//end of namespace
}
}

#endif /* PNITYPES_HPP_ */
