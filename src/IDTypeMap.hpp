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

/*!
\ingroup type_classes
\brief macro for ID to type map specialization

This macro is used to create a specialization of IDTypeMap.
*/
#define CREATE_ID_TYPE_MAP(tid,dtype)\
    template<> class IDTypeMap<tid>\
    {\
        public:\
            typedef dtype type;\
    };

    /*! 
    \ingroup type_classes
    \brief map from TypeID to type

    This template implements a map from a TypeID to a specific data type.
    */
    template<TypeID id> class IDTypeMap
    {
        public:
            typedef UInt8 type; //!< type identified by the template parameter
    };

    //! \cond NO_API_DOC
    CREATE_ID_TYPE_MAP(TypeID::UINT8,UInt8);
    CREATE_ID_TYPE_MAP(TypeID::INT8,Int8);
    CREATE_ID_TYPE_MAP(TypeID::UINT16,UInt16);
    CREATE_ID_TYPE_MAP(TypeID::INT16,Int16);
    CREATE_ID_TYPE_MAP(TypeID::UINT32,UInt32);
    CREATE_ID_TYPE_MAP(TypeID::INT32,Int32);
    CREATE_ID_TYPE_MAP(TypeID::UINT64,UInt64);
    CREATE_ID_TYPE_MAP(TypeID::INT64,Int64);
    CREATE_ID_TYPE_MAP(TypeID::FLOAT32,Float32);
    CREATE_ID_TYPE_MAP(TypeID::FLOAT64,Float64);
    CREATE_ID_TYPE_MAP(TypeID::FLOAT128,Float128);
    CREATE_ID_TYPE_MAP(TypeID::COMPLEX32,Complex32);
    CREATE_ID_TYPE_MAP(TypeID::COMPLEX64,Complex64);
    CREATE_ID_TYPE_MAP(TypeID::COMPLEX128,Complex128);
    CREATE_ID_TYPE_MAP(TypeID::STRING,String);
    CREATE_ID_TYPE_MAP(TypeID::BINARY,Binary);
    CREATE_ID_TYPE_MAP(TypeID::BOOL,Bool);
    //! \endcond NO_API_DOC

}
}


#endif /* IDTYPEMAP_HPP_ */
