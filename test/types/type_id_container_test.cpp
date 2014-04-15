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
// ===========================================================================
//
//  Created on: Sep 30, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <list>
#include <pni/core/arrays.hpp>

#include "type_id_container_test.hpp"
using namespace std;

template<typename T> using sarray = static_array<T,1>;
template<typename T> using darray = dynamic_array<T>;
template<typename T> using farray = fixed_dim_array<T,2>;

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
CTEST_REGISTRATION(std::vector,bool_t,type_id_t::BOOL);

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
CTEST_REGISTRATION(std::list,bool_t,type_id_t::BOOL);

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
CTEST_REGISTRATION(darray,bool_t,type_id_t::BOOL);

//====================sarray test==============================================
CTEST_REGISTRATION(sarray,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(sarray,int8,type_id_t::INT8);
CTEST_REGISTRATION(sarray,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(sarray,int16,type_id_t::INT16);
CTEST_REGISTRATION(sarray,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(sarray,int32,type_id_t::INT32);
CTEST_REGISTRATION(sarray,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(sarray,int64,type_id_t::INT64);

CTEST_REGISTRATION(sarray,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(sarray,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(sarray,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(sarray,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(sarray,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(sarray,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(sarray,string,type_id_t::STRING);
CTEST_REGISTRATION(sarray,binary,type_id_t::BINARY);
CTEST_REGISTRATION(sarray,bool_t,type_id_t::BOOL);

//====================farray test==============================================
CTEST_REGISTRATION(farray,uint8,type_id_t::UINT8);
CTEST_REGISTRATION(farray,int8,type_id_t::INT8);
CTEST_REGISTRATION(farray,uint16,type_id_t::UINT16);
CTEST_REGISTRATION(farray,int16,type_id_t::INT16);
CTEST_REGISTRATION(farray,uint32,type_id_t::UINT32);
CTEST_REGISTRATION(farray,int32,type_id_t::INT32);
CTEST_REGISTRATION(farray,uint64,type_id_t::UINT64);
CTEST_REGISTRATION(farray,int64,type_id_t::INT64);

CTEST_REGISTRATION(farray,float32,type_id_t::FLOAT32);
CTEST_REGISTRATION(farray,float64,type_id_t::FLOAT64);
CTEST_REGISTRATION(farray,float128,type_id_t::FLOAT128);
CTEST_REGISTRATION(farray,complex32,type_id_t::COMPLEX32);
CTEST_REGISTRATION(farray,complex64,type_id_t::COMPLEX64);
CTEST_REGISTRATION(farray,complex128,type_id_t::COMPLEX128);

CTEST_REGISTRATION(farray,string,type_id_t::STRING);
CTEST_REGISTRATION(farray,binary,type_id_t::BINARY);
CTEST_REGISTRATION(farray,bool_t,type_id_t::BOOL);
