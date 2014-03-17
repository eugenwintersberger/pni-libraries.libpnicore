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

#include "../types.hpp"

namespace pni{
namespace core{

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_classes
    //! \brief array identifier 
    //! 
    //! This type has a value of true if the template parameter ATYPE is an 
    //! array type. In order to be an array a type has to be an instance of 
    //! mdarray or array_view. 
    //! This is the default version and provides a false value.
    //! 
    //! \tparam ATYPE type of interest
    //!
    template<typename ATYPE> 
    struct is_array
    {
        //! type is not an array
        static const bool value = false;
    };

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
        return a.map().rank();
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
        auto c = container_utils<CTYPE>::create(rank(a));
        std::copy(a.map().begin(),a.map().end(),c.begin());
        return c;
    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_classes
    //! \brief get size
    //! 
    //! Return the number of elements stored in a container. The container can
    //! either a STL container or one of the array types.
    //! 
    //! \tparam CTYPE container type
    //! \param a reference to the container
    //! \return number of elements
    //! 
    template<typename CTYPE> 
    size_t size(const CTYPE &a)
    {
        return a.size();
    }

//end of namespace
}
}
