#include "BufferTest.hpp"

#include <pni/utils/DBuffer.hpp>
#include <pni/utils/SBuffer.hpp>

//-----------------------------------------------------------------------------
void BufferTest::setUp() { }

//-----------------------------------------------------------------------------
void BufferTest::tearDown() { }

//-----------------------------------------------------------------------------
void BufferTest::test_construction()
{
    DBuffer<Float64> db64(100);
    SBuffer<UInt64,20> sb64;

    Buffer buffer1;
    Buffer buffer2(std::move(db64));
    CPPUNIT_ASSERT(buffer2.size() == db64.size());
    CPPUNIT_ASSERT(buffer2.type_id() == DBuffer<Float64>::type_id);

    Buffer buffer3(db64);
    CPPUNIT_ASSERT(buffer3.size() == db64.size());

    db64[0] = 100.;
    std::cout<<db64[0]<<std::endl;



}

//-----------------------------------------------------------------------------
void BufferTest::test_assignment()
{

}

//-----------------------------------------------------------------------------
void BufferTest::test_size()
{

}

//-----------------------------------------------------------------------------
void BufferTest::test_ptr()
{

}

//-----------------------------------------------------------------------------
void BufferTest::test_typeid()
{
}
