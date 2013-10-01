/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Sep 18, 2013
 *     Author: Eugen Wintersberger
 *
 */

#include <map>
#include "type_id_map.hpp"

#pragma once

namespace pni{
namespace core{

    /*!
    \ingroup type_classes
    \brief get type id of element type

    Returns the type id of the data stored in a contianer. The container can be
    an array or any other STL container having a public value_type member type. 
    This is the default implementation. However, types that provide other means
    of providing its data type can provide an overloaded version of this
    function. 
    \tparam CTYPE container type 
    \tparam CPARAMS types of the container template parameter list
    \param c const reference to the container
    \return type ID of the stored elements.
    */
    template<template<typename...> class CTYPE,typename ...CPARAMS> 
        type_id_t type_id(const CTYPE<CPARAMS...> &c)
    {
        typedef typename CTYPE<CPARAMS...>::value_type value_type;
        return type_id_map<value_type>::type_id;
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief get type id of a POD

    Return the ID of the type of an instance of a primitve data type. The value
    passed to the function is not of importance it just provides the type
    information.
    \tparam T primitive type
    \param v reference to an instance of T 
    \return type ID 
    \
    */
    template<typename T> type_id_t type_id(const T &v)
    {
        return type_id_map<T>::type_id;
    }

    //------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief get type id of complex numbers

    Return the ID of a complex number. We need this special overload otherwise
    the container version would be loaded. 
    \tparam T base type of the complex type
    \param v reference to instance
    \return type id of the complex type
    */
    template<typename T> type_id_t type_id(const std::complex<T> &v)
    {
        return type_id_map<std::complex<T> >::type_id;
    }

    //------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief get type id of binary 

    This is an overload for the type_id template for scalar values for the
    binary type. As this is a template the compiler would choose the wrong
    version (the one for containers). 
    \param v instance of binary
    \return type_id_t::BOOL
    */
    type_id_t type_id(const binary &v);

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief get string type id

    This returns the type id for a string.
    \param v ref to string instance
    \return type id of a string
    */
    type_id_t type_id(const string &v);


    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief string to id map
    
    A map instance mapping the string representations of types to type IDs.
    */
    static const std::map<string,type_id_t> str2type_id =
    {{"uint8",type_id_t::UINT8},{"ui8",type_id_t::UINT8},
     {"int8",type_id_t::INT8},{"i8",type_id_t::INT8},
     {"uint16",type_id_t::UINT16},{"ui16",type_id_t::UINT16},
     {"int16",type_id_t::INT16},{"i16",type_id_t::INT16},
     {"uint32",type_id_t::UINT32},{"ui32",type_id_t::UINT32},
     {"int32",type_id_t::INT32},{"i32",type_id_t::INT32},
     {"uint64",type_id_t::UINT64},{"ui64",type_id_t::UINT64},
     {"int64",type_id_t::INT64},{"i64",type_id_t::INT64},
     {"float32",type_id_t::FLOAT32},{"f32",type_id_t::FLOAT32},
     {"float64",type_id_t::FLOAT64},{"f64",type_id_t::FLOAT64},
     {"float128",type_id_t::FLOAT128},{"f128",type_id_t::FLOAT128},
     {"complex32",type_id_t::COMPLEX32},{"c32",type_id_t::COMPLEX32},
     {"complex64",type_id_t::COMPLEX64},{"c64",type_id_t::COMPLEX64},
     {"complex128",type_id_t::COMPLEX128},{"c128",type_id_t::COMPLEX128},
     {"string",type_id_t::STRING},{"str",type_id_t::STRING},
     {"binary",type_id_t::BINARY}
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief type ID to string map

    This map provides mapping from type_id to the string representations of a
    type.
    */
    static const std::map<type_id_t,string> type_id2str =
    {{type_id_t::UINT8,"uint8"},   {type_id_t::INT8,"int8"},
     {type_id_t::UINT16,"uint16"}, {type_id_t::INT16,"int16"},
     {type_id_t::UINT32,"uint32"}, {type_id_t::INT32,"int32"},
     {type_id_t::UINT64,"uint64"}, {type_id_t::INT64,"int64"},
     {type_id_t::FLOAT32,"float32"},
     {type_id_t::FLOAT64,"float64"},
     {type_id_t::FLOAT128,"float128"},
     {type_id_t::COMPLEX32,"complex32"},
     {type_id_t::COMPLEX64,"complex64"},
     {type_id_t::COMPLEX128,"complex128"},
     {type_id_t::STRING,"string"},
     {type_id_t::BINARY,"binary"}
    };

//end of namespace
}
}
