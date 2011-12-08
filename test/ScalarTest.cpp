#include<iostream>
#include<typeinfo>

#include<cppunit/extensions/HelperMacros.h>

#include "ScalarTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ScalarTest);

void ScalarTest::setUp(){
    

}

void ScalarTest::tearDown(){

}

        
void ScalarTest::testConstructors(){
    Int32Scalar s;

    //test standard operator
    s = Int32Scalar(100);
    CPPUNIT_ASSERT(s.value() == 100);
    CPPUNIT_ASSERT(s.name() == "");
    CPPUNIT_ASSERT(s.description() == "");
    CPPUNIT_ASSERT(s.unit() == "");

    s = Int32Scalar(101,"test1","unit1");
    CPPUNIT_ASSERT(s.value() == 101);
    CPPUNIT_ASSERT(s.name() == "test1");
    CPPUNIT_ASSERT(s.description() == "");
    CPPUNIT_ASSERT(s.unit() == "unit1");
    
    s = Int32Scalar(102,"test2","unit2","description2");
    CPPUNIT_ASSERT(s.value() == 102);
    CPPUNIT_ASSERT(s.name() == "test2");
    CPPUNIT_ASSERT(s.description() == "description2");
    CPPUNIT_ASSERT(s.unit() == "unit2");

    s = Int32Scalar("test3","unit3");
    CPPUNIT_ASSERT(s.name() == "test3");
    CPPUNIT_ASSERT(s.description() == "");
    CPPUNIT_ASSERT(s.unit() == "unit3");

    s = Int32Scalar("test3","unit3","description3");
    CPPUNIT_ASSERT(s.name() == "test3");
    CPPUNIT_ASSERT(s.description() == "description3");
    CPPUNIT_ASSERT(s.unit() == "unit3");
}

void ScalarTest::testConversion(){
	Float64Scalar sf64;

	//starting with integer conversions
	UInt8 ui8;
	Int32Scalar si32;
	UInt8Scalar sui8;

	//check for type errors
	CPPUNIT_ASSERT_THROW(ui8 = sf64,TypeError);

	//checking rang errors
	CPPUNIT_ASSERT_NO_THROW(si32 = -100);
	CPPUNIT_ASSERT_THROW(ui8 = si32,RangeError);
	CPPUNIT_ASSERT_NO_THROW(si32 = 100000);
	CPPUNIT_ASSERT_THROW(ui8 = si32,RangeError);
	CPPUNIT_ASSERT_NO_THROW(si32 = 1);
	CPPUNIT_ASSERT_NO_THROW( ui8 = si32);

	//checking for floating point
	Float128Scalar sf128;
	Float64 f64;

	CPPUNIT_ASSERT_NO_THROW(sf64 = 100.23);
	CPPUNIT_ASSERT_NO_THROW(f64 = sf64);
	CPPUNIT_ASSERT(f64 == sf64);

	//range errors
	CPPUNIT_ASSERT_NO_THROW(sf128 = 1.e+400l);
	CPPUNIT_ASSERT_THROW(f64 = sf128,RangeError);
	CPPUNIT_ASSERT_NO_THROW(sf128 = -1.e+400l);
	CPPUNIT_ASSERT_THROW(f64 = sf128,RangeError);

	//finally this should work
	CPPUNIT_ASSERT_NO_THROW(sf128 = 100.2344);
	CPPUNIT_ASSERT_NO_THROW(f64 = sf128);
	CPPUNIT_ASSERT(f64 == sf128);

	//cannot use the conversion operator with complex numbers.
	//need to fix this somehow
}

