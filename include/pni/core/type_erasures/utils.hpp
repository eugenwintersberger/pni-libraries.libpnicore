//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jan 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<iostream>
#include<memory>

#include "../types/types.hpp"
#include "../types/convert.hpp"
#include "../types/type_conversion.hpp"
#include "../types/traits.hpp"

namespace pni{
namespace core{


    template<
             typename TT,
             typename ST,
             bool     convertible=false
            > 
    struct value_converter
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        static TT convert(const ST &v)
        {
            throw type_error(EXCEPTION_RECORD,"Conversion not possible!");
            return TT();
        }
#pragma GCC diagnostic pop
    };

    template<
             typename TT,
             typename ST
            >
    struct value_converter<TT,ST,true>
    {
        static TT convert(const ST &v)
        {
            return pni::core::convert<TT>(v);
        }
    };

    template<
             typename TT,
             typename ST
            >
    using strategy = value_converter<TT,ST,convertible<ST,TT>::value>;

//end of namespace
}
}
