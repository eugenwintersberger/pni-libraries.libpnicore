//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "Array.hpp"

#include "ArrayFactory.hpp"
#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "BufferHelper.hpp"

using namespace pni::utils;

template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
class ArrayTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(ArrayTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST_SUITE_END();
    private:
        Shape s1,s2;
        size_t r1,r2;
        

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
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::setUp(){
    s1 = {3,4};
    s2 = {2,3,5};
}

//------------------------------------------------------------------------------
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T,
         template<typename,typename> class BTYPE,
         typename ALLOCATOR
        >
void ArrayTest<T,BTYPE,ALLOCATOR>::test_construction()
{
    typedef ArrayFactory<T,BTYPE,ALLOCATOR> factory;
    //check for simple array-construction
    auto a1 = factory::create(s1);
    auto a2 = factory::create(s2);

    BTYPE<T,ALLOCATOR> buffer;
    allocate_buffer(buffer,s1.size());

    auto a3 = factory::create(s1,buffer);

    //construction from a default array
    auto a4 = factory::create(s1,T(17));
    for(auto v: a4) check_equality(v,T(17));

    auto data = RandomDistribution::uniform<std::vector<T> >(s1.size());
    auto a5 = factory::create(s1,data);

    size_t index = 0;
    for(auto v: a5)
        check_equality(v,data[index++]);
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
    for(typename factory::array_type::value_type &v: a1)
        v = data[index++];
    
    index = 0;
    for(auto &v: a1)
        check_equality(v,data[index++]);


    //-------------------check const iterator-----------------------------
    const typename factory::array_type &a = a1;

    index = 0;
    for(auto v: a)
        check_equality(v,data[index++]); 
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
