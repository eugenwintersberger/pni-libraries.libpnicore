/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Oct 28, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <boost/current_function.hpp>
#include <algorithm>

#include "common.hpp"

#include "../data_generator.hpp"
#include "../EqualityCheck.hpp"

using namespace pni::core;

/*!
\brief darray template test

\tparam STORAGE type
\tparam MAPT index map type
 */
template<typename ATYPE>
class dynamic_mdarray_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(dynamic_mdarray_test);
        CPPUNIT_TEST(test_constructors);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef typename ATYPE::map_type     index_map_type;
        typedef typename ATYPE::storage_type storage_type;
        typedef typename ATYPE::value_type   value_type;
        std::vector<value_type> ref_data; //buffer with reference data
        ATYPE array;
        shape_t shape;

        //---------------------------------------------------------------------
        template<typename CTYPE> 
        static void allocate_storage(CTYPE &s,size_t n)
        {
            s = CTYPE(n);
        }

    public:
        void setUp();
        void tearDown();
        void test_constructors();
        void test_assignment();
};

//------------------------------------------------------------------------------
template<typename ATYPE> 
void dynamic_mdarray_test<ATYPE>::setUp()
{
    shape = {2,3,5};
    ref_data = std::vector<value_type>(2*3*5);
    std::generate(ref_data.begin(),ref_data.end(),random_generator<value_type>());
}

//------------------------------------------------------------------------------
template<typename ATYPE> 
void dynamic_mdarray_test<ATYPE>::tearDown() { }

//------------------------------------------------------------------------------
template<typename ATYPE>
void dynamic_mdarray_test<ATYPE>::test_constructors()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //check parameters after default construction
    ATYPE array1;
    CPPUNIT_ASSERT(array1.size() == 0);
    CPPUNIT_ASSERT(array1.rank() == 0);

    //check default construction
    //we construct the array from an map instance and a storage instance using 
    //copy construction of the objects
    auto map = map_utils<index_map_type>::create(shape);
    storage_type storage;
    allocate_storage(storage,map.max_elements());
    ATYPE array2(map,storage);
   
    CPPUNIT_ASSERT(array2.rank() == 3);
    CPPUNIT_ASSERT(array2.size() == storage.size());

    //this is however not very efficient - try move construction of the map and
    //storage
    ATYPE array3(std::move(map),std::move(storage));
    CPPUNIT_ASSERT(array3.size() == 30);
    CPPUNIT_ASSERT(array3.rank() == 3);
    CPPUNIT_ASSERT(storage.size()==0);
    CPPUNIT_ASSERT(map.rank() == 0);

    //now lets do some move construction
    ATYPE array4 = std::move(array3);
    CPPUNIT_ASSERT(array4.rank() == array2.rank());
    CPPUNIT_ASSERT(array4.size() == array2.size());
    CPPUNIT_ASSERT(array3.size() == 0);
    CPPUNIT_ASSERT(array3.rank() == 0);
}

//------------------------------------------------------------------------------
template<typename ATYPE>
void dynamic_mdarray_test<ATYPE>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    auto map = map_utils<index_map_type>::create(shape);
    storage_type storage;
    allocate_storage(storage,map.max_elements());
    ATYPE array1(std::move(map),std::move(storage));

    ATYPE array2,array3;

    //copy assignment
    array2 = array1;
    CPPUNIT_ASSERT(array2.rank() == array1.rank());
    CPPUNIT_ASSERT(array2.size() == array1.size());
    CPPUNIT_ASSERT(std::equal(array1.begin(),array1.end(),array2.begin()));

    //do move assignment
    array3 = std::move(array1);
    CPPUNIT_ASSERT(array2.rank() == array3.rank());
    CPPUNIT_ASSERT(array2.size() == array3.size());
    CPPUNIT_ASSERT(std::equal(array1.begin(),array1.end(),array3.begin()));

    //check if the original is destroyed
    CPPUNIT_ASSERT(array1.rank() == 0);
    CPPUNIT_ASSERT(array1.size() == 0);
}

