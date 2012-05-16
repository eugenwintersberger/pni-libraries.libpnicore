//unit test for the Buffer class

#ifndef __BUFFERTEST_HPP__
#define __BUFFERTEST_HPP__


#include<random>
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Buffer.hpp"
#include "NewAllocator.hpp"
#include "RefBuffer.hpp"
#include "TypeInfo.hpp"
#include "Types.hpp"

using namespace pni::utils;

template<typename CT,bool is_int,bool is_complex> class UniformDistribution;

//create integer data uniformly distributed
template<typename CT> class UniformDistribution<CT,true,false> 
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);
            
            std::mt19937_64 engine;
            std::uniform_int_distribution<> 
                dist(TypeInfo<value_type>::min(),TypeInfo<value_type>::max());

            for(value_type &v: container)
            {
                v = dist(engine);
            }

            return container;
        }
};

//create floating point uniform distribution
template<typename CT> class UniformDistribution<CT,false,false>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            CT container(n);
            
            std::mt19937_64 engine;
            std::uniform_real_distribution<> 
                dist(TypeInfo<Float32>::min(),TypeInfo<Float32>::max());

            for(value_type &v: container)
            {
                v = dist(engine);
            }

            return container;
        }
};

//create complex uniform distribution
template<typename CT> class UniformDistribution<CT,false,true>
{
    public:
        static CT create_data(size_t n)
        {
            typedef typename CT::value_type value_type;
            typedef typename value_type::value_type base_type;
            CT container(n);
            
            std::mt19937_64 engine;
            std::uniform_real_distribution<>
                dist(TypeInfo<Float32>::min(),
                     TypeInfo<Float32>::max());

            for(value_type &v: container)
            {
                v = value_type(dist(engine),dist(engine));
            }

            return container;
        }
};

class RandomDistribution
{
    public:
        template<typename CT> static CT uniform(size_t n)
        {
            return UniformDistribution<CT,
                                       TypeInfo<typename CT::value_type>::is_integer,
                                       TypeInfo<typename CT::value_type>::is_complex>
                                           ::create_data(n);
        }
};

template<typename T,bool is_int,bool is_complex> class EqualityCheck;

template<typename T> class EqualityCheck<T,true,false>
{
    public:
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT(a == b);
        }
};

template<typename T> class EqualityCheck<T,false,false>
{
    public:
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-8);
        }
};

template<typename T> class EqualityCheck<T,false,true>
{
    public:
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a.real(),b.real(),1.e-8);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a.imag(),b.imag(),1.e-8);
        }
};


template<typename T> void check_equality(const T &a,const T &b)
{
    EqualityCheck<T,TypeInfo<T>::is_integer,TypeInfo<T>::is_complex>::check(a,b);
}



//testing Buffer<T> and BufferObject concepts.
template<typename BTYPE> 
class BufferTest:public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BufferTest<BTYPE>);
    CPPUNIT_TEST(test_default_constructors);
    CPPUNIT_TEST(test_specific_constructors);
    CPPUNIT_TEST(test_allocation);
    CPPUNIT_TEST(test_access);
    CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_comparison);
    CPPUNIT_TEST(test_iterator);
    CPPUNIT_TEST_SUITE_END();
private:
    UInt64 n1,n2;

    //============private member functions===================================
    template<typename T,typename Allocator>
        void _allocate_buffer(Buffer<T,Allocator> &b,size_t n)
    {
        b =  Buffer<T,Allocator>(n);
    }


    //-------------------------------------------------------------------------
    template<typename T,typename Allocator>
        void _allocate_buffer(RefBuffer<T,Allocator> &b,size_t n)
    {
        b = RefBuffer<T,Allocator>(n,new T[n]);
    }


    //-------------------------------------------------------------------------
    template<typename T,typename Allocator>
        void _test_special_constructor(Buffer<T,Allocator> &b)
    {
        //test constructor with initializer list
        typedef T value_type;
        BTYPE ibuffer = {value_type(1),value_type(6),value_type(12)};
        CPPUNIT_ASSERT(ibuffer[0] == value_type(1));
        CPPUNIT_ASSERT(ibuffer[1] == value_type(6));
        CPPUNIT_ASSERT(ibuffer[2] == value_type(12));

        //test constructor with vector
        std::vector<typename BTYPE::value_type> vec = {3,9,1};
        BTYPE vbuffer = vec;
        CPPUNIT_ASSERT(vbuffer.is_allocated());
        CPPUNIT_ASSERT(vbuffer.size() == 3);
        CPPUNIT_ASSERT(vbuffer[0] == value_type(3));
        CPPUNIT_ASSERT(vbuffer[1] == value_type(9));
        CPPUNIT_ASSERT(vbuffer[2] == value_type(1));
    }

    template<typename T,typename Allocator>
        void _test_special_constructor(RefBuffer<T,Allocator> &b)
    {
    }

public:
    void setUp();
    void tearDown();

    void test_default_constructors();
    void test_specific_constructors();
    void test_assignment();
    void test_comparison();
    void test_allocation();
    void test_access();
    void test_iterator();

};

//-----------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::setUp()
{
    this->n1 = 1000;
    this->n2 = 2000;
}

//-----------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_default_constructors()
{
    //create first buffer using the default constructor
    BTYPE b1; //default constructor
    CPPUNIT_ASSERT(!b1.is_allocated());
    
    //create the second constructor with the standard constructor
    //allocating memory
    BTYPE b2;
    this->_allocate_buffer(b2,this->n2);
    CPPUNIT_ASSERT(b2.is_allocated());

    //using copy constructor
    BTYPE b3(b2);
    CPPUNIT_ASSERT(b2.is_allocated());
    CPPUNIT_ASSERT(b3.is_allocated());
    CPPUNIT_ASSERT(b3.size() == b2.size());

    //using the move constructor
    BTYPE b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.is_allocated());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.is_allocated());

}

