/*! \file */
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

#include "Binary.hpp"

#ifndef __TYPES_HPP__
#define __TYPES_HPP__


//define some standard types
namespace pni{
namespace utils{

    /*! \addtogroup type_classes
      @{
     */

    //! 8Bit signed integer type
    typedef int8_t   Int8;   
    typedef uint8_t  UInt8;  //!< 8Bit unsigned integer type
    typedef int16_t  Int16;  //!< 16Bit signed integer type
    typedef uint16_t UInt16; //!< 16Bit unsigned integer type
    typedef int32_t  Int32;  //!< 32Bit signed integer type
    typedef uint32_t UInt32; //!< 32Bit unsigned integer type
    typedef int64_t  Int64;  //!< 64Bit signed integer type
    typedef uint64_t UInt64; //!< 64Bit unsigned integer type

    //floating point numbers
    typedef double Float64;         //!< 64Bit IEEE floating point type
    typedef float Float32;          //!< 32Bit IEEE floating point type
    typedef long double Float128;   //!< 128Bit IEEE floating point type

    //complex numbers
    typedef std::complex<float> Complex32;  //!< 32Bit complex floating point type
    typedef std::complex<double> Complex64; //!< 64Bit complex floating point type
    typedef std::complex<long double> Complex128; //!< 128Bit complex floating point type

    typedef std::string String; //!< String type

    typedef BinaryType<UInt8> Binary; //!< data type for binary data
    typedef bool Bool;    //!< data type for boolean expressions
    /*! @} */

    /*!
    \ingroup type_classes
    \brief test function

    This is just a testing function.
    */
    void function();


    /*! 
    \ingroup type_classes
    \brief type codes for PNI data types
    Typed enumeration with type IDs. 
    */
    enum class TypeID {NONE,       //!< no data type
                       INT8,       //!< signed 8Bit integer
                       UINT8,      //!< unsigned 8Bit integer
                       INT16,      //!< signed 16Bit integer
                       UINT16,     //!< unsigned 16Bit integer
                       INT32,      //!< signed 32Bit integer
                       UINT32,     //!< unsigned 32Bit integer
                       INT64,      //!< signed 64Bit integer
                       UINT64,     //!< unsigned 64Bit integer
                       FLOAT32,    //!< 32Bit IEEE floating point
                       FLOAT64,    //!< 64Bit IEEE floating point
                       FLOAT128,   //!< 128Bit IEEE floating point
                       COMPLEX32,  //!< 32Bit IEEE floating point complex
                       COMPLEX64,  //!< 64Bit IEEE floating point complex
                       COMPLEX128, //!< 128Bit IEEE floating point complex
                       STRING,     //!< String type
                       BINARY,     //!< binary data
                       BOOL        //!< boolean data
                      };

    /*! 
    \ingroup type_classes
    \brief output operator for TypeID

    Adds a string representation of a TypeID to the output stream.
    \param o reference to output stream
    \param tid reference to the TypID 
    \return reference to output stream
    */
    std::ostream &operator<<(std::ostream &o,const TypeID &tid);


    //! classes of data types provided by the PNI utility library
    enum class TypeClass {NONE,       //!< unspecified type
                          INTEGER,    //!< integer type
                          FLOAT,      //!< floating point type
                          BINARY,     //!< binary data type
                          BOOL,       //!< boolean data type
                          COMPLEX,    //!< complex data type
                          STRING      //!< class for string types
                         };




//if the compiler does not provide comparison operators for typed enumerations
//we have to do this by ourselves
#ifdef ENUMBUG
    /*!
    \ingroup type_classes
    \brief < operator for TypeID

    gcc 4.4 does not implement the < operator for scoped enums. In such cases
    this overloaded version is used. This operator will only be used if the code
    is compiled with \c -DENUMBUG.
    */
    bool operator<(TypeID a,TypeID b);

    bool operator>(TypeID a,TypeID b);
    bool operator<=(TypeID a,TypeID b);
    bool operator>=(TypeID a,TypeID b);

    bool operator<(TypeClass a,TypeClass b);
    bool operator>(TypeClass a,TypeClass b);
    bool operator<=(TypeClass a,TypeClass b);
    bool operator>=(TypeClass a,TypeClass b);
#endif

//end of namespace
}
}

#endif 
