//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "StaticArray.hpp"

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "BufferHelper.hpp"

using namespace pni::utils;

template<typename  >
class StaticArrayTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(StaticArrayTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_typeinfo();
};

//------------------------------------------------------------------------------
template<typename T> void StaticArrayTest<T>::setUp(){ }

//------------------------------------------------------------------------------
template<typename T> void StaticArrayTest<T>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T> void StaticArrayTest<T>::test_construction()
{
    StaticArray<T,2,3> a1;
    StaticArray<T,2,3,5> a2;
    StaticArray<T,2,3> a3;


    //construction from a default array
    auto a4 = factory::create(s1,T(17));
#ifdef NOFOREACH
    for(auto iter = a4.begin();iter!=a4.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto v: a4)
    {
#endif
        check_equality(v,T(17));
    }

    auto data = RandomDistribution::uniform<std::vector<T> >(s1.size());
    auto a5 = factory::create(s1,data);

    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = a5.begin(); iter!=a5.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto v: a5)
    {
#endif
        check_equality(v,data[index++]);
    }
}

//------------------------------------------------------------------------------
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::test_linear_access()
{
    typedef ArrayFactory<T,BTYPE,ALLOCATOR> factory;
	auto a1 = factory::create(s1);

    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        a1[i] = T(i);

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        check_equality(T(i),a1[i]);

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        a1.at(i) = T(i);

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        check_equality(T(i),a1.at(i));

    CPPUNIT_ASSERT_THROW(a1.at(s1.size()+10),IndexError);

}

//------------------------------------------------------------------------------
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::test_iterators()
{
    typedef ArrayFactory<T,BTYPE,ALLOCATOR> factory;
	auto a1 = factory::create(s1);

    //--------------------check standard iterator----------------
	//access via [] operator
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin(); iter!=a1.end();iter++)
    {
        typename factory::array_type::value_type &v = *iter;
#else
    for(typename factory::array_type::value_type &v: a1)
    {
#endif
        v = data[index++];
    }
    
    index = 0;
#ifdef NOFOREACH
    for(auto iter=a1.begin();iter!=a1.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto &v: a1)
    {
#endif
        check_equality(v,data[index++]);
    }


    //-------------------check const iterator-----------------------------
    const typename factory::array_type &a = a1;

    index = 0;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto v: a)
    {
#endif
        check_equality(v,data[index++]); 
    }
}

//-----------------------------------------------------------------------------
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::test_multiindex_access()
{   
    typedef ArrayFactory<T,BTYPE,ALLOCATOR> factory;

    auto a1 = factory::create(s1);
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
            a1(i,j) = data[a1.shape().offset(i,j)];

    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
            check_equality(a1(i,j),data[a1.shape().offset(i,j)]);

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            a1(index) = data[a1.shape().offset(index)];
        }
    }

    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            check_equality(a1(index),data[a1.shape().offset(index)]);
        }
    }
}
//------------------------------------------------------------------------------
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::test_typeinfo()
{
    TypeID id1 = Array<T,BTYPE,ALLOCATOR>::type_id;
    TypeID id2 = TypeIDMap<T>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}
