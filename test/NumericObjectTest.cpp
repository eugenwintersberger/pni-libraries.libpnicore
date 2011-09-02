/*
 * NumericObjectTest.cpp
 *
 *  Created on: Sep 2, 2011
 *      Author: eugen
 */

#include<cppunit/extensions/HelperMacros.h>
#include "NumericObjectTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(NumericObjectTest);

void NumericObjectTest::setUp(){

}

void NumericObjectTest::tearDown(){

}

void NumericObjectTest::testCreation(){
	NumericObject o;

	//checking the setting routine
	o.setName("object");
	o.setDescription("new object");
	o.setUnit("nm");

	CPPUNIT_ASSERT(o.getName() == "object");
	CPPUNIT_ASSERT(o.getDescription() == "new object");
	CPPUNIT_ASSERT(o.getUnit() == "nm");

	//check constructors
	NumericObject o1("object2","m");
	CPPUNIT_ASSERT(o1.getName() == "object2");
	CPPUNIT_ASSERT(o1.getUnit() == "m");

	NumericObject o2("object3","um","the last object");
	CPPUNIT_ASSERT(o2.getName() == "object3");
	CPPUNIT_ASSERT(o2.getDescription() == "the last object");
	CPPUNIT_ASSERT(o2.getUnit() == "um");

	NumericObject o3("object4");
	CPPUNIT_ASSERT(o3.getUnit() == "object4");

}

void NumericObjectTest::testAssignment(){
	NumericObject o("object","nm","testing data");

	NumericObject o1;
	o1 = o;
	CPPUNIT_ASSERT(o1.getName() == o.getName());
	CPPUNIT_ASSERT(o1.getDescription() == o.getDescription());
	CPPUNIT_ASSERT(o1.getUnit() == o.getUnit());
}



