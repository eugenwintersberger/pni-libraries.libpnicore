#include<cppunit/extensions/HelperMacros.h>

#include "IteratorTest.hpp"
#include <algorithm>
#include <iterator>

CPPUNIT_TEST_SUITE_REGISTRATION(IteratorTest);

//-----------------------------------------------------------------------------
void IteratorTest::setUp()
{
    vector = Iterable{1,2,3,4,5,6,7};
}

//-----------------------------------------------------------------------------
void IteratorTest::tearDown()
{

}

//-----------------------------------------------------------------------------
void IteratorTest::test_construction()
{
    //==================testing default construction===========================
    iterator iterator1;
    //after default construction the interator should be invalid
    CPPUNIT_ASSERT(!iterator1);

    const_iterator const_iterator1;
    CPPUNIT_ASSERT(!const_iterator1);

    //====================testing standard construction========================
    //check construction on the first element - this is how begin() method
    //would create an interator.
    iterator iterator2(&vector,0);
    CPPUNIT_ASSERT(iterator2);

    const_iterator const_iterator2(&vector,0);
    CPPUNIT_ASSERT(const_iterator2);

    //check construction on the last+1 element - this is how end() method
    //produces the final iterator.
    iterator iterator3(&vector,vector.size());
    const_iterator const_iterator3(&vector,vector.size());
    CPPUNIT_ASSERT(!iterator3);
    CPPUNIT_ASSERT(!const_iterator3);


    //check construction on a negative element (should lead to an invalid 
    //iterator)
    iterator iterator4(&vector,-1);
    const_iterator const_iterator4(&vector,-1);
    CPPUNIT_ASSERT(!iterator4);
    CPPUNIT_ASSERT(!const_iterator4);

    //====================check copy construction==============================
    iterator iterator5(iterator2);
    const_iterator const_iterator5(const_iterator2);
    CPPUNIT_ASSERT(iterator5);
    CPPUNIT_ASSERT(iterator2 == iterator5);
    CPPUNIT_ASSERT(const_iterator5);
    CPPUNIT_ASSERT(const_iterator5 == const_iterator2);

    //======================check move construction===========================
    iterator iterator6 = std::move(iterator2);
    CPPUNIT_ASSERT(!iterator2);
    CPPUNIT_ASSERT(iterator6);

    const_iterator const_iterator6 = std::move(const_iterator2);
    CPPUNIT_ASSERT(!const_iterator2);
    CPPUNIT_ASSERT(const_iterator6);
}

//-----------------------------------------------------------------------------
void IteratorTest::test_assignment()
{
    iterator iterator1(&vector,2);
    const_iterator const_iterator1(&vector,2);
    
    iterator iterator2;
    const_iterator const_iterator2;

    //====================check copy assignment================================
    iterator2 = iterator1;
    const_iterator2 = const_iterator1;
    CPPUNIT_ASSERT(iterator2);
    CPPUNIT_ASSERT(iterator1);
    CPPUNIT_ASSERT(const_iterator2);
    CPPUNIT_ASSERT(const_iterator1);

    //======================check move assignment==============================
    iterator iterator3;
    const_iterator const_iterator3;

    iterator3 = std::move(iterator1);
    const_iterator3 = std::move(const_iterator1);
    CPPUNIT_ASSERT(iterator3);
    CPPUNIT_ASSERT(!iterator1);
    CPPUNIT_ASSERT(const_iterator3);
    CPPUNIT_ASSERT(!const_iterator1);

}

