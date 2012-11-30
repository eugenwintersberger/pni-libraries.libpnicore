//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/utils/Slice.hpp>

using namespace pni::utils;

class SliceTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(SliceTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_functions);
        CPPUNIT_TEST_SUITE_END();
    private:
        void _construct(size_t start,size_t stop);
        void _construct(size_t start,size_t stop,size_t stride);
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
        void test_functions();
};
