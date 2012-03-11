
#include<cppunit/extensions/HelperMacros.h>


#include "Buffer.hpp"
#include "IndexMapTest.hpp"
CPPUNIT_TEST_SUITE_REGISTRATION(IndexMapTest);

using namespace pni::utils;


void IndexMapTest::test_offset()
{
    std::cout<<"IndexMaptest::test_offset()..........................";
    std::cout<<std::endl;
    IndexMap imap({0,0},{1,1},{2,3});

    CPPUNIT_ASSERT(imap.offset(1,2)==5);

    IndexMap imap1({0,0},{2,3},{5,4});

    std::cout<<imap1.offset(1,2)<<std::endl;
    CPPUNIT_ASSERT(imap1.offset(1,2) == 30);

    

}
