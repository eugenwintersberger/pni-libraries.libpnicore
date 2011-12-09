/*
 * Type map from IDs to PNI types
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
 * Type map which maps type IDs to real PNI data types.
 *
 * Created on: Oct 13, 2011
 *     Author: Eugen Wintersberger
 *
 */


#include "PNITypes.hpp"

#ifndef PNITYPEIDMAP_HPP_
#define PNITYPEIDMAP_HPP_


namespace pni{
namespace utils{

//! template defining a map between a type ID and a data type
template<PNITypeID id> class PNITypeIDMap{
public:
	typedef UInt8 Type;
};

//! \cond NO_API_DOC
//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::UINT8>{
public:
	typedef UInt8 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::INT8>{
public:
	typedef Int8 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::UINT16>{
public:
	typedef UInt16 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::INT16>{
public:
	typedef Int16 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::INT32>{
public:
	typedef Int32 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::UINT32>{
public:
	typedef UInt32 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::INT64>{
public:
	typedef Int64 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::UINT64>{
public:
	typedef UInt64 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::FLOAT32>{
public:
	typedef Float32 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::FLOAT64>{
public:
	typedef Float64 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::FLOAT128>{
public:
	typedef Float128 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::COMPLEX32>{
public:
	typedef Complex32 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::COMPLEX64>{
public:
	typedef Complex64 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::COMPLEX128>{
public:
	typedef Complex128 Type;
};

//------------------------------------------------------------------------------
template<> class PNITypeIDMap<PNITypeID::BINARY>{
public:
	typedef Binary Type;
};

//! \endcond

}
}


#endif /* PNITYPEIDMAP_HPP_ */
