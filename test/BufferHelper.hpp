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
 *  Created on: May 22, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/DBuffer.hpp>
#include <pni/core/RBuffer.hpp>
#include <pni/core/NewAllocator.hpp>

using namespace pni::core;

//-----------------------------------------------------------------------------
template<typename T,typename Allocator>
    void allocate_buffer(DBuffer<T,Allocator> &b,size_t n)
{
    b =  DBuffer<T,Allocator>(n);
}


//-----------------------------------------------------------------------------
template<typename T>
    void allocate_buffer(RBuffer<T> &b,size_t n)
{
    b = RBuffer<T>(n,new T[n]);
}
