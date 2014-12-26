//
// Declaration of template class TypeInfo
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 10, 2011
//      Author: Eugen Wintersberger
//
#pragma once

#include "type_id_map.hpp"
#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "../error/exceptions.hpp"
#include "../error/exception_utils.hpp"
#include "type_info.hpp"
#include "unchecked_convertible.hpp"
#include "checked_convertible.hpp"
#include "type_conversion.hpp"


namespace pni{
namespace core{

    using namespace boost::numeric;


    //-------------------------------------------------------------------------
    //!
    //! ingroup type_classes_internal
    //! \brief type conversion function template
    //! 
    //! This function template finally performs the type conversion. Several
    //! static asserts are performed which ensure the two cases of conversions
    //! will not even compile: conversion from a floating point number of an
    //! integer value and conversion from a complex value to a non-complex 
    //! type.
    //!
    //! \throws range_error if u does not fit in the range covered by T
    //! \throws type_error in case of all other errors
    //! \tparam T target type
    //! \tparam U source type
    //! \param u value of type U
    //! \return value of u converted to T
    //!
    template<
             typename T,
             typename S
            > 
    T convert(const S &source)
    {

        if(unchecked_convertible<S,T>::value)
            return T(source);
        else if(checked_convertible<S,T>::value)
        {
            try
            {
                return boost::numeric_cast<T>(source);
            }
            catch(const boost::numeric::positive_overflow &error)
            {
                throw range_error(EXCEPTION_RECORD,
                        "Source value exceeded range of target type!");
            }
            catch(const boost::numeric::negative_overflow &error)
            {
                throw range_error(EXCEPTION_RECORD,
                        "Source value exceeded range of target type!");
            }
            catch(...)
            {
                throw type_error(EXCEPTION_RECORD,
                        "Unknown error during type conversion!");
            }
        }
        else
            throw type_error(EXCEPTION_RECORD,
                             "Type conversion not possible!");
    }

//end of namespace
}
}
