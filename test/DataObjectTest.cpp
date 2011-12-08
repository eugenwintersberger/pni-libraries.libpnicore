/*
 * DataObjectTest.cpp
 *
 *  Created on: Sep 2, 2011
 *      Author: eugen
 */

#include<cppunit/extensions/HelperMacros.h>
#include "DataObjectTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(DataObjectTest);

void DataObjectTest::setUp(){

}

void DataObjectTest::tearDown(){

}

void DataObjectTest::testCreation(){
	DataObject o("test","a testing object");

	CPPUNIT_ASSERT(o.name()=="test");
	CPPUNIT_ASSERT(o.description()=="a testing object");

	DataObject o2;

	o2.name("test2");
	o2.description("another description");

	CPPUNIT_ASSERT(o2.name()=="test2");
	CPPUNIT_ASSERT(o2.description()=="another description");

	DataObject o3("test3");
	CPPUNIT_ASSERT(o3.name() == "test3");
	o3.description("test description");
	CPPUNIT_ASSERT(o3.description() == "test description");
}

void DataObjectTest::testAssignment(){
	DataObject o("o1","a stupid object");

	DataObject b;

	b = o;

	CPPUNIT_ASSERT(b.name() == o.name());
	CPPUNIT_ASSERT(b.description() == o.description());


}



