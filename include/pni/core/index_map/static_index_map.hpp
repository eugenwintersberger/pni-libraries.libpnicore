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
 * Created on: Oct 25, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <algorithm>
#include <numeric>

namespace pni{
namespace core{

    /*!
    \ingroup index_mapping_classes
    \brief the static general index map template 

    This is the basic static index map. In comparision to index_map its number
    of elements along each dimensions as well as the number of dimensions cannot
    be changed after the type has been defined. As all data is static this type
    is rather efficient as everything resides on the stack. Thus it is perfectly
    suited for small objects like vectors and matrices. 

    To create an index map for a 3x3 matrix one could use something like this
    \code
    //first we need to define the index policy (here we want c order)
    typedef index_policy<c_index_policy_imp> c_index_policy;
    //now we can define the index map for the matrix
    typedef static_index_map<c_index_policy,3,3> c_matrix_index_map;
    \endcode

    This class has no special constructors as it is ready to use just be using
    the default constructor. Unlike index_map this template provides only const
    iterators (as its dimensions cannot be changed once declared).

    \tparam MAP_POL policy to compute the index and offset data
    \tparam DIMS number of elements along each dimension
    */
    template<typename MAP_POL,size_t... DIMS> class static_index_map
    {
        public:
            //=================public types====================================
            //! storage type
            typedef std::array<size_t,sizeof...(DIMS)> storage_type;
            //! policy type
            typedef MAP_POL     policy_type;
            //! index type 
            typedef storage_type index_type;
            //! constant iterator over the map
            typedef typename storage_type::const_iterator const_iterator;
        private:
            //! storage for shape information
            constexpr static storage_type _shape= {DIMS...};
        public:

            //-----------------------------------------------------------------
            /*!
            \brief get number of elements

            Returns the total number of elements that can be addressed by this
            map. This can be used to allocate some linear storage on which the
            index map can work. 
            \return number of allocatable elements
            */
            size_t max_elements() const
            {
                return std::accumulate(_shape.begin(),_shape.end(),1,
                                       std::multiplies<size_t>()); 
            }

            //-----------------------------------------------------------------
            /*!
            \brief get number of dimensions

            Returns the total number of dimensions currently manged by this
            index map. 

            \return number of dimensions
            */
            size_t rank() const { return sizeof...(DIMS); }

            //-----------------------------------------------------------------
            /*!
            \brief get number of elements

            This is just a synonym for rank(). 

            \return the number of dimensions
            */
            size_t size() const { return rank(); }

            //-----------------------------------------------------------------
            /*!
            \brief compute the offset 

            This method will be used when the index is passed as an lvalue
            reference. 
            
            \tparam CTYPE index container type
            \param index instance of CTYPE with the index data
            \return linear offset
            */
            template<typename CTYPE> 
            size_t offset(const CTYPE &index) const
            {
                //here we forward the index container to the policy class
                return MAP_POL::template offset(_shape,index);
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the offset

            This method is used in the case where the index is passed as an
            rvalue reference. 

            \code
            typedef static_index_map<...> static_map;
            typedef std::vector<size_t>   index_t;
            static_map map;
           
            size_t offset = map.offset(index_t{1,2,3});

            //or alternatively 
            index_t index;
            ....
            offset = map.offset(std::move(index));
            \endcode

            \tparam CTYPE container type for index data
            \param index instance of CTYPE with container data
            \return linear offset
            */
            template<typename CTYPE,
                     //the SFINAE construction here ensures that only rvalue
                     //references are passed to this function
                     typename = typename std::enable_if<
                     !std::is_lvalue_reference<CTYPE>::value
                         >::type
                    >
            size_t offset(CTYPE &&index)
            {
                return MAP_POL::template offset(_shape,
                                                std::forward<CTYPE>(index));
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute offset 

            In the special case that the index is passed as an instance of
            std::array pass by value is the prefered method. 

            \code
            typedef ... static_map;
            typedef std::array<size_t,3> index_t;

            static_map map;
            index_t index{{1,3,2}};

            size_t offset = map.offset(index);
            \endcode

            \tparam T data type of std::array 
            \tparam N number of elements of std::array
            \return linear offset
            */
            template<typename T,size_t N> 
            size_t offset(std::array<T,N> index) const
            {
                return MAP_POL::template offset(_shape,
                                                std::forward<std::array<T,N>>(index));
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the offset 

            Compute the offset from indexes passed to a variadic function. 

            \code
            typedef .... static_map;
    
            static_map map;
            size_t offset = map.offset(1,3,9);
            \endcode

            \tparam ITYPES index types
            \return linear offset
            */
            template<typename... ITYPES>
            size_t offset(ITYPES ...index) const
            {
                return MAP_POL::template offset(_shape,
                        std::array<size_t,sizeof...(ITYPES)>{{index...}});
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute index

            Compute the index that belongs to a particular linear offset. 
            The index can be stored in any STL compliant container type
            determined by the template parameter CTYPE. 

            \code
            typedef ... static_map;
            typedef std::vector<size_t> index_type;
            
            static_map map;
            auto index = map.index<index_type>(100);
            \endcode

            \tparam CTYPE index container type
            \param offset linear offset
            \return CTYPE instance with index values
            */
            template<typename CTYPE> CTYPE index(size_t offset) const
            {
                return MAP_POL::template index<CTYPE>(_shape,offset);
            }

            //-----------------------------------------------------------------
            //! get a const iterator to the first element
            const_iterator begin() const { return _shape.begin(); }

            //-----------------------------------------------------------------
            //! get a const iterator to the last+1 element
            const_iterator end() const { return _shape.end(); }

    };
    
template<typename MAP_POL,size_t... DIMS> 
    constexpr typename static_index_map<MAP_POL,DIMS...>::storage_type 
    static_index_map<MAP_POL,DIMS...>::_shape;
//end of namespace
}
}
