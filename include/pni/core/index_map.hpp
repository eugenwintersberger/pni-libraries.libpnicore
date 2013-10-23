/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Oct 22, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <algorithm>
#include <numeric>

namespace pni{
namespace core{

    template<typename SHAPE_STORE,typename MAP_POL> class index_map
    {
        private:
            SHAPE_STORE _shape;
        public:
            //===================public data types=============================
            typedef SHAPE_STORE storage_type;
            typedef MAP_POL     policy_type;
            typedef storage_type::const_iterator const_iterator;

            template<typename... CARGS>
            index_map(CARGS ...args):_shape(args...)
            {}

            //-----------------------------------------------------------------
            size_t size() const
            {
                return std::accumulate(_shape.begin(),_shape.end(),
                                       std::mult(),1); 
            }

            //-----------------------------------------------------------------
            size_t rank() const
            {
                return _shape.size();
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> 
            size_t offset(const CTYPE &index) const
            {
                return MAP_POL::template offset(_shape,index);
            }

            //-----------------------------------------------------------------
            template<typename T,size_t N> 
            size_t offset(std::array<T,N> index) const
            {
                return MAP_POL::template offset(_shape,index);
            }

            //-----------------------------------------------------------------
            template<typename T> 
            size_t offset(std::initializer_list<T> index) const
            {
                return MAP_POL::template offset(_shape,index);
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> CTYPE index(size_t offset) const
            {
                return MAP_POL::template index<CTYPE>(_shape,offset);
            }

            //-----------------------------------------------------------------
            const_iterator begin() const
            {
                return _shape.begin();
            }

            //-----------------------------------------------------------------
            const_iterator end() const
            {
                return _shape.end();
            }

            //-----------------------------------------------------------------
            const

            

    };
//end of namespace
}
}
