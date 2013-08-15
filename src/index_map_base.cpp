/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jul 19, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/core/index_map_base.hpp>

namespace pni{
namespace core{

    void index_map_base::_size_update()
    {
        size_t tmp = 0;
        for(size_t i=0;i<_shape.size();++i)
        {
            if(i==0) tmp = _shape[i];
            else tmp *= _shape[i];
        }

        _size = tmp;
    }

    //-------------------------------------------------------------------------
    index_map_base::index_map_base():_shape(),_size(0) {}

    //-------------------------------------------------------------------------
    index_map_base::index_map_base(const index_map_base &m):
        _shape(m._shape),
        _size(m._size)
    {}

    //-------------------------------------------------------------------------
    index_map_base::index_map_base(index_map_base &&m):
        _shape(std::move(m._shape)),
        _size(std::move(m._size))
    {}
    //-------------------------------------------------------------------------
    index_map_base &index_map_base::operator=(const index_map_base &m)
    {
        if(this == &m) return *this;

        _shape = m._shape;
        _size = m._size;
        return *this;
    }

    //-------------------------------------------------------------------------
    index_map_base &index_map_base::operator=(index_map_base &&m)
    {
        if(this == &m) return *this;
        _shape = std::move(m._shape);
        _size = m._size;
        m._size = 0;
        return *this;
    }


    //--------------------------------------------------------------------------
    size_t index_map_base::rank() const
    {
        if(_shape.size() == 0) return 0;
        return _shape.size();
    }

//end of namespace
}
}
