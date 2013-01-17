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
 * Created on: Jan 11, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "value_holder_interface.hpp"

namespace pni{
namespace core{
    template<typename T> T& get_reference(T& v)
    {
        return v;
    }

    template<typename T> T& get_reference(std::reference_wrapper<T> &v)
    {
        return v.get();
    }

    template<typename T>
    const T& get_reference(const std::reference_wrapper<T> &v) 
    {
        return v.get();
    }

    template<typename T> struct is_reference_holder
    {
        static const bool value = false;
    };

    template<typename T> struct is_reference_holder<std::reference_wrapper<T> >
    {
        static const bool value = true;
    };

    template<typename T> struct get_reference_type
    {
        typedef T value_type;
    };

    template<typename T> struct get_reference_type<std::reference_wrapper<T> >
    {
        typedef T value_type;
    };

    /*!
    \brief implementation of the holder interface

    This template implements the holder interface for the value class.
    \tparam T type of the data wrapped
    */
    template<typename T> 
        class value_holder : public value_holder_interface
    {
        private:
            T _value; //!< the data value

        public:
            //---------------------------------------------------------
            //! default constructor
            value_holder():_value(T(0)) {}

            //---------------------------------------------------------
            //! value constructor
            value_holder(T v):_value(v) {}


            //===============public inerface implementation============
            
            virtual TypeID type_id() const 
            {
                return TypeIDMap<typename get_reference_type<T>::value_type >::type_id;
            }

            //---------------------------------------------------------
            virtual value_holder_interface *clone() const
            {
                return new value_holder<T>(_value);
            }

            //---------------------------------------------------------
            T as() const { return _value; } 

            //---------------------------------------------------------
            virtual std::ostream &write(std::ostream &stream) const
            {
                stream<<get_reference(_value);
                return stream;
            }

            //----------------------------------------------------------
            virtual std::istream &read(std::istream &stream)
            {
                stream>>get_reference(_value);
                return stream;
            }

            virtual bool holds_reference() const
            {
                return is_reference_holder<T>::value;
            }
    };

//end of namespace
}
}
