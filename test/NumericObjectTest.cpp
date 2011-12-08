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
	o.name("object");
	o.description("new object");
	o.unit("nm");

	CPPUNIT_ASSERT(o.name() == "object");
	CPPUNIT_ASSERT(o.description() == "new object");
	CPPUNIT_ASSERT(o.unit() == "nm");

	//check constructors
	NumericObject o1("object2","m");
	CPPUNIT_ASSERT(o1.name() == "object2");
	CPPUNIT_ASSERT(o1.unit() == "m");

	NumericObject o2("object3","um","the last object");
	CPPUNIT_ASSERT(o2.name() == "object3");
	CPPUNIT_ASSERT(o2.description() == "the last object");
	CPPUNIT_ASSERT(o2.unit() == "um");


}

void NumericObjectTest::testAssignment(){
	NumericObject o("object","nm","testing data");

	NumericObject o1;
	o1 = o;
	CPPUNIT_ASSERT(o1.name() == o.name());
	CPPUNIT_ASSERT(o1.description() == o.description());
	CPPUNIT_ASSERT(o1.unit() == o.unit());
}