void ScalarTest::testSetGetValue(){
	Complex128Scalar sc128;
	Complex128 c128;
	Complex64Scalar sc64;
	Complex64 c64;
	Float64Scalar sfa,sf64;
	Float64 fa;
	Float128 f128;
	Float128Scalar sf128;
	UInt32Scalar su32;
	UInt32 u32;
	Int32 i32;
	Int32Scalar si32;

	//checking integer values
	su32 = 0;

	si32 = -14;
	CPPUNIT_ASSERT_THROW(su32.value(si32),RangeError);
	CPPUNIT_ASSERT(su32.value() == 0);

	i32 = -100;
	CPPUNIT_ASSERT_THROW(su32.value(i32),RangeError);
	CPPUNIT_ASSERT(su32.value() == 0);

	fa = 1.2434;
	CPPUNIT_ASSERT_THROW(su32.value(fa),TypeError);
	CPPUNIT_ASSERT(su32.value() == 0);

	sfa = fa;
	CPPUNIT_ASSERT_THROW(su32.value(sfa),TypeError);
	CPPUNIT_ASSERT(su32.value() == 0);

	si32 = 100;
	CPPUNIT_ASSERT_NO_THROW(su32.value(si32));
	CPPUNIT_ASSERT(su32.value() == si32.value());
	i32 = 1000;
	CPPUNIT_ASSERT_NO_THROW(su32.value(i32));
	CPPUNIT_ASSERT(su32.value() == i32);


	//checking floating point numbers
	sfa = 0.;
	f128 = 1.e+400l;
	CPPUNIT_ASSERT_THROW(sfa.value(f128),RangeError);
	CPPUNIT_ASSERT(sfa.value() == 0.);

	f128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(sfa.value(f128),RangeError);
	CPPUNIT_ASSERT(sfa.value() == 0.);

	sf128 = 1.e+400l;
	CPPUNIT_ASSERT_THROW(sfa.value(sf128),RangeError);
	CPPUNIT_ASSERT(sfa.value() == 0.);

	sf128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(sfa.value(sf128),RangeError);
	CPPUNIT_ASSERT(sfa.value() == 0.);

	f128 = 100.234;
	CPPUNIT_ASSERT_NO_THROW(sfa.value(f128));
	CPPUNIT_ASSERT(sfa.value() == f128);

	sf128 = f128;
	CPPUNIT_ASSERT_NO_THROW(sfa.value(sf128));
	CPPUNIT_ASSERT(sfa.value() == f128);

	fa = -100.23;
	CPPUNIT_ASSERT_NO_THROW(sfa.value(fa));
	CPPUNIT_ASSERT(sfa.value() == fa);



	//checking complex value
	c128 = Complex128(1,2);
	CPPUNIT_ASSERT_NO_THROW(sc128.value(c128));
	CPPUNIT_ASSERT(sc128.value() == c128);

	c64 = Complex64(0,0);
	sc64 = c64;
	c128 = Complex128(1.e+400l,1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64.value(c128),RangeError);
	CPPUNIT_ASSERT(sc64.value() == c64);

	c128 = Complex128(-1.e+400l,-1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64.value(c128),RangeError);
	CPPUNIT_ASSERT(sc64.value() == c64);

	sc128 = Complex128(1.e+400l,1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64.value(sc128),RangeError);
	CPPUNIT_ASSERT(sc64.value() == c64);

	sc128 = Complex128(-1.e+400l,-1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64.value(sc128),RangeError);
	CPPUNIT_ASSERT(sc64.value() == c64);

	f128 = 1.e+400l;
	CPPUNIT_ASSERT_THROW(sc64.value(f128),RangeError);
	CPPUNIT_ASSERT(sc64.value() == c64);

	f128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(sc64.value(f128),RangeError);
	CPPUNIT_ASSERT(sc64.value() == c64);

	c128 = Complex128(1.2344,1309.1032);

	CPPUNIT_ASSERT_NO_THROW(sc64.value(c128));
	CPPUNIT_ASSERT_NO_THROW(sc128.value(c128));
	CPPUNIT_ASSERT(sc64.value() == c128);
	CPPUNIT_ASSERT(sc128.value() == sc64.value());

	fa = 1.4521;
	CPPUNIT_ASSERT_NO_THROW(sc64.value(fa));
	CPPUNIT_ASSERT(sc64.value() == Complex64(fa,0));
}

void ScalarTest::testAssignment(){
	//we test here the assignment operator for
	//functionality

	//------------start with checking the integer types-------------------------
	UInt8Scalar sui8;
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
	sc128 = Complex128(1.e+400l,1e+400l);
	CPPUNIT_ASSERT_THROW(sc64 = sc128,RangeError);


}

void ScalarTest::testComparison(){
	Complex64Scalar sca,scb;
	Complex64 ca,cb;
	Complex128Scalar sc128;

	ca = Complex64(1,2);
	sc128 = Complex128(1,2);
	cb = Complex64(-4.5,1000.398781);
	sca = ca;
	scb = ca;
	CPPUNIT_ASSERT(sca == scb);
	CPPUNIT_ASSERT(sca != cb);
	CPPUNIT_ASSERT(cb != sca);
	CPPUNIT_ASSERT(ca == sca);
	scb = cb;
	CPPUNIT_ASSERT(scb != sca);
	sc128 = ca;
	CPPUNIT_ASSERT(sc128 == ca);
	ca = cb;
	//ca = sc128;
	//CPPUNIT_ASSERT(ca == sc128);
}

