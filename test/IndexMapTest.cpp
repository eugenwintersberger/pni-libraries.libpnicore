
#include<cppunit/extensions/HelperMacros.h>


#include "Buffer.hpp"
#include "IndexMapTest.hpp"
CPPUNIT_TEST_SUITE_REGISTRATION(IndexMapTest);

using namespace pni::utils;


void IndexMapTest::test_offset()
{
    std::cout<<"IndexMaptest::test_offset()..........................";
    std::cout<<std::endl;
    Shape s{2,3};
    IndexMap imap(s,{0,0},{1,1});

    CPPUNIT_ASSERT(imap.offset(1,2)==5);

    s = {5,4};
    IndexMap imap1(s,{0,0},{2,3});

    std::cout<<imap1.offset(1,2)<<std::endl;
    CPPUNIT_ASSERT(imap1.offset(1,2) == 30);

    

}

void IndexMapTest::test_index()
{
    std::cout<<"IndexMaptest::test_index()...........................";
    std::cout<<std::endl;

    Shape s{2,3};
    IndexMap imap(s,{0,0},{1,1});

    auto i = imap.index<std::vector<size_t> >(5);
    CPPUNIT_ASSERT(i[0] == 1);
    CPPUNIT_ASSERT(i[1] == 2);

}
