//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "SArray.hpp"

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"

using namespace pni::utils;

template<typename T>
class SArrayTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(SArrayTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST(test_view);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_typeinfo();
        void test_stl();
        void test_view();
};

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::setUp(){ }

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_construction()
{
    //testing the default constructor
    SArray<T,2,3> a1;
    CPPUNIT_ASSERT(a1.rank() == 2);
    CPPUNIT_ASSERT(a1.size() == 6);

    //testing initializer list constructor
    SArray<T,2,3> a2{1,2,3,4,5,6};
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.size() == 6);

    //testing copy constructor
    SArray<T,2,3> a3(a2);
    CPPUNIT_ASSERT(a3.rank() == a2.rank());
    CPPUNIT_ASSERT(a3.size() == a2.size());
}

//------------------------------------------------------------------------------ 
template<typename T> void SArrayTest<T>::test_linear_access()
{
    SArray<T,2,3> a1{1,2,3,4,5,6};
    std::vector<T> v1{1,2,3,4,5,6};
   
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

    CPPUNIT_ASSERT_THROW(a1.at(a1.size()+10),IndexError);

}

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_iterators()
{
    SArray<T,2,3> a1;

    //--------------------check standard iterator----------------
	//access via [] operator
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    //----------------------testing write data---------------------------------
    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = a1.begin(); iter!=a1.end();iter++)
    {
        T &v = *iter;
#else
    for(T &v: a1)
    {
#endif
        v = data[index++];
    }
   
    //-----------------------test reading data---------------------------------
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

    index = 0;
#ifdef NOFOREACH
    for(auto iter = a.begin();iter!=a.end();iter++)
    {
        const T &v = *iter;
#else
    for(auto v: a1)
    {
#endif
        check_equality(v,data[index++]); 
    }
}

//-----------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_multiindex_access()
{   
    SArray<T,2,3> a1;
    
    auto data = RandomDistribution::uniform<std::vector<T> >(a1.size());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            a1(i,j) = data[i*3+j];

    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            check_equality(a1(i,j),data[i*3+j]);

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            a1(index) = data[i*3+j];
        }
    }

    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            check_equality(a1(index),data[i*3+j]);
        }
    }
}

//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_view()
{
    SArray<T,10,3> v;
    std::vector<Slice> s{Slice(0),Slice(0,3,1)};

    for(size_t i=0;i<10;i++)
    {
        auto view = v(std::vector<Slice>{Slice(i),Slice(0,3,1)});
        std::fill(view.begin(),view.end(),T(i));
    }
    
    for(size_t i=0;i<10;i++)
    {
        //for reading we use a different construction here
        auto view = v(i,Slice(0,3,1));
        for(auto v: view) check_equality(v,T(i));
    }

    //check construction of a static array from a view
    auto view = v(2,Slice(0,3));
    SArray<T,3> c(view);

    for(auto viter=view.begin(),citer=c.begin();viter!=view.end();
            ++viter,++citer)
    {
        check_equality(*viter,*citer);
    }

   
}
//------------------------------------------------------------------------------
template<typename T> void SArrayTest<T>::test_typeinfo()
{
    TypeID id1 = SArray<T,2,3>::type_id;
    TypeID id2 = TypeIDMap<T>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}