void ScalarTest::testBinaryAddOperation(){
	Int64Scalar sai64,sbi64,sci64;
	Int64 ai64,bi64;
	UInt32Scalar saui32,sbui32,scui32;
	UInt32 aui32,bui32;

	//check integer operations
	ai64 = 100;
	bi64 = 2234;
	sai64 = ai64; sbi64 = bi64;
	CPPUNIT_ASSERT_NO_THROW(sci64 = sai64 + sbi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 + bi64);
	CPPUNIT_ASSERT_NO_THROW(sci64 = sai64 + bi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 + bi64);
	CPPUNIT_ASSERT_NO_THROW(sci64 = ai64 + sbi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 + bi64);

	//checking range errors
	bi64 = -22345;
	sbi64 = bi64;
	CPPUNIT_ASSERT_THROW(scui32 = sai64 + sbi64,RangeError);
	CPPUNIT_ASSERT_THROW(scui32 = sai64 + bi64,RangeError);

	//checking mixed type operations
	aui32 = 100;
	CPPUNIT_ASSERT_THROW(scui32 = aui32 + sbi64,RangeError);
	bi64 = 23134; sbi64 = bi64;
	CPPUNIT_ASSERT_NO_THROW(scui32 = aui32 + sbi64);
	CPPUNIT_ASSERT(scui32 == aui32 + bi64);

	//check float operations
	Float128Scalar saf128,sbf128,scf128;
	Float128 af128,bf128;
	Float64Scalar saf64,sbf64,scf64;
	Float64 af64,bf64;

	af64 = 123.123; bf64 = 3.e+2;
	saf64 = af64; sbf64 = bf64;
	//everything in float
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 + sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 + bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 + sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 + bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 + bf64);
	CPPUNIT_ASSERT(scf64.value() == af64 + bf64);

	//mixed float operations with range error
	af128 = 34413.3400923l; bf128 = -456789.7844l;
	saf128 = af128; sbf128 = bf128;
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 + sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 + bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 + sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 + bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 + bf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 + bf128,scf64.value(),DOUBLE_PREC);
	af128 = 1.e+400l; saf128 = af128;
	CPPUNIT_ASSERT_THROW(scf64 = saf128 + sbf128,RangeError);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 + bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_THROW(scf64 = af128 + sbf128,RangeError);

	//mixed float - integer operations
	ai64 = 391883; sai64 = ai64;
	CPPUNIT_ASSERT_NO_THROW(scf64 = sai64 + sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 + bf64,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = ai64 + sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 + bf64,scf64.value(),DOUBLE_PREC);

	//produce some type errors
	CPPUNIT_ASSERT_THROW(sci64 = sai64 + sbf64,TypeError);
	CPPUNIT_ASSERT_THROW(sci64 = ai64 + sbf64,TypeError);


	//testing with complex numbers
	Complex32 ac32,bc32,cc32;
	Complex32Scalar sac32,sbc32,scc32;
	Complex128 ac128,bc128,cc128;
	Complex128Scalar sac128,sbc128,scc128;

	ac32 = Complex32(2.321323,-043.e+2);
	bc32 = Complex32(-2.4201,4568.78);
	sac32 = ac32; sbc32 = bc32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 + sbc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 + bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 + bc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 + bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac32 + sbc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 + bc32);

	//mixed complex operations
	ac128 = Complex128(4578.748,-587.3240);
	bc128 = Complex128(458.747,7893.1334);
	sac128 = ac128; sbc128 = bc128;
	CPPUNIT_ASSERT_NO_THROW(scc128 = sac128 + sbc32);
	CPPUNIT_ASSERT(scc128.value() == ac128 + (Complex128)bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac128 + sbc32);
	CPPUNIT_ASSERT(scc32.value() == (Complex32)ac128 + bc32);

	//mixed complex double operations
	af64 = 12.31344; saf64 = af64;
	CPPUNIT_ASSERT_NO_THROW(scc32 = saf64 + sbc32);
	CPPUNIT_ASSERT(scc32.value() == Complex32(af64) + bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = af64 + sbc32);
	CPPUNIT_ASSERT(scc32.value() == Complex32(af64) + bc32);
	//checking overflows in complex - double operations
	af64 = 1.e+300; saf64 = af64;
	CPPUNIT_ASSERT_THROW(scc32 = saf64 + saf64,RangeError);
	CPPUNIT_ASSERT_THROW(scc32 = saf64 + af64,RangeError);

	//mixed complex integer operations
	bui32 = 100; sbui32 = bui32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 + sbui32);
	CPPUNIT_ASSERT(scc32.value() == ac32 + Complex32(bui32));
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 + bui32);
	CPPUNIT_ASSERT(scc32.value() == ac32 + Complex32(bui32));

}

