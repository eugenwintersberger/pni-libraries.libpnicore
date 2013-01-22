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
 * Created on: 11 08, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <iostream>
#include "value.hpp"
#include "value_ref.hpp"

namespace pni{
namespace core{
    /*!
    \brief interface class

    Internal class that defines the interface of the holder class
    */
    class array_holder_interface
    {
        public:
            /*!
            \brief return type id 

            Return the type ID of the held object.
            \return type id
            */
            virtual TypeID type_id() const = 0;
            
            //-----------------------------------------------------------------
            /*!
            \brief get poiter

            Provide a const pointer of type void to the data stored in the
            original object.
            \return const pointer to void
            */
            //not yet implemented
            //virtual const void *ptr() const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief get rank

            Return the rank of the data stored. If the rank is 0 the data is a
            scalar. In all other cases we assume the data to be a
            multidimensional array.
            \return rank (number of dimensions)
            */
            virtual size_t rank() const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief get shape

            Return the shape of the data. This is the number of elements along
            each dimension. In the case of a scalar the shape is empty (size()
            == 0).
            \return shape of data
            */
            virtual shape_t shape() const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief get size

            Return the size of the original data. This is the number of elements
            of a particular type (determined by the type id).  
            \return size
            */
            virtual size_t size() const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief write data 

            Write data to a standard  C++ stream.
            \param os reference to output stream
            \return reference to output stream
            */
            virtual std::ostream &write(std::ostream &os) const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief read data

            Read data from a standard C++ stream.
            \param is reference to input stream
            \return reference to input stream
            */
            virtual std::istream &read(std::istream &is) = 0;

            //-----------------------------------------------------------------
            /*!
            \brief clone yourself

            This member function clones the wrapped object. This is particullary
            important when the resulting type earsure shall be copied.
            \return pointer to new interface instance
            */
            virtual array_holder_interface *clone() const = 0;

            //-----------------------------------------------------------------
            /*!
            \brief get type name 

            Return the mangled name of the original type wrapped by the type
            erasure.
            \return type name
            */
            virtual String type_name() const = 0;

            //-----------------------------------------------------------------
            virtual value operator[](size_t i) const = 0;

            //-----------------------------------------------------------------
            virtual value_ref operator[](size_t i) = 0;

            //-----------------------------------------------------------------
            virtual value at(size_t i) const = 0;

            //-----------------------------------------------------------------
            virtual value_ref at(size_t i) = 0;

            //-----------------------------------------------------------------
            virtual const void *ptr() const = 0;

    };

//end of namespace
}
}
