//test fixture for the DataValue class

#ifndef __LIBDDFDATA_DATAVALUE_HPP__
#define __LIBDDFDATA_DATAVALUE_HPP__

#include<cppunit/TestFixture.h>


#include "datavalue.hpp"

class DataValueTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(DataValueTest);
    CPPUNIT_TEST(testConstructors);
    CPPUNIT_TEST(testSetAndGet);
    CPPUNIT_TEST_SUITE_END();
    private:
        DataValue *v1;
        DataValue *v2;
    public:
        
        void setUp(){
            v1 = new DataValue();
        }
        
        void tearDown(){
            delete v1;
        }
        
        void testConstructors();
        void testSetAndGet();
        
        
    
};



#endif
