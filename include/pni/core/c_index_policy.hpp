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
 * Created on: Oct 20, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include "exceptions.hpp"
#include "exception_utils.hpp"

namespace pni{
namespace core{
    
    /*!
    \ingroup index_mapping_classes
    \brief policy for C-order index computation

    */
    struct c_index_policy
    {
        template<typename IITERT,typename SITERT> static
        size_t compute(IITERT &&index_start,IITERT &&index_stop,SITERT &&shape_start)
        {
            size_t offset = *index_start++,stride=1;

            while(index_start!=index_stop)
            {
                stride *= *shape_start++;
                offset += stride*(*index_start++);
            }

            return offset;
        }

        //---------------------------------------------------------------------
        /*!
        \brief compute the offset

        */
        template<typename CSHAPE,typename CINDEX> 
        static size_t offset(const CSHAPE &shape,const CINDEX &index)
        {
            return compute(index.rbegin(),index.rend(),shape.rbegin());
        }

        //---------------------------------------------------------------------
        template<typename CSHAPE,size_t N,typename T>
        static size_t offset(const CSHAPE &shape,std::array<T,N> indexes)
        {
            return compute(indexes.rbegin(),indexes.rend(),shape.rbegin());
        }
     
        //---------------------------------------------------------------------
        /*!
        \brief compute the offset

        This is most probably the fastest method to compute the offset. Here
        both, indexes and shape are passed by value as static arrays. 
        */
        template<size_t N,typename T> 
        static size_t offset(std::array<T,N> shape,std::array<T,N> indexes)
        {
            return compute(indexes.rbegin(),indexes.rend(),shape.rbegin());
        }

        //---------------------------------------------------------------------
        template<typename CINDEX> static CINDEX index(size_t offset)
        {

        }
    };



//end of namespace
}
}
