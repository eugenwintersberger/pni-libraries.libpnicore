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
 * Created on: Jul 23,2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#pragma once

namespace pni{
namespace core{

    /*!
    \ingroup numeric_array_classes
    \brief vector tag
    
    It can be used to identify types that provide a math_object_tag to identify
    it as a vector. 

    \code{.cpp}
    numarray<sarray<float64,3>,vector_tag> vector_t;
    \endcode

    Vectors are assumed to be one dimensional objects.
    */
    struct vector_tag{};

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief matrix tag
    
    It can be used to identify types that provide a math_object_tag to identify
    it as a matrix. 

    \code{.cpp}
    numarray<sarray<float64,3>,vector_tag> vector_t;
    \endcode

    Matrices are assumed to be 2D objects. 
    */
    struct matrix_tag{};

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_class
    \brief nothing special tag

    This is the default tag if a numeric type needs to special treatment. 
    */
    struct non_tag{};

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_class
    \brief tensor tag

    Identifies an array as a tensor. 
    */
    struct tensor_tag{};

    //-------------------------------------------------------------------------
    template<typename TAG> struct is_matrix;

    template<> struct is_matrix<matrix_tag>
    {
        bool value = true;
    };

    //-------------------------------------------------------------------------
    template<typename TAG> struct is_vector;

    template<> struct is_vector<vector_tag>
    {
        bool value = true;
    };

    //-------------------------------------------------------------------------
    template<typename TAG> struct is_tensor;

    template<> struct is_tensor<tensor_tag>
    {
        bool value = true;
    };




//end of namespace
}
}
