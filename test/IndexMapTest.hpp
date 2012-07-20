#ifndef __INDEXMAPTEST_HPP__
#define __INDEXMAPTEST_HPP__


#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "CIndexMap.hpp"

#include<vector>
#include<list>

using namespace pni::utils;


template<typename MTYPE>
class IndexMapTest:public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(IndexMapTest<MTYPE>);
        CPPUNIT_TEST(test_offset<std::vector<size_t> >);
        CPPUNIT_TEST(test_offset<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_offset<std::vector<int> >);
        CPPUNIT_TEST(test_offset<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_offset<std::list<size_t> >);
        CPPUNIT_TEST(test_offset<std::list<ssize_t> >);
        CPPUNIT_TEST(test_offset<std::list<int> >);
        CPPUNIT_TEST(test_offset<std::list<unsigned int> >);
        CPPUNIT_TEST(test_index<std::vector<size_t> >);
        CPPUNIT_TEST(test_index<std::vector<ssize_t> >);
        CPPUNIT_TEST(test_index<std::vector<int> >);
        CPPUNIT_TEST(test_index<std::vector<unsigned int> >);
        CPPUNIT_TEST(test_index<std::list<size_t> >);
        CPPUNIT_TEST(test_index<std::list<ssize_t> >);
        CPPUNIT_TEST(test_index<std::list<int> >);
        CPPUNIT_TEST(test_index<std::list<unsigned int> >);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp(){}
        void tearDown() {}
    
        template<typename CTYPE> void test_offset();
        template<typename CTYPE> void test_index();
};


template<typename MTYPE> 
template<typename CTYPE> void IndexMapTest<MTYPE>::test_offset()
{
    std::cout<<"IndexMaptest::test_offset()..........................";
    std::cout<<std::endl;

    MTYPE map{2,3};
    CPPUNIT_ASSERT(map.offset(1,2)==5);
    CPPUNIT_ASSERT(map.offset(CTYPE{1,2}) == 5);

    map = MTYPE{5,4};
    CPPUNIT_ASSERT(map.offset(1,2) == 6);
    CPPUNIT_ASSERT(map.offset(CTYPE{1,2}) == 6);

}

template<typename MTYPE> 
template<typename CTYPE> void IndexMapTest<MTYPE>::test_index()
{
    std::cout<<"IndexMaptest::test_index()...........................";
    std::cout<<std::endl;
   
    MTYPE map{2,3};
    auto i = map.template index<CTYPE>(5);

    CTYPE ic{1,2};
    CPPUNIT_ASSERT(std::equal(ic.begin(),ic.end(),i.begin()));

}
#endif
