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
 *  Created on: Nov 30, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

using namespace pni::utils;

template<typename T> class MultiIndexIOPointer
{
    private:
        T *_ptr;
        size_t _nx;
        size_t _ny;
        T _result;
    public:
        //==================construtors========================================
        MultiIndexIOPointer(size_t nx,size_t ny):
            _ptr(new T[nx*ny]),
            _nx(nx),
            _ny(ny),
            _result(0)
        { }

        //---------------------------------------------------------------------
        MultiIndexIOPointer(const MultiIndexIOPointer<T> &mip):
            _ptr(new T[mip._nx*mip._ny]),
            _nx(mip._nx),
            _ny(mip._ny),
            _result(mip._result)
        {
            for(size_t i=0;i<_nx*_ny;++i) _ptr[i] = mip._ptr[i]; 
        }

        //---------------------------------------------------------------------
        MultiIndexIOPointer(MultiIndexIOPointer<T> &&mip):
            _ptr(mip._ptr),
            _nx(mip._nx),
            _ny(mip._ny),
            _result(mip._result)
        {
            mip._ptr = nullptr;
            mip._nx = 0;
            mip._ny = 0;
        }

        //---------------------------------------------------------------------
        ~MultiIndexIOPointer()
        {
            if(_ptr) delete [] _ptr;
        }

        //=====================assignment operators============================
        MultiIndexIOPointer<T> &operator=(const MultiIndexIOPointer<T> &mip)
        {
            if(this == &mip) return *this;

            if(_ptr) delete [] _ptr;

            _nx = mip._nx;
            _ny = mip._ny;
            _ptr = new T[_nx*_ny];
            _result = mip._result;

            return *this;
        }

        MultiIndexIOPointer<T> &operator=(MultiIndexIOPointer<T> &&mip)
        {
            if(this == &mip) return *this;

            _ptr = mip._ptr;
            mip._ptr = nullptr;
            _nx  = mip._nx;
            mip._nx = 0;
            _ny  = mip._ny;
            mip._ny = 0;
            _result = mip._result;

            return *this;
        }

        //================public member functions==============================
        void write_data()
        {
            T index(0);

            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _ptr[i*_ny+j] = index++;

        }

        //---------------------------------------------------------------------
        void read_data()
        {
            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _result += _ptr[i*_ny+j];
        }


        //---------------------------------------------------------------------
        String name() const
        {
            return String("Linear IO DBuffer template benchmark");
        }
            
};
