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
#include <list>
#include <vector>
#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/utilities/container_utils.hpp>
#include "../data_generator.hpp"

using namespace pni::core;

typedef boost::mpl::list<std::vector<uint8>,
                         std::vector<int8>> test_types;


template<typename T> struct test_trait
{
    typedef container_utils<T>     utils_type;
    typedef typename T::value_type value_type;
    typedef std::vector<value_type> ref_type; 
    typedef random_generator<value_type> generator_type;
};

BOOST_AUTO_TEST_SUITE(container_utils_std_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_size,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::generator_type generator_type;

        //without initializiation value
        auto c1 = utils_type::create(10);
        BOOST_CHECK_EQUAL(c1.size(),10);

        //with initializiation value
        auto init_value = generator_type()();
        auto c2 = utils_type::create(100,init_value);
        for(auto c: c2) BOOST_CHECK_EQUAL(c,init_value);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_range,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::ref_type   vector_type;
        typedef typename trait_type::generator_type generator_type; 
    
        generator_type generator;
        vector_type v(100);
        std::generate(v.begin(),v.end(),generator);
        auto c = utils_type::create(v.begin(),v.end());
        BOOST_CHECK_EQUAL(c.size(),v.size());
        
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),c.begin(),c.end());
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_container,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::ref_type   vector_type;
        typedef typename trait_type::generator_type generator_type;

        generator_type generator;
        vector_type v(100);
        std::generate(v.begin(),v.end(),generator);

        auto c = utils_type::create(v);
        BOOST_CHECK_EQUAL(c.size(),v.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),c.begin(),c.end());
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_create_from_init_list,CTYPE,test_types)
    {
        typedef test_trait<CTYPE> trait_type;
        typedef typename trait_type::utils_type utils_type;
        typedef typename trait_type::ref_type   vector_type;

        auto v = vector_type{1,2,3,4};
        auto c = utils_type::create({1,2,3,4});
        BOOST_CHECK_EQUAL(c.size(),v.size());
        BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(),v.end(),c.begin(),c.end());
    }

BOOST_AUTO_TEST_SUITE_END()

