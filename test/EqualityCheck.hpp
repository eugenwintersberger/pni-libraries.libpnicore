/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: May 22, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/TypeInfo.hpp>

using namespace pni::core;

/*!
\brief class for equality check

In CppUnit checking for the equality of two values cannot be done in a generic
way. This is particularly true for numeric types. Integers are compared
differently than floating point numbers and complex numbers need a special
treatment in any case. This template provides overloads for different
situations. A single static member function is provided by these specializations
to perform the equality check.
\tparam T data type
\tparam is_int is true if T is an integer
\tparam is_complex set to true if T is a complex type.
*/
template<typename T,bool is_int,bool is_complex> class EqualityCheck;

//-----------------------------------------------------------------------------
/*!
\brief check integers

This is a specialization of the EqualityCheck template for integers. 
\tparam T integer type
*/
template<typename T> class EqualityCheck<T,true,false>
{
    public:
        /*!
        \brief check for equality

        Checks for the equality of two integer types.  The function does not
        return any boolean value but rather throws the appropriate CPPUNIT
        exception.
        \param a instance of T
        \param b instnace of T 
        */
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT(a == b);
        }
};

//-----------------------------------------------------------------------------
/*!
\brief check floating point numbers

Specialization of the EqualityCheck template for floating point numbers.
*/
template<typename T> class EqualityCheck<T,false,false>
{
    public:
        /*!
        \brief check for equality

        Checks for the equality of two floating point types.  The function does
        not return any boolean value but rather throws the appropriate CPPUNIT
        exception.
        \param a instance of T
        \param b instnace of T 
        */
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a,b,1.e-8);
        }
};

//-----------------------------------------------------------------------------
/*!
\brief check for complex numbers

Specialization of the EqualityCheck template for complex types. Complex types
are consideres equal if their real and imaginary parts are. 
*/
template<typename T> class EqualityCheck<T,false,true>
{
    public:
        /*!
        \brief check for equality

        Checks for the equality of two complex point types.  The function does
        not return any boolean value but rather throws the appropriate CPPUNIT
        exception.
        \param a instance of T
        \param b instnace of T 
        */
        static void check(const T &a,const T &b)
        {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a.real(),b.real(),1.e-8);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a.imag(),b.imag(),1.e-8);
        }
};

//-----------------------------------------------------------------------------
/*!
\brief equality check

The EqualityCheck template is rather complex to use. This is a convenience
function making its usage rather simple. Just call the function - no additional
configuration is required.
\tparam T type of the values we want to check
\param a instance of T
\param b instance of T 
*/
template<typename T> void check_equality(const T &a,const T &b)
{
    EqualityCheck<T,TypeInfo<T>::is_integer,TypeInfo<T>::is_complex>::check(a,b);
}

