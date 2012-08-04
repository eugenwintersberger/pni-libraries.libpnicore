//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include "NumArray.hpp"
#include "DArray.hpp"
#include "SArray.hpp"

#include "RandomDistributions.hpp"
#include "EqualityCheck.hpp"
#include "BufferHelper.hpp"

using namespace pni::utils;

template<typename ATYPE>
class NumArrayTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(NumArrayTest);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST(test_unary_add);
        CPPUNIT_TEST(test_unary_sub);
        CPPUNIT_TEST(test_unary_mult);
        CPPUNIT_TEST(test_unary_div);
        CPPUNIT_TEST(test_view);
        CPPUNIT_TEST_SUITE_END();
    private:
        template<typename T,typename ST,typename MT>
        void create_array(DArray<T,ST,MT> &a)
        {
            a = DArray<T,ST,MT>(std::vector<size_t>{3,4});
        }

        template<typename AT> AT create_array()
        {
            AT result;
            create_array(result);
            return result;
        }

            
        
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_assignment();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_typeinfo();
        void test_unary_add();
        void test_unary_sub();
        void test_unary_mult();
        void test_unary_div();
       void test_view();
};

//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::setUp(){ }

//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::tearDown(){ } 
//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_construction()
{
    //default construction
    NumArray<ATYPE> a1(create_array<ATYPE>());
    CPPUNIT_ASSERT(a1.size() == 12);
    CPPUNIT_ASSERT(a1.rank() == 2);

    //copy construction
    NumArray<ATYPE> a2(a1);
    CPPUNIT_ASSERT(a2.rank() == a1.rank());
    CPPUNIT_ASSERT(a2.size() == a1.size());
}

//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_assignment()
{
    NumArray<ATYPE> a1(create_array<ATYPE>());
    size_t i;
    for(typename ATYPE::value_type  &a: a1) a = typename ATYPE::value_type(i);
   
    //copy assignment
    NumArray<ATYPE> a2(create_array<ATYPE>());
    a2 = a1;
    CPPUNIT_ASSERT(a2.rank() == a1.rank());
    CPPUNIT_ASSERT(a2.size() == a2.size());
    CPPUNIT_ASSERT(std::equal(a1.begin(),a1.end(),a2.begin()));
}

//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_linear_access()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a1(create_array<ATYPE>());


    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1[i] = value_type(i));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(value_type(i),a1[i]));

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(a1.at(i) = value_type(i));

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        CPPUNIT_ASSERT_NO_THROW(check_equality(value_type(i),a1.at(i)));

    CPPUNIT_ASSERT_THROW(a1.at(a1.size() + 100),IndexError);
    CPPUNIT_ASSERT_THROW(a1.insert(2*a1.size(),100),IndexError);

}

//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_iterators()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a1(create_array<ATYPE>());

    //--------------------check standard iterator----------------
	//access via [] operator
    auto data = RandomDistribution::uniform<std::vector<value_type> >(a1.size());

    size_t index = 0;
    for(value_type &v: a1) v = data[index++];
    
    index = 0;
    for(auto &v: a1) check_equality(v,data[index++]);


    //-------------------check const iterator-----------------------------
    const NumArray<ATYPE> &a = a1;

    index = 0;
    for(auto v: a) check_equality(v,data[index++]); 
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_multiindex_access()
{   
    typedef typename NumArray<ATYPE>::value_type value_type;
    typedef std::vector<size_t> stype;
    std::cout<<"void NumArrayTest<T,STORAGE>::test_multiindex_access()";
    std::cout<<std::endl;

    NumArray<ATYPE> a1(create_array<ATYPE>());
    auto s1 = a1.template shape<std::vector<size_t> >();
    auto data = RandomDistribution::uniform<std::vector<value_type> >(a1.size());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
        {
            CPPUNIT_ASSERT_NO_THROW(a1(i,j) = 
                    data[a1.template shape<stype>()[0]*i+j]);
        }
            

    for(size_t i=0;i<s1[0];i++)
        for(size_t j=0;j<s1[1];j++)
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(i,j),
                        data[a1.template shape<stype>()[0]*i+j]));

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(a1(index) = 
                    data[a1.template shape<stype>()[0]*i+j]);
        }
    }

    for(size_t i=0;i<s1[0];i++)
    {
        for(size_t j=0;j<s1[1];j++)
        {
            std::vector<size_t> index{i,j};
            CPPUNIT_ASSERT_NO_THROW(check_equality(a1(index),
                        data[a1.template shape<stype>()[0]*i+j]));
        }
    }

    //check some exceptions 
    CPPUNIT_ASSERT_THROW(a1(100,1),IndexError);
    CPPUNIT_ASSERT_THROW(a1(1,100),IndexError);
    CPPUNIT_ASSERT_THROW(a1(1),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(a1(1,2,4),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(a1(std::vector<size_t>{100,1}),IndexError);
    CPPUNIT_ASSERT_THROW(a1(std::vector<size_t>{1,100}),IndexError);
    CPPUNIT_ASSERT_THROW(a1(std::vector<size_t>{1}),ShapeMissmatchError);
    CPPUNIT_ASSERT_THROW(a1(std::vector<size_t>{1,100,3}),ShapeMissmatchError);
    
}

//------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_typeinfo()
{
    TypeID id1 = NumArray<ATYPE>::type_id;
    TypeID id2 = TypeIDMap<typename ATYPE::value_type>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}

//-------------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_unary_add()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(1));

    //add a scalar
    a += value_type(1);
    for(auto v: a) check_equality(v,value_type(2));

    //add a array
    NumArray<ATYPE> b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(3));

    a += b;
    for(auto v: a) check_equality(v,value_type(5));

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(10));
    a += c;
    for(auto v: a) check_equality(v,value_type(15));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_unary_sub()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(15));

    //add a scalar
    a -= value_type(1);
    for(auto v: a) check_equality(v,value_type(14));

    //add a array
    NumArray<ATYPE> b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(3));

    a -= b;
    for(auto v: a) check_equality(v,value_type(11));

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(10));
    a -= c;
    for(auto v: a) check_equality(v,value_type(1));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_unary_mult()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(1));

    //add a scalar
    a *= value_type(2);
    for(auto v: a) check_equality(v,value_type(2));

    //add a array
    NumArray<ATYPE> b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(3));

    a *= b;
    for(auto v: a) check_equality(v,value_type(6));

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(10));
    a *= c;
    for(auto v: a) check_equality(v,value_type(60));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_unary_div()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(12));

    //add a scalar
    a /= value_type(2);
    for(auto v: a) check_equality(v,value_type(12/2));

    //add a array
    NumArray<ATYPE> b(create_array<ATYPE>());
    std::fill(b.begin(),b.end(),value_type(2));

    a /= b;
    for(auto v: a) check_equality(v,value_type(12/2/2));

    //try an arbitary container
    std::vector<value_type> c(a.size());
    std::fill(c.begin(),c.end(),value_type(2));
    a /= c;
    for(auto v: a) check_equality(v,value_type(value_type(12)/value_type(2)/
                                  value_type(2)/value_type(2)));
}

//-----------------------------------------------------------------------------
template<typename ATYPE> void NumArrayTest<ATYPE>::test_view()
{
    typedef typename NumArray<ATYPE>::value_type value_type;
    NumArray<ATYPE> a(create_array<ATYPE>());

    //set initial value
    std::fill(a.begin(),a.end(),value_type(12));

    auto view = a(size_t(0),Slice(0,4));
}
