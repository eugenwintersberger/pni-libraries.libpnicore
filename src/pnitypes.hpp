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

//integer types
typedef char           Int8;
typedef unsigned char  UInt8;
typedef short          Int16;
typedef unsigned short UInt16;
typedef int            Int32;
typedef unsigned int   UInt32;
typedef long           Int64;
typedef unsigned long  UInt64;

//floating point numbers
typedef double Float64;
typedef float Float32;
typedef long double Float128;

//complex numbers
typedef std::complex<float> Complex32;
typedef std::complex<double> Complex64;
typedef std::complex<long double> Complex128;

typedef std::string String;

#endif /* TYPES_HPP_ */
