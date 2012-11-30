//testing class for Iterators objects

#ifndef __ITERATORTEST_HPP__
#define __ITERATORTEST_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<vector>
#include <pni/utils/Iterator.hpp>

using namespace pni::utils;

class IteratorTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(IteratorTest);
	CPPUNIT_TEST(test_construction);
	CPPUNIT_TEST(test_assignment);
	CPPUNIT_TEST(test_comparison);
    CPPUNIT_TEST(test_unary_arithmetics);
    CPPUNIT_TEST(test_binary_arithmetics);
    CPPUNIT_TEST(test_stl_algos);
    CPPUNIT_TEST(test_increment);
	CPPUNIT_TEST_SUITE_END();
private:
    typedef std::vector<double> Iterable;
    typedef Iterator<Iterable,1> const_iterator;
    typedef Iterator<Iterable,0> iterator;
    Iterable vector;
public:
	void setUp();
	void tearDown();

	void test_construction();
	void test_assignment();
    void test_comparison();
    void test_unary_arithmetics();
    void test_binary_arithmetics();
    void test_stl_algos();
    void test_increment();

};

#endif
