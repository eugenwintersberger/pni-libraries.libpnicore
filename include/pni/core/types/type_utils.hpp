//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Sep 18, 2013
//!     Author: Eugen Wintersberger
//!
//!
#pragma once

#include <map>
#include "type_id_map.hpp"


namespace pni{
namespace core{
    
    //------------------------------------------------------------------------
    //call this to obtain the type id of a complex value
    template<typename T> type_id_t get_type_id(const std::complex<T> &v)
    {
        return type_id_map<std::complex<T> >::type_id;
    }

    //------------------------------------------------------------------------
    //call this to obtain the type ID of a binary value
    type_id_t get_type_id(const binary &v);

    //-------------------------------------------------------------------------
    //call this to obtain the type ID of a string value
    type_id_t get_type_id(const string &v);


    //-------------------------------------------------------------------------
    //if T is POD this is the one you use
    template<typename T > 
    type_id_t get_type_id(const T &v,
                          typename std::enable_if<
                          std::is_pod<T>::value
                          >::type* = 0)
    {
        return type_id_map<T>::type_id;
    }

    //-------------------------------------------------------------------------
    // if T is a container type use this function
    template<typename T> 
    type_id_t get_type_id(const T &v,
                          typename std::enable_if<
                          !std::is_pod<T>::value
                          >::type* = 0)
    {
        return type_id_map<typename T::value_type>::type_id;
    }
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get type id of an object
    //!
    //! This function returns the type ID of an instance of an object. In the 
    //! case of scalar data the type if a variable is returned. If the 
    //! argument passed is a container the type id of the element type 
    //! is returned.
    //!
    //! \tparam T type if the object
    //! \param v instance of T 
    //! \return type ID 
    //!
    template<typename T> 
    type_id_t type_id(T v)
    {
        typedef typename std::remove_const<
            typename std::remove_pointer<T>::type
            >::type  type;
        return get_type_id(type());
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get a type ID from a string
    //! 
    //! Returns the type ID for a particular string representation of a type. 
    //! If the string passed is not a valid type representation an exception 
    //! will be thrown.
    //!
    //! \throws key_error if the string does not describe a type
    //! \param s string representation of the type
    //! \return corresponding type ID
    //!
    type_id_t type_id_from_str(const string &s);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief get the string rep. for a type
    //!
    //! Returns the string representation for a type determined by its type 
    //! id. If the type determined by the ID does not have a string 
    //! representation an exception will be thrown. 
    //! 
    //! \throws key_error if the type has no string representation
    //! \param id type ID of the type
    //! \return string representation of the type
    //!
    string str_from_type_id(type_id_t id);



//end of namespace
}
}
