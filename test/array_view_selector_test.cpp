/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jul 18, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include<cppunit/extensions/HelperMacros.h>

#include <typeinfo>
#include <pni/core/types.hpp>
#include <pni/core/slice.hpp>
#include <pni/core/numarray.hpp>
#include <pni/core/sarray.hpp>
#include <pni/core/array_view.hpp>
#include <pni/core/service.hpp>

#include "array_view_selector_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_view_selector_test);


void array_view_selector_test::test_selector()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef sarray<float64,3,4,5,6> array_type;
    typedef array_view_selector<array_type,size_t,size_t,size_t> scalar_selector_view;
    typedef array_view_selector<array_type,size_t,size_t,slice,size_t> array_selector_view;

    CPPUNIT_ASSERT(typeid(scalar_selector_view::viewtype).name()==
                   typeid(float64).name());

    CPPUNIT_ASSERT(typeid(array_selector_view::viewtype).name() == 
                   typeid(array_view<array_type>).name());

    //this should return an array view
    CPPUNIT_ASSERT(typeid(array_view_selector<array_type,slice,slice,size_t,size_t,size_t>::viewtype).name()==typeid(array_view<array_type>).name());

    typedef numarray<array_type> narray_type;

    //this will return a scalar view
    CPPUNIT_ASSERT(typeid(array_view_selector<narray_type,size_t,size_t,size_t,size_t>::viewtype).name()
                   == typeid(float64).name());

    std::cout<<"---------------------------------------"<<std::endl;
    std::cout<<"type: "<<
    demangle_cpp_name(typeid(
    array_view_selector<narray_type,slice,size_t,slice,size_t>::viewtype).name()
    )<<std::endl;
    std::cout<<"type: "<<
    demangle_cpp_name(typeid(numarray<array_view<narray_type> >).name())<<std::endl;
    std::cout<<"---------------------------------------"<<std::endl;
    CPPUNIT_ASSERT(
    typeid(array_view_selector<narray_type,slice,size_t,slice,size_t>::viewtype).name()
                   == typeid(numarray<array_view<narray_type> >).name());

}
