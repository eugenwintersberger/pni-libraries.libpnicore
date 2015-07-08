//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
// Created on: Nov 20, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <vector>
#include <array>

#include <functional>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/size.hpp>

namespace pni{
namespace core{

    template<typename ATYPE> class array_view;
    
    //==============================Define some useful macros===================
#define IDX_ARRAY(IT,i)\
    std::array<size_t,sizeof...(IT)>{{size_t(i)...}}

    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief check if an index type is a valid index type
    //!
    //! Index types are all integer types and slice.
    //!
    //! \tparam T type to check
    //!
    template<typename T>
    struct is_index_type
    {
        //! true if T is integer or a slice type, false otherwise
        static const bool value = std::is_integral<T>::value || 
                                  std::is_same<T,slice>::value;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief check a set of types for index 
    //!
    //! This template checks a range of types whether or not they are index 
    //! types. If all of the types are index types the member value is true.
    //! Otherwise it is false.
    //!
    //! \tparam ITYPES variadic set of types to check
    //!
    template<typename ...ITYPES>
    struct is_index_types
    {
        //!
        //! \brief predicate type for count_if
        //!
        //! This internal type implements a predicate to be used in connection 
        //! with count_if from MPL. 
        //! 
        //! \tparam T input type
        //! 
        template<typename T> 
        struct is_index_type_pred
        {
            //! result type 
            typedef is_index_type<T> type;
        };

        //! load the _ placeholder from boost::mpl
        using _ = boost::mpl::placeholders::_;
        //! list of types passed by the user
        typedef typename boost::mpl::vector<ITYPES...> types;

        //! count all index types
        typedef boost::mpl::count_if<types,is_index_type_pred<_>> n_index_types;

        //! if the number of index types is equal to the number of types passed
        //! by the user, all passed types are valid index types
        static const bool value = n_index_types::value ==
            int(boost::mpl::size<types>::value);
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief checks for view index
    //!
    //! This type checks if the types passed by a variadic index represent a 
    //! view or a single data item. While for a single element index the 
    //! individual index values must all be of integer type 
    //! (typically size_t), a view index contains at least one instance of 
    //! slice. 
    //! 
    //! \code
    //! is_view_index<size_t,size_t,size_t>::value; //this would be false
    //! is_view_index<size_t,size_t,slice>::value;  //this would be true
    //! \endcode
    //! 
    //! \tparam ITYPES index types
    //!
    template<typename ...ITYPES> 
    struct is_view_index
    {
        //! result type of MPL expression
        typedef typename boost::mpl::contains<
                                   typename boost::mpl::vector<ITYPES...>::type,
                                   slice
                                  >::type type;

        //! true if ITYPES represent a view
        static const bool value = type::value;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief check if valid index
    //!
    //! Checks if a list of variadic arguments are a valid view or element 
    //! index. This is the case if the arguments are either of an unsigned 
    //! integer type or instances of slice.
    //!
    //! \code
    //! is_valid_index<size_t,size_t,slice>::value;  //would be true
    //! is_valid_index<size_t,size_t,size_t>::value; //would be true
    //! is_valid_index<slice,slice>::value;          //true either
    //! is_valid_index<slice,string>::value;         //definitely false
    //! \endcode
    //! 
    //! \tparam ITYPES index types
    //!
    template<typename ...ITYPES> 
    struct is_valid_index
    {
        //! result type of MPL exrepssion
        typedef typename boost::mpl::contains<
            typename boost::mpl::vector<ITYPES...>::type,slice>::type has_slice;
        //! result type of MPL expression
        typedef typename boost::mpl::contains<
            typename boost::mpl::vector<ITYPES...>::type,size_t>::type
            has_size_t;

        //! true if the types are valid index types
        static const bool value = has_slice::value || has_size_t::value;
    };


    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief check if view index 
    //! 
    //! This template checks if a container identifies a view. This is the 
    //! case if its value_type is slice. 
    //! 
    template<typename CTYPE> struct is_view_cont
    {
        //! by default CTYPE is no view container
        static const bool value = false;
    };
   
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief check if view index
    //! 
    //! This template checks 
    template<typename T> struct is_view_cont<std::vector<T>>
    {
        //! true if CTYPE holds view information
        static const bool value = std::is_same<T,slice>::value;
    };

    template<typename T,size_t N> struct is_view_cont<std::array<T,N>>
    {
        static const bool value = std::is_same<T,slice>::value;
    };


  
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief view trait
    //!
    //! Depending on the index types the ()-operator of mdarray has to either 
    //! return an instance of array_view or a single value or a reference to 
    //! a particular element of the array. 
    //! This template provides the return types for view indexes or and 
    //! single element indexes.
    //! There are two specializations of this template available: one for 
    //! views and one for single elements. 
    //!
    //! \tparam ATYPE array type
    //! \tparam is_view true if the index represents a view, false otherwise
    //!
    template<
             typename ATYPE,
             bool is_view
            > 
    struct array_view_trait;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief view trait for views 
    //!
    //! This is the specialization of array_view_trait provides the view 
    //! types in case that the indexes passed to the ()-operator represent 
    //! a view. 
    //!
    //! \tparam ATYPE array type
    //!
    template<typename ATYPE> 
    struct array_view_trait<ATYPE,true>    
    {
        //! non-const view type
        typedef array_view<ATYPE> type;
        //! const view type
        typedef array_view<const ATYPE> const_type;
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief trait for single elements 
    //!
    //! This is the specialization of array_view_trait for single element 
    //! access.
    //!
    template<typename ATYPE> 
    struct array_view_trait<ATYPE,false>
    {
        //! single element reference
        typedef typename ATYPE::value_type& type;
        //! single element value 
        typedef typename ATYPE::value_type  const_type;

    };

template<typename CTYPE>
    using enable_element_cont = std::enable_if<!is_index_type<CTYPE>::value && 
                                               !is_view_cont<CTYPE>::value >;

template<typename CTYPE>
    using enable_view_cont = std::enable_if<!is_index_type<CTYPE>::value && 
                                            is_view_cont<CTYPE>::value >;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \ingroup provides views 
    //!
    //! A limitation of variadic template expansion in gcc 4.7 makes this 
    //! template necessary. Its purpose is to provide static functions that 
    //! extract 
    //!
    template<
             typename RTYPE,
             bool is_view
            > 
    struct view_provider;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief single value view_provider 
    //!
    //! Specialization of the view_provider template for single element 
    //! access.  This is the case when all indices passed to the () operator of
    //! original array are of an unsinged integer type.
    //!
    //! \tparam ATYPE array type
    //! 
    template<typename ATYPE> 
    struct view_provider<ATYPE,false>
    {
        //! reference type
        typedef typename array_view_trait<ATYPE,false>::type ref_type;
        //! const type (value type)
        typedef typename array_view_trait<ATYPE,false>::const_type type;
       
