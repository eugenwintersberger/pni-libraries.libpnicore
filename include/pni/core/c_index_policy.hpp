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

#include "exceptions.hpp"
#include "exception_utils.hpp"

namespace pni{
namespace core{
    
    /*!
    \ingroup index_mapping_classes
    \brief policy for C-order index computation

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
    */
    class c_index_policy
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
            static size_t compute_offset(IITERT &&index_start,
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
            static void compute_index(SITERT &&shape_start,
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
            static size_t offset(const CSHAPE &shape,const CINDEX &index)
            {
                return compute_offset(index.rbegin(),index.rend(),
                                      shape.rbegin());
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the offset

            In this case we have an lvalue reference as an index which can be
            moved. This will dramatically improve the performance of the code. 
            
            A typicall application would look like this
            \code
            std::vector<size_t> shape{3,3};

            size_t offset = c_index_policy::offset(shape,{1,2});
            \endcode

            A SFINAE construction is used to determine whether or not the index
            container is an rvalue or an lvalue reference.

            \tparam CSHAPE container type for the shape
            \tparam CINDEX container type for the index
            \param shape container with shape information
            \param index container with index information
            \return linear offset of the data element
            */
            template<typename CSHAPE,
                     typename CINDEX,
                     typename = typename std::enable_if<
                         !std::is_lvalue_reference<CINDEX>::value
                         >::type
                    >
            static size_t offset(const CSHAPE &shape,CINDEX &&index)
            {
                return compute_offset(index.rbegin(),index.rend(),
                                      shape.rbegin());
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
            static size_t offset(std::array<ST,N> shape,const CINDEX &index)
            {
                return compute_offset(index.rbegin(),index.rend(),
                                      shape.rbegin());
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the offset

            Here we assume that the shape is held by an instance of std::array
            (which should be passed by value) but the index container is an
            rvalue reference. 

            \tparam ST value type of the index 
            \tparam N number of shape elements
            \tparam CINDEX container type for index data
            \param shape the std::array with the shape data
            \param index instance of CINDEX with index data
            \return linear offset of the data element
            */
            template<typename ST,
                     size_t   N,
                     typename CINDEX,
                     typename = typename std::enable_if<
                         !std::is_lvalue_reference<CINDEX>::value
                         >::type
                    >
            static size_t offset(std::array<ST,N> shape,CINDEX &&index)
            {
                return compute_offset(index.rbegin(),index.rend(),
                                      shape.rbegin());
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

                compute_index(shape.begin(),shape.end(),index.begin(),offset);
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

                compute_index(shape.begin(),shape.end(),index.begin(),offset);
                return index;
            }
    };



//end of namespace
}
}
