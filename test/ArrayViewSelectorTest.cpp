#include<cppunit/extensions/HelperMacros.h>

#include <typeinfo>
#include "Types.hpp"
#include "Slice.hpp"
#include "NumArray.hpp"
#include "SArray.hpp"
#include "ArrayViewSelectorTest.hpp"
#include "ArrayView.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayViewSelectorTest);

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

    CPPUNIT_ASSERT(typeid(ArrayViewSelector<narray_type,Slice,size_t,Slice,size_t>::viewtype).name()
                   == typeid(ArrayView<narray_type>).name());

}

