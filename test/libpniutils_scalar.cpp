#include<iostream>

#include<cppunit/extensions/HelperMacros.h>

#include "Scalar.hpp"
#include "libpniutils_scalar.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ScalarTest);

void ScalarTest::setUp(){
    v1_i8 = -15; v2_i8 = 5;
    s1_i8 = new pni::utils::Int8Scalar(v1_i8);
    s2_i8 = new pni::utils::Int8Scalar(v2_i8);

    v1_ui8 = 15; v2_ui8 = 5;
    s1_ui8 = new pni::utils::UInt8Scalar(v1_ui8);
    s2_ui8 = new pni::utils::UInt8Scalar(v2_ui8);

    v1_i16 = -23; v2_i16 = 5012;
    v1_ui16 = 100; v2_ui16 = 16000;

    v1_i32 = -43000; v2_i32 = 100000;
    v1_ui32 = 30212; v2_ui32 = 100000;
    
    v1_i64 = 5000000000; v2_i64 = -500000;
    v1_ui64 = 6000000000; v2_ui64 = 500000;
    

}

void ScalarTest::tearDown(){
	if(s1_i8 != NULL) delete s1_i8;
	if(s2_i8 != NULL) delete s2_i8;
	if(s1_ui8 != NULL) delete s1_ui8;
	if(s2_ui8 != NULL) delete s2_ui8;
}

        
void ScalarTest::testConstructors(){
    //use the char values to check the constructors
    //since we have a template everything should work
    pni::utils::Int8Scalar s1(v1_i8,"data","");
    CPPUNIT_ASSERT(s1.getValue() == v1_i8);
    CPPUNIT_ASSERT(s1.getName() == "data");
    
    s1 = pni::utils::Int8Scalar(v1_i8,"data2","degree");
    CPPUNIT_ASSERT(s1.getValue() == v1_i8);
    CPPUNIT_ASSERT(s1.getName() == "data2");
    CPPUNIT_ASSERT(s1.getUnit() == "degree");
    
    s1 = pni::utils::Int8Scalar(v1_i8,"data3","degree","test data");
    CPPUNIT_ASSERT(s1.getValue() == v1_i8);
    CPPUNIT_ASSERT(s1.getName() == "data3");
    CPPUNIT_ASSERT(s1.getUnit() == "degree");
    CPPUNIT_ASSERT(s1.getDescription() == "test data");
    
}

void ScalarTest::testCharOperations(){
    pni::utils::Int8 result;
    
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
    pni::utils::UInt8 result;
    
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

