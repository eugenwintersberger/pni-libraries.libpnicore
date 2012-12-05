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
