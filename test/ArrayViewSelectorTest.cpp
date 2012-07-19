#include<cppunit/extensions/HelperMacros.h>

#include <typeinfo>
#include "Types.hpp"
#include "Slice.hpp"
#include "SArray.hpp"
#include "ArrayViewSelectorTest.hpp"
#include "ArrayView.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayViewSelectorTest);

void ArrayViewSelectorTest::test_selector()
{
    typedef SArray<Float64,3,4,5,6> array_type;
    typedef ArrayViewSelector<array_type,size_t,size_t,size_t> scalar_view;
    typedef ArrayViewSelector<array_type,size_t,size_t,Slice,size_t> array_view;

    CPPUNIT_ASSERT(typeid(scalar_view::viewtype).name()==
                   typeid(Float64).name());

    CPPUNIT_ASSERT(typeid(array_view::viewtype).name() == 
                   typeid(ArrayView<array_type>).name());

}

