#include "Buffer.hpp"

namespace pni{
namespace utils{

    //-------------------------------------------------------------------------
    Buffer::Buffer(const Buffer &buffer):_ptr(buffer._ptr)
    {}

    //-------------------------------------------------------------------------
    Buffer::Buffer(Buffer &&buffer):_ptr(buffer._ptr)
    {
        buffer._ptr = nullptr;
    }

    //-------------------------------------------------------------------------
    Buffer &Buffer::operator=(const Buffer &buffer)
    {
        if(this == &buffer) return *this;

        if(_ptr) delete _ptr;

        _ptr = buffer._ptr;

        return *this;
    }

    //-------------------------------------------------------------------------
    Buffer &Buffer::operator=(Buffer &&buffer)
    {
        if(this == &buffer) return *this;

        if(_ptr) delete _ptr;

        _ptr = buffer._ptr;
        buffer._ptr = nullptr;

        return *this;
    }

    //-------------------------------------------------------------------------
    size_t Buffer::size() const
    {
        return _ptr->size(); 
    }

    //-------------------------------------------------------------------------
    const void *Buffer::ptr() const
    {
        return _ptr->ptr();
    }

    //-------------------------------------------------------------------------
    TypeID Buffer::type_id() const
    {
        return _ptr->type_id();
    }


//end of namespace
}
}