void ScalarTest::testBinarySubtractionOperation(){
	Int64Scalar sai64,sbi64,sci64;
	Int64 ai64,bi64;
	UInt32Scalar saui32,sbui32,scui32;
	UInt32 aui32,bui32;

	//check integer operations
	ai64 = 100;
	bi64 = 2234;
	sai64 = ai64; sbi64 = bi64;
	CPPUNIT_ASSERT_NO_THROW(sci64 = sai64 - sbi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 - bi64);
	CPPUNIT_ASSERT_NO_THROW(sci64 = sai64 - bi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 - bi64);
	CPPUNIT_ASSERT_NO_THROW(sci64 = ai64 - sbi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 - bi64);

	//checking range errors
	bi64 = 22345;
	sbi64 = bi64;
	CPPUNIT_ASSERT_THROW(scui32 = sai64 - sbi64,RangeError);
	CPPUNIT_ASSERT_THROW(scui32 = sai64 - bi64,RangeError);

	//checking mixed type operations
	aui32 = 100;
	CPPUNIT_ASSERT_THROW(scui32 = aui32 - sbi64,RangeError);
	bi64 = -23134; sbi64 = bi64;
	CPPUNIT_ASSERT_NO_THROW(scui32 = aui32 - sbi64);
	CPPUNIT_ASSERT(scui32 == aui32 - bi64);

	//check float operations
	Float128Scalar saf128,sbf128,scf128;
	Float128 af128,bf128;
	Float64Scalar saf64,sbf64,scf64;
	Float64 af64,bf64;
	Float32Scalar saf32,sbf32,scf32;
	Float32 af32,bf32;

	af64 = 123.123; bf64 = 3.e+2;
	saf64 = af64; sbf64 = bf64;
	//everything in float
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 - sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 - bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 - sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 - bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 - bf64);
	CPPUNIT_ASSERT(scf64.value() == af64 - bf64);

	CPPUNIT_ASSERT_NO_THROW(scf32 = saf64 - sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 - bf64,scf32.value(),DOUBLE_PREC);

	//mixed float operations with range error
	af128 = 34413.3400923l; bf128 = -456789.7844l;
	saf128 = af128; sbf128 = bf128;
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 - sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 - bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 - sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 - bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 - bf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 - bf128,scf64.value(),DOUBLE_PREC);
	af128 = 1.e+400l; saf128 = af128;
	CPPUNIT_ASSERT_THROW(scf64 = saf128 - sbf128,RangeError);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 - bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_THROW(scf64 = af128 - sbf128,RangeError);

	//mixed float - integer operations
	ai64 = 391883; sai64 = ai64;
	CPPUNIT_ASSERT_NO_THROW(scf64 = sai64 - sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 - bf64,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = ai64 - sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 - bf64,scf64.value(),DOUBLE_PREC);

	//produce some type errors
	CPPUNIT_ASSERT_THROW(sci64 = sai64 - sbf64,TypeError);
	CPPUNIT_ASSERT_THROW(sci64 = ai64 - sbf64,TypeError);


	//testing with complex numbers
	Complex32 ac32,bc32,cc32;
	Complex32Scalar sac32,sbc32,scc32;
	Complex128 ac128,bc128,cc128;
	Complex128Scalar sac128,sbc128,scc128;

	ac32 = Complex32(2.321323,-043.e+2);
	bc32 = Complex32(-2.4201,4568.78);
	sac32 = ac32; sbc32 = bc32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 - sbc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 - bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 - bc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 - bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac32 - sbc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 - bc32);

	//mixed complex operations
	ac128 = Complex128(4578.748,-587.3240);
	bc128 = Complex128(458.747,7893.1334);
	sac128 = ac128; sbc128 = bc128;
	CPPUNIT_ASSERT_NO_THROW(scc128 = sac128 - sbc32);
	CPPUNIT_ASSERT(scc128.value() == ac128 - (Complex128)bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac128 - sbc32);
	//this does not work due to rounding errors - needs more investigation
	//Put this on a todo list and comment this test meanwhile
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ac128.real() - bc32.real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ac128.imag() - bc32.imag(),scc32.value().imag(),DOUBLE_PREC);

	//mixed complex double operations
	af64 = 12.31344; saf64 = af64;
	CPPUNIT_ASSERT_NO_THROW(scc32 = saf64 - sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Complex32(af64) - bc32).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Complex32(af64) - bc32).imag(),scc32.value().imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = af64 - sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Complex32(af64) - bc32).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Complex32(af64) - bc32).imag(),scc32.value().imag(),DOUBLE_PREC);
	//checking overflows in complex - double operations
	af64 = 1.e+300; saf64 = af64;
	CPPUNIT_ASSERT_THROW(scc32 = saf64 - sbf64,RangeError);
	CPPUNIT_ASSERT_THROW(scc32 = saf64 - bf64,RangeError);

	//mixed complex integer operations
	bui32 = 100; sbui32 = bui32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 - sbui32);
	CPPUNIT_ASSERT(scc32.value() == ac32 - Complex32(bui32));
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 - bui32);
	CPPUNIT_ASSERT(scc32.value() == ac32 - Complex32(bui32));
}

