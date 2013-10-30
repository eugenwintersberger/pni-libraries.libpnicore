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
 *  Created on: Oct 29, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "compare.hpp"


/*!
\brief comparison of value_ref instances
*/
#define COMPARE_VALUE_REF(a,b,tid)\
    if((a.type_id() == tid) &&\
       (b.type_id() == tid)) \
    {\
        compare(a.as<id_type_map<tid>::type>(),\
                b.as<id_type_map<tid>::type>());\
        return; \
    }

void compare(const value_ref &a,const value_ref &b)
{
    COMPARE_VALUE_REF(a,b,type_id_t::UINT8);
    COMPARE_VALUE_REF(a,b,type_id_t::INT8);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT16);
    COMPARE_VALUE_REF(a,b,type_id_t::INT16);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT32);
    COMPARE_VALUE_REF(a,b,type_id_t::INT32);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT64);
    COMPARE_VALUE_REF(a,b,type_id_t::INT64);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT32);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT64);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT128);
    COMPARE_VALUE_REF(a,b,type_id_t::STRING);
}

void compare(const value &a,const value &b)
{
    COMPARE_VALUE_REF(a,b,type_id_t::UINT8);
    COMPARE_VALUE_REF(a,b,type_id_t::INT8);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT16);
    COMPARE_VALUE_REF(a,b,type_id_t::INT16);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT32);
    COMPARE_VALUE_REF(a,b,type_id_t::INT32);
    COMPARE_VALUE_REF(a,b,type_id_t::UINT64);
    COMPARE_VALUE_REF(a,b,type_id_t::INT64);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT32);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT64);
    COMPARE_VALUE_REF(a,b,type_id_t::FLOAT128);
    COMPARE_VALUE_REF(a,b,type_id_t::STRING);
}
