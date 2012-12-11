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
 * A couple of utility operators and function for complex numbers.
 *
 * Created on: Sep 9, 2011
 *     Author: Eugen Wintersberger
 *
 */

#pragma once

#include "Types.hpp"
#include "TypeInfo.hpp"

using namespace pni::utils;

namespace pni{
namespace utils{

    //-------------------------------------------------------------------------
    template<typename C,typename O> C __convert(const O &v)
    {
        if(TypeInfo<O>::is_complex) return C(v.real(),v.imag());

        return C(v);
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number equality operator

    Comparison of 32- and 64-Bit complex numbers. The operator returns true if
    real and imaginary part of the two numbers are equal.
    \param a 32-Bit complex value
    \param b 64-Bit complex value
    \return true if equal.
    */
    bool operator==(const Complex32 &a,const Complex64 &b);
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number equality operator

    Comparison of 32- and 128-Bit complex numbers. The operator returns true if
    real and imaginary part of the two numbers are equal.
    \param a 32-Bit complex value
    \param b 128-Bit complex value
    \return true if equal.
    */
    bool operator==(const Complex32 &a,const Complex128 &b);

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number equality operator

    Comparison of 64- and 32-Bit complex numbers. The operator returns true if
    real and imaginary part of the two numbers are equal.
    \param a 64-Bit complex value
    \param b 32-Bit complex value
    \return true if equal.
    */
    bool operator==(const Complex64 &a,const Complex32 &b);
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number equality operator

    Comparison of 64- and 128-Bit complex numbers. The operator returns true if
    real and imaginary part of the two numbers are equal.
    \param a 64-Bit complex value
    \param b 128-Bit complex value
    \return true if equal.
    */
    bool operator==(const Complex64 &a,const Complex128 &b);

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number equality operator

    Comparison of 128- and 32-Bit complex numbers. The operator returns true if
    real and imaginary part of the two numbers are equal.
    \param a 128-Bit complex value
    \param b 32-Bit complex value
    \return true if equal.
    */
    bool operator==(const Complex128 &a,const Complex32 &b);
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number equality operator

    Comparison of 128- and 64-Bit complex numbers. The operator returns true if
    real and imaginary part of the two numbers are equal.
    \param a 128-Bit complex value
    \param b 64-Bit complex value
    \return true if equal.
    */
    bool operator==(const Complex128 &a,const Complex64 &b);

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number inequality operator

    Comparison of 32- and 64-Bit complex numbers. The operator returns true if
    either real or imaginary part or both of the two numbers differ.
    \param a 32-Bit complex value
    \param b 64-Bit complex value
    \return true if equal.
    */
    bool operator!=(const Complex32 &a,const Complex64 &b);
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number inequality operator

    Comparison of 32- and 128-Bit complex numbers. The operator returns true if
    either real or imaginary part or both of the two numbers differ.
    \param a 32-Bit complex value
    \param b 128-Bit complex value
    \return true if equal.
    */
    bool operator!=(const Complex32 &a,const Complex128 &b);

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number inequality operator

    Comparison of 64- and 32-Bit complex numbers. The operator returns true if
    either real or imaginary part or both of the two numbers differ.
    \param a 64-Bit complex value
    \param b 32-Bit complex value
    \return true if equal.
    */
    bool operator!=(const Complex64 &a,const Complex32 &b);
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number inequality operator

    Comparison of 64- and 128-Bit complex numbers. The operator returns true if
    either real or imaginary part or both of the two numbers differ.
    \param a 64-Bit complex value
    \param b 128-Bit complex value
    \return true if equal.
    */
    bool operator!=(const Complex64 &a,const Complex128 &b);

    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number inequality operator

    Comparison of 128- and 32-Bit complex numbers. The operator returns true if
    either real or imaginary part or both of the two numbers differ.
    \param a 128-Bit complex value
    \param b 32-Bit complex value
    \return true if equal.
    */
    bool operator!=(const Complex128 &a,const Complex32 &b);
    
    //-------------------------------------------------------------------------
    /*!
    \ingroup type_classes
    \brief complex number inequality operator

    Comparison of 128- and 64-Bit complex numbers. The operator returns true if
    either real or imaginary part or both of the two numbers differ.
    \param a 128-Bit complex value
    \param b 64-Bit complex value
    \return true if equal.
    */
    bool operator!=(const Complex128 &a,const Complex64 &b);

//end of namespace
}
}
