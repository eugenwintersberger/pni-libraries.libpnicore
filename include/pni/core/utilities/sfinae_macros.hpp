//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Nov 07, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <type_traits>
#include "../types/complex_utils.hpp"

namespace pni{
namespace core{

    template<typename T> using invoke = typename T::type;

    template<typename T1,
             typename T2
            > 
    struct or_t
    {
        static const bool value = T1::value || T2::value;
    };

    template<typename T> struct not_t
    {
        static const bool value = !T::value;
    };

    template<typename C> using enable_if = invoke<std::enable_if<C::value>>;
    
    template<typename T> using is_pod = std::is_pod<T>;

    template<typename T> using is_ptr = std::is_pointer<T>;

    template<typename T> using is_cmplx = is_complex<T>;

//end of namespace
}
}

//-----------------------------------------------------------------------------
//!
//! \ingroup utility_classes
//! \brief basic SFINAE macro
//!
//! This macro is the basement for all the SFINAE expressions used in pnicore.
//! 
//! \param EXPR must evaluate to true or false
//!
#define ENABLE(EXPR) typename = typename std::enable_if<EXPR>::type

//-----------------------------------------------------------------------------
//!
//! \ingroup utility_classes
//! \brief true of POD
//! 
//! Evaluates to true if T is a POD
//! 
//! \param T type to check 
//! 
#define IS_POD(T) std::is_pod<T>::value

//-----------------------------------------------------------------------------
//! 
//! \ingroup utility_classes
//! \brief true if pointer
//! 
//! evaluates to true if T is a pointer type. 
//! 
//! \param T type to check 
//! 
#define IS_PTR(T) std::is_pointer<T>::value

//-----------------------------------------------------------------------------
//! 
//! \ingroup utility_classes
//! \brief true if complex
//! 
//! evaluates to true if T is a complex type. 
//! 
//! \param T type to check 
//! 
#define IS_COMPLEX(T) is_complex<T>::value
