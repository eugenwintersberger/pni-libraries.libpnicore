#include "StrideTypeTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(StrideTypeTest);


void StrideTypeTest::test_computation()
{
    typedef Stride<1,2,3> comp1;

    //std::cout<<"stride value: "<<comp1::value<<std::endl;
    CPPUNIT_ASSERT(comp1::value == 1);


    typedef Stride<0,4,5,6> comp2;
    //std::cout<<"stride value: "<<comp2::value<<std::endl;
    CPPUNIT_ASSERT(comp2::value == 30);

    typedef Stride<3,5,7,1,3,9> comp3;
    CPPUNIT_ASSERT(comp3::value == 9);

}

void StrideTypeTest::test_calc()
{
    typedef StrideCalc<5,7,1,3,9> calc;

    size_t stride = calc::value<0>();
    CPPUNIT_ASSERT(stride == (7*9*3));
    stride = calc::value<1>();
    CPPUNIT_ASSERT(stride == (3*9));
    stride = calc::value<2>();
    CPPUNIT_ASSERT(stride == (3*9));
    stride = calc::value<3>();
    CPPUNIT_ASSERT(stride == 9);
    stride = calc::value<4>();
    CPPUNIT_ASSERT(stride == 1);

}

