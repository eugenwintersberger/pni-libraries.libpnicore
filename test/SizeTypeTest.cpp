#include "SizeTypeTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(SizeTypeTest);

void SizeTypeTest::test_size()
{
    CPPUNIT_ASSERT(SizeType<100>::size == 100);

    CPPUNIT_ASSERT(SizeType<100,2,4>::size == 800);
}
