#ifndef __POINTERBENCHMARK_HPP__
#define __POINTERBENCHMARK_HPP__

#include "IOBenchmark.hpp"

template<typename T>
class PointerBenchmark:public IOBenchmark
{
    private:
        //! pointer to allocated memory
        T *_ptr;
        //! number of elements
        size_t _size;
    public:
        PointerBenchmark():
            IOBenchmark(),
            _ptr(nullptr),
            _size(0)
        {}

        PointerBenchmark(size_t size):
            IOBenchmark(),
            _ptr(new T[size]),
            _size(size)
        {}

        virtual ~PointerBenchmark();

        virtual void write_cycle();

        virtual void read_cycle();
};

template<typename T> PointerBenchmark::~PointerBenchmark()
{
    if(_ptr) delete [] _ptr;
    _ptr = 0;
    _size = 0;
}

template<typename T> void PointerBenchmark::write_cycle()
{
    for(size_t i=0;i<_size;i++)
        _ptr[i] = T(i);
}

template<typename T> void PointerBenchmark::read_cycle()
{
    T value;
    for(size_t i=0;i<_size;i++)
        value += _ptr[i];
}
#endif
