#include "AbstractBuffer.hpp"

namespace pni{
namespace utils{


//-----------------------------------------------------------------------------
AbstractBuffer::AbstractBuffer() {}

//-----------------------------------------------------------------------------
AbstractBuffer::AbstractBuffer(const AbstractBuffer &buffer) {}

//-----------------------------------------------------------------------------
AbstractBuffer::AbstractBuffer(AbstractBuffer &&buffer) {}

//-----------------------------------------------------------------------------
AbstractBuffer::~AbstractBuffer() {}

//-----------------------------------------------------------------------------
AbstractBuffer &AbstractBuffer::operator=(const AbstractBuffer &buffer)
{
    if(this == &buffer) return *this;

    return *this;
}

//-----------------------------------------------------------------------------
AbstractBuffer &AbstractBuffer::operator=(AbstractBuffer &&buffer)
{
    if(this == &buffer) return *this;

    return *this;
}

//end of namespace
}
}
