//unit test for the Buffer class

#ifndef __LIBPNIUTILS_BUFFER_HPP__
#define __LIBPNIUTILS_BUFFER_HPP__



#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "Buffer.hpp"
#include "Types.hpp"

using namespace pni::utils;

//testing Buffer<T> and BufferObject concepts.
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
class BufferTest : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(BufferTest<T,BTYPE,ALLOCATOR>);
        CPPUNIT_TEST(test_default_constructors);
        CPPUNIT_TEST(test_specific_constructors);
        CPPUNIT_TEST(test_allocation);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_comparison);
        CPPUNIT_TEST_SUITE_END();
    private:
        UInt64 n1,n2;
    public:
        void setUp();
        void tearDown();

        void test_default_constructors();
        void test_specific_constructors();
        void test_assignment();
        void test_comparison();
        void test_allocation();
        void test_access();

};

//-----------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::setUp()
{
    this->n1 = 1000;
    this->n2 = 2000;
}

//-----------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::test_default_constructors()
{
    //create first buffer using the default constructor
    BTYPE<T,ALLOCATOR> b1; //default constructor
    CPPUNIT_ASSERT(!b1.is_allocated());
    
    //create the second constructor with the standard constructor
    //allocating memory
    BTYPE<T,ALLOCATOR> b2(n2);
    CPPUNIT_ASSERT(b2.is_allocated());

    //using copy constructor
    BTYPE<T,ALLOCATOR> b3(b2);
    CPPUNIT_ASSERT(b2.is_allocated());
    CPPUNIT_ASSERT(b3.is_allocated());
    CPPUNIT_ASSERT(b3.size() == b2.size());

    //using the move constructor
    BTYPE<T,ALLOCATOR> b4 = std::move(b2);
    CPPUNIT_ASSERT(b4.is_allocated());
    CPPUNIT_ASSERT(b4.size() == b3.size());
    CPPUNIT_ASSERT(!b2.is_allocated());

}

//-----------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::test_specific_constructors()
{
    
    //test constructor with initializer list
    BTYPE<T,ALLOCATOR> ibuffer = {1,-6,12};
    CPPUNIT_ASSERT(ibuffer[0] == 1);
    CPPUNIT_ASSERT(ibuffer[1] == -6);
    CPPUNIT_ASSERT(ibuffer[2] == 12);

    //test constructor with vector
    std::vector<T> vec = {3,9,1};
    BTYPE<T,ALLOCATOR> vbuffer = vec;
    CPPUNIT_ASSERT(vbuffer.is_allocated());
    CPPUNIT_ASSERT(vbuffer.size() == 3);
    CPPUNIT_ASSERT(vbuffer[0] == 3);
    CPPUNIT_ASSERT(vbuffer[1] == 9);
    CPPUNIT_ASSERT(vbuffer[2] == 1);
}

//------------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::test_assignment(){
	//testing here the assignment of equally typed buffers
	BTYPE<T,ALLOCATOR> buffer1;
	BTYPE<T,ALLOCATOR> buffer2;

	//check first for some standard problems
	//nothing happens - both are not allocated
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	//now the lhs is not allocated and the rhs is
    CPPUNIT_ASSERT_NO_THROW(buffer2.allocate(this->n1));
    CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
    //now the rhs is not allocate dnad the lhs is
    CPPUNIT_ASSERT_NO_THROW(buffer1.free());
    CPPUNIT_ASSERT_NO_THROW(buffer2 = buffer1);

    //booth buffers are allocated
	CPPUNIT_ASSERT_NO_THROW(buffer2.allocate(this->n1));
	CPPUNIT_ASSERT_NO_THROW(buffer1.allocate(this->n2));
    CPPUNIT_ASSERT(buffer1.size() != buffer2.size());
	//reallocation of the lhs
	CPPUNIT_ASSERT_NO_THROW(buffer1 = buffer2);
	CPPUNIT_ASSERT(buffer1.is_allocated());
	CPPUNIT_ASSERT(buffer2.is_allocated());
    CPPUNIT_ASSERT(buffer1.size() == buffer2.size());

	BTYPE<T,ALLOCATOR> buffer3;
	CPPUNIT_ASSERT_NO_THROW(buffer3 = buffer1);
	CPPUNIT_ASSERT(buffer3.is_allocated());
	CPPUNIT_ASSERT(buffer1.is_allocated());
    CPPUNIT_ASSERT(buffer3.size() == buffer1.size());

	//checking move assignment - moveing an  allocated
    //buffer to an not allocated one
	BTYPE<T,ALLOCATOR> buffer4;
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
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::test_allocation(){
	BTYPE<T,ALLOCATOR> dbuffer(this->n1);

	CPPUNIT_ASSERT(dbuffer.is_allocated());
	CPPUNIT_ASSERT(dbuffer.size() == this->n1);

	CPPUNIT_ASSERT_NO_THROW(dbuffer.free());
	CPPUNIT_ASSERT(dbuffer.size()==0);
	CPPUNIT_ASSERT(!dbuffer.is_allocated());

	BTYPE<T,ALLOCATOR> dbuffer2;
	CPPUNIT_ASSERT(dbuffer2.size() == 0);
	CPPUNIT_ASSERT(!dbuffer2.is_allocated());

	CPPUNIT_ASSERT_NO_THROW(dbuffer2.allocate(n2));
	CPPUNIT_ASSERT(dbuffer2.is_allocated());
	CPPUNIT_ASSERT(dbuffer2.size() == n2);

}

//------------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::test_access(){
	BTYPE<T,ALLOCATOR> dbuffer(1000);

	for(size_t i=0;i<1000;i++) dbuffer[i] = (T)i;

	for(size_t i=0;i<1000;i++){
		CPPUNIT_ASSERT(((T)i)==dbuffer[i]);
	}

    BTYPE<T,ALLOCATOR> ibuffer(4);
    for(size_t i=0;i<ibuffer.size();i++)
        ibuffer.at(i) = i;

    for(size_t i=0;i<ibuffer.size();i++)
        CPPUNIT_ASSERT(ibuffer.at(i) == i);

    //check for IndexError exception
    CPPUNIT_ASSERT_THROW(ibuffer.at(100),IndexError);

}

//------------------------------------------------------------------------------
template<typename T,template<typename,typename> class BTYPE,typename ALLOCATOR> 
void BufferTest<T,BTYPE,ALLOCATOR>::test_comparison(){
	BTYPE<T,ALLOCATOR> b1(100);
	BTYPE<T,ALLOCATOR> b2(100);
	b1 = T(1);
	b2 = T(2);

	CPPUNIT_ASSERT(b1 != b2);
	b2 = T(1);
	CPPUNIT_ASSERT(b1 == b2);
}

#endif
