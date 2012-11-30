#ifndef __BUFFERHOLDER_HPP__
#define __BUFFERHOLDER_HPP__

#include "AbstractBuffer.hpp"

namespace pni{
namespace utils{
    
    template<typename BTYPE> class BufferHolder : public AbstractBuffer
    {
        private:
            BTYPE _buffer;
        public:
            //=================constructors and destructor=====================
            BufferHolder():
                AbstractBuffer(),
                _buffer()
            {}

            //-----------------------------------------------------------------
            BufferHolder(const BufferHolder<BTYPE> &buffer):
                AbstractBuffer(),
                _buffer(buffer._buffer)
            {}

            //-----------------------------------------------------------------
            BufferHolder(BufferHolder<BTYPE> &&buffer):
                AbstractBuffer(),
                _buffer(std::move(buffer._buffer))
            {}

            //-----------------------------------------------------------------
            BufferHolder(const BTYPE &buffer):
                AbstractBuffer(),
                _buffer(buffer)
            {}

            //-----------------------------------------------------------------
            BufferHolder(BTYPE &&buffer):
                AbstractBuffer(),
                _buffer(std::move(buffer))
            {}

            //-----------------------------------------------------------------
            ~BufferHolder() {}

            //=========================assignment operators====================
            BufferHolder<BTYPE> &operator=(const BufferHolder<BTYPE> &o)
            {
                if(this == &o) return *this;
                _buffer = o._buffer;
                return *this;

            }

            //-----------------------------------------------------------------
            BufferHolder<BTYPE> &operator=(BufferHolder<BTYPE> &&o)
            {
                if(this == &o) return *this;
                _buffer = std::move(o._buffer);
                return *this;
            }

            //=======================public member functions===================
            virtual size_t size() const 
            {
                return _buffer.size();
            }

            virtual const void *ptr() const
            {
                return _buffer.ptr();
            }

            virtual TypeID type_id() const
            {
                return BTYPE::type_id;
            }

    };


}
};

#endif
