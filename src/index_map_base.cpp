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

#include "index_map_base.hpp"

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    index_map_base::index_map_base():_shape() {}

    //-------------------------------------------------------------------------
    index_map_base::index_map_base(const index_map_base &m):
        _shape(m._shape)
    {}

    //-------------------------------------------------------------------------
    index_map_base::index_map_base(index_map_base &&m):
        _shape(std::move(m._shape))
    {}
    //-------------------------------------------------------------------------
    index_map_base &index_map_base::operator=(const index_map_base &m)
    {
        if(this == &m) return *this;

        _shape = m._shape;
        return *this;
    }

    //-------------------------------------------------------------------------
    index_map_base &index_map_base::operator=(index_map_base &&m)
    {
        if(this == &m) return *this;
        _shape = std::move(m._shape);
        return *this;
    }

    //--------------------------------------------------------------------------
    size_t index_map_base::size() const
    {
        //return 0 if the map is not initialized
        if(_shape.size() == 0) return 0;

        size_t s = 1;
#ifdef NOFOREACH
        for(auto iter = _shape.begin();iter!=_shape.end();++iter)
        {
            auto v = *iter;
#else
        for(auto v: _shape)
        {
#endif
            s*=v;
        }
        return s;
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
