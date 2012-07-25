//test case for the IndexMapBase base class

#ifndef __ADDOPERATORTEST_HPP__
#define __ADDOPERATORTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>
#include "expr/Add.hpp"

#include "EqualityCheck.hpp"
#include "NumArray.hpp"
#include "DArray.hpp"
#include "Scalar.hpp"
#include <algorithm>

using namespace pni::utils;

/*!
 Do testing only for DArray - all array types provide the same interface and
 thus can be considered as equivalent. However, we have to check ArrayView
 wether or not it works.
 */
template<typename T> class AddOperatorTest: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(AddOperatorTest<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST(test_operator);
        CPPUNIT_TEST_SUITE_END();
    private:
        //==========private types==============================================
        typedef DArray<T> atype;
        typedef NumArray<atype> na_type;
        typedef Scalar<T> s_type;


        //===================private memebers==================================
        na_type a1;
        na_type a2;
        std::vector<size_t> shape;

    public:
        void setUp();
        void tearDown();
        
        void test_construction();
        void test_access();
        void test_iterator();
        void test_operator();

};

template<typename T> void AddOperatorTest<T>::setUp()
{
    shape = std::vector<size_t>{2,3,4};
    a1 = NumArray<atype>(atype(shape));
    a2 = NumArray<atype>(atype(shape));
    
    std::fill(a1.begin(),a1.end(),T(100));
    std::fill(a2.begin(),a2.end(),T(5));
}

template<typename T> void AddOperatorTest<T>::tearDown()
{
    
}

template<typename T> void AddOperatorTest<T>::test_construction()
{
    Add<na_type,na_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    s_type s = 10;
    Add<na_type,s_type> op2(a1,s);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    Add<s_type,s_type> op3(s,s);
    CPPUNIT_ASSERT(s.size() == op3.size());

}

template<typename T> void AddOperatorTest<T>::test_access()
{
    Add<na_type,na_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++)
        check_equality(op1[i],T(105));

    s_type s = 10;
    Add<na_type,s_type> op2(a1,s);

    for(size_t i=0;i<op2.size();i++)
        check_equality(op2[i],T(110));
}

template<typename T> void AddOperatorTest<T>::test_iterator()
{
    Add<na_type,na_type> op1(a1,a2);
    for(auto v: op1) check_equality(v,T(105));

    s_type s = 10;
    Add<na_type,s_type> op2(a1,s);
    for(auto v: op2) check_equality(v,T(110));
}

template<typename T> void AddOperatorTest<T>::test_operator()
{
    na_type r = atype(shape);
    r = a1+a2;
    for(auto v: r) check_equality(v,T(105));

    r = a1+10;
    for(auto v: r) check_equality(v,T(110));

    r = 95 + a1;
    for(auto v: r) check_equality(v,T(195));

    //put it all together

    r = a1 + 10 + a2;
    for(auto v: r) check_equality(v,T(115));

}
#endif
