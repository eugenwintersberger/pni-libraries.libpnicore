//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#include <pni/utils/DArray.hpp>

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "BufferHelper.hpp"

using namespace pni::utils;

template<typename T,typename STORAGE>
class DArrayTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(DArrayTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_multiindex_access_const);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST_SUITE_END();
    private:
        std::vector<size_t> s1,s2;
        size_t r1,r2;
        

    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_multiindex_access_const();
        void test_typeinfo();
        void test_unary_addition();
        void test_unary_subtraction();
};

//------------------------------------------------------------------------------
template<typename T,typename STORAGE> void DArrayTest<T,STORAGE>::setUp()
{
    s1 = {3,4};
    s2 = {2,3,5};
}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE> void DArrayTest<T,STORAGE>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    //test default construction
    DArray<T,STORAGE> a1;
    CPPUNIT_ASSERT(a1.size() == 0);
    CPPUNIT_ASSERT(a1.rank() == 0);

    //default construction
    DArray<T,STORAGE> a2(s1,STORAGE(12));
    CPPUNIT_ASSERT(a2.size() == 12);
    CPPUNIT_ASSERT(a2.rank() == 2);

    //copy construction
    DArray<T,STORAGE> a3(a2);
    CPPUNIT_ASSERT(a2.rank() == a3.rank());
    CPPUNIT_ASSERT(a2.size() == a3.size());

    //move construction
    DArray<T,STORAGE> a4 = std::move(a2);
    CPPUNIT_ASSERT(a2.size() == 0);
    CPPUNIT_ASSERT(a2.rank() == 0);
    CPPUNIT_ASSERT(a4.size() == a3.size());
    CPPUNIT_ASSERT(a4.rank() == a3.rank());

}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_assignment()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    DArray<T,STORAGE> a1(s1,STORAGE(12));
    size_t i;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();++iter)
    {
        T &a = *iter;
#else
    for(T &a: a1)
    {
#endif 
        a = T(i);
    }
   
    //copy assignment
    DArray<T,STORAGE> a2;
    a2 = a1;
    CPPUNIT_ASSERT(a2.rank() == a1.rank());
    CPPUNIT_ASSERT(a2.size() == a2.size());
    CPPUNIT_ASSERT(std::equal(a1.begin(),a1.end(),a2.begin()));
    
    //move assignment operator
    DArray<T,STORAGE> a3;
    a3 = std::move(a1); 
    CPPUNIT_ASSERT(a3.rank() == a2.rank());
    CPPUNIT_ASSERT(a3.size() == a2.size());
    CPPUNIT_ASSERT(a1.rank() == 0);
    CPPUNIT_ASSERT(a1.size() == 0);

    CPPUNIT_ASSERT(std::equal(a3.begin(),a3.end(),a2.begin()));

}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_linear_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    DArray<T,STORAGE> a1(s1,STORAGE(12));

    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1[i] = T(i));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(T(i),a1[i]));

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1.at(i) = T(i));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(T(i),a1.at(i)));

    CPPUNIT_ASSERT_THROW(a1.at(a1.size() + 100),IndexError);
    CPPUNIT_ASSERT_THROW(a1.insert(2*a1.size(),100),IndexError);

}

//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    DArray<T,STORAGE> a1(s1,STORAGE(12));

    //--------------------check standard iterator----------------
	//access via [] operator
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();++iter)
    {
        T &v = *iter;
#else
    for(T &v: a1)
    {
#endif
        v = data[index++];
    }
    
    index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin();iter!=a1.end();++iter)
    {
        auto &v = *iter;
#else
    for(auto &v: a1)
    {
#endif
        check_equality(v,data[index++]);
    }


    //-------------------check const iterator-----------------------------
    const DArray<T,STORAGE> &a = a1;

    index = 0;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: a)
    {
#endif
        check_equality(v,data[index++]); 
    }
}

//-----------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_multiindex_access()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    DArray<T,STORAGE> a1(s1,STORAGE(12));
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
        {
            CPPUNIT_ASSERT_NO_THROW(a1(i,j) = data[a1.shape()[1]*i+j]);
        }
            

    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(i,j),data[a1.shape()[1]*i+j]));

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(a1(index) = data[a1.shape()[1]*i+j]);
        }
    }

    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(index),data[a1.shape()[1]*i+j]));
        }
    }

    //check some exceptions 
}

//-----------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_multiindex_access_const()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //auto data = RandomDistribution::uniform<STORAGE>(12);
    STORAGE data{1,2,3,4,5,6,7,8,9,10,11,12};
    const DArray<T,STORAGE> a1(s1,data);
    CPPUNIT_ASSERT(a1.shape()[0] == s1[0]);
    CPPUNIT_ASSERT(a1.shape()[1] == s1[1]);

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(i,j),data[a1.shape()[1]*i+j]));
        }
    }

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(index),data[a1.shape()[1]*i+j]));
        }

    }
    
    //check some exceptions 
    
}
//------------------------------------------------------------------------------
template<typename T,typename STORAGE>
void DArrayTest<T,STORAGE>::test_typeinfo()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    TypeID id1 = DArray<T,STORAGE>::type_id;
    TypeID id2 = TypeIDMap<T>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}
