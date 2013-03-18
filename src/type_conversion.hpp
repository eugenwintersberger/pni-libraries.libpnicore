/*
 * Declaration of template class TypeInfo
 *
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
 * type_conversion.hpp
 *
 *  Created on: Dec 10, 2011
 *      Author: Eugen Wintersberger
 */
#pragma once

#include <limits>
#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

using namespace boost::numeric;

#include "exceptions.hpp"
#include "type_info.hpp"


namespace pni{
namespace core{

    /*! \ingroup type_classes
    \brief general conversion strategy template

    This template implements a generic type conversion between two types.
    The type conversion is done from type U to T. There are some special cases
    in the case where one or both of the types are complex. The core of the
    convert method is the boost::numeric_cast template function for type
    conversion.
    \tparam T target type
    \tparam U source type
    \tparam t_complex the target type is complex
    \tparam u_complex the target type is complex
    \sa class ConversionStrategy<T,U,true,false>
    \sa class ConversionStrategy<T,U,true,true>
    */
    template<typename T, typename U,bool t_complex,bool u_complex>
    class conversion_strategy{
        public:
            /*! \brief convert U to T

            Converts a value of type U to a value of type T. In case of errors
            several exceptions are thrown.
            \throws range_error if the value of u does not fit in the range 
            covered by T
            \throws type_error in case of all other errors
            \param u original value of type U
            \return converted value of type T
            */
            static T convert(const U &u)
            {
                T value;

                try{ value = boost::numeric_cast<T>(u); }
                catch(negative_overflow &error)
                {
                    throw range_error(EXCEPTION_RECORD,
                            "Cannot assign value doe to negative overflow!");
                }
                catch(positive_overflow &error)
                {
                    throw range_error(EXCEPTION_RECORD,
                            "Cannot assign value due to positive overflow!");
                }
                catch(...)
                {
                    throw type_error(EXCEPTION_RECORD,"Something went wrong!");
                }

                return value;
            }
    };

    /*! \ingroup type_classes
    \brief specialization of the type conversion template

    This is a specialization of ConversionStrategy template for the case
    that the target type T is complex. In this case the rhs object
    of the conversion operation (which is of type U) is converted to the
    base type of T and assigned to the real part of the complex value.
    */
    template<typename T,typename U> class conversion_strategy<T,U,true,false>{
        public:
            /*! \brief convert U to T

            Converts a value of type U to a value of type T. In case of errors
            several exceptions are thrown.
            \throws range_error if the value of u does not fit in the range 
            covered by T
            \throws type_error in case of all other errors
            \param u original value of type U
            \return converted value of type T
            */
            static T convert(const U &u)
            {
                typedef typename type_info<T>::BaseType TBaseType;
                T value;
                try
                {
                    value = std::complex<TBaseType>(
                            boost::numeric_cast<TBaseType>(u),0);
                }
                catch(negative_overflow &error)
                {
                    throw range_error(EXCEPTION_RECORD,
                            "Cannot convert type due to negative overflow!");
                }
                catch(positive_overflow &error)
                {
                    throw range_error(EXCEPTION_RECORD,
                            "Cannot convert type due to positive overflow!");
                }
                catch(...)
                {
                    throw type_error(EXCEPTION_RECORD,"Type conversion failed!");
                }

                return value;
            }
    };

    /*! \ingroup type_classes
    \brief specialization of the type conversion template

    A specialization of the ConversionStrategy template for the case that
    both types are complex. In this case the conversion is straight forward.
    */
    template<typename T,typename U> class conversion_strategy<T,U,true,true>{
        public:
            /*! \brief convert U to T

            Converts a value of type std::complex<U> to a value of type
            std::complex<T>. In case of errors several exceptions are thrown.
            \throws range_error if the value of u does not fit in the range 
            covered by T
            \throws type_error in case of all other errors
            \param u original value of type U
            \return converted value of type T
            */
            static T convert(const U &u)
            {
                typedef typename type_info<T>::BaseType TBaseType;
                TBaseType real;
                TBaseType imag;
                try
                {
                    real = boost::numeric_cast<TBaseType>(u.real());
                    imag = boost::numeric_cast<TBaseType>(u.imag());
                }
                catch(negative_overflow &error)
                {
                    throw range_error(EXCEPTION_RECORD,
                    "Cannot convert type due to negative overflow!");
                }
                catch(positive_overflow &error)
                {
                    throw range_error(EXCEPTION_RECORD,
                    "Cannot convert type due to positive overflow!");
                }
                catch(...)
                {
                    throw type_error(EXCEPTION_RECORD,"Type conversion failed!");
                }

                return std::complex<TBaseType>(real,imag);
            }
    };

    /*! ingroup type_classes
    \brief type conversion function template

    This function template finally performs the type conversion. Several
    static asserts are performed which ensure the two cases of conversions
    will not even compile: conversion from a floating point number of an
    integer value and conversion from a complex value to a non-complex type.
    \throws range_error if u does not fit in the range covered by T
    \throws type_error in case of all other errors
    \param u value of type U
    \return value of u converted to T
    */
    template<typename T,typename U> T convert(const U &u)
    {
        
        //static assert of the source type is float and T is an integer type
        //this avoids conversion from float to integer as supported by the
        //C++ standard.
        BOOST_STATIC_ASSERT(!((!std::numeric_limits<U>::is_integer)&&
                              (std::numeric_limits<T>::is_integer)));

        //need to check for complex types - you cannot convert a complex type
        //to a non-complex type
        BOOST_STATIC_ASSERT(!((!type_info<T>::is_complex)&&
                              (type_info<U>::is_complex)));

        T value;
        try
        {
            value = conversion_strategy<T,U,type_info<T>::is_complex,
                                     type_info<U>::is_complex >::convert(u);
        }
        catch(type_error &e)
        {
            e.append(EXCEPTION_RECORD);
            throw e;
        }
        catch(range_error &e)
        {
            e.append(EXCEPTION_RECORD);
            throw e;
        }

        return value;

    }


//end of namespace
}
}
