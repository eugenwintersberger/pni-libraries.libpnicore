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
 *
 * Created on: Nov 20, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

namespace pni{
namespace core{

    /*!
    \ingroup multidim_array_classes
    \brief checks for view index

    This type checks if the types passed by a variadic index represent a view or
    a single data item. While for a single element index the individual index
    values must all be of integer type (typically size_t), a view index contains
    at least one instance of slice. 

    \code
    is_view_index<size_t,size_t,size_t>::value; //this would be false
    is_view_index<size_t,size_t,slice>::value;  //this would be true
    \endcode

    \tparam ITYPES index types
    */
    template<typename ...ITYPES> struct is_view_index
    {
        typedef typename boost::mpl::contains<
                                   typename boost::mpl::vector<ITYPES...>::type,
                                   slice
                                  >::type type;

        //! true if ITYPES represent a view
        static const bool value = type::value;
    };

  
    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief view trait

    Depending on the index types the ()-operator of mdarray has to either return
    an instance of array_view or a single value or a reference to a particular
    element of the array. 
    This template provides the return types for view indexes or and single
    element indexes.
    There are two specializations of this template available: one for views and
    one for single elements. 

    \tparam ATYPE array type
    \tparam is_view true if the index represents a view, false otherwise
    */
    template<typename ATYPE,bool is_view> struct array_view_trait;

    /*!
    \ingroup multidim_array_classes
    \brief view trait for views 

    This is the specialization of array_view_trait provides the view types in
    case that the indexes passed to the ()-operator represent a view. 
    */
    template<typename ATYPE> struct array_view_trait<ATYPE,true>    
    {
        //! non-const view type
        typedef array_view<ATYPE> type;
        //! const view type
        typedef array_view<const ATYPE> const_type;
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief trait for single elements 

    This is the specialization of array_view_trait for single element access.
    */
    template<typename ATYPE> struct array_view_trait<ATYPE,false>
    {
        //! single element reference
        typedef typename ATYPE::value_type& type;
        //! single element value 
        typedef typename ATYPE::value_type  const_type;

    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \ingroup provides views 

    A limitation of variadic template expansion in gcc 4.7 makes this template
    necessary. Its purpose is to provide static functions that extract 
    */
    template<typename RTYPE,bool is_view> struct view_provider;

    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief single value view_provider 

    Specialization of the view_provider template for single element access. 
    */
    template<typename ATYPE> struct view_provider<ATYPE,false>
    {
        //! reference type
        typedef typename array_view_trait<ATYPE,false>::type ref_type;
        //! const type (value type)
        typedef typename array_view_trait<ATYPE,false>::const_type type;
       
        //---------------------------------------------------------------------
        /*!
        \brief get reference

        Return the reference to a single element. The function computes the
        offset for a particular container by means of an index map. 

        \tparam CTYPE container type 
        \tparam MAP index map type
        \tparam ITYPES indices of the element
        \param c reference to the data container 
        \param map reference to the index map
        \param indexes index values
        */
        template<typename CTYPE,typename MAP,typename... ITYPES> 
        static ref_type get_reference(CTYPE &c,MAP &map,ITYPES ...indexes)
        {
            
            std::array<size_t,sizeof...(ITYPES)> buffer{{size_t(indexes)...}};
#ifdef DEBUG
            check_indexes(buffer,map,EXCEPTION_RECORD);
#endif

            size_t offset = map.offset(buffer);
            return c[offset];
        }

        //---------------------------------------------------------------------
        /*!
        \brief get value

        Return a single value from a container. The function computes the
        linear offset. 

        \tparam CTYPE data container type
        \tparam MAP index map type
        \tparam ITYPES index types
        \param c reference to the data container
        \param map reference to the index map
        \param indexes index values as variadic arguments
        \return value of the referenced data element.
        */
        template<typename CTYPE,typename MAP,typename ...ITYPES>
        static type get_value(const CTYPE &c,MAP &map,ITYPES ...indexes)
        {
            std::array<size_t,sizeof...(ITYPES)> buffer{{size_t(indexes)...}};
#ifdef DEBUG
            check_indexes(buffer,map,EXCEPTION_RECORD);
#endif

            size_t offset = map.offset(buffer);
            return c[offset];
        }
         

    };
  
    //-------------------------------------------------------------------------
    /*!
    \ingroup multidim_array_classes
    \brief array view view_provider

    Return an array view. 
    */
    template<typename ATYPE> struct view_provider<ATYPE,true>
    {
        typedef typename array_view_trait<ATYPE,true>::type ref_type;
        typedef typename array_view_trait<ATYPE,true>::const_type type;
        typedef typename ATYPE::map_type::storage_type index_type;
       
        //---------------------------------------------------------------------
        /*!
        \brief get element reference

        Return the reference to a data element of a container. 

        \tparam CTYPE container type
        \tparam MAP index map type
        \tparam ITYPES index types
        \param c reference to the data container
        \param map reference to the index map
        \param indexes variadic argument list
        \return array view on the data container.
        */
        template<typename CTYPE,typename MAP,typename... ITYPES> 
        static ref_type get_reference(CTYPE &c,MAP &map,ITYPES ...indexes)
        {
            
            std::array<slice,sizeof...(ITYPES)> buffer{slice(indexes)...};

            return ref_type(c,array_selection<index_type>::create(buffer));
        }

        //---------------------------------------------------------------------
        /*!
        \brief get const view

        \tparam CTYPE data container type
        \tparam MAP index map type
        \tparam ITYPES index types
        \param c reference to the data container
        \param map reference to the index map
        \param indexes variadic argument list
        \return const array view
        */
        template<typename CTYPE,typename MAP,typename ...ITYPES>
        static type get_value(const CTYPE &c,MAP &map,ITYPES ...indexes)
        {
            std::array<slice,sizeof...(ITYPES)> buffer{slice(indexes)...};

            return type(c,array_selection<index_type>::create(buffer));
        }
         

    };

//end of namespace
}
}
