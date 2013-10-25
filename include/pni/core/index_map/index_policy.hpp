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
    
    /*!
    \ingroup index_mapping_classes
    \brief general policy for index computation

    This is the master template for managing index policies 
    Like any index policy this policy has to implement a function to compute the
    offset which will typically have the signature

    \code
    template<typename SCTYPE,typename ICTYPE> 
    size_t offset(const SCTYPE &shape,const ICTYPE &index);
    \endcode

    and a static member function to compute the index for a given offset with
    the signature

    \code 
    template<typename ICTYPE,typename SCTYPE> 
    CTYPE index(const SCTYPE &shape,size_t offset);
    \endcode

    For performance reasons specializations of these methods can be provided for
    different containers. 
    
    \tparam POLIMP policy implementation
    */
    template<typename POLIMP> class index_policy
    {
        private:

            //-----------------------------------------------------------------
            template<typename CTYPE>
            static void allocate_index(CTYPE &c,size_t size)
            {
                c = CTYPE(size);
            }

            //-----------------------------------------------------------------
            template<typename T,size_t N>
            static void allocate_index(std::array<T,N> &c,size_t size)
            {
                //do nothing here
            }

        public:

            //------------------------------------------------------------------
            /*!
            \brief compute the offset

            This is the default variant of the offset calculator. The shape as
            well as the index container are passed as const references. Though
            being rather general this method is also the slowest (this is due to
            the required dereferencing of the containers).

            A typical application would look like this
            \code
            std::vector<size_t> shape{3,3};
            std::vector<size_t> index{2,1};

            size_t c_index_policy::offset(shape,index);
            \endcode

            \tparam CSHAPE container type for the shape
            \tparam CINDEX container type for the index
            \param shape container with shape
            \param index container with index values
            \return offset value
            */
            template<typename CSHAPE,typename CINDEX> 
            static size_t offset(const CSHAPE &shape,CINDEX &&index)
            {
                return POLIMP::offset(shape,
                                      std::forward<
                                      typename std::remove_const<CINDEX>::type
                                      >(index));
            }



            //------------------------------------------------------------------
            /*!
            \brief compute the offset

            Typically we cannot move the container holding the shape as it is
            the primary data object in an index mape. However, in the case of
            std::array it would be feasible to pass the container by value
            rather than by reference. This particular overload provides the
            special case where the index is a reference to a container but the
            shape an instance of std::array.

            \tparam ST element type of the shape array
            \tparam N number of elements of the shape array
            \tparam CINDEX container type for the index
            \param shape std::array with shape data
            \param index CINDEX  instance with index data
            \return linear offset of data element
            */
            template<typename ST,size_t N,typename CINDEX>
            static size_t offset(std::array<ST,N> shape,CINDEX &&index)
            {
                return POLIMP::offset(std::forward<std::array<ST,N>>(shape),
                                      std::forward<CINDEX>(index));
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the index

            Take a shape and an offset and compute the corresponding index
            value. For this version the shape data is passed by reference. 

            \tparam ICT container type for the new index
            \tparam SCT container type for the shape data
            \param shape instance of SCT holding the shape information
            \param offset linear offset
            \return instance of ICT with index data
            */
            template<typename ICT,
                     typename SCT> 
            static ICT index(const SCT &shape,size_t offset)
            {
                ICT index;
                allocate_index(index,shape.size());
            
                POLIMP::index(shape,index,offset);
                
                return index;
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the index 

            Compute the multidimensional index corresponding to a linear offset
            value. The shape here is assumed to be an instance of std::array and
            is thus passed by value to the index computing function. 

            \tparam ICT index container type
            \tparam T element type of the std::array instance
            \tparam N number of elements for the std::array instance
            \param shape std::array with shape data
            \param offset the linear offset
            \return instance of ICT holding the index data
            */
            template<typename ICT,
                     typename T,
                     size_t N>
            static ICT index(std::array<T,N> shape,size_t offset)
            {
                ICT index;
                allocate_index(index,shape.size());
                
                POLIMP::index(std::forward<std::array<T,N>>(shape),
                              index,offset);
                return index;
            }
    };



//end of namespace
}
}
