/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Implementation of the IndexMap class. This class provides methods for easily
 * compute indices from multidimensional arrays.
 *
 * Created on: March 9, 2012
 *     Author: Eugen Wintersberger
 *
 */

#include "IndexMap.hpp"


namespace pni{
    namespace utils{
        //==========Implementation of constructors and destructor==============
        //implementation of the default constructor
        IndexMap::IndexMap():
            _offset(),
            _stride(),
            _count()
        { }

        //---------------------------------------------------------------------
        //implementation of the copy constructor
        IndexMap::IndexMap(const IndexMap &o):
            _offset(o._offset),
            _stride(o._stride),
            _count(o._count)
        {}

        //---------------------------------------------------------------------
        //implementation of the move constructor
        IndexMap::IndexMap(IndexMap &&o):
            _offset(std::move(o._offset)),
            _stride(std::move(o._stride)),
            _count(std::move(o._count))
        {}
        
        //---------------------------------------------------------------------
        //first standard constructor
        IndexMap::IndexMap(size_t rank):
            _offset(rank),
            _stride(rank),
            _count(rank)
        {}

        //---------------------------------------------------------------------
        //implementation of second standard constructor
        IndexMap::IndexMap(const Buffer<ssize_t> &o,const Buffer<ssize_t> &s,
                           const Buffer<ssize_t> &c):
            _offset(o),
            _stride(s),
            _count(c)
        { }

        //---------------------------------------------------------------------
        //implementation of the destructor
        IndexMap::~IndexMap()
        {
            _offset.free();
            _count.free();
            _stride.free();
        }

        //================implementation of assignment operators===============
        //implementation of copy assignment
        IndexMap &operator=(const IndexMap &o)
        {
            if(this != &o)
            {
                _offset = o._offset;
                _stride = o._stride;
                _count  = o._count;
            }
            return *this;
        }

        //---------------------------------------------------------------------
        //implementation of move assignment
        IndexMap &operator=(IndexMap &&o)
        {
            if(this != &o)
            {
                _offset = std::move(o._offset);
                _stride = std::move(o._stride);
                _count  = std::move(o._count);
            }
            return *this;
        }



    //end of namespace
    }
}
