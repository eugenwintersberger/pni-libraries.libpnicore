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
 *  Created on: Sep 30, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <list>
#include <pni/core/darray.hpp>
#include <pni/core/sarray.hpp>
#include <pni/core/numarray.hpp>

#include "type_id_container_test.hpp"
using namespace std;

template<typename T> using sarray_temp = sarray<T,1>;
template<typename T> using snarray = numarray<sarray_temp<T> >;
template<typename T> using dnarray = numarray<darray<T> >;

#define CTEST_REGISTRATION(ct,type,tid)\
static CPPUNIT_NS::AutoRegisterSuite< type_id_container_test<ct<type>,tid > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

#define TEST_FOR_CONTAINER(cont)\
    CTEST_REGISTRATION(cont,uint8,type_id_t::UINT8);\
    CTEST_REGISTRATION(cont,int8,type_id_t::INT8);\
    CTEST_REGISTRATION(cont,uint16,type_id_t::UINT16);\
    CTEST_REGISTRATION(cont,int16,type_id_t::INT16);\
    CTEST_REGISTRATION(cont,uint32,type_id_t::UINT32);\
    CTEST_REGISTRATION(cont,int32,type_id_t::INT32);\
    CTEST_REGISTRATION(cont,uint64,type_id_t::UINT64);\
    CTEST_REGISTRATION(cont,int64,type_id_t::INT64);\
    CTEST_REGISTRATION(cont,float32,type_id_t::FLOAT32);\
    CTEST_REGISTRATION(cont,float64,type_id_t::FLOAT64);\
    CTEST_REGISTRATION(cont,float128,type_id_t::FLOAT128);\
    CTEST_REGISTRATION(cont,complex32,type_id_t::COMPLEX32);\
    CTEST_REGISTRATION(cont,complex64,type_id_t::COMPLEX64);\
    CTEST_REGISTRATION(cont,complex128,type_id_t::COMPLEX128);\
    CTEST_REGISTRATION(cont,string,type_id_t::STRING);\
    CTEST_REGISTRATION(cont,binary,type_id_t::BINARY)

//TEST_FOR_CONTAINER(vector);
//=========================vector test=========================================
CTEST_REGISTRATION(std::vector,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(std::vector,int8,type_id_t::INT8);
CTEST_REGISTRATION(std::vector,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(std::vector,int16,type_id_t::INT16);
CTEST_REGISTRATION(std::vector,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(std::vector,int32,type_id_t::INT32);
CTEST_REGISTRATION(std::vector,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(std::vector,int64,type_id_t::INT64);

CTEST_REGISTRATION(std::vector,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(std::vector,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(std::vector,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(std::vector,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(std::vector,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(std::vector,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(std::vector,string,type_id_t::STRING);
CTEST_REGISTRATION(std::vector,binary,type_id_t::BINARY);

//====================list test================================================
CTEST_REGISTRATION(std::list,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(std::list,int8,type_id_t::INT8);
CTEST_REGISTRATION(std::list,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(std::list,int16,type_id_t::INT16);
CTEST_REGISTRATION(std::list,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(std::list,int32,type_id_t::INT32);
CTEST_REGISTRATION(std::list,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(std::list,int64,type_id_t::INT64);

CTEST_REGISTRATION(std::list,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(std::list,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(std::list,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(std::list,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(std::list,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(std::list,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(std::list,string,type_id_t::STRING);
CTEST_REGISTRATION(std::list,binary,type_id_t::BINARY);

//====================darray test==============================================
CTEST_REGISTRATION(darray,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(darray,int8,type_id_t::INT8);
CTEST_REGISTRATION(darray,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(darray,int16,type_id_t::INT16);
CTEST_REGISTRATION(darray,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(darray,int32,type_id_t::INT32);
CTEST_REGISTRATION(darray,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(darray,int64,type_id_t::INT64);

CTEST_REGISTRATION(darray,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(darray,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(darray,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(darray,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(darray,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(darray,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(darray,string,type_id_t::STRING);
CTEST_REGISTRATION(darray,binary,type_id_t::BINARY);


//====================sarray test==============================================
CTEST_REGISTRATION(sarray_temp,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(sarray_temp,int8,type_id_t::INT8);
CTEST_REGISTRATION(sarray_temp,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(sarray_temp,int16,type_id_t::INT16);
CTEST_REGISTRATION(sarray_temp,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(sarray_temp,int32,type_id_t::INT32);
CTEST_REGISTRATION(sarray_temp,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(sarray_temp,int64,type_id_t::INT64);

CTEST_REGISTRATION(sarray_temp,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(sarray_temp,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(sarray_temp,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(sarray_temp,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(sarray_temp,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(sarray_temp,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(sarray_temp,string,type_id_t::STRING);
CTEST_REGISTRATION(sarray_temp,binary,type_id_t::BINARY);

//====================snarray test=============================================
CTEST_REGISTRATION(snarray,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(snarray,int8,type_id_t::INT8);
CTEST_REGISTRATION(snarray,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(snarray,int16,type_id_t::INT16);
CTEST_REGISTRATION(snarray,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(snarray,int32,type_id_t::INT32);
CTEST_REGISTRATION(snarray,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(snarray,int64,type_id_t::INT64);

CTEST_REGISTRATION(snarray,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(snarray,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(snarray,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(snarray,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(snarray,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(snarray,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(snarray,string,type_id_t::STRING);
CTEST_REGISTRATION(snarray,binary,type_id_t::BINARY);

//====================dnarray test=============================================
CTEST_REGISTRATION(dnarray,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(dnarray,int8,type_id_t::INT8);
CTEST_REGISTRATION(dnarray,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(dnarray,int16,type_id_t::INT16);
CTEST_REGISTRATION(dnarray,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(dnarray,int32,type_id_t::INT32);
CTEST_REGISTRATION(dnarray,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(dnarray,int64,type_id_t::INT64);

CTEST_REGISTRATION(dnarray,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(dnarray,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(dnarray,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(dnarray,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(dnarray,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(dnarray,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(dnarray,string,type_id_t::STRING);
CTEST_REGISTRATION(dnarray,binary,type_id_t::BINARY);

