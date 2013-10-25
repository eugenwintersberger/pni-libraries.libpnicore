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

    /*!
    \ingroup index_mapping_classes
    \brief the general index map template 

    This is the basic index map template. Index maps provide all the
    functionality to map a vector of multidimensional indexes onto a linear
    memory offset and vica verse.  

    The index map behaves like an STL container whose elements are the number of
    elements along a particular dimension of a multidimensional array. This
    shape information is stored in an internal linear storage. Construction of
    an index map depends thus on the construction procedure of the internal
    storage type.

    \tparam SHAPE_STORE type storing the shape information
    \tparam MAP_POL policy to compute the index and offset data
    */
    template<typename SHAPE_STORE,typename MAP_POL> class index_map
    {
        public:
            //=================public types====================================
            //! storage type
            typedef SHAPE_STORE storage_type;
            //! policy type
            typedef MAP_POL     policy_type;
            //! read write iterator
            typedef typename storage_type::iterator iterator;
            //! constant iterator over the map
            typedef typename storage_type::const_iterator const_iterator;
        private:
            //! storage for shape information
            storage_type _shape;
        public:
            //-----------------------------------------------------------------
            /*!
            \brief constructor

            This constructor takes all the arguments that a constructor for type
            storage_type would use. 

            \tparam CARGS argument types for the storage_type constructor
            \param args arguments for the storage_type constructor
            */
            template<typename... CARGS>
            index_map(CARGS ...args):_shape(args...)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            This constructor does copy construction from a storage type
            instance.
            \param s instance of storage_type
            */
            index_map(const storage_type &s):_shape(s) {}

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            Performs move construction from an rvalue reference to an instance
            of storage_type.

            \param s rvalue reference to storage_type
            */
            index_map(storage_type &&s):_shape(std::move(s)) {}

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
            size_t rank() const { return _shape.size(); }

            //----------------------------------------------------------------
            /*!
            \brief get number of dimensions
            
            This function is a synonym for rank() and returns the total number
            of dimensions.

            \return number of dimensions
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
                return MAP_POL::template offset(_shape,index);
            }

            //-----------------------------------------------------------------
            /*!
            \brief compute the offset

            This method is used in the case where the index is passed as an
            lvalue reference. 

            \tparam CTYPE container type for index data
            \param index instance of CTYPE with container data
            \return linear offset
            */
            template<typename CTYPE,
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

            \tparam T data type of std::array 
            \tparam N number of elements of std::array
            \param index index for which to compute the offset
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
            \brief compute offset 

            The index is passed as variadic arguments. 

            \code
            size_t offset = map.offset(1,2,3);
            \endcode

            \tparam ITYPES variadic index arguments
            \parm index the index values
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

            Return the index stored in a container determined by the user as a
            template parameter.
            
            \code
            typedef index_map<...> map_t;
            map_t map(...)
            auto index = map.index<shape_t>(3);
            \endcode

            \tparam CTYPE container type where to store the index
            \param offset linear offset for which to compute the index
            \return instance of CTYPE with index values
            */
            template<typename CTYPE> CTYPE index(size_t offset) const
            {
                return MAP_POL::template index<CTYPE>(_shape,offset);
            }

            //-----------------------------------------------------------------
            //! return iterator to first element
            iterator begin() { return _shape.begin(); }

            //-----------------------------------------------------------------
            //! return iterator to last+1 element
            iterator end()   { return _shape.end(); }

            //-----------------------------------------------------------------
            //! return const iterator to first element
            const_iterator begin() const { return _shape.begin(); }

            //-----------------------------------------------------------------
            //! return const iterator to last+1 element
            const_iterator end() const { return _shape.end(); }

    };
//end of namespace
}
}
