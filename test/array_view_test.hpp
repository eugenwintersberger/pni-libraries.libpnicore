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
 *  Created on: May 14, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<vector>
#include <pni/core/ArrayView.hpp>
#include <pni/core/Array.hpp>
#include <pni/core/index_iterator.hpp>
#include "uniform_distribution.hpp"
#include "array_factory.hpp"
#include "data_generator.hpp"
#include "EqualityCheck.hpp"

using namespace pni::core;

#define NX 100
#define NY 125


template<typename ATYPE> class array_view_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_view_test<ATYPE>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterator_access);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef std::vector<size_t> Shape;
        Shape s1,s2;
        size_t r1,r2;
        shape_t _shape;
    public:
        void setUp();
        void tearDown();

        //---------------------------------------------------------------------
        /*! 
        \brief test construction

        Test the construction of an array view and check if the resulting view
        has proper parameters.
        */
        void test_construction();

        //---------------------------------------------------------------------
        /*! 
        \brief test linear acces with []

        Test linear read/write access with the [] operator
        */
        void test_linear_access();

        //---------------------------------------------------------------------
        /*! 
        \brief test iterator access 

        Test read/write access with iterators
        */
        void test_iterator_access();

        //---------------------------------------------------------------------
        /*! 
        \brief testing multindex access

        Test multiindex data access.
        */
        void test_multiindex_access();

        //---------------------------------------------------------------------
        //! test assignment
        void test_assignment();
};

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::setUp() 
{ 
    _shape = shape_t{NX,NY};
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_construction()
{
   std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   ATYPE  a = array_factory<ATYPE>::create(_shape);

   //select a 2D array from the original 2D array
   auto v1 = a(Slice(0,3),Slice(3,7));
   CPPUNIT_ASSERT(v1.rank() == 2);
   CPPUNIT_ASSERT(v1.size() == 3*4);
   shape_t v1_shape{3,4};

   auto view_shape = v1.template shape<shape_t>();
   CPPUNIT_ASSERT(view_shape.size() == 2);
   CPPUNIT_ASSERT(std::equal(view_shape.begin(),view_shape.end(),
                             v1_shape.begin()));

   //select a 1D strip from the 2D array
   auto v2 = a(1,Slice(3,7));
   CPPUNIT_ASSERT(v2.rank() == 1);
   CPPUNIT_ASSERT(v2.size() == 4);
   shape_t v2_shape{4};

   view_shape = v2.template shape<shape_t>();
   CPPUNIT_ASSERT(view_shape.size() == 1);
   CPPUNIT_ASSERT(std::equal(view_shape.begin(),view_shape.end(),
                             v2_shape.begin()));                             
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_linear_access()
{ 
    typedef std::vector<typename ATYPE::value_type> ctype;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create an array and fill it with random data
    ATYPE  a = array_factory<ATYPE>::create(_shape);
    data_generator::fill(a.begin(),a.end(),
                         uniform_distribution<typename ATYPE::value_type>());

    //create a selection
    auto view = a(Slice(0,1),Slice(2,7));
    for(size_t i=0;i<view.size();++i)
        check_equality(view[i],a(0,2+i));

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_iterator_access()
{
    typedef std::vector<typename ATYPE::value_type> ctype;
    typedef uniform_distribution<typename ATYPE::value_type> udist_type;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    ATYPE a = array_factory<ATYPE>::create(shape_t{NX,NY});
    data_generator::fill(a.begin(),a.end(),udist_type());

    //create the view
    auto v = a(Slice(10,35,2),Slice(100,125,3));
    shape_t view_shape{13,9};
    CPPUNIT_ASSERT(v.size() == 13*9);
    CPPUNIT_ASSERT(v.rank() == 2);

    //check shape
    auto s = v.template shape<shape_t>();
    CPPUNIT_ASSERT(std::equal(view_shape.begin(),view_shape.end(),
                              s.begin()));

    //create data for the selection
    ctype data(v.size());
    data_generator::fill(data.begin(),data.end(),udist_type());

    //check write access == set a constant value to all selected views
    auto diter = data.begin();
    for(auto iter = v.begin();iter!=v.end();++iter)
        *iter = *diter++;

    //read data back by an iterator
    //now we have to check data access
    diter = data.begin();
    for(auto iter = v.begin();iter!=v.end();++iter)
        check_equality(*iter,*diter++);

    //check if the data has been transfered to the original array
    ArraySelection  selection(view_shape,shape_t{10,100},shape_t{2,3});
    index_iterator<shape_t> index_iter(view_shape,0);
    for(auto iter = data.begin();iter!=data.end();++iter)
        check_equality(*iter,a(selection.index(*index_iter++)));

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_assignment()
{
    typedef uniform_distribution<typename ATYPE::value_type> udist_type;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl; 
   
    //create initial frame and fill it with data
    ATYPE frame = array_factory<ATYPE>::create(_shape);
    data_generator::fill(frame.begin(),frame.end(),udist_type());

    //select roi
    auto roi = frame(Slice(1,10),Slice(0,100));
   
    //allocate new array for a roi - we have to use a DArray here as for a
    //static array we would have to know the shape of the array
    DArray<typename ATYPE::value_type> roia(roi);
    auto roi_s = roi.template shape<shape_t>();
    auto roia_s = roia.template shape<shape_t>();
    CPPUNIT_ASSERT(roia_s.size() == roi_s.size());
    CPPUNIT_ASSERT(std::equal(roia_s.begin(),roia_s.end(),roi_s.begin()));

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_multiindex_access()
{
    typedef uniform_distribution<typename ATYPE::value_type> udist_type;
    typedef std::vector<typename ATYPE::value_type> ctype;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create array 
    ATYPE a = array_factory<ATYPE>::create(_shape);
    data_generator::fill(a.begin(),a.end(),udist_type());

    auto view = a(1,Slice(0,100));
    ctype data(view.size());
    data_generator::fill(data.begin(),data.end(),udist_type());
    std::copy(data.begin(),data.end(),view.begin());
    auto diter = data.begin();
    for(size_t i=0;i<view.size();++i) check_equality(*diter++,view(i));

}

