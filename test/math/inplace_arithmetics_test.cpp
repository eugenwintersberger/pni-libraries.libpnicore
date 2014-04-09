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
//!  Created on: Nov 27, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/algorithms/math/inplace_arithmetics.hpp>
#include "inplace_arithmetics_test.hpp"



#define DARRAY_ADD_TEST_REG(IPT,TYPE)\
static CPPUNIT_NS::AutoRegisterSuite<inplace_arithmetics_test<IPT,dynamic_array<TYPE> > >   \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

#define FARRAY_ADD_TEST_REG(IPT,TYPE)\
static CPPUNIT_NS::AutoRegisterSuite<inplace_arithmetics_test<IPT,fixed_dim_array<TYPE,3> > >   \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

#define SARRAY_ADD_TEST_REG(IPT,TYPE)\
static CPPUNIT_NS::AutoRegisterSuite<inplace_arithmetics_test<IPT,static_array<TYPE,2,3,4> > >   \
             CPPUNIT_MAKE_UNIQUE_NAME(autoRegisterRegistry__ )

//DARRAY_ADD_TEST_REG(inplace_arithmetics,int8);
DARRAY_ADD_TEST_REG(inplace_arithmetics,int16);
DARRAY_ADD_TEST_REG(inplace_arithmetics,int32);
DARRAY_ADD_TEST_REG(inplace_arithmetics,int64);
DARRAY_ADD_TEST_REG(inplace_arithmetics,float32);
DARRAY_ADD_TEST_REG(inplace_arithmetics,float64);
DARRAY_ADD_TEST_REG(inplace_arithmetics,float128);
DARRAY_ADD_TEST_REG(inplace_arithmetics,complex32);
DARRAY_ADD_TEST_REG(inplace_arithmetics,complex64);
DARRAY_ADD_TEST_REG(inplace_arithmetics,complex128);

//FARRAY_ADD_TEST_REG(inplace_arithmetics,int8);
FARRAY_ADD_TEST_REG(inplace_arithmetics,int16);
FARRAY_ADD_TEST_REG(inplace_arithmetics,int32);
FARRAY_ADD_TEST_REG(inplace_arithmetics,int64);
FARRAY_ADD_TEST_REG(inplace_arithmetics,float32);
FARRAY_ADD_TEST_REG(inplace_arithmetics,float64);
FARRAY_ADD_TEST_REG(inplace_arithmetics,float128);
FARRAY_ADD_TEST_REG(inplace_arithmetics,complex32);
FARRAY_ADD_TEST_REG(inplace_arithmetics,complex64);
FARRAY_ADD_TEST_REG(inplace_arithmetics,complex128);

//SARRAY_ADD_TEST_REG(inplace_arithmetics,int8);
SARRAY_ADD_TEST_REG(inplace_arithmetics,int16);
SARRAY_ADD_TEST_REG(inplace_arithmetics,int32);
SARRAY_ADD_TEST_REG(inplace_arithmetics,int64);
SARRAY_ADD_TEST_REG(inplace_arithmetics,float32);
SARRAY_ADD_TEST_REG(inplace_arithmetics,float64);
SARRAY_ADD_TEST_REG(inplace_arithmetics,float128);
SARRAY_ADD_TEST_REG(inplace_arithmetics,complex32);
SARRAY_ADD_TEST_REG(inplace_arithmetics,complex64);
SARRAY_ADD_TEST_REG(inplace_arithmetics,complex128);



