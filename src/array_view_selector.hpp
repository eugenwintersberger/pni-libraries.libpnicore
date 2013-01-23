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
 * Declaration of the ArrayView template
 *
 * Created on: Jul 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include "array_view.hpp"


namespace pni {
namespace core {

    template<typename ATYPE,template<typename> class IPA> class numarray;

    /*! 
    \ingroup util_classes
    \brief select return type of an array multiindex access

    When accessing array data using the () operator with an an argument list the
    return type can either be a single scalar value or an ArrayView object. 
    The return type depends on whether or not the one of the arguments is an
    instance of Slice type. 
    \code

    Array a ....;

    //return a single value
    auto value = a(1,2,3,4);

    //return a view
    auto view = a(1,2,Slice(1,2),Slice(2,4));

    \endcode
    This type decides on the return type depending on the argument types.
    */
    template<typename ATYPE,typename ...ITYPES> struct array_view_selector
    {};

    //-------------------------------------------------------------------------
    /*!
    \ingroup util_classes
    \brief specialization of the return type selection type

    This is the default version of the ArrayViewSelector type. The selector type
    is instantiated recursively.
    */
    template<typename ATYPE,typename T,typename ...ITYPES> struct
        array_view_selector<ATYPE,T,ITYPES...>
    {
        //! recursive instantiation of the selector type
        typedef typename array_view_selector<ATYPE,ITYPES...>::viewtype viewtype;
        //! reference type
        typedef typename array_view_selector<ATYPE,ITYPES...>::reftype  reftype;
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup util_classes
    \brief return type iteration break condition 

    Break condition for return type specialization if the return type is a view
    type.
    */
    template<typename ATYPE,typename ...ITYPES> struct
        array_view_selector<ATYPE,Slice,ITYPES...>
    {
        //! array view return type
        typedef array_view<ATYPE> viewtype; 
        //! array view reference type
        typedef array_view<ATYPE> reftype; 
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup util_classes
    \brief return a special type for numeric arrays

    For numeric arrays we need to wrap the ArrayView template into a NumArray
    class.
    */
    template<typename ATYPE,template<typename> class IPA,typename ...ITYPES> 
        struct array_view_selector<numarray<ATYPE,IPA>,Slice,ITYPES...>
    {
        //! array view return type
        typedef numarray<array_view<numarray<ATYPE,IPA> >,IPA > viewtype;
        //! array view reference type
        typedef numarray<array_view<numarray<ATYPE,IPA> >,IPA > reftype;
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup util_classes
    \brief return type iterator break condition

    Break condition for recursive template type instantiation for a scalar
    return type. This will be chosen if all arguments are single index types.
    */
    template<typename ATYPE> struct array_view_selector<ATYPE>
    {
        //! element type
        typedef typename ATYPE::value_type viewtype; 
        //! element type reference
        typedef typename ATYPE::value_type &reftype;
    };

//end of namespace
}
}
