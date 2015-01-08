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
// Created on: Dec 29, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<iostream>
#include<memory>

#include "../types/types.hpp"
#include "../types/convert.hpp"
#include "../types/type_conversion.hpp"
#include "../types/traits.hpp"
#include "value.hpp"

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

    template<
             typename T
            > 
    T as(const value &v)
    {
        //type ID of the type erasure
        type_id_t source_tid = v.type_id();
        //type ID of the requested type
        type_id_t target_tid = type_id_map<T>::type_id;

        //check if the type are convertible at all
        if(!is_convertible(source_tid,target_tid))
            throw type_error(EXCEPTION_RECORD,"Types are not convertible!");

        switch(source_tid)
        {
            case type_id_t::UINT8:   
                return strategy<T,uint8>::convert(v.as<uint8>());
            case type_id_t::INT8:    
                return strategy<T,int8>::convert(v.as<int8>());
            case  type_id_t::UINT16: 
                return strategy<T,uint16>::convert(v.as<uint16>());
            case type_id_t::INT16:
                return strategy<T,int16>::convert(v.as<int16>());
            case type_id_t::UINT32:
                return strategy<T,uint32>::convert(v.as<uint32>());
            case type_id_t::INT32:
                return strategy<T,int32>::convert(v.as<int32>());
            case type_id_t::UINT64:
                return strategy<T,uint64>::convert(v.as<uint64>());
            case type_id_t::INT64:
                return strategy<T,int64>::convert(v.as<int64>());
            case type_id_t::FLOAT32:
                return strategy<T,float32>::convert(v.as<float32>());
            case type_id_t::FLOAT64:
                return strategy<T,float64>::convert(v.as<float64>());
            case type_id_t::FLOAT128:
                return strategy<T,float128>::convert(v.as<float128>());
            case type_id_t::COMPLEX32:
                return strategy<T,complex32>::convert(v.as<complex32>());
            case type_id_t::COMPLEX64:
                return strategy<T,complex64>::convert(v.as<complex64>());
            case type_id_t::COMPLEX128:
                return strategy<T,complex128>::convert(v.as<complex128>());
                /*
            case type_id_t::STRING:
                if(target_tid == source_tid)
                    return v.as<string>();
                else
                    throw type_error(EXCEPTION_RECORD,
                            "Source and target type must match for strings!");
            case type_id_t::BINARY:
                if(target_tid == source_tid)
                    return v.as<binary>();
                else 
                    throw type_error(EXCEPTION_RECORD,
                            "Source and target type must match for binary data!");
            case type_id_t::BOOL:
                if(target_tid == source_tid)
                    return v.as<bool_t>();
                else
                    throw type_error(EXCEPTION_RECORD,
                            "Source and target type must match for bool data!");
                            */
            default: 
                throw type_error(EXCEPTION_RECORD,"Unkown type ID!");
        }
    }

    template<> string as(const value &v);
    template<> binary as(const value &v);
    template<> bool_t as(const value &v);

//end of namespace
}
}
