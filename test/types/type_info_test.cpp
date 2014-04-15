//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Oct 01, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include<cppunit/extensions/HelperMacros.h>
#include<limits>

#include "type_info_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(type_info_test);

//-----------------------------------------------------------------------------
void type_info_test::test_min_max()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //--------------testing integer types----------------------
    CPPUNIT_ASSERT(type_info<uint8>::min() == std::numeric_limits<uint8>::min() );
    CPPUNIT_ASSERT(type_info<uint8>::max() == std::numeric_limits<uint8>::max() );

    CPPUNIT_ASSERT(type_info<int8>::min() == std::numeric_limits<int8>::min());
    CPPUNIT_ASSERT(type_info<int8>::max() == std::numeric_limits<int8>::max());

    CPPUNIT_ASSERT(type_info<uint16>::min() == std::numeric_limits<uint16>::min());
    CPPUNIT_ASSERT(type_info<uint16>::max() == std::numeric_limits<uint16>::max());

    CPPUNIT_ASSERT(type_info<int16>::min() == std::numeric_limits<int16>::min());
    CPPUNIT_ASSERT(type_info<int16>::max() == std::numeric_limits<int16>::max());

    CPPUNIT_ASSERT(type_info<uint32>::min() == std::numeric_limits<uint32>::min());
    CPPUNIT_ASSERT(type_info<uint32>::max() == std::numeric_limits<uint32>::max());

    CPPUNIT_ASSERT(type_info<int32>::min() == std::numeric_limits<int32>::min());
    CPPUNIT_ASSERT(type_info<int32>::max() == std::numeric_limits<int32>::max());

    CPPUNIT_ASSERT(type_info<int64>::min() == std::numeric_limits<int64>::min());
    CPPUNIT_ASSERT(type_info<int64>::max() == std::numeric_limits<int64>::max());

    CPPUNIT_ASSERT(type_info<uint64>::min() == std::numeric_limits<uint64>::min());
    CPPUNIT_ASSERT(type_info<uint64>::max() == std::numeric_limits<uint64>::max());


    //---------------------testing floating point type----------
    CPPUNIT_ASSERT(type_info<float32>::min() == -FLT_MAX);
    CPPUNIT_ASSERT(type_info<float32>::max() == +FLT_MAX);

    CPPUNIT_ASSERT(type_info<float64>::min() == -DBL_MAX);
    CPPUNIT_ASSERT(type_info<float64>::max() == +DBL_MAX);

    CPPUNIT_ASSERT(type_info<float128>::min() == -LDBL_MAX);
    CPPUNIT_ASSERT(type_info<float128>::max() == +LDBL_MAX);

    //------------------testing floating point numbers----------
    CPPUNIT_ASSERT(type_info<complex32>::min() == -FLT_MAX);
    CPPUNIT_ASSERT(type_info<complex32>::max() == +FLT_MAX);

    CPPUNIT_ASSERT(type_info<complex64>::min() == -DBL_MAX);
    CPPUNIT_ASSERT(type_info<complex64>::max() == +DBL_MAX);

    CPPUNIT_ASSERT(type_info<complex128>::min() == -LDBL_MAX);
    CPPUNIT_ASSERT(type_info<complex128>::max() == +LDBL_MAX);

    //------------------special types---------------------------
    CPPUNIT_ASSERT(type_info<bool>::min() == false);
    CPPUNIT_ASSERT(type_info<bool>::max() == true);

}

//----------------------------------------------------------------------------
void type_info_test::test_binary()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef type_info<binary> info_type;
        
    CPPUNIT_ASSERT(info_type::size == 1);
    CPPUNIT_ASSERT(info_type::is_integer);
    CPPUNIT_ASSERT(!info_type::is_signed);
    CPPUNIT_ASSERT(!info_type::is_complex);

    CPPUNIT_ASSERT(info_type::min() == 0);
    CPPUNIT_ASSERT(info_type::max() == 255);
}

//----------------------------------------------------------------------------
void type_info_test::test_bool()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef type_info<bool_t> info_type;

    CPPUNIT_ASSERT(info_type::size == 1);
    CPPUNIT_ASSERT(info_type::is_integer);
    CPPUNIT_ASSERT(!info_type::is_signed);
    CPPUNIT_ASSERT(!info_type::is_complex);

    CPPUNIT_ASSERT(info_type::min() == false);
    CPPUNIT_ASSERT(info_type::max() == true);
}

