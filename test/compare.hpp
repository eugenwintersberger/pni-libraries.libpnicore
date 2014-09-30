//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//!  Created on: Oct 29, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once
#include <type_traits>
#include <complex>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>

using namespace pni::core;

template<typename T>
using is_int_or_string = std::enable_if<(std::is_pod<T>::value && 
                                        !std::is_floating_point<T>::value) || 
                                        std::is_same<T,string>::value || 
                                        std::is_same<T,bool_t>::value >;

template<typename T>
using is_float = std::enable_if<std::is_pod<T>::value && 
                                std::is_floating_point<T>::value>;

//!
//! \brief compare integers and strings
//! 
//! This template function compares two values which are integers and strings. 
//! 
template<
         typename TA,
         typename TB,
         typename = typename std::enable_if<std::is_floating_point<TA>::value || 
                                            std::is_floating_point<TB>::value>::type
        > 
void compare(const TA &a,const TB &b)
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-12);
}


//----------------------------------------------------------------------------
//!
//! \brief compare floats
//! 
//! This function compares floating points values.
//! 
template<
         typename TA,
         typename TB,
         typename = typename std::enable_if<!(std::is_floating_point<TA>::value || 
                                            std::is_floating_point<TB>::value)>::type
        > 
void compare(const TA &a,const TB &b)
{
    CPPUNIT_ASSERT(a==b);
}

//---------------------------------------------------------------------------
//!
//! \brief compare complex
//! 
//! Function template comparing two complex numbers
//!
template<typename T>
void compare(const std::complex<T> &a,const std::complex<T> &b)
{
    compare(a.real(),b.real());
    compare(a.imag(),b.imag());
}

//----------------------------------------------------------------------------
//!
//! \brief comparison of value_ref instances
//!
/*
#define COMPARE_VALUE_WITH_REF(a,b,tid)\
    if((a.type_id() == tid) &&\
       (b.type_id() == tid)) \
    {\
        compare(a.as<id_type_map<tid>::type>(),\
                b.as<id_type_map<tid>::type>());\
        return; \
    }
*/
template<typename T> void compare(const value_ref &a, const T &b)
{
    type_id_t t_id = type_id_map<T>::type_id;
    type_id_t r_id = a.type_id();

    if(t_id == r_id) compare(a.as<T>(),b);
    
}


//----------------------------------------------------------------------------
template<typename T> void compare(const T &a,const value_ref &b)
{
    compare(b,a);
}

//----------------------------------------------------------------------------
void compare(const value_ref &a,const value_ref &b);

//----------------------------------------------------------------------------
void compare(const value &a,const value &b);

//----------------------------------------------------------------------------
void compare(const string &a,const string &b);