//-----------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_specific_constructors()
{
    BTYPE ibuffer;

    this->_test_special_constructor(ibuffer);
}

//------------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_assignment()
{
	//testing here the assignment of equally typed buffers
	BTYPE buffer1;
	BTYPE buffer2;

	//check first for some standard problems
	//nothing happens - both are not allocated
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	//now the lhs is not allocated and the rhs is
    CPPUNIT_ASSERT_NO_THROW(this->_allocate_buffer(buffer2,this->n1));
    CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
    //now the rhs is not allocate dnad the lhs is
    CPPUNIT_ASSERT_NO_THROW(buffer1.free());
    CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);

    //booth buffers are allocated
	CPPUNIT_ASSERT_NO_THROW(this->_allocate_buffer(buffer2,this->n1));
	CPPUNIT_ASSERT_NO_THROW(this->_allocate_buffer(buffer1,this->n2));
    CPPUNIT_ASSERT(buffer1.size() != buffer2.size());
	//reallocation of the lhs
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	CPPUNIT_ASSERT(buffer1.is_allocated());
	CPPUNIT_ASSERT(buffer2.is_allocated());
    CPPUNIT_ASSERT(buffer1.size() == buffer2.size());

	BTYPE buffer3;
	CPPUNIT_ASSERT_NO_THROW(buffer3 = buffer1);
	CPPUNIT_ASSERT(buffer3.is_allocated());
	CPPUNIT_ASSERT(buffer1.is_allocated());
    CPPUNIT_ASSERT(buffer3.size() == buffer1.size());

	//checking move assignment - moveing an  allocated
    //buffer to an not allocated one
	BTYPE buffer4;
	CPPUNIT_ASSERT_NO_THROW(buffer4 = std::move(buffer3));
	CPPUNIT_ASSERT(buffer4.is_allocated());
	CPPUNIT_ASSERT(!buffer3.is_allocated());
	CPPUNIT_ASSERT(buffer4.size() == buffer1.size());

    //buffer3 is not allocated now - moving a not allocated buffer to an
    //allocated one
    CPPUNIT_ASSERT_NO_THROW(buffer4 = std::move(buffer3));
    CPPUNIT_ASSERT(!buffer4.is_allocated());
    CPPUNIT_ASSERT(!buffer3.is_allocated());
    CPPUNIT_ASSERT(buffer4.size() == 0);
    CPPUNIT_ASSERT(buffer3.size() == 0);

}

//------------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_allocation()
{
	BTYPE dbuffer;
    this->_allocate_buffer(dbuffer,this->n1);

	CPPUNIT_ASSERT(dbuffer.is_allocated());
	CPPUNIT_ASSERT(dbuffer.size() == this->n1);

	CPPUNIT_ASSERT_NO_THROW(dbuffer.free());
	CPPUNIT_ASSERT(dbuffer.size()==0);
	CPPUNIT_ASSERT(!dbuffer.is_allocated());

	BTYPE dbuffer2;
	CPPUNIT_ASSERT(dbuffer2.size() == 0);
	CPPUNIT_ASSERT(!dbuffer2.is_allocated());

	CPPUNIT_ASSERT_NO_THROW(this->_allocate_buffer(dbuffer2,n2));
	CPPUNIT_ASSERT(dbuffer2.is_allocated());
	CPPUNIT_ASSERT(dbuffer2.size() == n2);

}

//------------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_access()
{
    typedef typename BTYPE::value_type value_type;
	BTYPE dbuffer;
    this->_allocate_buffer(dbuffer,1000);

	for(size_t i=0;i<1000;i++) dbuffer[i] = typename BTYPE::value_type(i);

	for(size_t i=0;i<1000;i++){
		CPPUNIT_ASSERT((typename BTYPE::value_type(i))==dbuffer[i]);
	}

    BTYPE ibuffer;
    this->_allocate_buffer(ibuffer,4);
    for(size_t i=0;i<ibuffer.size();i++)
        ibuffer.at(i) = value_type(i);

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == value_type(i));

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(100),IndexError);

}

//------------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_comparison()
{
	BTYPE b1;
    this->_allocate_buffer(b1,100);
	BTYPE b2;
    this->_allocate_buffer(b2,100);

	b1 = typename BTYPE::value_type(1);
	b2 = typename BTYPE::value_type(2);

	CPPUNIT_ASSERT(b1 != b2);
	b2 = typename BTYPE::value_type(1);
	CPPUNIT_ASSERT(b1 == b2);
}

//-----------------------------------------------------------------------------
template<typename BTYPE> void BufferTest<BTYPE>::test_iterator()
{
    std::cout<<"void BufferTest<BTYPE>::test_iterator()----------------------";
    std::cout<<std::endl;
    BTYPE b1;
    typedef typename BTYPE::value_type value_type;
    this->_allocate_buffer(b1,1000);

    auto data = RandomDistribution::uniform<std::vector<value_type> >(1000);
   
    size_t index = 0;
    std::cout<<"writing data to buffer ..."<<std::endl;
    for(value_type &v: b1)
    {
        v = data[index];
        index ++;
    }

    //read data back
    index = 0;
    std::cout<<"reading data from buffer ..."<<std::endl;
    for(auto v: b1)
    {
        check_equality(v,data[index]);
        index ++;
    }

}

#endif
