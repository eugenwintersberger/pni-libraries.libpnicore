/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jul 18, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include<cppunit/extensions/HelperMacros.h>

#include <typeinfo>
#include <pni/core/Types.hpp>
#include <pni/core/Slice.hpp>
#include <pni/core/NumArray.hpp>
#include <pni/core/SArray.hpp>
#include <pni/core/ArrayView.hpp>
#include <pni/core/service.hpp>

#include "ArrayViewSelectorTest.hpp"

//CPPUNIT_TEST_SUITE_REGISTRATION(ArrayViewSelectorTest);

/*
void ArrayViewSelectorTest::test_selector()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef SArray<Float64,3,4,5,6> array_type;
    typedef ArrayViewSelector<array_type,size_t,size_t,size_t> scalar_view;
    typedef ArrayViewSelector<array_type,size_t,size_t,Slice,size_t> array_view;

    CPPUNIT_ASSERT(typeid(scalar_view::viewtype).name()==
                   typeid(Float64).name());

    CPPUNIT_ASSERT(typeid(array_view::viewtype).name() == 
                   typeid(ArrayView<array_type>).name());

    CPPUNIT_ASSERT(typeid(ArrayViewSelector<array_type,Slice,Slice,size_t,size_t,size_t>::viewtype).name()==typeid(ArrayView<array_type>).name());

    typedef NumArray<array_type> narray_type;

    CPPUNIT_ASSERT(typeid(ArrayViewSelector<narray_type,size_t,size_t,size_t,size_t>::viewtype).name()
                   == typeid(Float64).name());

    std::cout<<"---------------------------------------"<<std::endl;
    std::cout<<"type: "<<demangle_cpp_name(typeid(ArrayViewSelector<narray_type,Slice,size_t,Slice,size_t>::viewtype).name())<<std::endl;
    std::cout<<"type: "<<demangle_cpp_name(typeid(NumArray<ArrayView<narray_type> >).name())<<std::endl;
    std::cout<<"---------------------------------------"<<std::endl;
    CPPUNIT_ASSERT(typeid(ArrayViewSelector<narray_type,Slice,size_t,Slice,size_t>::viewtype).name()
                   == typeid(NumArray<ArrayView<narray_type> >).name());

}

*/
