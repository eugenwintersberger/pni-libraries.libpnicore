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
// ===========================================================================
//  Created on: Oct 29, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "compare.hpp"


/*!
\brief comparison of value_ref instances
*/
#define COMPARE_VALUE_REF(a,b,tid)\
    if((a.type_id() == tid) &&\
       (b.type_id() == tid)) \
    {\
        typedef id_type_map<tid>::type value_type;\
        value_type a_value = a.as<value_type>();\
        value_type b_value = b.as<value_type>();\
        compare(a_value,b_value);\
        return; \
    }

bool have_id(type_id_t tid_a,type_id_t tid_b,type_id_t tid_ref)
{
    return (tid_a == tid_ref) && (tid_b == tid_ref);
}

void compare(const value_ref &a,const value_ref &b)
{
    type_id_t tid_a = a.type_id();
    type_id_t tid_b = b.type_id();
    
    if(have_id(tid_a,tid_b,type_id_t::UINT8))
        compare(a.as<uint8>(),b.as<uint8>());
    else if(have_id(tid_a,tid_b,type_id_t::INT8))
        compare(a.as<int8>(),b.as<int8>());
    else if(have_id(tid_a,tid_b,type_id_t::UINT16))
        compare(a.as<uint16>(),b.as<uint16>());
    else if(have_id(tid_a,tid_b,type_id_t::INT16))
        compare(a.as<int16>(),b.as<int16>());
    else if(have_id(tid_a,tid_b,type_id_t::UINT32))
        compare(a.as<uint32>(),b.as<uint32>());
    else if(have_id(tid_a,tid_b,type_id_t::INT32))
        compare(a.as<int32>(),b.as<int32>());
    else if(have_id(tid_a,tid_b,type_id_t::UINT64))
        compare(a.as<uint64>(),b.as<uint64>());
    else if(have_id(tid_a,tid_b,type_id_t::INT64))
        compare(a.as<int64>(),b.as<int64>());
    else if(have_id(tid_a,tid_b,type_id_t::FLOAT32))
        compare(a.as<float32>(),b.as<float32>());
    else if(have_id(tid_a,tid_b,type_id_t::FLOAT64))
        compare(a.as<float64>(),b.as<float64>());
    else if(have_id(tid_a,tid_b,type_id_t::FLOAT128))
        compare(a.as<float128>(),b.as<float128>());
    else if(have_id(tid_a,tid_b,type_id_t::STRING))
        compare(a.as<string>(),b.as<string>());
}

void compare(const value &a,const value &b)
{
    type_id_t tid_a = a.type_id();
    type_id_t tid_b = b.type_id();
    
    if(have_id(tid_a,tid_b,type_id_t::UINT8))
        compare(a.as<uint8>(),b.as<uint8>());
    else if(have_id(tid_a,tid_b,type_id_t::INT8))
        compare(a.as<int8>(),b.as<int8>());
    else if(have_id(tid_a,tid_b,type_id_t::UINT16))
        compare(a.as<uint16>(),b.as<uint16>());
    else if(have_id(tid_a,tid_b,type_id_t::INT16))
        compare(a.as<int16>(),b.as<int16>());
    else if(have_id(tid_a,tid_b,type_id_t::UINT32))
        compare(a.as<uint32>(),b.as<uint32>());
    else if(have_id(tid_a,tid_b,type_id_t::INT32))
        compare(a.as<int32>(),b.as<int32>());
    else if(have_id(tid_a,tid_b,type_id_t::UINT64))
        compare(a.as<uint64>(),b.as<uint64>());
    else if(have_id(tid_a,tid_b,type_id_t::INT64))
        compare(a.as<int64>(),b.as<int64>());
    else if(have_id(tid_a,tid_b,type_id_t::FLOAT32))
        compare(a.as<float32>(),b.as<float32>());
    else if(have_id(tid_a,tid_b,type_id_t::FLOAT64))
        compare(a.as<float64>(),b.as<float64>());
    else if(have_id(tid_a,tid_b,type_id_t::FLOAT128))
        compare(a.as<float128>(),b.as<float128>());
    else if(have_id(tid_a,tid_b,type_id_t::STRING))
        compare(a.as<string>(),b.as<string>());
}

void compare(const string &a,const string &b)
{
    CPPUNIT_ASSERT(a == b);
}
