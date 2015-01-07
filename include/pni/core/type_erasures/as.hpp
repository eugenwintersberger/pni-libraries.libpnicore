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


namespace pni{
namespace core{

    template<
             typename T,
             typename V
            > 
    T as(const V &v)
    {
        //type ID of the type erasure
        type_id_t source_tid = v.type_id();
        //type ID of the requested type
        type_id_t target_tid = type_id_map<T>::type_id;

        if(is_numeric(source_tid))
        {
            if(!is_convertible(source_tid,target_tid))
                throw type_error(EXCEPTION_RECORD,
                        "Type conversion not possible!");

            if(source_tid == type_id_t::UINT8)
                return convert<T>(v.template as<uint8>());
            else if(source_tid == type_id_t::INT8)
                return convert<T>(v.template as<int8>());
            else if(source_tid == type_id_t::UINT16)
                return convert<T>(v.template as<uint16>());
            else if(source_tid == type_id_t::INT16)
                return convert<T>(v.template as<int16>());
            else if(source_tid == type_id_t::UINT32)
                return convert<T>(v.template as<uint32>());
            else if(source_tid == type_id_t::INT32)
                return convert<T>(v.template as<int32>());
            else if(source_tid == type_id_t::UINT64)
                return convert<T>(v.template as<uint64>());
            else if(source_tid == type_id_t::INT64)
                return convert<T>(v.template as<int64>());
            else if(source_tid == type_id_t::FLOAT32)
                return convert<T>(v.template as<float32>());
            else if(source_tid == type_id_t::FLOAT64)
                return convert<T>(v.template as<float64>());
            else if(source_tid == type_id_t::FLOAT128)
                return convert<T>(v.template as<float128>());
            else if(source_tid == type_id_t::COMPLEX32)
                return convert<T>(v.template as<complex32>());
            else if(source_tid == type_id_t::COMPLEX64)
                return convert<T>(v.template as<complex64>());
            else if(source_tid == type_id_t::COMPLEX128)
                return convert<T>(v.template as<complex128>());
            else
                throw type_error(EXCEPTION_RECORD,"Unknown type ID");
        }
        else
        {
            //for non numeric types the type IDs must be equal
            if(source_tid != target_tid)
                throw type_error(EXCEPTION_RECORD,
                        "Types must match for non-numeric types!");


            if(source_tid == type_id_t::STRING)
                return v.template as<string>();
            else if(source_tid == type_id_t::BINARY)
                return v.template as<binary>();
            else if(source_tid == type_id_t::BOOL)
                return v.template as<bool_t>();
            else 
                throw type_error(EXCEPTION_RECORD,"Unkown type ID!");


        }

    }

//end of namespace
}
}
