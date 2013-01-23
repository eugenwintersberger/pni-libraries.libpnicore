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
 * Created on: Jul 20, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "cindex_map.hpp"

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    void cindex_map::_compute_strides()
    {
        const DBuffer<size_t> &s = shape();

        for(ssize_t i=_strides.size()-1;i>=0;i--)
        {
            if(i==(ssize_t)_strides.size()-1)
                _strides[(size_t)i] = 1;
            else
                _strides[(size_t)i] = _strides[(size_t)i+1]*s[(size_t)i+1];
        }

    }

//end of namespace
}
}
