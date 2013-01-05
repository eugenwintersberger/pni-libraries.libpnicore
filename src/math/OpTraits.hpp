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
 * Created on: Jul 25,2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "../Scalar.hpp"

namespace pni{
namespace core{
    
    /*! 
    \ingroup numeric_array_classes
    \brief operator reference trait

    */
    template<typename OT> struct OpTrait
    {
        //! reference type for the operand
        typedef OT const& ref_type; 
    };

    /*! 
    \ingroup numeric_array_classes
    \brief operator reference trait - specialization
    */
    template<typename T> struct OpTrait<Scalar<T> >
    {
        //! reference type for a scalar operand
        typedef Scalar<T> ref_type;
    };
//end of namespace
}
}
