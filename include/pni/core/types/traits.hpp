//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Dec 29, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include "types.hpp"
#include <boost/mpl/contains.hpp>

namespace pni{
namespace core{

    //------------------------------------------------------------------------
    template<typename T> struct integer_type
    {
        static const bool value = boost::mpl::contains<integer_types,T>::value;
    };

    //------------------------------------------------------------------------
    template<typename T> struct float_type
    {
        static const bool value = boost::mpl::contains<float_types,T>::value;
    };

    //------------------------------------------------------------------------
    template<typename T> struct complex_type
    {
        static const bool value = boost::mpl::contains<complex_types,T>::value;
    };

    //-------------------------------------------------------------------------
    template<typename T> struct numeric_type
    {
        static const bool value = boost::mpl::contains<numeric_types,T>::value;
    };

    //-------------------------------------------------------------------------
    template<typename T> struct non_numeric_type
    {
        static const bool value =
            boost::mpl::contains<non_numeric_types,T>::value;
    };

    bool is_numeric(type_id_t tid);

    bool is_integer_type(type_id_t tid);

    bool is_complex_type(type_id_t tid);

    bool is_float_type(type_id_t tid);
    
//end of namespace
}
}
