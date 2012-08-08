//test case for the IndexMapBase base class

#ifndef __SUBOPERATORTEST_HPP__
#define __SUBOPERATORTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>

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
template<typename T> class SubOperatorTest: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(SubOperatorTest<T>);
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
        typedef std::vector<size_t> shape_t;


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

template<typename T> void SubOperatorTest<T>::setUp()
{
    shape = shape_t(3);
    shape[0] = 2; shape[1] = 3; shape[2] = 4;
    a1 = na_type(shape);
    a2 = na_type(shape);
    
    std::fill(a1.begin(),a1.end(),T(100));
    std::fill(a2.begin(),a2.end(),T(5));
}

template<typename T> void SubOperatorTest<T>::tearDown()
{
    
}

template<typename T> void SubOperatorTest<T>::test_construction()
{
    Sub<na_type,na_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    s_type s(10);
    Sub<na_type,s_type> op2(a1,s);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    Sub<s_type,s_type> op3(s,s);
    CPPUNIT_ASSERT(s.size() == op3.size());

}

template<typename T> void SubOperatorTest<T>::test_access()
{
    Sub<na_type,na_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++)
        check_equality(op1[i],T(95));

    s_type s(10);
    Sub<na_type,s_type> op2(a1,s);

    for(size_t i=0;i<op2.size();i++)
        check_equality(op2[i],T(90));
}

template<typename T> void SubOperatorTest<T>::test_iterator()
{
    Sub<na_type,na_type> op1(a1,a2);
#ifdef NOFOREACH
    for(auto iter = op1.begin();iter!=op1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op1) 
    {
#endif 
        check_equality(v,T(95));
    }

    s_type s(10);
    Sub<na_type,s_type> op2(a1,s);
#ifdef NOFOREACH
    for(auto iter = op2.begin();iter!=op2.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op2) 
    {
#endif
        check_equality(v,T(90));
    }
}

template<typename T> void SubOperatorTest<T>::test_operator()
{
    na_type r = atype(shape);
    r = a1-a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(95));
    }

    r = a1-10;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(90));
    }

    r = 110 - a1;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(10));
    }

    //put it all together

    r = 110 - a1 - a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,T(5));
    }

}
#endif
