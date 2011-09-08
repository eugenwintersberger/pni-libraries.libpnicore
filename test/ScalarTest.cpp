#include<iostream>
#include<typeinfo>

#include<cppunit/extensions/HelperMacros.h>

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

	std::cout<<"use native conversion operator!"<<std::endl;
	CPPUNIT_ASSERT_NO_THROW(ui8  = sui8);
	CPPUNIT_ASSERT(ui8 == 10);
	std::cout<<"use template conversion operator!"<<std::endl;
	CPPUNIT_ASSERT_NO_THROW(f64 = sui8);
	CPPUNIT_ASSERT(f64 == 10.);

}

        
void ScalarTest::testConstructors(){
    
    
}

void ScalarTest::testSetGetValue(){
	Complex128Scalar sca;
	Complex128 ca;
	Float64Scalar sfa;
	Float64 fa;
	UInt32Scalar su32;
	Int32Scalar si32;

	//checking integer values
	si32 = -14;
	CPPUNIT_ASSERT_THROW(su32.setValue(si32),RangeError);
	fa = 1.2434;
	CPPUNIT_ASSERT_THROW(su32.setValue(fa),TypeError);

	ca = Complex128(1,2);
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(ca));
	CPPUNIT_ASSERT(sca == ca);
	CPPUNIT_ASSERT(sca.getValue() == ca);

	fa = 1.4521;
	sfa = fa;
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(fa));
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(sfa));
	CPPUNIT_ASSERT(sca.getValue().real() == fa);

	CPPUNIT_ASSERT_THROW(su32.setValue(sfa),TypeError);
	//CPPUNIT_ASSERT_THROW(sia.setValue(sca),TypeError);
	su32 = 100;
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(su32));
	CPPUNIT_ASSERT(sca.getValue().real() == su32.getValue());
}

void ScalarTest::testAssignment(){
	//we test here the assignment operator for
	//functionality

	//------------start with checking the integer types-------------------------
	UInt8Scalar sui8;
	UInt8 ui8;
	UInt64Scalar sui64;
	UInt64 ui64;
	Int64Scalar si64,si64_2;
	Int64 i64;
	Int8Scalar si8;
	Int8 i8;

	i8 = 100;
	CPPUNIT_ASSERT_NO_THROW(si8 = i8); CPPUNIT_ASSERT(si8 == i8);
	ui64 = 10000;
	CPPUNIT_ASSERT_THROW(si8 = ui64,RangeError);
	i64 = -10000;
	CPPUNIT_ASSERT_THROW(si8 = i64,RangeError);
	ui64 = 20;
	si8 = ui64;
	CPPUNIT_ASSERT_NO_THROW(si8 = ui64);
	CPPUNIT_ASSERT(si8 == ui64);
	i64 = -10000;
	CPPUNIT_ASSERT_THROW(sui64 = i64,RangeError);
	i64 = 100000;
	CPPUNIT_ASSERT_NO_THROW(sui64 = i64);
	CPPUNIT_ASSERT(sui64 == i64);

	si64_2 = 1000000;
	CPPUNIT_ASSERT_NO_THROW(si64 = si64_2);
	CPPUNIT_ASSERT(si64 == si64_2);
	sui64 = 13918834;
	CPPUNIT_ASSERT_NO_THROW(si64 = sui64);
	CPPUNIT_ASSERT(si64 == sui64);

	si64 = -10000;
	CPPUNIT_ASSERT_THROW(sui64 = si64,RangeError);

	//-----------start checking floating point numbers-------------------------
	Float64Scalar sf64, sf64_2;
	Float32Scalar sf32;
	Float64 f64;

	//here everything should work fine
	f64 = -1.32e-9;
	CPPUNIT_ASSERT_NO_THROW(sf64 = f64);
	CPPUNIT_ASSERT(sf64 == f64);

	//this should go wrong - we cannot assign float to integer
	CPPUNIT_ASSERT_THROW(si64 = sf64,TypeError);
	CPPUNIT_ASSERT_THROW(si64 = f64,TypeError);

	//ok - need to check some ranges now
	f64 = 1.e+300;
	CPPUNIT_ASSERT_THROW(sf32 = f64,RangeError);
	f64 = 1.443;
	CPPUNIT_ASSERT_NO_THROW(sf32 = f64);

	//---------------start checking complex numbers----------------------------
	Complex128Scalar sc128;
	Complex64Scalar sc64;
	Complex128 c128(1.,-2.);
	Complex32 c32(34,-290);

	//this is trivial
	CPPUNIT_ASSERT_NO_THROW(sc128 = c128);
	CPPUNIT_ASSERT(sc128 == c128);

	//this should not work - does not even compile
	//CPPUNIT_ASSERT_THROW(si64 = c32,TypeError);
	//CPPUNIT_ASSERT_THROW(sf64 = c32,TypeError);

	//this should work
	CPPUNIT_ASSERT_NO_THROW(sc128 = f64);
	CPPUNIT_ASSERT_NO_THROW(sc128 = sui64);

	//push it to the limits
	sc128 = Complex128(1.e+400,1e+400);
	CPPUNIT_ASSERT_THROW(sc64 = sc128,RangeError);


}