        //---------------------------------------------------------------------
        //!
        //! \brief get reference
        //!
        //! Return the reference to a single element. The function computes 
        //! the offset for a particular container by means of an index map. 
        //! This overload works with indexes passed as variadic arguments.
        //!
        //! \tparam CTYPE container type 
        //! \tparam MAP index map type
        //! \tparam ITYPES indices of the element
        //! \param c reference to the data container 
        //! \param map reference to the index map
        //! \param indexes index values
        //! \return reference to the single element
        //!
        template<
                 typename CTYPE,
                 typename MAP,
                 typename... ITYPES
                > 
        static ref_type get_reference(CTYPE &c,MAP &map,ITYPES ...indexes)
        {
            typedef std::array<size_t,sizeof...(ITYPES)> array_type; 
#ifdef DEBUG
            array_type buffer{{size_t(indexes)...}};
            check_indexes(buffer,map,EXCEPTION_RECORD);
#endif

            size_t offset = map.offset(array_type{{size_t(indexes)...}});
            return c[offset];
        }

        //---------------------------------------------------------------------
        //!
        //! \brief get value
        //!
        //! Return a single value from a container. The function computes 
        //! the linear offset. Here the indexes are passed as variadic
        //! arguments.
        //!
        //! \tparam CTYPE data container type
        //! \tparam MAP index map type
        //! \tparam ITYPES index types
        //! \param c reference to the data container
        //! \param map reference to the index map
        //! \param indexes index values as variadic arguments
        //! \return value of the referenced data element.
        //!
        template<
                 typename CTYPE,
                 typename MAP,
                 typename ...ITYPES
                >
        static type get_value(const CTYPE &c,MAP &map,ITYPES ...indexes)
        {
            typedef std::array<size_t,sizeof...(ITYPES)> array_type;
#ifdef DEBUG
            array_type buffer{{size_t(indexes)...}};
            check_indexes(buffer,map,EXCEPTION_RECORD);
#endif

            size_t offset = map.offset(array_type{{size_t(indexes)...}});
            return c[offset];
        }

    };
  
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief array view view_provider
    //!
    //! This overload of the view_provider template returns array_view
    //! instances. 
    //! 
    //! \tparam ATYPE array type
    //!
    template<typename ATYPE> 
    struct view_provider<ATYPE,true>
    {
        //! reference type
        typedef typename array_view_trait<ATYPE,true>::type ref_type;
        //! const reference type
        typedef typename array_view_trait<ATYPE,true>::const_type type;
       
        //---------------------------------------------------------------------
        //!
        //! \brief get view object
        //!
        //! Return a non-const view instance on the array. The indexes (slices) 
        //! determining the view are passed as variadic arguments. 
        //!
        //! \tparam CTYPE array type
        //! \tparam MAP index map type
        //! \tparam ITYPES index types
        //! \param c reference to the data container
        //! \param map reference to the index map
        //! \param indexes variadic argument list
        //! \return array view on array
        //!
        template<
                 typename CTYPE,
                 typename MAP,
                 typename... ITYPES
                > 
        static ref_type get_reference(CTYPE &c,MAP &,ITYPES ...indexes)
        {
            typedef std::array<slice,sizeof...(ITYPES)> array_type; 

            return ref_type(c,array_selection::create(
                            array_type{{slice(indexes)...}}));
        }


        //---------------------------------------------------------------------
        //!
        //! \brief get const view
        //! 
        //! This overload returns a const view of an array. The indexes and
        //! slices are passed as variaidc templates to the function.
        //!
        //! \tparam CTYPE array type
        //! \tparam MAP index map type
        //! \tparam ITYPES index and slice types
        //! \param c reference to the data container
        //! \param map reference to the index map
        //! \param indexes variadic argument list
        //! \return const array view
        //! 
        template<
                 typename CTYPE,
                 typename MAP,
                 typename ...ITYPES
                >
        static type get_value(const CTYPE &c,MAP &,ITYPES ...indexes)
        {
            typedef std::array<slice,sizeof...(ITYPES)> array_type;

            return type(c,array_selection::create(
                        array_type{{slice(indexes)...}}));
        }

    };

template<typename ATYPE,
         typename ...ITYPES
        >
    using view_type_trait = array_view_trait<ATYPE,
                                       is_view_index<ITYPES...>::value>;

template<typename ...ITYPES>
    using enable_valid_index = std::enable_if<is_index_types<ITYPES...>::value>;
//end of namespace
}
}
