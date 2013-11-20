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
 *
 * Created on: Aug 5, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <vector>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/lexical_cast.hpp>
#include "mdarray.hpp"
#include "numarray.hpp"
#include "types.hpp"
#include "slice.hpp"


namespace pni{
namespace core{

    //define here a new set of array templates using aliases
    /*!
    \ingroup multidim_array_classes
    \brief a dynamic array template
    
    This template creates a fully dynamic array type. Its rank as well as its
    number of elements along each dimension (the shape) can be created
    dynamically. Use this type if all decisions have to be made at runtime. 

    \code
    typedef dynamic_array<float64> array_type; 

    array_type a = ...;
    \endcode


    \tparam T element type
    */
    template<typename T> 
    using dynamic_array = mdarray<std::vector<T>,dynamic_cindex_map>;

    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief array template with fixed dimension 

    This array template fixes the number of dimensions for an array type at
    compile time. It will be the appropriate type for most applications. 
    The following code defines an image type (we know that images have always
    2 dimensions): 

    \code
    typedef fixed_dim_array<uint32,2> image_type;
    \endcode

    \tparam T element data type
    \tparam D number of dimensions
    */
    template<typename T,size_t D>
    using fixed_dim_array = mdarray<std::vector<T>,fixed_dim_cindex_map<D>>;

    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief static array template 

    This template can be used for static array types. These are types where
    the number of dimensions as well as the total number of elements along each
    dimension are known at compile time. A typical application would be matrices
    and vectors for 3D operations. 

    \code
    typedef static_array<float64,3> vector_type;
    typedef static_array<float64,3,3> matrix_type; 
    typedef static_array<float64,6,6> elasticity_tensor;
    \endcode

    Instances of such types usually reside on the stack which makes access to
    their data elements extremely fast. 

    \tparam T element data type
    \tparam NDIMS number of elements along each dimension
    */
    template<typename T,size_t... NDIMS>
    using static_array = mdarray<std::array<T,boost::mpl::times<
                                              boost::mpl::size_t<1>,
                                              boost::mpl::size_t<NDIMS>...
                                              >::value
                                           >,
                                 static_cindex_map<NDIMS...>
                                >;


    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief array factory 

    This utility template provides static functions for array construction. 

    \tparam ATYPE array type
    */
    template<typename ATYPE> struct array_factory
    {
        typedef ATYPE array_type;
        typedef typename array_type::value_type value_type;
        typedef typename array_type::map_type map_type;
        typedef typename array_type::storage_type storage_type;


        //---------------------------------------------------------------------
        /*!
        \brief create array from shape

        Create an array from a container with shape data and initialize all its
        elements with a default value.

        \code
        typedef ......................... array_type; 
        typedef array_type::value_type    value_type
        typedef arrya_factory<array_type> factory;

        //create array without initial value
        auto a = factory::create(shape_t{100,200});

        //create array with initial value
        auto b = factory::create(shape_t{1024,1024},value_type(0));
        \endcode

        \tparam STYPE container type for shape information
        \param s shape of the array
        \param dev_val default value for data
        \return instance of array_type
        */
        template<typename STYPE> 
        static array_type create(const STYPE &s,value_type def_val = value_type())
        {
            //create the index map
            auto map = map_utils<map_type>::create(s);
            storage_type storage(map.max_elements());
            std::fill(storage.begin(),storage.end(),def_val);
            
            return array_type(std::move(map),std::move(storage));
        }

        //---------------------------------------------------------------------
        /*!
        \brief create array from shape and data

        Usually array types can only be created from their original index map
        and storage type. This function allows construction from a shape and
        data stored in arbitrary containers. 

        \code 
        typedef ...................... array_type; 
        typedef array_type::value_type value_type;
        typedef std::list<size_t>     shape_type;
        typedef std::list<value_type> storage_type;
        typedef array_factory<array_type> factory;


        shape_type shape  = ....;
        storage_type data = ....;
        auto a = factory::create(shape,data);
        \endcode

        \tparam STYPE container type for shape
        \tparam DTYPE container type for data
        \param s reference to shape container
        \param data reference to data container
        \return instance of ATYPE
        */
        template<typename STYPE,
                 typename DTYPE
                >
        static array_type create(const STYPE &s,const DTYPE &data)
        {
            auto map = map_utils<map_type>::create(s);
            if(map.max_elements() != data.size())
                throw size_mismatch_error(EXCEPTION_RECORD,
                        "Total number of elements from map ("
                        +boost::lexical_cast<string>(map.max_elements())+
                        ") does not match data size ("
                        +boost::lexical_cast<string>(data.size())+")!");

            storage_type storage(data.size());
            std::copy(data.begin(),data.end(),storage.begin());
            return array_type(std::move(map),std::move(storage));
        }

        //---------------------------------------------------------------------
        /*!
        \brief construct from initializer list 

        This is maybe the lazy mans version of an array construction function.
        It uses initializer lists and is thus best suited for the construction
        of small arrays (like matrices). 

        \code
        typedef ......................... array_type;
        typedef array_type::value_type    value_type;
        typedef array_factory<array_type> factory;

        auto a = factory::create({3,3},{1,2,3,4,5,6,7,8,9});
        \endcode

        \tparam IT shape value type
        \tparam DT data value type
        \param shape initializer list with shape data
        \param data initializer list with array data
        \return instance of ATYPE
        */
        template<typename IT,
                 typename DT>
        static array_type create(std::initializer_list<IT> shape,
                                 std::initializer_list<DT> data)
        {
            auto map = map_utils<map_type>::create(shape);
            if(map.max_elements() != data.size())
                throw size_mismatch_error(EXCEPTION_RECORD,
                        "Total number of elements from map ("
                        +boost::lexical_cast<string>(map.max_elements())+
                        "does not match data size ("
                        +boost::lexical_cast<string>(data.size())+")!");

            storage_type storage(data.size());
            std::copy(data.begin(),data.end(),storage.begin());
            return array_type(std::move(map),std::move(storage));
        }
        
    };
   
//end of namespace
}
}