//-----------------------------------------------------------------------------
void IteratorTest::test_comparison()
{
    iterator iterator1(&vector,0);
    const_iterator const_iterator1(&vector,0);

    iterator iterator2 = iterator1;
    const_iterator const_iterator2 = const_iterator1;

    //check for equality
    CPPUNIT_ASSERT(iterator1 == iterator2);
    CPPUNIT_ASSERT(const_iterator1 == const_iterator2);

    //check for inequality
    iterator iterator3(&vector,3);
    const_iterator const_iterator3(&vector,3);
    CPPUNIT_ASSERT(iterator1 != iterator3);
    CPPUNIT_ASSERT(const_iterator1 != const_iterator3);

    //check for greater than
    CPPUNIT_ASSERT(iterator3 > iterator1);
    CPPUNIT_ASSERT(const_iterator3 > const_iterator1);
    CPPUNIT_ASSERT(iterator3 >= iterator1);
    CPPUNIT_ASSERT(const_iterator3 >= const_iterator1);

    CPPUNIT_ASSERT(iterator1 < iterator3);
    CPPUNIT_ASSERT(const_iterator1 < const_iterator3);
    CPPUNIT_ASSERT(iterator1 <= iterator3);
    CPPUNIT_ASSERT(const_iterator1 <= const_iterator3);

    iterator1 += 3;
    const_iterator1 += 3;
    CPPUNIT_ASSERT(iterator3 >= iterator1);
    CPPUNIT_ASSERT(const_iterator3 >= const_iterator1);
    CPPUNIT_ASSERT(iterator1 <= iterator3);
    CPPUNIT_ASSERT(const_iterator1 <= const_iterator3);

}

//-----------------------------------------------------------------------------
void IteratorTest::test_unary_arithmetics()
{
    iterator iterator1(&vector,0);
    const_iterator const_iterator1(&vector,0);

    iterator1 += 5;
    const_iterator1 += 5;
    CPPUNIT_ASSERT(iterator1 == iterator(&vector,5));
    CPPUNIT_ASSERT(const_iterator1 == const_iterator(&vector,5));

    iterator1 -= 2;
    const_iterator1 -= 2;
    CPPUNIT_ASSERT(iterator1 == iterator(&vector,3));
    CPPUNIT_ASSERT(const_iterator1 == const_iterator(&vector,3));

}

//-----------------------------------------------------------------------------
void IteratorTest::test_binary_arithmetics()
{
    iterator iterator1(&vector,0);
    const_iterator const_iterator1(&vector,0);

    //=================test binary add=========================================
    CPPUNIT_ASSERT((iterator1+5) == iterator(&vector,5));
    CPPUNIT_ASSERT((5+iterator1) == iterator(&vector,5));
    CPPUNIT_ASSERT((const_iterator1+5) == const_iterator(&vector,5));
    CPPUNIT_ASSERT((5+const_iterator1) == const_iterator(&vector,5));

    //====================test binary sub======================================
    iterator1 = iterator(&vector,3);
    const_iterator1 = const_iterator(&vector,3);
    CPPUNIT_ASSERT((iterator1-2) == iterator(&vector,1));
    CPPUNIT_ASSERT((const_iterator1-2) == const_iterator(&vector,1));

    //=====================test binary add iterators===========================
    iterator iterator2(&vector,5);
    const_iterator const_iterator2(&vector,5);
    CPPUNIT_ASSERT((iterator2 - iterator1) == 2);
    CPPUNIT_ASSERT((const_iterator2 - const_iterator1) == 2);
}

//-----------------------------------------------------------------------------
void IteratorTest::test_stl_algos()
{
    Iterable::iterator siter1 = vector.begin()+2;
    Iterable::iterator siter2 = vector.begin()+5;
    CPPUNIT_ASSERT(std::distance(siter1,siter2) == 3);
    
    iterator iter1(&vector,2),iter2(&vector,5);
    CPPUNIT_ASSERT(std::distance(iter1,iter2) == 3);
}

//-----------------------------------------------------------------------------
void IteratorTest::test_increment()
{
    iterator iter(&vector,0);

    CPPUNIT_ASSERT(*iter == 1);
    iter++;
    CPPUNIT_ASSERT(*iter == 2);
    ++iter;
    CPPUNIT_ASSERT(*iter == 3);
    CPPUNIT_ASSERT(*iter++ == 3);
}

