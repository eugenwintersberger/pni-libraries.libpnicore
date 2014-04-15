//!
//! (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//!  Created on: May 14, 2012
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!/
#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/current_function.hpp>

#include "array_view_test.hpp"



template<typename T> using dyn_array_view_test = array_view_test<dynamic_array<T> >;

CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<string>);
CPPUNIT_TEST_SUITE_REGISTRATION(dyn_array_view_test<bool_t>);

template<typename T>
using fix_array_view_test = array_view_test<fixed_dim_array<T,2>>;

CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<string>);
CPPUNIT_TEST_SUITE_REGISTRATION(fix_array_view_test<bool_t>);

template<typename T> 
using static_array_view_test = array_view_test<static_array<T,NX,NY>>;
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<uint8>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<uint16>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<uint32>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<uint64>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<int64>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<float128>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<complex128>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<string>);
CPPUNIT_TEST_SUITE_REGISTRATION(static_array_view_test<bool_t>);







