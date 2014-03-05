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
//!  Created on: Nov 13, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!/
#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <vector>
#include <list>
#include <array>

#include <pni/core/index_map/c_index_map_imp.hpp>
#include "cindex_implementation_test.hpp"
#include "common.hpp"

#define REGISTER_TEST_SUITE(templ,stype,itype)\
  static CPPUNIT_NS::AutoRegisterSuite<templ<stype,itype> >       \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

//------------------define some common types---------------------------
typedef std::vector<size_t> vector_type;
typedef std::list<size_t>   list_type;

template<size_t N> using array = std::array<size_t,N>;

//-------------define some test parameters here------------------------
typedef test_params<3,4,5> test_params_1;
typedef test_params<10>    test_params_3;
typedef test_params<2,3>   test_params_2;

typedef array<test_params_1::rank> array_test_1;
typedef array<test_params_3::rank> array_test_3;
typedef array<test_params_2::rank> array_test_2;

//----------------------define here the first test--------------------
template<typename ST,typename IT> 
using test_1 = cindex_implementation_test<c_index_map_imp,
                                          test_params_1,
                                          ST, IT, 33,1,2,3> ;


REGISTER_TEST_SUITE(test_1,vector_type,vector_type);
REGISTER_TEST_SUITE(test_1,list_type,vector_type);
REGISTER_TEST_SUITE(test_1,vector_type,list_type);
REGISTER_TEST_SUITE(test_1,list_type,list_type);
REGISTER_TEST_SUITE(test_1,vector_type,array_test_1);
REGISTER_TEST_SUITE(test_1,array_test_1,vector_type);
REGISTER_TEST_SUITE(test_1,vector_type,array_test_1);
REGISTER_TEST_SUITE(test_1,array_test_1,array_test_1);
REGISTER_TEST_SUITE(test_1,list_type,array_test_1);
REGISTER_TEST_SUITE(test_1,array_test_1,list_type);
REGISTER_TEST_SUITE(test_1,list_type,array_test_1);
REGISTER_TEST_SUITE(test_1,array_test_1,array_test_1);

//--------------------define the second test here--------------------
template<typename ST,typename IT>
using test_2 = cindex_implementation_test<c_index_map_imp,
                                          test_params_2,
                                          ST, IT, 5,1,2>;

REGISTER_TEST_SUITE(test_2,vector_type,vector_type);
REGISTER_TEST_SUITE(test_2,list_type,vector_type);
REGISTER_TEST_SUITE(test_2,vector_type,list_type);
REGISTER_TEST_SUITE(test_2,list_type,list_type);
REGISTER_TEST_SUITE(test_2,vector_type,array_test_2);
REGISTER_TEST_SUITE(test_2,array_test_2,vector_type);
REGISTER_TEST_SUITE(test_2,vector_type,array_test_2);
REGISTER_TEST_SUITE(test_2,array_test_2,array_test_2);
REGISTER_TEST_SUITE(test_2,list_type,array_test_2);
REGISTER_TEST_SUITE(test_2,array_test_2,list_type);
REGISTER_TEST_SUITE(test_2,list_type,array_test_2);
REGISTER_TEST_SUITE(test_2,array_test_2,array_test_2);

//--------------------define the third test here--------------------
template<typename ST,typename IT>
using test_3 = cindex_implementation_test<c_index_map_imp,
                                          test_params_3,
                                          ST, IT, 3,3>;

REGISTER_TEST_SUITE(test_3,vector_type,vector_type);
REGISTER_TEST_SUITE(test_3,list_type,vector_type);
REGISTER_TEST_SUITE(test_3,vector_type,list_type);
REGISTER_TEST_SUITE(test_3,list_type,list_type);
REGISTER_TEST_SUITE(test_3,vector_type,array_test_3);
REGISTER_TEST_SUITE(test_3,array_test_3,vector_type);
REGISTER_TEST_SUITE(test_3,vector_type,array_test_3);
REGISTER_TEST_SUITE(test_3,array_test_3,array_test_3);
REGISTER_TEST_SUITE(test_3,list_type,array_test_3);
REGISTER_TEST_SUITE(test_3,array_test_3,list_type);
REGISTER_TEST_SUITE(test_3,list_type,array_test_3);
REGISTER_TEST_SUITE(test_3,array_test_3,array_test_3);
