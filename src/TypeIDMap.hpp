/*
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
#pragma once

#include "Types.hpp"

namespace pni{
namespace core{

/*!
\ingroup type_classes
\brief macro to create type to type id maps

This macro is used to create a specialization of the TypeIDMap type map.
*/
#define CREATE_TYPE_ID_MAP(type,tid)\
    template<> class TypeIDMap<type>\
    {\
        public:\
            static const TypeID type_id = tid;\
    }

    /*! 
    \ingroup type_classes
    \brief map from a type to TypeID

    This template implements a map from a concrete type to its TypeID
    */
    template<typename T> class TypeIDMap
    {
        public:
            static const TypeID type_id = TypeID::NONE; //!< id value for type T
    };

    //! \cond NO_API_DOC
    CREATE_TYPE_ID_MAP(UInt8,TypeID::UINT8);
    CREATE_TYPE_ID_MAP(Int8,TypeID::INT8);
    CREATE_TYPE_ID_MAP(UInt16,TypeID::UINT16);
    CREATE_TYPE_ID_MAP(Int16,TypeID::INT16);
    CREATE_TYPE_ID_MAP(UInt32,TypeID::UINT32);
    CREATE_TYPE_ID_MAP(Int32,TypeID::INT32);
    CREATE_TYPE_ID_MAP(UInt64,TypeID::UINT64);
    CREATE_TYPE_ID_MAP(Int64,TypeID::INT64);
    CREATE_TYPE_ID_MAP(Float32,TypeID::FLOAT32);
    CREATE_TYPE_ID_MAP(Float64,TypeID::FLOAT64);
    CREATE_TYPE_ID_MAP(Float128,TypeID::FLOAT128);
    CREATE_TYPE_ID_MAP(Complex32,TypeID::COMPLEX32);
    CREATE_TYPE_ID_MAP(Complex64,TypeID::COMPLEX64);
    CREATE_TYPE_ID_MAP(Complex128,TypeID::COMPLEX128);
    CREATE_TYPE_ID_MAP(String,TypeID::STRING);
    CREATE_TYPE_ID_MAP(Binary,TypeID::BINARY);
    CREATE_TYPE_ID_MAP(Bool,TypeID::BOOL);
    //! \endcond NO_API_DOC

//end of namespace
}
}
