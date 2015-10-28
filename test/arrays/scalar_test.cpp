//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Sep 02, 2011
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include "../types.hpp"
#include "../data_generator.hpp"
#include<iostream>
#include<typeinfo>

using namespace pni::core;

template<typename T> struct scalar_fixture
{
    typedef random_generator<T> generator_type;
    generator_type generator;
    T v;

    scalar_fixture():
        generator(),
        v(generator())
    {}
};

BOOST_AUTO_TEST_SUITE(scalar_test)

    BOOST_AUTO_TEST_SUITE_TEMPLATE(test_construction,T,numeric_types)   
    {
        typedef scalar_fixture<T> fixture_type;
        fixture_type fixture; 

        scalar<T> s;
        BOOST_CHECK_EQUAL(s.rank(),0);
        BOOST_CHECK_EQUAL(s.size(),1);

        //check the default constructor
        scalar<T> s1(fixture.v);
        BOOST_CHECK_EQUAL(T(s1),fixture.v);

        //copy construction
        scalar<T> s2 = s1;
        BOOST_CHECK_EQUAL(
    }

BOOST_AUTO_TEST_SUITE_END()