void ScalarTest::testBinaryDivisionOperation(){
	Int64Scalar sai64,sbi64,sci64;
	Int64 ai64,bi64;
	UInt32Scalar saui32,sbui32,scui32;
	UInt32 aui32,bui32;

	//check integer operations
	ai64 = 100;
	bi64 = 2234;
	sai64 = ai64; sbi64 = bi64;
	Float64Scalar iresult;
	CPPUNIT_ASSERT_NO_THROW(iresult = sai64 / sbi64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Float64)ai64 / bi64,iresult.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(iresult = sai64 / bi64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Float64)ai64/bi64,iresult.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(iresult = ai64 / sbi64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Float64)ai64/bi64,iresult.value(),DOUBLE_PREC);

	//since the result of a division is always a float value  we do not
	//have to care about range errors due to the signdness of the result

	//checking mixed type operations
	aui32 = 100;
	CPPUNIT_ASSERT_NO_THROW(iresult = aui32/sbi64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Float64)aui32/bi64,iresult.value(),DOUBLE_PREC);

	//check float operations
	Float128Scalar saf128,sbf128,scf128;
	Float128 af128,bf128;
	Float64Scalar saf64,sbf64,scf64;
	Float64 af64,bf64;

	af64 = 123.123; bf64 = 3.e+2;
	saf64 = af64; sbf64 = bf64;
	//everything in float
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 / sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 / bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 / sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 / bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 / bf64);
	CPPUNIT_ASSERT(scf64.value() == af64 / bf64);

	//mixed float operations with range error
	af128 = 34413.3400923l; bf128 = -456789.7844l;
	saf128 = af128; sbf128 = bf128;
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 / sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 / bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 / sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 / bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 / bf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 / bf128,scf64.value(),DOUBLE_PREC);
	af128 = 1.e+400l; saf128 = af128;
	CPPUNIT_ASSERT_THROW(scf64 = saf128 / sbf128,RangeError);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 / bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_THROW(scf64 = af128 / sbf128,RangeError);

	//mixed float - integer operations
	ai64 = 391883; sai64 = ai64;
	CPPUNIT_ASSERT_NO_THROW(scf64 = sai64 / sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 / bf64,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = ai64 / sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 / bf64,scf64.value(),DOUBLE_PREC);

	//produce some type errors
	CPPUNIT_ASSERT_THROW(sci64 = sai64 / sbf64,TypeError);
	CPPUNIT_ASSERT_THROW(sci64 = ai64 / sbf64,TypeError);


	//testing with complex numbers
	Complex32 ac32,bc32,cc32;
	Complex32Scalar sac32,sbc32,scc32;
	Complex128 ac128,bc128,cc128;
	Complex128Scalar sac128,sbc128,scc128;

	ac32 = Complex32(2.321323,-043.e+2);
	bc32 = Complex32(-2.4201,4568.78);
	sac32 = ac32; sbc32 = bc32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 / sbc32);
	std::cout<<scc32<<std::endl;
	std::cout<<ac32/bc32<<std::endl;
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(ac32 / bc32).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(ac32 / bc32).imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 / bc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(ac32 / bc32).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(ac32 / bc32).imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac32 / sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(ac32 / bc32).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(ac32 / bc32).imag(),DOUBLE_PREC);

	//mixed complex operations
	ac128 = Complex128(4578.748,-587.3240);
	bc128 = Complex128(458.747,7893.1334);
	sac128 = ac128; sbc128 = bc128;
	CPPUNIT_ASSERT_NO_THROW(scc128 = sac128 / sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc128.value().real(),(ac128 / (Complex128)bc32).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc128.value().imag(),(ac128 / (Complex128)bc32).imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac128 / sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((((Complex32)ac128) / bc32).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((((Complex32)ac128) / bc32).imag(),scc32.value().imag(),DOUBLE_PREC);

	//mixed complex double operations
	af64 = 12.31344; saf64 = af64;
	CPPUNIT_ASSERT_NO_THROW(scc32 = saf64 / sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(Complex32(af64)/bc32).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(Complex32(af64)/bc32).imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = af64 / sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(Complex32(af64) / bc32).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(Complex32(af64) / bc32).imag(),DOUBLE_PREC);

	//mixed complex integer operations
	bui32 = 100; sbui32 = bui32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 / sbui32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(ac32/Complex32(bui32)).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(ac32/Complex32(bui32)).imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 / bui32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().real(),(ac32/Complex32(bui32)).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc32.value().imag(),(ac32/Complex32(bui32)).imag(),DOUBLE_PREC);

}

