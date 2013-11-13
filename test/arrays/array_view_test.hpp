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
#include <pni/core/array_view.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/index_iterator.hpp>
#include "../data_generator.hpp"
#include "../compare.hpp"

using namespace pni::core;

#define NX 100
#define NY 125


template<typename ATYPE> class array_view_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(array_view_test<ATYPE>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_construction_from_array);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterator_access);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST_SUITE_END();

        typedef array_view<ATYPE> view_type;
        typedef ATYPE array_type;
        typedef typename ATYPE::value_type value_type;
        typedef typename std::vector<slice> slice_container;
        typedef typename ATYPE::map_type map_type;
    private:
        shape_t s1,s2;
        size_t r1,r2;
        shape_t _shape;
        ATYPE array;

        template<typename VTYPE>
        void check_view(const VTYPE &view,const shape_t &ref)
        {
            size_t ref_size = std::accumulate(ref.begin(),ref.end(),1,
                    std::multiplies<size_t>());
            size_t ref_rank = ref.size();

            CPPUNIT_ASSERT(view.rank() == ref_rank);
            CPPUNIT_ASSERT(view.size() == ref_size);

            auto shape = view.template shape<shape_t>();
            CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),ref.begin()));

        }
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
        \brief test construction from an array

        Test the construction of a view from an array. 
        */
        void test_construction_from_array();

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
    _shape = shape_t({NX,NY});
   array = array_factory<ATYPE>::create(_shape);
   std::generate(array.begin(),array.end(),random_generator<value_type>());
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::tearDown() { }

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_construction()
{
   std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

   //select a 2D array from the original 2D array
   view_type v1(array,
                array_selection::create(slice_container{slice(0,3),slice(3,7)}));
   check_view(v1,shape_t{3,4});

   //select a 1D strip from the 2D array
   view_type v2(array,array_selection::create(slice_container{1,slice(3,7)}));
   check_view(v2,shape_t{4});
}

//-----------------------------------------------------------------------------
template<typename ATYPE> 
void array_view_test<ATYPE>::test_construction_from_array()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    slice_container selection{slice(0,3),slice(3,7)};
    shape_t view_shape{3,4};

    view_type v = array(selection);
    check_view(v,view_shape);
    
    //check construction from a const array
    const array_type &carray = array;
    auto v2 = carray(selection);
    check_view(v2,view_shape);
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_linear_access()
{ 
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create a selection
    view_type view(array,
                   array_selection::create(slice_container{slice(0,1),slice(2,7)}));
    check_view(view,shape_t{5});

    for(size_t i=0;i<view.size();++i) 
    {
        value_type v1 = array(0,2+i);
        value_type v2 = view[i];
        compare(view[i],array(0,2+i));
    }

    //-----------------check for front-----------------------------------------
    value_type v = array.front();
    CPPUNIT_ASSERT_NO_THROW(view.front() = v);
    compare(view.front(),v);

    //-----------------check for back------------------------------------------
    CPPUNIT_ASSERT_NO_THROW(view.back()=v);
    compare(view.back(),v);

}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_iterator_access()
{
    typedef std::vector<value_type> ctype;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //create the view
    view_type v(array,
                array_selection::create(slice_container{slice(10,35,2),slice(100,125,3)}));
    check_view(v,shape_t{13,9});

    //create data for the selection
    ctype data(v.size());
    std::generate(data.begin(),data.end(),random_generator<value_type>());

    //---------------------check write access----------------------------------
    auto diter = data.begin();

    for(auto iter = v.begin();iter!=v.end();++iter,++diter)
        *iter = *diter;

    //----------------------check read access----------------------------------
    diter = data.begin();
    for(auto iter = v.begin();iter!=v.end();++iter,++diter)
        compare(*iter,*diter);

    //-----now we need to check if the data arrived at the original array------
    array_selection  selection(shape_t{13,9},shape_t{10,100},shape_t{2,3});
    index_iterator<shape_t,map_type> index_iter(shape_t{13,9},0);
    for(auto iter = data.begin();iter!=data.end();++iter)
    {
        auto index = selection.template index<shape_t>(*index_iter++);
        value_type v1 = *iter;
        value_type v2 = array(index);
        compare(v1,v2);
    }
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl; 

    //select roi
    /*
    view_type roi(array,
                  array_selection::create(slice_container{slice(1,10),slice(0,100)}));
                  */
   
    //allocate new array for a roi - we have to use a DArray here as for a
    //static array we would have to know the shape of the array
    /*
    darray<typename ATYPE::value_type> roia(roi);
    auto roi_s = roi.template shape<shape_t>();
    auto roia_s = roia.template shape<shape_t>();
    CPPUNIT_ASSERT(roia_s.size() == roi_s.size());
    CPPUNIT_ASSERT(std::equal(roia_s.begin(),roia_s.end(),roi_s.begin()));
    */
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void array_view_test<ATYPE>::test_multiindex_access()
{
    typedef std::vector<value_type> ctype;
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
     
    slice_container slices{slice(10,40),slice(0,100)};
    view_type view(array,array_selection::create(slices));
    check_view(view,shape_t{30,100});
    auto shape = view.template shape<shape_t>();

    ctype data(view.size());
    std::generate(data.begin(),data.end(),random_generator<value_type>());
    //-----------------writing data----------------------------
    auto diter = data.begin();
    for(size_t i=0;i<shape[0];++i)
        for(size_t j=0;j<shape[1];++j)
        {
            //std::cout<<i<<" "<<j<<std::endl;
            value_type v = *diter++;
            view(i,j) = v;
        }

    //----------------reading data-----------------------------
    diter = data.begin();
    for(size_t i=0;i<shape[0];++i)
        for(size_t j=0;j<shape[1];++j)
            compare(view(i,j),*diter++);
}

