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
//!  Created on: Nov 07, 2013
//!      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <array>
#include <pni/core/utilities/container_utils.hpp>
#include "../data_generator.hpp"
#include "../compare.hpp"

using namespace pni::core;

template<typename T>
using array_type = std::array<T,4>;

//data types for which to test container construction
typedef boost::mpl::list<array_type<uint8>,
                         array_type<int8>,
                         array_type<uint16>,
                         array_type<int16>,
                         array_type<uint32>,
                         array_type<int32>,
                         array_type<uint64>,
                         array_type<int64>,
                         array_type<float32>,
                         array_type<float64>,
                         array_type<float128>,
                         array_type<complex32>,
                         array_type<complex64>,
                         array_type<complex128>,
                         array_type<string>,
                         array_type<bool_t>
                         > test_types;

template<typename T> struct test_trait
{
    typedef container_utils<T>     utils_type;
    typedef typename T::value_type value_type;
    typedef std::vector<value_type> ref_type; 
    typedef random_generator<value_type> generator_type;
};


BOOST_AUTO_TEST_SUITE(container_utils_array_test)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_size,CT,test_types)
{
    typedef test_trait<CT> trait_type;
    typedef typename trait_type::generator_type generator_type;
    typedef typename trait_type::utils_type utils_type;
    generator_type generator;

    //without initializiation value
    auto c1 = utils_type::create(4);
    BOOST_CHECK_EQUAL(c1.size(),4);


    //with initializiation value
    auto random_value = generator();
    auto c2 = utils_type::create(4,random_value);
    for(auto c: c2)
        BOOST_CHECK_EQUAL(c,random_value);

    //check exception
    BOOST_CHECK_THROW(utils_type::create(5),size_mismatch_error);
    BOOST_CHECK_THROW(utils_type::create(3),size_mismatch_error);
}


BOOST_AUTO_TEST_SUITE_END()



