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
//!  Created on: Nov 28, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "mdarray_unary_arithmetic_test.hpp"



#define DYNARRAY_TEST_REGISTRATION(type)\
static CPPUNIT_NS::AutoRegisterSuite< mdarray_unary_arithmetic_test<dynamic_array<type> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

#define FIXARRAY_TEST_REGISTRATION(type,ndims)\
static CPPUNIT_NS::AutoRegisterSuite< mdarray_unary_arithmetic_test<fixed_dim_array<type,ndims> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

template<typename T> using static_a = static_array<T,2,3,5>;
#define STATARRAY_TEST_REGISTRATION(type)\
static CPPUNIT_NS::AutoRegisterSuite< mdarray_unary_arithmetic_test<static_a<type> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )


//-------------------dynamic array tests-----------------------------------
DYNARRAY_TEST_REGISTRATION(int16);
DYNARRAY_TEST_REGISTRATION(int32);
DYNARRAY_TEST_REGISTRATION(int64);
DYNARRAY_TEST_REGISTRATION(float32);
DYNARRAY_TEST_REGISTRATION(float64);
DYNARRAY_TEST_REGISTRATION(float128);
DYNARRAY_TEST_REGISTRATION(complex32);
DYNARRAY_TEST_REGISTRATION(complex64);
DYNARRAY_TEST_REGISTRATION(complex128);


//-------------------fixed dimension array tests---------------------------
FIXARRAY_TEST_REGISTRATION(int16,3);
FIXARRAY_TEST_REGISTRATION(int32,3);
FIXARRAY_TEST_REGISTRATION(int64,3);
FIXARRAY_TEST_REGISTRATION(float32,3);
FIXARRAY_TEST_REGISTRATION(float64,3);
FIXARRAY_TEST_REGISTRATION(float128,3);
FIXARRAY_TEST_REGISTRATION(complex32,3);
FIXARRAY_TEST_REGISTRATION(complex64,3);
FIXARRAY_TEST_REGISTRATION(complex128,3);

//-------------------static array tests------------------------------------
STATARRAY_TEST_REGISTRATION(int16);
STATARRAY_TEST_REGISTRATION(int32);
STATARRAY_TEST_REGISTRATION(int64);
STATARRAY_TEST_REGISTRATION(float32);
STATARRAY_TEST_REGISTRATION(float64);
STATARRAY_TEST_REGISTRATION(float128);
STATARRAY_TEST_REGISTRATION(complex32);
STATARRAY_TEST_REGISTRATION(complex64);
STATARRAY_TEST_REGISTRATION(complex128);
