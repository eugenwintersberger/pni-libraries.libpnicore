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
void StaticShapeTest::test_construction(){
	std::cout<<"void ShapeTest::testConstruction()-----------------------";
	std::cout<<std::endl;

    StaticCIndexMap<3,4,5> s1;
    CPPUNIT_ASSERT(s1.size() == 3*4*5);
    CPPUNIT_ASSERT(s1.rank() == 3);

}

//------------------------------------------------------------------------------
void StaticShapeTest::test_offset()
{
	std::cout<<"void ShapeTest::testOffset()----------------------------------";
	std::cout<<std::endl;

    StaticCIndexMap<3,4> s1;

    size_t offset = 0;
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(2,1));
    CPPUNIT_ASSERT(offset == 9);
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(std::vector<size_t>{2,1}));
    CPPUNIT_ASSERT(offset == 9);
    CPPUNIT_ASSERT_NO_THROW(offset = s1.offset(std::list<size_t>{2,1}));
    CPPUNIT_ASSERT(offset == 9);

    //test exceptions for offset computation
    CPPUNIT_ASSERT_THROW(s1.offset(2,10),IndexError);
    CPPUNIT_ASSERT_THROW(s1.offset(10,1),IndexError);
    CPPUNIT_ASSERT_THROW(s1.offset(std::list<size_t>{10,1}),IndexError);
    CPPUNIT_ASSERT_THROW(s1.offset(std::list<size_t>{1,2,3,4}),ShapeMissmatchError);

    StaticCIndexMap<2,3,5> s2;
    CPPUNIT_ASSERT(s2.offset(0,1,3) == 8);
    CPPUNIT_ASSERT(s2.offset(0,1,3) == 8);

    CPPUNIT_ASSERT_THROW(s2.offset(10,1,3),IndexError);
    CPPUNIT_ASSERT_THROW(s2.offset(0,10,3),IndexError);
    CPPUNIT_ASSERT_THROW(s2.offset(0,1,10),IndexError);


}

//------------------------------------------------------------------------------
void StaticShapeTest::test_index(){
	std::cout<<"void ShapeTest::testIndex()-----------------------------------";
	std::cout<<std::endl;

    StaticCIndexMap<3,4> s1;
    StaticCIndexMap<2,3,5> s2;

	CPPUNIT_ASSERT(s1.offset(2,1)==9);
    auto index = s1.index<std::vector<size_t> >(9);
    CPPUNIT_ASSERT(index[0] == 2);
    CPPUNIT_ASSERT(index[1] == 1);

	CPPUNIT_ASSERT(s2.offset(0,1,3)==8);
    auto list = s2.index<std::vector<size_t> >(8);
    CPPUNIT_ASSERT(list.at(1) == 1);
    CPPUNIT_ASSERT(list.at(2) == 3);
    CPPUNIT_ASSERT(list.at(0) == 0);

    std::vector<size_t> index1(2);
    std::list<size_t> index2(3);
    CPPUNIT_ASSERT_NO_THROW(s1.index(9,index1));
    CPPUNIT_ASSERT_NO_THROW(s2.index(8,index2));
    CPPUNIT_ASSERT_THROW(s1.index(9,index2),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(s2.index(8,index1),ShapeMissmatchError);

    CPPUNIT_ASSERT_THROW(s1.index(900,index1),SizeMissmatchError);
    CPPUNIT_ASSERT_THROW(s2.index(800,index2),SizeMissmatchError);
}

