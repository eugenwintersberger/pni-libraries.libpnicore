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
	//test here the functionality of the conversion operator
	UInt8Scalar sui8;
	UInt8 ui8;
	Float64 f64;

	sui8 = (UInt8)10;

	CPPUNIT_ASSERT_NO_THROW(ui8  = sui8);
	CPPUNIT_ASSERT(ui8 == 10);
	CPPUNIT_ASSERT_NO_THROW(f64 = sui8);
	CPPUNIT_ASSERT(f64 = 10.);

}

        
void ScalarTest::testConstructors(){
    
    
}

void ScalarTest::testSetGetValue(){

}

void ScalarTest::testAssignment(){
	//we test here the assignment operator for
	//functionality
	UInt8Scalar sui8;
	UInt64Scalar sui64;
	Int64Scalar si64;
	Float64Scalar sf64;
	Float64Scalar sf64_2;
	Complex128Scalar sc128;
	UInt8 ui8 = 10;
	Float64 f64 = -1000.30189;
	Complex128 c128(1.,-2.);


	//start here with the assignment of native variables
	//to a Scalar<T> object.

	//this should call the native assignment operator
	//for Float64 scalar objects - this seems to work.
	CPPUNIT_ASSERT_NO_THROW(sf64 = f64);
	//this should call the template operator with the
	//type checking
	CPPUNIT_ASSERT_NO_THROW(sf64 = ui8);

	//should throw an error since we cannot assign a float
	//value to an integer
	CPPUNIT_ASSERT_THROW(sui8 = f64,TypeError);
	si64 = -10000;
	//should throw an exception since we try to assign
	//a negative value to a type that does not support signed values
	CPPUNIT_ASSERT_THROW(sui64 = si64,TypeError);
	//should throw an exception since the target type is smaller
	//than the source type.
	CPPUNIT_ASSERT_THROW(sui8 = si64,TypeError);

	//need here some tests for complex numbers - they need some special handling
	CPPUNIT_ASSERT_NO_THROW(sc128 = c128);
	//for this we would allready get an compile time error.
	//CPPUNIT_ASSERT_THROW(sf64 = c128,TypeError);
	//should work
	CPPUNIT_ASSERT_NO_THROW(sc128 = f64);


	//check now the assignment between objects of type
	//Scalar<T>
	CPPUNIT_ASSERT_NO_THROW(sf64 = 14658789.78984);
	//should call the native assignment operator
	CPPUNIT_ASSERT_NO_THROW(sf64_2 = sf64);
	CPPUNIT_ASSERT_NO_THROW(sui8 = (UInt8)100);
	CPPUNIT_ASSERT_NO_THROW(sf64 = sui8);
	si64 = -10000;
	//cannot work because of different size
	CPPUNIT_ASSERT_THROW(sui8 = si64,TypeError);
	//cannot work due to sign
	CPPUNIT_ASSERT_THROW(sui64 = si64,TypeError);
	//cannot work due to float to integer conversion
	CPPUNIT_ASSERT_THROW(si64 = sf64,TypeError);
}

void ScalarTest::testBinaryAddOperation(){
	Float64Scalar a,b,c;
	Int64Scalar ci,ai,bi;
	Float64 av = 1.,bv = -45.2390;

	a = av;
	ai = 1;
	b = bv;
	CPPUNIT_ASSERT_NO_THROW(c = a+b);
	CPPUNIT_ASSERT(c == av+bv);
	std::cout<<"add two floats to an integer!"<<std::endl;
	ai = 100;
	bi = -20;
	CPPUNIT_ASSERT_NO_THROW(ci = ai+bi);


}

void ScalarTest::testUnaryAddOperation(){
	Float64Scalar saf64,sbf64;
	Float64 af64,bf64;
	UInt8Scalar sui8;

	saf64 = 0.;
	sbf64 = 100.;
	CPPUNIT_ASSERT_NO_THROW(saf64 += sbf64);
	CPPUNIT_ASSERT(saf64 == sbf64);
	saf64 = 0;
	bf64 = -20;
	CPPUNIT_ASSERT_NO_THROW(saf64 += bf64);
	CPPUNIT_ASSERT(saf64 == bf64);

	CPPUNIT_ASSERT_NO_THROW( sui8 += saf64);
	std::cout<<sui8<<std::endl;


}


