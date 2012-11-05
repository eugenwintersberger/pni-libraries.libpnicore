#include "BufferTest.hpp"

#include "DBuffer.hpp"
#include "SBuffer.hpp"

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
    Buffer buffer2;
    buffer  = db64;
    CPPUNIT_ASSERT(buffer2.size() == db64.size());
    CPPUNIT_ASSERT(buffer2.type_id() == DBuffer<Float64>::type_id);

    Buffer buffer3;
    buffer3 = sb64;


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
