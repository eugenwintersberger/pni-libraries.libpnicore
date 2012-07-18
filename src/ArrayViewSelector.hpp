/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of the ArrayView template
 *
 * Created on: Jul 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __ARRAYVIEWSELECTOR_HPP__
#define __ARRAYVIEWSELECTOR_HPP__

#include "ArrayView.hpp"


namespace pni {
namespace utils {

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
    template<typename ATYPE,typename ...ITYPES> struct ArrayViewSelector
    {}

    //-------------------------------------------------------------------------
    /*!
    \ingroup util_classes
    \brief specialization of the return type selection type

    This is the default version of the ArrayViewSelector type. The selector type
    is instantiated recursively.
    */
    template<typename ATYPE,typename T,typename ...ITYPES> struct
        ArrayViewSelector<ATYPE,T,ITYPES...>
    {
        //!< recursive instantiation of the selector type
        typedef typename ArrayViewSelector<ATYPE,ITYPES...>::viewtype viewtype;
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup util_classes
    \brief return type iteration break condition 

    Break condition for return type specialization if the return type is a view
    type.
    */
    template<typename ATYPE,typename ...ITYPES> struct
        ArrayViewSelector<ATYPE,Slice,ITYPES...>
    {
        typedef ArrayView<ATYPE> viewtype; //!< array view return type
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup util_classes
    \brief return type iterator break condition

    Break condition for recursive template type instantiation for a scalar
    return type. This will be chosen if all arguments are single index types.
    */
    template<typename ATYPE> struct ArrayViewSelector<ATYPE>
    {
        typedef typename ATYPE::value_type &viewtype; //!< return type
    };

//end of namespace
}
}

#endif
