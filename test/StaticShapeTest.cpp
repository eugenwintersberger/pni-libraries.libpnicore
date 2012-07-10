//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "Types.hpp"
#include "StaticShapeTest.hpp"
#include <list>

CPPUNIT_TEST_SUITE_REGISTRATION(StaticShapeTest);

//------------------------------------------------------------------------------
void StaticShapeTest::setUp(){
}

//------------------------------------------------------------------------------
void StaticShapeTest::tearDown(){
}

//------------------------------------------------------------------------------
void StaticShapeTest::testConstruction(){
	std::cout<<"void ShapeTest::testConstruction()-----------------------";
	std::cout<<std::endl;

    StaticShape<3,4,5> s1;
    CPPUNIT_ASSERT(s1.size() == 3*4*5);
    CPPUNIT_ASSERT(s1.rank() == 3);

}

//------------------------------------------------------------------------------
void StaticShapeTest::testAssignment(){
}

//------------------------------------------------------------------------------
void StaticShapeTest::testComparison(){

}

//------------------------------------------------------------------------------
void StaticShapeTest::testOffset()
{
	std::cout<<"void ShapeTest::testOffset()----------------------------------";
	std::cout<<std::endl;

    StaticShape<3,4> s1;

    size_t offset = 0;
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(2,1));
    CPPUNIT_ASSERT(offset == 9);
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(std::vector<size_t>{2,1}));
    CPPUNIT_ASSERT(offset == 9);

    StaticShape<2,3,5> s2;
    CPPUNIT_ASSERT(s2.offset(0,1,3) == 8);
    CPPUNIT_ASSERT(s2.offset(0,1,3) == 8);

}

//------------------------------------------------------------------------------
void StaticShapeTest::testIndex(){
	std::cout<<"void ShapeTest::testIndex()-----------------------------------";
	std::cout<<std::endl;

    StaticShape<3,4> s1;
    StaticShape<2,3,5> s2;

	CPPUNIT_ASSERT(s1.offset(2,1)==9);
    auto index = s1.index<std::vector<size_t> >(9);
    CPPUNIT_ASSERT(index[0] == 2);
    CPPUNIT_ASSERT(index[1] == 1);

	CPPUNIT_ASSERT(s2.offset(0,1,3)==8);
    auto list = s2.index<std::vector<size_t> >(8);
    CPPUNIT_ASSERT(list.at(1) == 1);
    CPPUNIT_ASSERT(list.at(2) == 3);
    CPPUNIT_ASSERT(list.at(0) == 0);

}

//------------------------------------------------------------------------------
void StaticShapeTest::testExceptions(){
    /*
	std::cout<<"void ShapeTest::testExceptions()------------------------------";
	std::cout<<std::endl;
	Shape s(_s1);

	CPPUNIT_ASSERT_THROW(s.dim(10),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(-10),IndexError);

    s = Shape(_s2);

	CPPUNIT_ASSERT_THROW(s.offset(1,100,1),IndexError);
	CPPUNIT_ASSERT_THROW(s.offset({-1,0}),ShapeMissmatchError);

	CPPUNIT_ASSERT_THROW(s.offset(0,3),ShapeMissmatchError);
	CPPUNIT_ASSERT_THROW(s.offset(std::vector<size_t>()),MemoryAccessError);

	Shape s2;
	CPPUNIT_ASSERT_THROW(s2.offset({0,3}),MemoryAccessError);

	//now we can do the same game with the getIndex method
	//the offset exceeds the size of the shape
	CPPUNIT_ASSERT_THROW(s.index<std::vector<size_t> >(10000),MemoryAccessError);
	//the index has the wrong rank
    std::vector<size_t> index(2);
	CPPUNIT_ASSERT_THROW(s.index(1,index),ShapeMissmatchError);
	//the shape object is not allocated
	CPPUNIT_ASSERT_THROW(s2.index(1,index),MemoryAccessError);
    */

}