void ScalarTest::testComparison(){
	Complex64Scalar sca,scb;
	Complex64 ca,cb;

	ca = Complex64(1,2);
	cb = Complex64(-4.5,1000.398781);
	sca = ca;
	scb = ca;
	CPPUNIT_ASSERT(sca == scb);
	CPPUNIT_ASSERT(sca != cb);
	CPPUNIT_ASSERT(cb != sca);
	CPPUNIT_ASSERT(ca == sca);
	scb = cb;
	CPPUNIT_ASSERT(scb != sca);
}

void ScalarTest::testBinaryAddOperation(){
	Float128Scalar a,b,c;
	Int64Scalar ci,ai,bi;
	UInt64Scalar sui64;
	Float128 av = 1.,bv = -45.2390;

	//what we are allowed to do
	a = av;
	b = bv;
	//everything in float
	std::cout<<"Should use template operator + Scalar Scalar!"<<std::endl;
	CPPUNIT_ASSERT_NO_THROW(c = a + b);
	CPPUNIT_ASSERT(c == av+bv);
	CPPUNIT_ASSERT_NO_THROW(c = a + av);
	CPPUNIT_ASSERT(c == av+av);
	CPPUNIT_ASSERT_NO_THROW(c = bv + b);
	CPPUNIT_ASSERT(c == bv+bv);
	ai = 1;
	bi = 2;
	CPPUNIT_ASSERT_NO_THROW(c = ai+bi);
	//can assign an integer to a float
	CPPUNIT_ASSERT(c == (ai+bi));
	//can assign integer to integer
	CPPUNIT_ASSERT_NO_THROW(ci = ai+bi);
	CPPUNIT_ASSERT(ci == ai+bi);

	//if an integer is not negative it can be assigned to an
	//unsigned int
	ai = 1;
	bi = 2;
	CPPUNIT_ASSERT_NO_THROW(sui64 = ai+bi);

	//test complex numbers
	Complex128 sca,scb,scc;
	sca = Complex128(4.4,1.0);
	scb = Complex128(3.1,-0.37);
	CPPUNIT_ASSERT_NO_THROW(scc = sca+scb);
	CPPUNIT_ASSERT(scc == sca+scb);


	//what will not work
	//the intermediate type is a float type and thus we
	//cannot assign a float scalar to an integer one
	CPPUNIT_ASSERT_THROW(ci = ai+b,TypeError);
	//cannot assign an negative integer to unsigned integer
	ai = 1;
	bi = -2;
	CPPUNIT_ASSERT_THROW(sui64 = ai+bi,RangeError);


}

void ScalarTest::testUnaryAddOperation(){
	Float64Scalar saf64,sbf64;
	Float64 af64,bf64;
	UInt8Scalar sui8;

	CPPUNIT_ASSERT_NO_THROW(saf64 = 0.);
	CPPUNIT_ASSERT_NO_THROW(sbf64 = 100.);
	CPPUNIT_ASSERT_NO_THROW(saf64 += sbf64);
	CPPUNIT_ASSERT(saf64 == sbf64);
	saf64 = 0;
	CPPUNIT_ASSERT_NO_THROW(bf64 = -20);
	CPPUNIT_ASSERT_NO_THROW(saf64 += bf64);
	CPPUNIT_ASSERT(saf64 == bf64);

	//this should not work
	CPPUNIT_ASSERT_THROW( sui8 += saf64,RangeError);
	std::cout<<sui8<<std::endl;

	Complex128Scalar sca(Complex128(0,0));
	CPPUNIT_ASSERT_NO_THROW(sca += Complex128(1,-34.20));
	CPPUNIT_ASSERT_NO_THROW(sca -= Complex64(-5,123.34));
	CPPUNIT_ASSERT_NO_THROW(sca *= Complex128(.04321,1.e-4));
	CPPUNIT_ASSERT_NO_THROW(sca /= Complex64(5.32,5.24345));
}

void ScalarTest::testUnarySubOperation(){

}

void ScalarTest::testUnaryDivOperation(){

}

void ScalarTest::testUnaryMultOperation(){

}


