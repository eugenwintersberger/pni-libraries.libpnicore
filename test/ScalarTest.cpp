#include<iostream>
#include<typeinfo>

#include<cppunit/extensions/HelperMacros.h>

#include "Scalar.hpp"
#include "ScalarTest.hpp"
#include "ResultTypeTrait.hpp"

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
	Complex128Scalar sca;
	Complex128 ca;
	Float64Scalar sfa;
	Float64 fa;
	UInt32Scalar sia;

	ca = Complex128(1,2);
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(ca));
	CPPUNIT_ASSERT(sca == ca);
	CPPUNIT_ASSERT(sca.getValue() == ca);

	fa = 1.4521;
	sfa = fa;
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(fa));
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(sfa));
	CPPUNIT_ASSERT(sca.getValue().real() == fa);

	CPPUNIT_ASSERT_THROW(sia.setValue(sfa),TypeError);
	sia = 100;
	CPPUNIT_ASSERT_NO_THROW(sca.setValue(sia));
	CPPUNIT_ASSERT(sca.getValue().real() == sia);
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
	Float128 av = 1.,bv = -45.2390;
	Complex64Scalar sca,scb,scc;
	Complex64 ca,cb,cc;


	//what we are allowed to do
	a = av;
	b = bv;
	CPPUNIT_ASSERT_NO_THROW(c = a+b);
	CPPUNIT_ASSERT(c == av+bv);
	CPPUNIT_ASSERT_NO_THROW(c = a+av);
	CPPUNIT_ASSERT(c == av+av);
	CPPUNIT_ASSERT_NO_THROW(c = bv+b);
	CPPUNIT_ASSERT(c == bv+bv);
	ai = 1;
	bi = 2;
	CPPUNIT_ASSERT_NO_THROW(c = ai+bi);
	CPPUNIT_ASSERT(c == ai+bi);
	CPPUNIT_ASSERT_NO_THROW(ci = ai+bi);
	CPPUNIT_ASSERT(ci == ai+bi);

	//checking complex numbers
	ca = Complex64(1.,2);
	cb = Complex64(4,-2.);
	sca = ca;
	scb = cb;
	CPPUNIT_ASSERT(sca == ca);
	CPPUNIT_ASSERT(scb == cb);

	/*
	std::cout<<typeid(sca).name()<<" "<<typeid(Complex64Scalar()).name()<<std::endl;
	std::cout<<typeid(scb).name()<<" "<<typeid(Complex64Scalar()).name()<<std::endl;
	std::cout<<typeid(scc).name()<<" "<<typeid(Complex64Scalar()).name()<<std::endl;
	std::cout<<typeid(a).name()<<" "<<typeid(Float64Scalar()).name()<<std::endl;
	 */

	std::cout<<"------------------ResultTypeTrait<Complex64,Complex64>---------------"<<std::endl;
	ResultTypeTrait<Complex64,Complex64>::AddResultType o;
	std::cout<<typeid(ca).name()<<std::endl;
	std::cout<<typeid(o).name()<<std::endl;
	std::cout<<"---------------------------------------------------------------------"<<std::endl;
	scc = sca + scb;
	cc = ca+cb;

	//CPPUNIT_ASSERT_NO_THROW(scc = sca+scb);
	//CPPUNIT_ASSERT(scc == ca+cb);


	//what will not work
	//the intermediate type is a float type and thus we
	//cannot assign a float scalar to an integer one
	CPPUNIT_ASSERT_THROW(ci = ai+b,TypeError);

	//try something with binary


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

	Complex128Scalar sca(Complex128(0,0));
	CPPUNIT_ASSERT_NO_THROW(sca += Complex128(1,-34.20));
	CPPUNIT_ASSERT_NO_THROW(sca -= Complex64(-5,123.34));
	CPPUNIT_ASSERT_NO_THROW(sca *= Complex128(.04321,1.e-4));
	CPPUNIT_ASSERT_NO_THROW(sca /= Complex64(5.32,5.24345));
}


