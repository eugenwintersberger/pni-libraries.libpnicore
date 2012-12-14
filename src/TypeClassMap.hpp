/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * TypeClassMap.hpp
 *
 *  Created on: Sep 27, 2012
 *      Author: Eugen Wintersberger
 */
#pragma once

#include "Types.hpp"

namespace pni{
namespace utils{
   
/*!
\ingroup type_classes
\brief macro for type/class map creation

This macro creates a type to type class map specialization. 
*/
#define CREATE_TYPE_CLASS_MAP(type,tclass)\
    template<> class TypeClassMap<type>\
    {\
        public:\
            static const TypeClass type_class = tclass;\
    }
    
    /*!
    \ingroup type_classes
    \brief type to class mapping
    
    Template mapping a particular data type to its type class.
    \tparam T data type
    */
    template<typename T> class TypeClassMap
    {
        public:
            //! class of type T
            static const TypeClass type_class = TypeClass::NONE;
    };

    //! \cond NO_API_DOC
    CREATE_TYPE_CLASS_MAP(UInt8,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(Int8,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(UInt16,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(Int16,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(UInt32,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(Int32,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(UInt64,TypeClass::INTEGER);
    CREATE_TYPE_CLASS_MAP(Int64,TypeClass::INTEGER);
    
    CREATE_TYPE_CLASS_MAP(Float32,TypeClass::FLOAT);
    CREATE_TYPE_CLASS_MAP(Float64,TypeClass::FLOAT);
    CREATE_TYPE_CLASS_MAP(Float128,TypeClass::FLOAT);

    CREATE_TYPE_CLASS_MAP(Complex32,TypeClass::COMPLEX);
    CREATE_TYPE_CLASS_MAP(Complex64,TypeClass::COMPLEX);
    CREATE_TYPE_CLASS_MAP(Complex128,TypeClass::COMPLEX);

    CREATE_TYPE_CLASS_MAP(Bool,TypeClass::BOOL);
    CREATE_TYPE_CLASS_MAP(Binary,TypeClass::BINARY);
    CREATE_TYPE_CLASS_MAP(String,TypeClass::STRING);

    //! \endcond NO_API_DOC

//end of namespace
}
}
