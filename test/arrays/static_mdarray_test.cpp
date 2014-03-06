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
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "static_mdarray_test.hpp"


template<typename T> using static_a = static_array<T,2,3,5>;
#define STATARRAY_TEST_REGISTRATION(type)\
static CPPUNIT_NS::AutoRegisterSuite< static_mdarray_test<static_a<type> > >  \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

//-------------------dynamic array tests-----------------------------------
STATARRAY_TEST_REGISTRATION(uint8);
STATARRAY_TEST_REGISTRATION(int8);
STATARRAY_TEST_REGISTRATION(uint16);
STATARRAY_TEST_REGISTRATION(int16);
STATARRAY_TEST_REGISTRATION(uint32);
STATARRAY_TEST_REGISTRATION(int32);
STATARRAY_TEST_REGISTRATION(uint64);
STATARRAY_TEST_REGISTRATION(int64);
STATARRAY_TEST_REGISTRATION(float32);
STATARRAY_TEST_REGISTRATION(float64);
STATARRAY_TEST_REGISTRATION(float128);
STATARRAY_TEST_REGISTRATION(complex32);
STATARRAY_TEST_REGISTRATION(complex64);
STATARRAY_TEST_REGISTRATION(complex128);
STATARRAY_TEST_REGISTRATION(string);