void ScalarTest::testBinaryMultiplicationOperation(){
	Int64Scalar sai64,sbi64,sci64;
	Int64 ai64,bi64;
	UInt32Scalar saui32,sbui32,scui32;
	UInt32 aui32,bui32;

	//check integer operations
	ai64 = 100;
	bi64 = 2234;
	sai64 = ai64; sbi64 = bi64;
	CPPUNIT_ASSERT_NO_THROW(sci64 = sai64 * sbi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 * bi64);
	CPPUNIT_ASSERT_NO_THROW(sci64 = sai64 * bi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 * bi64);
	CPPUNIT_ASSERT_NO_THROW(sci64 = ai64 * sbi64);
	CPPUNIT_ASSERT(sci64.value() == ai64 * bi64);

	//checking range errors
	bi64 = -22345;
	sbi64 = bi64;
	CPPUNIT_ASSERT_THROW(scui32 = sai64 * sbi64,RangeError);
	CPPUNIT_ASSERT_THROW(scui32 = sai64 * bi64,RangeError);

	//checking mixed type operations
	aui32 = 100;
	CPPUNIT_ASSERT_THROW(scui32 = aui32 * sbi64,RangeError);
	bi64 = 23134; sbi64 = bi64;
	CPPUNIT_ASSERT_NO_THROW(scui32 = aui32 * sbi64);
	CPPUNIT_ASSERT(scui32 == aui32 * bi64);

	//check float operations
	Float128Scalar saf128,sbf128,scf128;
	Float128 af128,bf128;
	Float64Scalar saf64,sbf64,scf64;
	Float64 af64,bf64;

	af64 = 123.123; bf64 = 3.e+2;
	saf64 = af64; sbf64 = bf64;
	//everything in float
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 * sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 * bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 * sbf64);
	CPPUNIT_ASSERT(scf64.value() == af64 * bf64);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 * bf64);
	CPPUNIT_ASSERT(scf64.value() == af64 * bf64);

	//mixed float operations with range error
	af128 = 34413.3400923l; bf128 = -456789.7844l;
	saf128 = af128; sbf128 = bf128;
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 * sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 * bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = af64 * sbf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 * bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = saf64 * bf128);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 * bf128,scf64.value(),DOUBLE_PREC);
	af128 = 1.e+400l; saf128 = af128;
	CPPUNIT_ASSERT_THROW(scf64 = saf128 * sbf128,RangeError);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(af64 * bf128,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_THROW(scf64 = af128 * sbf128,RangeError);

	//mixed float - integer operations
	ai64 = 391883; sai64 = ai64;
	CPPUNIT_ASSERT_NO_THROW(scf64 = sai64 * sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 * bf64,scf64.value(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scf64 = ai64 * sbf64);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(ai64 * bf64,scf64.value(),DOUBLE_PREC);

	//produce some type errors
	CPPUNIT_ASSERT_THROW(sci64 = sai64 * sbf64,TypeError);
	CPPUNIT_ASSERT_THROW(sci64 = ai64 * sbf64,TypeError);


	//testing with complex numbers
	Complex32 ac32,bc32,cc32;
	Complex32Scalar sac32,sbc32,scc32;
	Complex128 ac128,bc128,cc128;
	Complex128Scalar sac128,sbc128,scc128;

	ac32 = Complex32(2.321323,-043.e+2);
	bc32 = Complex32(-2.4201,4568.78);
	sac32 = ac32; sbc32 = bc32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 * sbc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 * bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 * bc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 * bc32);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac32 * sbc32);
	CPPUNIT_ASSERT(scc32.value() == ac32 * bc32);

	//mixed complex operations
	ac128 = Complex128(4578.748,-587.3240);
	bc128 = Complex128(458.747,7893.1334);
	sac128 = ac128; sbc128 = bc128;
	CPPUNIT_ASSERT_NO_THROW(scc128 = sac128 * sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc128.value().real(),(ac128*Complex128(bc32)).real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(scc128.value().imag(),(ac128*Complex128(bc32)).imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = ac128 * sbc32);
	//need to define here some rules for comparison
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Float32)(ac128 * (Complex128)bc32).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((Float32)(ac128 * (Complex128)bc32).imag(),scc32.value().imag(),DOUBLE_PREC);

	//mixed complex double operations
	af64 = 12.31344; saf64 = af64;
	CPPUNIT_ASSERT_NO_THROW(scc32 = saf64 * sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(((Complex32)(Complex64(af64) * Complex64(bc32))).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(((Complex32)(Complex64(af64) * Complex64(bc32))).imag(),scc32.value().imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = af64 * sbc32);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(((Complex32)(Complex64(af64)*Complex64(bc32))).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(((Complex32)(Complex64(af64)*Complex64(bc32))).imag(),scc32.value().imag(),DOUBLE_PREC);
	//checking overflows in complex - double operations
	af64 = 1.e+300; saf64 = af64;
	CPPUNIT_ASSERT_THROW(scc32 = saf64 * saf64,RangeError);
	CPPUNIT_ASSERT_THROW(scc32 = saf64 * af64,RangeError);

	//mixed complex integer operations
	bui32 = 100; sbui32 = bui32;
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 * sbui32);
	CPPUNIT_ASSERT(scc32.value() == ac32 * Complex32(bui32));
	CPPUNIT_ASSERT_DOUBLES_EQUAL((ac32*Complex32(bui32)).real(),scc32.value().real(),DOUBLE_PREC);
	CPPUNIT_ASSERT_DOUBLES_EQUAL((ac32*Complex32(bui32)).imag(),scc32.value().imag(),DOUBLE_PREC);
	CPPUNIT_ASSERT_NO_THROW(scc32 = sac32 * bui32);
	CPPUNIT_ASSERT(scc32.value() == ac32 * Complex32(bui32));

}

void ScalarTest::testUnaryAddOperation(){
	Float64Scalar saf64,sbf64;
	Float64 af64,bf64;
	Float128Scalar sf128,saf128,sbf128;
	Float128 f128,af128,bf128;
	Complex64 c64;

	//some integer scalars
	UInt8Scalar sui8,saui8,sbui8;
	UInt8 ui8,aui8,bui8;
	Int32Scalar si32,sai32,sbi32;
	Int32 i32,ai32,bi32;

	//checking unary integer operations
	sui8 = 0;
	saui8 = 0;
	sbui8 = 100;
	CPPUNIT_ASSERT_NO_THROW(saui8 += sbui8);
	//CPPUNIT_ASSERT(saui8 ==
	i32 = 100;
	CPPUNIT_ASSERT_NO_THROW(sui8 += i32);  //adding singed to unsigned
	CPPUNIT_ASSERT(sui8 == i32);
	sui8 = 0;
	si32 = 100;
	CPPUNIT_ASSERT_NO_THROW(sui8 += si32); //adding signed to unsigned
	CPPUNIT_ASSERT(sui8 == si32);

	sai32 = 0;
	sbi32 = -10000;
	CPPUNIT_ASSERT_NO_THROW(sai32 += sbi32); //adding signed to signed
	CPPUNIT_ASSERT(sai32 == sbi32);

	//check type errors
	saf64 = 1.e-4;
	CPPUNIT_ASSERT_THROW(sui8 += saf64,TypeError);
	af64 = -1.e-4;
	CPPUNIT_ASSERT_THROW(sui8 += af64,TypeError);

	//testing range error exceptions for integers
	sui8 = 0;
	i32 = 300;
	CPPUNIT_ASSERT_THROW(sui8 += i32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	i32 = -100;
	CPPUNIT_ASSERT_THROW(sui8 += i32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	i32 = -300;
	CPPUNIT_ASSERT_THROW(sui8 += i32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	si32 = -300;
	CPPUNIT_ASSERT_THROW(sui8 += si32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	si32 = 300;
	CPPUNIT_ASSERT_THROW(sui8 += si32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);


	//check floating point numbers
	CPPUNIT_ASSERT_NO_THROW(saf64 = 0);
	CPPUNIT_ASSERT_NO_THROW(sbf64 = 100);
	CPPUNIT_ASSERT_NO_THROW(saf64 += sbf64);
	CPPUNIT_ASSERT(saf64 == sbf64);

	CPPUNIT_ASSERT_NO_THROW(saf64 = 0);
	i32 = 100324;
	CPPUNIT_ASSERT_NO_THROW(saf64 = i32);
	CPPUNIT_ASSERT(saf64 == i32);

	saf64 = 0;
	CPPUNIT_ASSERT_NO_THROW(bf64 = -20);
	CPPUNIT_ASSERT_NO_THROW(saf64 += bf64);
	CPPUNIT_ASSERT(saf64 == bf64);

	//check floating point overflow
	f128 = 1.e+400l;
	saf64 = 0;
	CPPUNIT_ASSERT_THROW(saf64 += f128,RangeError);
	f128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(saf64 += f128,RangeError);

	//--------------------check complex numbers----------------------
	Complex128Scalar sc128(Complex128(0,0));
	Complex64Scalar sc64(Complex64(-1.23,2.3901));
	CPPUNIT_ASSERT_NO_THROW(sc128 += Complex128(1,-34.20));
	CPPUNIT_ASSERT_NO_THROW(sc128 += sc64);
	CPPUNIT_ASSERT(sc128 == sc128);
	CPPUNIT_ASSERT_NO_THROW(sc64 += sc128);

	c64 = Complex64(1.3,435.3);
	sc64 = Complex64(0,0);
	CPPUNIT_ASSERT_NO_THROW(sc64 += c64);
	CPPUNIT_ASSERT(sc64 == c64);


	//testing complex overflow with scalar + native variable
	Complex128 c128(1.e+400l,1.e+400l);;
	sc64 = Complex64(0,0);
	CPPUNIT_ASSERT_THROW(sc64 += c128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));
	c128 = Complex128(-1.e+400l,-1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64 += c128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));

	//testing complex overflow with scalar + scalar
	sc128 = Complex128(1.e+400l,1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64 += sc128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));
	sc128 = Complex128(-1.e+400l,-1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64 += sc128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));

	//testing complex overflow with simple float value
	f128 = 1.e+400l;
	CPPUNIT_ASSERT_THROW(sc64 += f128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));
	f128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(sc64 += f128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));


}

