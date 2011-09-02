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

	CPPUNIT_ASSERT(o.getName()=="test");
	CPPUNIT_ASSERT(o.getDescription()=="a testing object");

	DataObject o2;

	o2.setName("test2");
	o2.setDescription("another description");

	CPPUNIT_ASSERT(o2.getName()=="test2");
	CPPUNIT_ASSERT(o2.getDescription()=="another description");

	DataObject o3("test3");
	CPPUNIT_ASSERT(o3.getName() == "test3");
	o3.setDescription("test description");
	CPPUNIT_ASSERT(o3.getDescription() == "test description");
}

void DataObjectTest::testAssignment(){
	DataObject o("o1","a stupid object");

	DataObject b;

	b = o;

	CPPUNIT_ASSERT(b.getName() == o.getName());
	CPPUNIT_ASSERT(b.getDescription() == o.getDescription());


}



