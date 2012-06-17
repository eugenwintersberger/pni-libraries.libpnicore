#include "SizeTypeTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(SizeTypeTest);

void SizeTypeTest::test_size()
{
    size_t s = SizeType<100>::size;
    CPPUNIT_ASSERT(s == 100);
    s = SizeType<100,2,4>::size;
    CPPUNIT_ASSERT(s == 800);
}