void ScalarTest::testUnarySubOperation(){
	Float64Scalar saf64,sbf64;
	Float64 af64,bf64;
	Complex64 c64;
	UInt8Scalar sui8;
	Int32Scalar si32;
	Int32Scalar sai32,sbi32;
	Int32 i32;

	//checking unary integer operations
	sui8 = 0;
	i32 = -100;
	CPPUNIT_ASSERT_NO_THROW(sui8 -= i32);  //adding singed to unsigned
	CPPUNIT_ASSERT(sui8 == -i32);
	sui8 = 0;
	si32 = -100;
	CPPUNIT_ASSERT_NO_THROW(sui8 -= si32); //adding signed to unsigned
	CPPUNIT_ASSERT(sui8 == -si32.value());

	sai32 = 0;
	sbi32 = -10000;
	CPPUNIT_ASSERT_NO_THROW(sai32 += sbi32); //adding signed to signed
	CPPUNIT_ASSERT(sai32 == sbi32);

	//check type errors
	saf64 = 1.e-4;
	CPPUNIT_ASSERT_THROW(sui8 += saf64,TypeError);

	//testing range error exceptions for integers
	sui8 = 0;
	i32 = 300;
	CPPUNIT_ASSERT_THROW(sui8 += i32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	i32 = -100;
	CPPUNIT_ASSERT_THROW(sui8 += i32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	i32 = -300;
	CPPUNIT_ASSERT_THROW(sui8 += i32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	si32 = -300;
	CPPUNIT_ASSERT_THROW(sui8 += si32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);
	si32 = 300;
	CPPUNIT_ASSERT_THROW(sui8 += si32,RangeError);
	CPPUNIT_ASSERT(sui8 == 0);


	//check floating point numbers
	CPPUNIT_ASSERT_NO_THROW(saf64 = 0);
	CPPUNIT_ASSERT_NO_THROW(sbf64 = 100);
	CPPUNIT_ASSERT_NO_THROW(saf64 += sbf64);
	CPPUNIT_ASSERT(saf64 == sbf64);

	CPPUNIT_ASSERT_NO_THROW(saf64 = 0);
	i32 = 100324;
	CPPUNIT_ASSERT_NO_THROW(saf64 = i32);
	CPPUNIT_ASSERT(saf64 == i32);

	saf64 = 0;
	CPPUNIT_ASSERT_NO_THROW(bf64 = -20);
	CPPUNIT_ASSERT_NO_THROW(saf64 += bf64);
	CPPUNIT_ASSERT(saf64 == bf64);

	//check floating point overflow
	Float128 f128 = 1.e+400l;
	saf64 = 0;
	CPPUNIT_ASSERT_THROW(saf64 += f128,RangeError);
	f128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(saf64 += f128,RangeError);

	//--------------------check complex numbers----------------------
	Complex128Scalar sc128(Complex128(0,0));
	Complex64Scalar sc64(Complex64(-1.23,2.3901));
	CPPUNIT_ASSERT_NO_THROW(sc128 += Complex128(1,-34.20));
	CPPUNIT_ASSERT_NO_THROW(sc128 += sc64);
	CPPUNIT_ASSERT(sc128 == sc128);
	CPPUNIT_ASSERT_NO_THROW(sc64 += sc128);

	c64 = Complex64(1.3,435.3);
	sc64 = Complex64(0,0);
	CPPUNIT_ASSERT_NO_THROW(sc64 += c64);
	CPPUNIT_ASSERT(sc64 == c64);


	//testing complex overflow with scalar + native variable
	Complex128 c128(1.e+400l,1.e+400l);;
	sc64 = Complex64(0,0);
	CPPUNIT_ASSERT_THROW(sc64 += c128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));
	c128 = Complex128(-1.e+400l,-1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64 += c128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));

	//testing complex overflow with scalar + scalar
	sc128 = Complex128(1.e+400l,1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64 += sc128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));
	sc128 = Complex128(-1.e+400l,-1.e+400l);
	CPPUNIT_ASSERT_THROW(sc64 += sc128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));

	//testing complex overflow with simple float value
	f128 = 1.e+400l;
	CPPUNIT_ASSERT_THROW(sc64 += f128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));
	f128 = -1.e+400l;
	CPPUNIT_ASSERT_THROW(sc64 += f128,RangeError);
	CPPUNIT_ASSERT(sc64 == Complex64(0,0));


}

void ScalarTest::testUnaryDivOperation(){

}

void ScalarTest::testUnaryMultOperation(){

}


