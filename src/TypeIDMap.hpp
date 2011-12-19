/*
 * Map from PNI types to IDs
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
 * TypeIDMap.hpp
 *
 *  Created on: Dec 13, 2011
 *      Author: Eugen Wintersberger
 */

#include "Types.hpp"

#ifndef TYPEIDMAP_HPP_
#define TYPEIDMAP_HPP_

namespace pni{
namespace utils{

//! \ingroup type_classes
//! \brief map from a type to TypeID

//! This template implements a map from a concrete type to its TypeID
template<typename T> class TypeIDMap{
public:
	static const TypeID type_id = TypeID::NONE; //!< id value for type T
};

//! \cond NO_API_DOC
//------------------------------------------------------------------------------
template<> class TypeIDMap<UInt8>{
public:
	static const TypeID type_id = TypeID::UINT8;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Int8>{
public:
	static const TypeID type_id = TypeID::INT8;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<UInt16>{
public:
	static const TypeID type_id = TypeID::UINT16;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Int16>{
public:
	static const TypeID type_id = TypeID::INT16;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Int32>{
public:
	static const TypeID type_id = TypeID::INT32;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<UInt32>{
public:
	static const TypeID type_id = TypeID::UINT32;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Int64>{
public:
	static const TypeID type_id = TypeID::INT64;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<UInt64>{
public:
	static const TypeID type_id = TypeID::UINT64;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Float32>{
public:
	static const TypeID type_id = TypeID::FLOAT32;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Float64>{
public:
	static const TypeID type_id = TypeID::FLOAT64;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Float128>{
public:
	static const TypeID type_id = TypeID::FLOAT128;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Complex32>{
public:
	static const TypeID type_id = TypeID::COMPLEX32;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Complex64>{
public:
	static const TypeID type_id = TypeID::COMPLEX64;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<Complex128>{
public:
	static const TypeID type_id = TypeID::COMPLEX128;
};

//------------------------------------------------------------------------------
template<> class TypeIDMap<String> {
public:
	static const TypeID type_id = TypeID::STRING;
};


//end of namespace
}
}


#endif /* TYPEIDMAP_HPP_ */
