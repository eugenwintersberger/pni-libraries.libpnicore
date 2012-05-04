//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "Types.hpp"
#include "Shape.hpp"
#include "ShapeTest.hpp"
#include "Index.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ShapeTest);

//------------------------------------------------------------------------------
void ShapeTest::setUp(){
    _s1 = {3,4};
    _s2 = {2,3,5};
}

//------------------------------------------------------------------------------
void ShapeTest::tearDown(){
}

//------------------------------------------------------------------------------
void ShapeTest::testConstruction(){
	std::cout<<"void ShapeTest::testConstruction()-----------------------";
	std::cout<<std::endl;
    //default initialization of a shape from a std::vector object
	Shape s(_s1);

	//manual construction
	CPPUNIT_ASSERT(s.rank() == _s1.size());
	for(size_t i=0;i<s.rank();i++){
        CPPUNIT_ASSERT(s[i]==_s1[i]);
	}

	//now we change rank and shape of the object - this should go via 
    //implicit conversion from the std::vector object to the shape
	s = _s2;
	for(size_t i=0;i<s.rank();i++){
		CPPUNIT_ASSERT(_s2[i] == s.dim(i));
		CPPUNIT_ASSERT(s[i] == _s2[i]);
	}

    //using copy construction
	Shape s1(s);

    //check comparison of shape objects
	CPPUNIT_ASSERT(s1 == s);

    //construct from an initializer list
    Shape s3 = {10,30,12};
    CPPUNIT_ASSERT(s3[0] == 10);
    CPPUNIT_ASSERT(s3[1] == 30);
    CPPUNIT_ASSERT(s3[2] == 12);
    CPPUNIT_ASSERT(s3.rank() == 3);

    //using move construction
    Shape s4 = std::move(s);
    CPPUNIT_ASSERT(s4.rank() == _s2.size());
    CPPUNIT_ASSERT(s4.size() == s1.size());
    CPPUNIT_ASSERT(s.rank() == 0);
    CPPUNIT_ASSERT(s.size() == 0);

    //reset dimensions using an initializer list
    s4.dim({1,2,3});
    CPPUNIT_ASSERT(s4.size()==6);

}

//------------------------------------------------------------------------------
void ShapeTest::testAssignment(){
	std::cout<<"void ShapeTest::testAssignment()------------------------------";
	std::cout<<std::endl;
	//testing the assignment operator
	Shape s1 = {1,2,3,4};
    Shape s2,s3;

    //copy assignment
    CPPUNIT_ASSERT_NO_THROW(s2 = s1);
    CPPUNIT_ASSERT(s2 == s1);
    CPPUNIT_ASSERT_NO_THROW(s3 = std::move(s1));
    CPPUNIT_ASSERT(s3 == s2);
    CPPUNIT_ASSERT(s3 != s1);
    CPPUNIT_ASSERT(s1.rank() == 0);
    CPPUNIT_ASSERT(s1.size() == 0);

	Shape snon;
	CPPUNIT_ASSERT(s1 == snon);

    //this is done implicitely via the conversion constructor
    snon = {1,2,3,4};
    CPPUNIT_ASSERT(snon.rank() == 4);
    CPPUNIT_ASSERT(snon[0] == 1);
    CPPUNIT_ASSERT(snon[1] == 2);
    CPPUNIT_ASSERT(snon[2] == 3);
    CPPUNIT_ASSERT(snon[3] == 4);
}

//------------------------------------------------------------------------------
void ShapeTest::testComparison(){
	std::cout<<"void ShapeTest::testComparison()------------------------------";
	std::cout<<std::endl;
    Shape s1(_s1);
    Shape s2(_s2);

	Shape s3(s2);

	CPPUNIT_ASSERT(s1 == s1);
	CPPUNIT_ASSERT(s2 == s3);
	CPPUNIT_ASSERT(s1 != s2);

	//what happens with unallocated shapes
	Shape s4,s5;
	CPPUNIT_ASSERT(s4 == s5);
}

//------------------------------------------------------------------------------
void ShapeTest::testOffset(){
	std::cout<<"void ShapeTest::testOffset()----------------------------------";
	std::cout<<std::endl;
	Shape s1(_s1);
	Shape s2(_s2);
	Index index;

	index.rank(s1.rank());
	index[0] = 2;
	index[1] = 1;
	CPPUNIT_ASSERT(s1.offset(index)==9);
    CPPUNIT_ASSERT(s1.offset({2,1}) == 9);

	index.rank(s2.rank());
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	CPPUNIT_ASSERT(s2.offset(index)==8);
    CPPUNIT_ASSERT(s2.offset({0,1,3}) == 8);

}

//------------------------------------------------------------------------------
void ShapeTest::testIndex(){
	std::cout<<"void ShapeTest::testIndex()-----------------------------------";
	std::cout<<std::endl;
	Shape s1(_s1),s2(_s2);
	Index index;

	index.rank(s1.rank());
	index[0] = 2;
	index[1] = 1;
	CPPUNIT_ASSERT(s1.offset(index)==9);
	Index ti(s1.rank());
	CPPUNIT_ASSERT_NO_THROW(s1.index(9,ti));
	CPPUNIT_ASSERT(ti == index);

	index.rank(s2.rank());
	ti.rank(s2.rank());
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	CPPUNIT_ASSERT(s2.offset(index)==8);
	CPPUNIT_ASSERT_NO_THROW(s2.index(8,ti));
	CPPUNIT_ASSERT(ti == index);

    //testing setting dimensions using a vector
    std::vector<size_t> indices = {5,2,9};
    s2.dim(indices);
    CPPUNIT_ASSERT(s2.size() == 90);
    CPPUNIT_ASSERT(s2.rank() == 3);
    CPPUNIT_ASSERT(s2[0] == 5);
    CPPUNIT_ASSERT(s2[1] == 2);
    CPPUNIT_ASSERT(s2[2] == 9);

}

//------------------------------------------------------------------------------
void ShapeTest::testExceptions(){
	std::cout<<"void ShapeTest::testExceptions()------------------------------";
	std::cout<<std::endl;
	Shape s(_s1);

	CPPUNIT_ASSERT_THROW(s.dim(10,0),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(-10,0),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(10),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(-10),IndexError);
	CPPUNIT_ASSERT_THROW(s[10],IndexError);
	CPPUNIT_ASSERT_THROW(s[-10],IndexError);

    s = _s2;

	Index i(s.rank());
	i[0] = 1; i[1] = 100; i[2] = 1;
	CPPUNIT_ASSERT_THROW(s.offset(i),IndexError);
	i[0] = -1; i[1] = 0;
	CPPUNIT_ASSERT_THROW(s.offset(i),IndexError);

	Index i2(2);
	CPPUNIT_ASSERT_THROW(s.offset(i2),ShapeMissmatchError);
	Index i3;
	CPPUNIT_ASSERT_THROW(s.offset(i3),MemoryAccessError);

	Shape s2;
	CPPUNIT_ASSERT_THROW(s2.offset(i),MemoryAccessError);

	//now we can do the same game with the getIndex method
	//the offset exceeds the size of the shape
	CPPUNIT_ASSERT_THROW(s.index(10000,i),MemoryAccessError);
	//the index has the wrong rank
	CPPUNIT_ASSERT_THROW(s.index(1,i2),ShapeMissmatchError);
	//the shape object is not allocated
	CPPUNIT_ASSERT_THROW(s2.index(1,i),MemoryAccessError);


}
