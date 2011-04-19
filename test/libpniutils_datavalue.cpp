#include<iostream>

#include<cppunit/extensions/HelperMacros.h>

#include "libpniutils_datavalue.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(DataValueTest);

void DataValueTest::testConstructors(){
    DataValue d = DataValue();
    CPPUNIT_ASSERT(d.getName() == DEFAULT_VALUE_NAME);
    CPPUNIT_ASSERT(d.getUnit() == DEFAULT_VALUE_UNIT);
    CPPUNIT_ASSERT(d.getDescription() == DEFAULT_VALUE_DESCRIPTION);
    
    d = DataValue("motor");
    CPPUNIT_ASSERT(d.getName() == "motor");
    
    d = DataValue("motor2","mm");
    CPPUNIT_ASSERT(d.getName() == "motor2");
    CPPUNIT_ASSERT(d.getUnit() == "mm");
    
    d = DataValue("motor3","degree","a simple motor");
    CPPUNIT_ASSERT(d.getName() == "motor3");
    CPPUNIT_ASSERT(d.getUnit() == "degree");
    CPPUNIT_ASSERT(d.getDescription() == "a simple motor");
}
void DataValueTest::testSetAndGet(){
    v1->setName("motor");
    CPPUNIT_ASSERT(v1->getName() == "motor");
    v1->setUnit("mm");
    CPPUNIT_ASSERT(v1->getUnit() == "mm");
    v1->setDescription("a motor");
    CPPUNIT_ASSERT(v1->getDescription() == "a motor");
}
