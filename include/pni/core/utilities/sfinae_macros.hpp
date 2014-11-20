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

    //!
    //! \ingroup utility_classes 
    //! \brief alias to invoke a metafunction
    //!
    template<typename T> using invoke = typename T::type;

    //------------------------------------------------------------------------
    //!
    //! \ingroup utility_classes
    template<
             typename T1,
             typename T2
            > 
    struct or_t
    {
        static const bool value = T1::value || T2::value;
    };

    //------------------------------------------------------------------------
    template<
             typename T1,
             typename T2
            >
    struct and_t
    {
        static const bool value = T1::value && T2::value;
    };

    //------------------------------------------------------------------------
    template<typename T> struct not_t
    {
        static const bool value = !T::value;
    };

    //------------------------------------------------------------------------
    template<typename C> using enable_if = invoke<std::enable_if<C::value>>;
    
    //------------------------------------------------------------------------
    template<typename T> using is_pod = std::is_pod<T>;

    //------------------------------------------------------------------------
    template<typename T> using is_ptr = std::is_pointer<T>;

    //------------------------------------------------------------------------
    template<typename T> using is_cmplx = is_complex<T>;

//end of namespace
}
}


