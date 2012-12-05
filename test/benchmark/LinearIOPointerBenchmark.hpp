/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Oct 25, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <typeinfo>
#include <pni/utils/service.hpp>
#include "../../src/Types.hpp"

using namespace pni::utils;

template<typename T> class LinearIOPointerBenchmark
{
    private:
        size_t _size; //!< number of element allocated for the benchmark
        T *_ptr;      //!< pointer to allocated memory
        T _result;    //!< temporary result 
    public:
        //=================constructor and destructor==========================
        /*!
        \brief constructor

        Constructor for the benchmark. It allocates a pointer of type T to a
        memory region for n elements.
        \param n number of elements 
        */
        LinearIOPointerBenchmark(size_t n):
            _size(n),
            _ptr(new T[n]),
            _result(0)
        {}

        //---------------------------------------------------------------------
        //! move constructor
        LinearIOPointerBenchmark(LinearIOPointerBenchmark<T> &&bm):
            _size(bm._size),
            _ptr(bm._ptr),
            _result(bm._result)
        {
            bm._size = 0;
            bm._ptr = nullptr;
            bm._result = T(0);
        }

        //---------------------------------------------------------------------
        //! copy constructor
        LinearIOPointerBenchmark(const LinearIOPointerBenchmark<T> &bm):
            _size(bm._size),
            _ptr(new T[_size]),
            _result(bm._result)
        {
            for(size_t i=0;i<_size;++i) _ptr[i] = bm._ptr[i];
        }

        //---------------------------------------------------------------------
        /*!
        \brief destructor

        Frees the memory allocated by the constructor.
        */
        ~LinearIOPointerBenchmark()
        {
            if(_ptr) delete [] _ptr;
            _ptr = nullptr;
        }

        //====================assignment operators=============================
        //! copy assignment operator
        LinearIOPointerBenchmark<T> &operator=(const LinearIOPointerBenchmark<T> &bm)
        {
            if(this == &bm) return *this;

            if(_ptr) delete [] _ptr;

            _size = bm._size;
            _ptr = new T[_size];
            for(size_t i=0;i<_size;++i) _ptr[i] = bm._ptr[i];
            _result = bm._result;
            return *this;
        }

        //---------------------------------------------------------------------
        //! move assignment operator
        LinearIOPointerBenchmark<T> &operator=(LinearIOPointerBenchmark<T> &&bm)
        {
            if(this == &bm) return *this;

            if(_ptr) delete [] _ptr;

            _size = bm._size; bm._size = 0;
            _ptr  = bm._ptr;  bm._ptr = nullptr;
            _result = bm._reslt; bm._result = T(0);
            return *this;
        }

        //=======================public member functions=======================
        /*!
        \brief write benchmark

        Benchmark the IO performance by writing data to all the elements of the
        allocated memory region. 
        */
        void write_data()
        {
            T index(0);
            for(size_t i=0;i<_size;i++) _ptr[i] = index++;
        }

        //---------------------------------------------------------------------
        /*!
        \brief read benchmark

        Benchmark read performance by reading data from all the elements in the
        allocated memory region. 
        */
        void read_data()
        {
            _result = T(0);
            for(size_t i=0;i<_size;i++) _result += _ptr[i];
        }

        //-----------------------------------------------------------------
        //! get benchmark name
        String name() const
        {
            return "Linear IO (Pointer) "+demangle_cpp_name(typeid(T*).name());
        }
};
