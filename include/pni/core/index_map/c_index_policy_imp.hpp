
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
#include <numeric>
#include <algorithm>
#include <functional>

#include "../exceptions.hpp"
#include "../exception_utils.hpp"

namespace pni{
namespace core{

    class c_index_policy_imp
    {
        private:
            /*!
            \brief compute the offset 

            Compute the offset for an index range and a given shape.
            \tparam IITERT index iterator type
            \tparam SITERT shape iterator type
            \param index_start start iterator for the index range
            \param index_top   stop iterator for the index range
            \param shape_start start iterator for the shape range
            \return offset value
            */
            template<typename IITERT,
                     typename SITERT> 
            static size_t offset(IITERT &&index_start,
                                 IITERT &&index_stop, 
                                 SITERT &&shape_start)
            {
                size_t offset = *index_start++,stride=1;

                while(index_start!=index_stop)
                {
                    stride *= *shape_start++;
                    offset += stride*(*index_start++);
                }

                return offset;
            }

            //------------------------------------------------------------------
            /*!
            \brief compute the index

            */
            template<typename IITERT,
                     typename SITERT>
            static void index(SITERT &&shape_start,
                              SITERT &&shape_stop,
                              IITERT &&index_start,
                              size_t offset)
            {
                size_t stride,t;
                while(shape_start != shape_stop)
                {
                    //increment here the shape_start iterator - we already start
                    //with start+1 with the stride computation
                    stride = std::accumulate(++shape_start,shape_stop,1,
                                             std::multiplies<size_t>());
                    t = offset%stride;
                    *(index_start++) = (offset-t)/stride;
                    offset = t;
                }
            }
        public:

            //-----------------------------------------------------------------
            template<typename CSHAPE,
                     typename CINDEX
                    >
            static size_t offset(CSHAPE &&shape,CINDEX &&index)
            {
                return offset(index.rbegin(),index.rend(),shape.rbegin());
            }

            //-----------------------------------------------------------------
            template<typename CINDEX,
                     typename CSHAPE
                    >
            static void index(CSHAPE &&shape,CINDEX &&idx,size_t offset)
            {
                index(shape.begin(),shape.end(),idx.begin(),offset); 
            }



    };
//end of namespace
}
}
