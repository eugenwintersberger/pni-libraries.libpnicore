//implementation of the arrayshape test

#include<cppunit/extensions/HelperMacros.h>

#include "PNITypes.hpp"
#include "ArrayShape.hpp"
#include "ArrayShapeTest.hpp"
#include "Index.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayShapeTest);

//------------------------------------------------------------------------------
void ArrayShapeTest::setUp(){
	_r1 = 2;
	_r2 = 3;

	_s1 = new unsigned int[_r1];
	_s2 = new unsigned int[_r2];

	_s1[0] = 3; _s1[1] = 4;
	_s2[0] = 2; _s2[1] = 3; _s2[2] = 5;
}

//------------------------------------------------------------------------------
void ArrayShapeTest::tearDown(){
	if (_s1!=NULL) delete [] _s1;
	if (_s2!=NULL) delete [] _s2;
}

//------------------------------------------------------------------------------
void ArrayShapeTest::testConstruction(){
	std::cout<<"void ArrayShapeTest::testConstruction()-----------------------";
	std::cout<<std::endl;
	ArrayShape s;

	//manual construction
	CPPUNIT_ASSERT_NO_THROW(s.rank(_r1));
	CPPUNIT_ASSERT(s.rank() == _r1);
	for(size_t i=0;i<s.rank();i++){
		s.dim(i,_s1[i]);
	}

	//check here if all parameters are set correctly
	CPPUNIT_ASSERT(_r1==s.rank());
	for(size_t i=0;i<_r1;i++){
		CPPUNIT_ASSERT(_s1[i]==s.dim(i));
		CPPUNIT_ASSERT(s[i]==_s1[i]);
	}

	//now we change rank and shape of the object
	s.rank(_r2);
	for(size_t i=0;i<s.rank();i++) s.dim(i,_s2[i]);
	for(size_t i=0;i<s.rank();i++){
		CPPUNIT_ASSERT(_s2[i] == s.dim(i));
		CPPUNIT_ASSERT(s[i] == _s2[i]);
	}

	ArrayShape s1(_r2);
	for(size_t i=0;i<s1.rank();i++) s1.dim(i,_s2[i]);
	CPPUNIT_ASSERT(s1 == s);

	//copy constructor
	ArrayShape s2(s);
	CPPUNIT_ASSERT(s==s2);
}

//------------------------------------------------------------------------------
void ArrayShapeTest::testAssignment(){
	//testing the assignment operator
	ArrayShape s1,s2;

	CPPUNIT_ASSERT_NO_THROW(s1 = s2);
	s1.rank(3);
	CPPUNIT_ASSERT_NO_THROW(s2 = s1);
	CPPUNIT_ASSERT(s1.rank() == s2.rank());

	ArrayShape snon;
	CPPUNIT_ASSERT_NO_THROW(s1 = snon);
	CPPUNIT_ASSERT(s1 == snon);
}

//------------------------------------------------------------------------------
void ArrayShapeTest::testComparison(){
	ArrayShape s1(_r1);
	ArrayShape s2(_r2);
	for(size_t i=0;i<s1.rank();i++) s1.dim(i,_s1[i]);
	for(size_t i=0;i<s2.rank();i++) s2.dim(i,_s2[i]);

	ArrayShape s3(s2);

	CPPUNIT_ASSERT(s1 == s1);
	CPPUNIT_ASSERT(s2 == s3);
	CPPUNIT_ASSERT(s1 != s2);

	//what happens with unallocated shapes
	ArrayShape s4,s5;
	CPPUNIT_ASSERT(s4 == s5);
}

//------------------------------------------------------------------------------
void ArrayShapeTest::testOffset(){
	ArrayShape s1;
	ArrayShape s2;
	Index index;

	s1.rank(_r1);
	for(size_t i=0;i<s1.rank();i++) s1.dim(i,_s1[i]);
	s2.rank(_r2);
	for(size_t i=0;i<s2.rank();i++) s2.dim(i,_s2[i]);

	index.rank(s1.rank());
	index[0] = 2;
	index[1] = 1;
	CPPUNIT_ASSERT(s1.offset(index)==9);

	index.rank(s2.rank());
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	CPPUNIT_ASSERT(s2.offset(index)==8);

}

//------------------------------------------------------------------------------
void ArrayShapeTest::testIndex(){
	ArrayShape s1(_r1);
	for(size_t i=0;i<s1.rank();i++) s1.dim(i,_s1[i]);
	ArrayShape s2(_r2);
	for(size_t i=0;i<s2.rank();i++) s2.dim(i,_s2[i]);
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

}

//------------------------------------------------------------------------------
void ArrayShapeTest::testExceptions(){
	ArrayShape s(_r2);

	CPPUNIT_ASSERT_THROW(s.dim(10,0),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(-10,0),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(10),IndexError);
	CPPUNIT_ASSERT_THROW(s.dim(-10),IndexError);
	CPPUNIT_ASSERT_THROW(s[10],IndexError);
	CPPUNIT_ASSERT_THROW(s[-10],IndexError);

	for(size_t i=0;i<s.rank();i++) s.dim(i,_s2[i]);

	Index i(s.rank());
	i[0] = 1; i[1] = 100; i[2] = 1;
	CPPUNIT_ASSERT_THROW(s.offset(i),IndexError);
	i[0] = -1; i[1] = 0;
	CPPUNIT_ASSERT_THROW(s.offset(i),IndexError);

	Index i2(2);
	CPPUNIT_ASSERT_THROW(s.offset(i2),ShapeMissmatchError);
	Index i3;
	CPPUNIT_ASSERT_THROW(s.offset(i3),MemoryAccessError);

	ArrayShape s2;
	CPPUNIT_ASSERT_THROW(s2.offset(i),MemoryAccessError);

	//now we can do the same game with the getIndex method
	//the offset exceeds the size of the shape
	CPPUNIT_ASSERT_THROW(s.index(10000,i),MemoryAccessError);
	//the index has the wrong rank
	CPPUNIT_ASSERT_THROW(s.index(1,i2),ShapeMissmatchError);
	//the shape object is not allocated
	CPPUNIT_ASSERT_THROW(s2.index(1,i),MemoryAccessError);


}
