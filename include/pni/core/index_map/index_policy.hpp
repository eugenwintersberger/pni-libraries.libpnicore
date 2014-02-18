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
#include "../container_utils.hpp"

namespace pni{
namespace core{
    
    /*!
    \ingroup index_mapping_classes
    \brief general policy for index computation

    Index policies are types used by index maps (dynamic or static) to compute
    the linear offset for a particular multidimensional index vector and vica
    verse. All computational work in done in the implementation type POLIMP. 
    This template just ensures that all arguments to the functions are passed in
    their most effective way to the numerical routines. As index computations
    are performed nearly everywhere when working with multidimensional arrays
    their performance is cirtical to an application. One performance critical
    aspect is how containers are passed to the functions. 

    In its most simplest case an index policy provides two functions where the
    first one has the signature

    \code
    template<typename SHAPET,typename INDEXT>
    size_t offset(const SHAPET &shape,const INDEXT &index);
    \endcode

    computing the linear offset for a mulitindex stored in index in an
    array whose shape (number of elements along each dimension) is stored in
    shape. And the second one 

    \code
    template<typename ITYPE,typename STYPE> 
    ITYPE index(const STYPE &shape,size_t offset);
    \endcode

    computing the index for a given linear offset in an array of shape shape. 

    For the performance of these functions it is crucial how the container types
    are passed. The call by references as shown in the above example slows down
    the performance dramatically in particular if the index container passed is
    an rvalue reference.
    
    \tparam POLIMP policy implementation
    */
    template<typename POLIMP> struct index_policy
    {

        //---------------------------------------------------------------------
        /*!
        \brief compute the offset

        Here the shape container is passed by a const reference while the index
        container by a universal reference (matches everything). 

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

        //---------------------------------------------------------------------
        /*!
        \brief compute the offset

        Typically we cannot move the container holding the shape as it is the
        primary data object in an index mape. However, in the case of std::array
        it would be feasible to pass the container by value rather than by
        reference. This particular overload provides the special case where the
        index is a reference to a container but the shape an instance of
        std::array.

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

        //---------------------------------------------------------------------
        /*!
        \brief compute the index

        Take a shape and an offset and compute the corresponding index value.
        For this version the shape data is passed by reference. 

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
            auto idx = container_utils<ICT>::create(shape.size());
        
            POLIMP::index(shape,idx,offset);
            
            return idx;
        }

        //---------------------------------------------------------------------
        /*!
        \brief compute the index 

        Compute the multidimensional index corresponding to a linear offset
        value. The shape here is assumed to be an instance of std::array and is
        thus passed by value to the index computing function. 

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
            auto idx = container_utils<ICT>::create(shape.size());
            
            POLIMP::index(std::forward<std::array<T,N>>(shape),
                          idx,offset);
            return idx;
        }

        //---------------------------------------------------------------------
        template<typename CTYPE,typename SELTYPE>
        static bool is_contiguous(const CTYPE &s,const SELTYPE &sel) 
        {
            return POLIMP::is_contiguous(s,sel);
        }
    };



//end of namespace
}
}
