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


#include "Types.hpp"

#ifndef IDTYPEMAP_HPP_
#define IDTYPEMAP_HPP_


namespace pni{
namespace utils{

//! \ingroup type_classes
//! \brief map from TypeID to type

//! This template implements a map from a TypeID to a specific data type.
template<TypeID id> class IDTypeMap{
    public:
        typedef UInt8 type; //!< type identified by the template parameter
};

//! \cond NO_API_DOC
//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::UINT8>{
    public:
        typedef UInt8 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::INT8>{
    public:
        typedef Int8 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::UINT16>{
    public:
        typedef UInt16 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::INT16>{
    public:
        typedef Int16 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::INT32>{
    public:
        typedef Int32 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::UINT32>{
    public:
        typedef UInt32 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::INT64>{
    public:
        typedef Int64 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::UINT64>{
    public:
        typedef UInt64 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::FLOAT32>{
    public:
        typedef Float32 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::FLOAT64>{
    public:
        typedef Float64 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::FLOAT128>{
    public:
        typedef Float128 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::COMPLEX32>{
    public:
        typedef Complex32 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::COMPLEX64>{
    public:
        typedef Complex64 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::COMPLEX128>{
    public:
        typedef Complex128 type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::STRING>{
    public:
        typedef String type;
};

//------------------------------------------------------------------------------
template<> class IDTypeMap<TypeID::BINARY>{
    public:
        typedef Binary type;
};

//! \endcond

}
}


#endif /* IDTYPEMAP_HPP_ */
