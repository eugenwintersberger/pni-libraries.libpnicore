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
 * class provides information about native data types. This class provides
 * similar information to PNITypeInfo. In order to avoid redundancies one
 * of the two classes will vanish in future.
 *
 * Created on: Sep 9, 2011
 *     Author: Eugen Wintersberger
 *
 */
#pragma once

#include <limits>

#include "types.hpp"

namespace pni{
namespace core{

    /*! 
    \ingroup type_classes
    \brief type information class

    class that describes a PNI type as defined in PNITypes.hpp.  This template
    is used to obtain information about types in other classes like arrays and
    scalars.
    */
    template<typename T> class type_info
    {
        public:
            //==================public types===================================
            //! the type of T
            typedef T type;        
           
            //! the base type (only interesting for complex types)
            typedef T base_type;    
            
            //=================static members==================================
            //! size of the type in bytes
            static const size_t size = sizeof(T); 

            //! true if the type is an integer, false otherwise
            static const bool is_integer = std::numeric_limits<T>::is_integer; 

            //! true if the type is signed, false otherwise
            static const bool is_signed = std::numeric_limits<T>::is_signed; 
            
            //! true if the type represents a complex number, false otherwise
            static const bool is_complex = false; 

            //======================static member methods======================

            /*! 
            \brief sign check

            Method returns true if value is negative, false otherwise.
            \param value value for which to check the sign
            \return true if value<0, false otherwise
            */
            static bool is_negative(T value)
            {
                if (value < 0) return true;
                return false;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief minimum limit

            returns the smallest value that can be represented by type T.
            \return lower limit of T
            */
            static T min()
            {
                //in the case of integers we can use min
                if (std::numeric_limits<T>::is_integer)
                    return std::numeric_limits<T>::min();
                else
                    //for floating point numbers this is a bit different min
                    //would yield here the value of the smallest possible number
                    return -std::numeric_limits<T>::max();
            }

            //-----------------------------------------------------------------
            /*! 
            \brief maximum limit

            Returns the largest value that can be represented by T.
            \return upper limit of T
            */
            static T max() { return std::numeric_limits<T>::max(); }

    };


    //! \cond NO_API_DOC
    template<> class type_info<complex32>
    {
        public:

            typedef complex32 type;
            typedef float32 base_type;

            static const size_t size = sizeof(complex32);
            static const bool is_integer = std::numeric_limits<float32>::is_integer;
            static const bool is_signed = std::numeric_limits<float32>::is_signed;
            static const bool is_complex = true;

            //---------------------------------------------------------------------
            static bool is_negative(complex32 value){ return false; }


            //---------------------------------------------------------------------
            //! return the minimum value of the Complex32 type
            static float32 min() { return -std::numeric_limits<float32>::max(); }

            //---------------------------------------------------------------------
            //! return the maximum value of the Complex32 type
            static float32 max() { return std::numeric_limits<float32>::max(); }

    };



    //! \ingroup Data-objects
    //! \brief PNITypes specialization for 64Bit IEEE floating point complex type
    template<> class type_info<complex64>
    {
        public:

            typedef complex64 type;
            typedef float64 base_type;

            static const size_t size = sizeof(complex64);
            static const bool is_integer = std::numeric_limits<float64>::is_integer;
            static const bool is_signed = std::numeric_limits<float64>::is_signed;
            static const bool is_complex = true;

            //-----------------------------------------------------------------
            static bool is_negative(complex64 value){ return false; }

            //-----------------------------------------------------------------
            //! return the minimum value of the Complex64 type
            static float64 min() { return -std::numeric_limits<float64>::max(); }

            //-----------------------------------------------------------------
            //! return the maximum value of the Complex64 type
            static float64 max() { return std::numeric_limits<float64>::max(); }

    };

    //! \ingroup Data-objects
    //! \brief PNITypes specialization for 128Bit IEEE floating point complex type
    template<> class type_info<complex128>
    {
        public:
            typedef complex128 type;
            typedef float128 base_type;

            static const size_t size = sizeof(complex128);
            static const bool is_integer = std::numeric_limits<float128>::is_integer;
            static const bool is_signed = std::numeric_limits<float128>::is_signed;
            static const bool is_complex = true;

            //-----------------------------------------------------------------
            static bool is_negative() { return false; }

            //-----------------------------------------------------------------
            //! return the minimum value of the Complex128 type
            static float128 min() { return -std::numeric_limits<float128>::max(); }

            //-----------------------------------------------------------------
            //! return the maximum value of the Complex128 type
            static float128 max() { return std::numeric_limits<float128>::max(); }
    };

    //! \ingroup Data-objects
    //! \brief type info for bool
    template<> class type_info<bool>
    {
        public:
            typedef bool type;
            typedef bool base_type;

            static const size_t size = sizeof(bool);
            static const bool is_integer = true;
            static const bool is_signed = false;
            static const bool is_complex = false;

            static bool is_negative() { return false; }

            static bool min() { return false; }

            static bool max() { return true; }

    };
    //! \endcond

//end of namespace
}
}
