#include<iostream>

#include<cppunit/extensions/HelperMacros.h>

#include "scalar.hpp"
#include "libpniutils_scalar.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ScalarTest);

void ScalarTest::setUp(){
    v1_char = -15;
    v2_char = 5;
    s1_char = new CharScalar(v1_char);
    s2_char = new CharScalar(v2_char);
    
    v1_uchar = 15;
    v2_uchar = 5;
    s1_uchar = new UCharScalar(v1_uchar);
    s2_uchar = new UCharScalar(v2_uchar);
    
    v1_short = -23;
    v1_ushort = 100;
    v1_int = -43000;
    v1_uint = 30212;
    v1_long = 5000000000;
    v1_ulong = 6000000000;
    v1_float = 34.567;
    v1_double = 49.0498;
    v1_string = "hello world";
    v2_string = "this is a test";
    
    s1_string = new StringScalar(v1_string);
    s2_string = new StringScalar(v2_string);
}

void ScalarTest::tearDown(){
    delete s1_char;
    delete s2_char;
    
    delete s1_uchar;
    delete s2_uchar;
    
    delete s1_string;
    delete s2_string;
}

        
void ScalarTest::testConstructors(){
    //use the char values to check the constructors
    //since we have a template everything should work
    CharScalar s1(v1_char,"data");
    CPPUNIT_ASSERT(s1.getValue() == v1_char);
    s1 = CharScalar(v1_char,"data");
    CPPUNIT_ASSERT(s1.getValue() == v1_char);
    CPPUNIT_ASSERT(s1.getName() == "data");
    
    s1 = CharScalar(v1_char,"data","degree");
    CPPUNIT_ASSERT(s1.getValue() == v1_char);
    CPPUNIT_ASSERT(s1.getName() == "data");
    CPPUNIT_ASSERT(s1.getUnit() == "degree");
    
    s1 = CharScalar(v1_char,"data","degree","test data");
    CPPUNIT_ASSERT(s1.getValue() == v1_char);
    CPPUNIT_ASSERT(s1.getName() == "data");
    CPPUNIT_ASSERT(s1.getUnit() == "degree");
    CPPUNIT_ASSERT(s1.getDescription() == "test data");
    
    StringScalar s2("hello world");
    CPPUNIT_ASSERT(s2.getValue() == "hello world");
    s2 = StringScalar("1","text");
    CPPUNIT_ASSERT(s2.getValue() == "1");
    CPPUNIT_ASSERT(s2.getName() == "text");
}

void ScalarTest::testCharOperations(){
    char result;
    
    //check division operator
    result = v1_char/v2_char;
    CPPUNIT_ASSERT(((*s1_char)/(*s2_char)) == result);
    CPPUNIT_ASSERT(((*s1_char)/v2_char) == result);
    CPPUNIT_ASSERT((v1_char/(*s2_char)) == result);
    
    //check addition operator
    result = v1_char + v2_char;
    CPPUNIT_ASSERT(((*s1_char)+(*s2_char)) == result);
    CPPUNIT_ASSERT(((*s1_char)+v2_char) == result);
    CPPUNIT_ASSERT((v1_char + (*s2_char)) == result);
    
    //check multiplication operator
    result = v1_char * v2_char;
    CPPUNIT_ASSERT(((*s1_char)*(*s2_char)) == result);
    CPPUNIT_ASSERT(((*s1_char)*v2_char) == result);
    CPPUNIT_ASSERT((v1_char*(*s2_char)) == result);
    
    //check the subtraction operator
    result = v1_char - v2_char;
    CPPUNIT_ASSERT(((*s1_char)-(*s2_char)) == result);
    CPPUNIT_ASSERT(((*s1_char)-v2_char) == result);
    CPPUNIT_ASSERT((v1_char-(*s2_char)) == result);


}

void ScalarTest::testUCharOperations(){
    unsigned char result;
    
    //check division operator
    result = v1_uchar/v2_uchar;
    CPPUNIT_ASSERT(((*s1_uchar)/(*s2_uchar)) == result);
    CPPUNIT_ASSERT(((*s1_uchar)/v2_uchar) == result);
    CPPUNIT_ASSERT((v1_uchar/(*s2_uchar)) == result);
    
    //check addition operator
    result = v1_uchar + v2_uchar;
    CPPUNIT_ASSERT(((*s1_uchar)+(*s2_uchar)) == result);
    CPPUNIT_ASSERT(((*s1_uchar)+v2_uchar) == result);
    CPPUNIT_ASSERT((v1_uchar + (*s2_uchar)) == result);
    
    //check multiplication operator
    result = v1_uchar * v2_uchar;
    CPPUNIT_ASSERT(((*s1_uchar)*(*s2_uchar)) == result);
    CPPUNIT_ASSERT(((*s1_uchar)*v2_uchar) == result);
    CPPUNIT_ASSERT((v1_uchar*(*s2_uchar)) == result);
    
    //check the subtraction operator
    result = v1_uchar - v2_uchar;
    CPPUNIT_ASSERT(((*s1_uchar)-(*s2_uchar)) == result);
    CPPUNIT_ASSERT(((*s1_uchar)-v2_uchar) == result);
    CPPUNIT_ASSERT((v1_uchar-(*s2_uchar)) == result);
    

}

void ScalarTest::testStringOperations(){
    String result;
    
    result = v1_string + v2_string;
    CPPUNIT_ASSERT(((*s1_string)+(*s2_string))==result);    
    CPPUNIT_ASSERT((v1_string+(*s2_string)) == result);
    CPPUNIT_ASSERT(((*s1_string)+v2_string) == result);
    
    //all other operators make no sense for strings and will 
    //in any case stop the compiler run    
}
