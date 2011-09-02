#include<iostream>

#include<cppunit/extensions/HelperMacros.h>

#include "Scalar.hpp"
#include "ScalarTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ScalarTest);

void ScalarTest::setUp(){
    

}

void ScalarTest::tearDown(){

}

void ScalarTest::testConversion(){
	Int32Scalar a(12);
	Float64Scalar b;

	b = a;

	CPPUNIT_ASSERT(b == 12.0);
	UInt8Scalar u;

	CPPUNIT_ASSERT_THROW(u = b,TypeError);
	Float64Scalar c;
	c = b;
}

        
void ScalarTest::testConstructors(){
    
    
}

void ScalarTest::testCharOperations(){
    Int8 result;
    
    //check division operator
    result = v1_i8/v2_i8;
    CPPUNIT_ASSERT(((*s1_i8)/(*s2_i8)) == result);
    CPPUNIT_ASSERT(((*s1_i8)/v2_i8) == result);
    CPPUNIT_ASSERT((v1_i8/(*s2_i8)) == result);
    
    //check addition operator
    result = v1_i8 + v2_i8;
    CPPUNIT_ASSERT(((*s1_i8)+(*s2_i8)) == result);
    CPPUNIT_ASSERT(((*s1_i8)+v2_i8) == result);
    CPPUNIT_ASSERT((v1_i8 + (*s2_i8)) == result);
    
    //check multiplication operator
    result = v1_i8 * v2_i8;
    CPPUNIT_ASSERT(((*s1_i8)*(*s2_i8)) == result);
    CPPUNIT_ASSERT(((*s1_i8)*v2_i8) == result);
    CPPUNIT_ASSERT((v1_i8*(*s2_i8)) == result);
    
    //check the subtraction operator
    result = v1_i8 - v2_i8;
    CPPUNIT_ASSERT(((*s1_i8)-(*s2_i8)) == result);
    CPPUNIT_ASSERT(((*s1_i8)-v2_i8) == result);
    CPPUNIT_ASSERT((v1_i8-(*s2_i8)) == result);


}

void ScalarTest::testUCharOperations(){
    UInt8 result;
    
    //check division operator
    result = v1_ui8/v2_ui8;
    CPPUNIT_ASSERT(((*s1_ui8)/(*s2_ui8)) == result);
    CPPUNIT_ASSERT(((*s1_ui8)/v2_ui8) == result);
    CPPUNIT_ASSERT((v1_ui8/(*s2_ui8)) == result);
    
    //check addition operator
    result = v1_ui8 + v2_ui8;
    CPPUNIT_ASSERT(((*s1_ui8)+(*s2_ui8)) == result);
    CPPUNIT_ASSERT(((*s1_ui8)+v2_ui8) == result);
    CPPUNIT_ASSERT((v1_ui8 + (*s2_ui8)) == result);
    
    //check multiplication operator
    result = v1_ui8 * v2_ui8;
    CPPUNIT_ASSERT(((*s1_ui8)*(*s2_ui8)) == result);
    CPPUNIT_ASSERT(((*s1_ui8)*v2_ui8) == result);
    CPPUNIT_ASSERT((v1_ui8*(*s2_ui8)) == result);
    
    //check the subtraction operator
    result = v1_ui8 - v2_ui8;
    CPPUNIT_ASSERT(((*s1_ui8)-(*s2_ui8)) == result);
    CPPUNIT_ASSERT(((*s1_ui8)-v2_ui8) == result);
    CPPUNIT_ASSERT((v1_ui8-(*s2_ui8)) == result);
    

}

