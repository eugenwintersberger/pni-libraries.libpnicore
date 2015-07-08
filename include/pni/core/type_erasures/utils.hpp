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
#include "value_holder.hpp"

namespace pni{
namespace core{


    //------------------------------------------------------------------------
    template<
             typename TT,
             typename ST,
             bool     convertible=false
            > 
    struct value_converter
    {
        typedef TT target_type;
        typedef ST source_type;
        static target_type convert(const source_type &)
        {
            throw type_error(EXCEPTION_RECORD,"Conversion not possible!");
            return target_type();
        }
    };



    //------------------------------------------------------------------------
    template<
             typename TT,
             typename ST
            >
    struct value_converter<TT,ST,true>
    {
        typedef TT target_type;
        typedef ST source_type;

        static target_type convert(const source_type &v)
        {
            return pni::core::convert<target_type>(v);
        }
    };

    //------------------------------------------------------------------------
    template<
             typename TT,
             typename ST
            >
    using strategy = value_converter<TT,ST,convertible<ST,TT>::value>;

    //------------------------------------------------------------------------
    //!
    //! \brief alias for std::reference_wrapper
    //!
    //! A simple alias for the std::reference_wrapper template to reduce
    //! typing work. 
    //!
    //! \tparam T type of the reference
    //!
    template<typename T> using ref_type = std::reference_wrapper<T>;

    //------------------------------------------------------------------------
    template<
             typename T,
             typename PTR
            >
    value_holder<T> *get_holder_ptr(PTR &ptr)
    {
        typedef value_holder<T> holder_type;
                
        return dynamic_cast<holder_type*>(ptr.get());
    }

    //------------------------------------------------------------------------
    template<
             typename T,
             typename S,
             typename PTR
            > 
    T get_value(PTR holder_ptr)  
    {
        typedef strategy<T,S>   strategy_type;

        return strategy_type::convert(holder_ptr->as()); 
    }

    //------------------------------------------------------------------------
    template<
             typename S,
             typename T,
             typename PTR
            >
    void set_value(PTR holder_ptr,const T &v)
    {
        typedef strategy<S,T> strategy_type;

        holder_ptr->as() = strategy_type::convert(v);
    }



//end of namespace
}
}
