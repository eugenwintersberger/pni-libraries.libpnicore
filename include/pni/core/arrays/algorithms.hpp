//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Mar 11, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "mdarray.hpp"
#include "array_view.hpp"

namespace pni{
namespace core{


    //!
    //! \ingroup mdim_array_classes
    //! \brief get data pointer
    //! 
    //! Get the pointer to the data stored in an mdarray.
    //! 
    //! \tparam ARGS mdarray template arguments
    //! \param a reference to the array
    //! \return pointer to data
    template<typename ...ARGS> 
    const typename mdarray<ARGS...>::value_type* data(const mdarray<ARGS...> &a)
    {
        return a.storage().data();
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief get data pointer
    //! 
    //! Get the pointer to the data of an array_view instance. This function
    //! will only succeed if the selection on which the view is based on is 
    //! contiguous. Otherwise an exception will be thrown.
    //! 
    //! \tparam ATYPE array type of the view
    //! \param v reference to the view
    //! \return pointer to data
    //! 
    template<typename ATYPE>
    const typename array_view<ATYPE>::value_type*
    data(const array_view<ATYPE> &v)
    {
        return v.data();
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_classes
    //! \brief get rank
    //! 
    //! Return the rank of an array or view.
    //! 
    //! \tparam ATYPE array or view type
    //! \param a reference to the array or view
    //! \return number of dimensions
    //! 
    template<typename ATYPE> 
    size_t rank(const ATYPE &a)
    {
        return a.rank();
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief get shape
    //! 
    //! Returns a container with the number of elements along each dimension of
    //! an array or view. 
    //! 
    //! \tparam CTYPE container for the shape data
    //! \tparam ATYPE array or view type
    //! \param a reference to the array or view
    //! 
    template<
             typename CTYPE,
             typename ATYPE
            >
    CTYPE shape(const ATYPE &a)
    {
        return a.template shape<CTYPE>();     
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief get size
    //! 
    //! Returns the number of elements stored in an array or view. 
    //! 
    //! \tparam ATYPE array or view type
    //! \param a reference to the array or view
    //! \return number of elements
    //! 
    template<typename ATYPE>
    size_t size(const ATYPE &a)
    {
        return a.size();
    }




//end of namespace
}
}
