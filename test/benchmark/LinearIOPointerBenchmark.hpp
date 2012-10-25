#ifndef __LINEARIOPOINTERBENCHMARK_HPP__
#define __LINEARIOPOINTERBENCHMARK_HPP__

#include "../../src/Types.hpp"

using namespace pni::utils;

template<typename T> class LinearIOPointerBenchmark
{
    private:
        size_t _size; //!< number of element allocated for the benchmark
        T *_ptr;      //!< pointer to allocated memory
        T _result;    //!< temporary result 
    public:
        //=================constructor and destructor======================
        LinearIOPointerBenchmark(size_t n):
            _size(n),
            _ptr(new T[n]),
            _result(0)
        {}

        //=======================public member functions===================
        void write_data()
        {
            T index(0);
            for(size_t i=0;i<_size;i++) _ptr[i] = index++;
        }

        //-----------------------------------------------------------------
        void read_data()
        {
            _result = T(0);
            for(size_t i=0;i<_size;i++) _result += _ptr[i];
        }

        //-----------------------------------------------------------------
        String name() const
        {
            return "Linear IO Pointer benchmark";
        }
};

#endif
