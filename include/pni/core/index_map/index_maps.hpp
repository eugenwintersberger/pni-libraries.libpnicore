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
#include <sstream>
#include "index_map.hpp"
#include "static_index_map.hpp"
#include "index_policy.hpp"
#include "c_index_policy_imp.hpp"

namespace pni{
namespace core{
    /*!
    \ingroup index_mapping_classes
    \brief a C index policy
    
    This is the default C index policy. Use this to define index maps which
    should handle arrays in row major ordering (where the last index varies
    fasters).
    */
    typedef index_policy<c_index_policy_imp> c_index_policy;

    //-------------------------------------------------------------------------
    /*!
    \ingroup index_mapping_classes
    \brief template for  a static C map
   
    A template alias for a static index map with c ordering. To define the index
    map for a 3x3 matrix use something like this
    \code
    static_cindex_map<3,3> matrix_map; 
    \endcode

    \tparam DIMS number of elements along each dimension
    */
    template<size_t... DIMS> 
    using static_cindex_map = static_index_map<c_index_policy,DIMS...>;

    //-------------------------------------------------------------------------
    /*!
    \ingroup index_mapping_classes
    \brief definition of a dynamic C index map
    
    Type definition of a fully dynamic C index map. The structure of the map can
    be fully determined at runtime. The structure of an array.
    */
    typedef index_map<std::vector<size_t>,c_index_policy> dynamic_cindex_map;
    typedef index_map<std::vector<size_t>,c_index_policy> cindex_map;

    //-------------------------------------------------------------------------
    /*!
    \ingroup index_mapping_classes
    \brief fixed dimension dynamic C index map

    For such a map the number of elements along each dimension can be changed,
    however the total size (rank) of the map cannot be changed once the concrete
    type has been defined. 
    A typical example would be to define a map for an image which has always a
    rank of 2 like this
    \code
    typedef fixed_dim_cindex_map<2> image_map; 
    \endcode

    \tparam NDIMS number of dimensions
    */
    template<size_t NDIMS> 
    using fixed_dim_cindex_map = index_map<std::array<size_t,NDIMS>,c_index_policy>;

    //=================define some convienance function========================

    /*!
    \ingroup index_mapping_classes
    \brief utility class for index maps

    This template provides static utility member functions to create index maps.
    Several specializations exist for this template to handle different index
    map types. The major difference between the different types is the storage
    container used to hold the shape information. 
    This is the default implementation for STL compliant containers.

    \tparam MAPT index map type
    */
    template<typename MAPT> struct map_utils
    {
        /*!
        \brief create map from container

        Create a new map from a container. In this case the map can do a full
        resizeing. This would be the case when the map allows also resizeing its
        internal storage.

        \tparam CTYPE container type
        \param c instance of CTYPE with shape information
        \return instance of MAPT
        */
        template<typename CTYPE> static MAPT create(const CTYPE &c)
        {
            typename MAPT::storage_type storage(c.size());
            std::copy(c.begin(),c.end(),storage.begin());
            return MAPT(storage); 
        }

    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup index_mapping_classes
    \brief utility class for maps with std::array storage

    This is a specialization of the map_utils template for index maps using the
    std::array template as storage facility. 

    \param T element type of the std::array template
    \param NDIMS number of dimensions
    \param POLTYPE policy type
    */
    template<typename T,size_t NDIMS,typename POLTYPE> 
    struct map_utils<index_map<std::array<T,NDIMS>,POLTYPE> >
    {
        typedef index_map<std::array<T,NDIMS>,POLTYPE> map_type;
        /*!
        \brief create map from container
    
        In this case std::array is used as internal storage for the map. This
        implies that the map can be resized but the numbers of dimensions cannot
        be changed. If the number of elements in the container does not match
        the number of elements in the map type an exception will be thrown.

        \throw shape_mismatch_error map rank and container size do not match.
        \tparam CTYPE container type 
        \param c instance of CTYPE with the new shape information
        \return new map type 
        */
        template<typename CTYPE> static map_type create(const CTYPE &c)
        {
            typename map_type::storage_type storage;

            if(map_type().rank() != c.size())
            {
                std::stringstream ss;
                ss<<"The map supports only a fixed number of dimensions ("
                    <<storage.size()<<")! However, the container you are "
                    <<"passing has ("<<c.size()<<") elements!"<<std::endl;
                throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
            }

            std::copy(c.begin(),c.end(),storage.begin());
            return map_type(storage);
        }

    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup index_mapping_classes
    \brief utility class for static index maps

    Static index maps are quite special as they cannot be altered after
    instantiation (all information is fixed at compile time. 
    
    
    \tparam POLTYPE policy type
    \tparam DIMS number of elements along each dimension
    */
    template<typename POLTYPE,size_t...DIMS>
    struct map_utils<static_index_map<POLTYPE,DIMS...> >
    {
        /*!
        \brief creat map from container

        */
        typedef static_index_map<POLTYPE,DIMS...> map_type;
        template<typename CTYPE> static map_type create(const CTYPE &c)
        {
            //static_assert(false,"You cannot create a new shape object");
        }
        
    };






     

//end of namespace
}
}
