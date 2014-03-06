//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: Dec 2, 2013
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
#pragma once

#include "mdarray.hpp"
//#include "arrays.hpp"
#include "index_map/index_maps.hpp"
#include "../types/complex_utils.hpp"
#include "scalar.hpp"
#include "math/add_op.hpp"
#include "math/sub_op.hpp"
#include "math/mult_op.hpp"
#include "math/div_op.hpp"

namespace pni{
namespace core{

    //======================binary addition operator===========================
    /*!
    \ingroup numeric_array_classes
    \brief binary addition operator 

    Addition between two instaces of array like objects.
    
    \code
    mdarray<...> a = ...;
    mdarray<...> b = ...;
    mdarray<...> c = ...;

    c = a+b;
    \endcode

    \tparam LHS left hand side array type
    \tparam RHS right hand side array type
    \param a left operand instance
    \param b right operand instance
    \return mdarray with the expression template
    */
    template<typename LHS,typename RHS,
            typename = typename std::enable_if<
            is_array<LHS>::value && is_array<RHS>::value
            >::type
            >
    mdarray<add_op<LHS,RHS>,typename LHS::map_type,typename LHS::inplace_arithmetic>
    operator+(const LHS &a,const RHS &b)
    {
        typedef add_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename LHS::inplace_arithmetic>
        return_type;

        return return_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary addition operator

    Addition operator between an array type object and a scalar.
    \code
    dynamic_array<float32> a = ....;
    dynamic_array<float32> c = ....;
    float32 d = ...;

    c = a+d;
    \endcode

    \tparam LHS left hand side array type
    \tparam T   scalar data type
    \param a reference to LHS operand
    \param b reference to RHS operand
    \return mdarray with the expression template
    */
    template<typename LHS,
             typename T,
             typename = typename std::enable_if<
              is_array<LHS>::value && !is_array<T>::value
              >::type
             >
    mdarray<add_op<LHS,scalar<T>>,typename LHS::map_type,typename LHS::inplace_arithmetic>
    operator+(const LHS &a, const T& b)
    {
        typedef add_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename
            LHS::inplace_arithmetic> return_type;

        return return_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary addition operator

    Addition operator between an array type object and a scalar.
    \code
    dynamic_array<float32> a = ....;
    dynamic_array<float32> c = ....;
    float32 d = ...;

    c = d+a;
    \endcode

    \tparam T data type of the scalar operand
    \tparam RHS data type of the right hand side operand
    \param a scalar value
    \param b instance of an RHS array
    \return mdarray instance with the expression template
    */
    template<typename T,
             typename RHS,
             typename = typename std::enable_if<
             !is_array<T>::value && is_array<RHS>::value
                 >::type
            >
    mdarray<add_op<scalar<T>,RHS>,typename RHS::map_type,typename RHS::inplace_arithmetic>
    operator+(const T& a, const RHS &b)
    {
        typedef add_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,typename RHS::map_type,typename
            RHS::inplace_arithmetic> result_type;
        typedef scalar<T> scalar_type;
        
        return result_type(b.map(),operator_type(scalar_type(a),b));
    }

    //======================binary subtraction operator========================
    /*!
    \ingroup numeric_array_classes
    \brief binary subtraction operator 
    
    Subtraction between two array like objects.
    
    \code
    mdarray<...> a = ...;
    mdarray<...> b = ...;
    mdarray<...> c = ...;

    c = a - b;
    \endcode

    \tparam LHS left hand side operator type
    \tparam RHS right hand side operator type
    \param a left operand
    \param b right operand
    \return mdarray with the expression template
    */
    template<typename LHS,
             typename RHS,
             typename = typename std::enable_if<
             is_array<LHS>::value && is_array<RHS>::value >::type
            >
    mdarray<sub_op<LHS,RHS >,typename LHS::map_type, typename LHS::inplace_arithmetic>
    operator-(const LHS &a, const RHS &b)
    {
        typedef sub_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,
                        typename LHS::inplace_arithmetic> result_type;


        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary subtraction operator

    Subtracting a scalar type from an array type.
    \code
    dynamic_array<float32> a = ...;
    dynamic_array<float32> c = ...;
    float32 b = ...;

    c = a - b; 
    \endcode

    \tparam LHS left hand side array type
    \tparam T right handside scalar type
    \param a left operand 
    \param b right operand 
    \return mdarray instance with the expression template
    */
    template<typename LHS,
             typename T,
             typename = typename std::enable_if<
             is_array<LHS>::value && !is_array<T>::value>::type
            >
    mdarray<sub_op<LHS,scalar<T> >,typename LHS::map_type,typename LHS::inplace_arithmetic >
    operator-(const LHS &a, const T& b)
    {
        typedef sub_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename
            LHS::inplace_arithmetic> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary subtraction operator

    Subtracting an array from a scalar
    \code
    float32 b = ...;
    dynamic_array<float32> a = ...;
    dynamic_array<float32> c = ...;

    c = b - a;
    \endcode
    
    \tparam T scalar right handside type
    \tparam RHS right hand side array type
    \param a scalar value
    \param b array like right handside
    \return instance of NumArray with an expression template
    */
    template<typename T,typename RHS,
             typename = typename std::enable_if<
             !is_array<T>::value && is_array<RHS>::value>::type
            >
    mdarray<sub_op<scalar<T>,RHS>,typename RHS::map_type,typename RHS::inplace_arithmetic>
    operator-(const T &a, const RHS &b)
    {
        typedef sub_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,typename RHS::map_type,typename
            RHS::inplace_arithmetic> result_type;
        
        return result_type(b.map(),operator_type(a,b));
    }
    
    //=================binary division operator================================
    /*!
    \ingroup numeric_array_classes
    \brief binary division operator 

    Binary division between two array objects
    
    \code
    mdarray<...> a = ...;
    mdarray<...> b = ...;
    mdarray<...> c = ...;
    c = a / b;
    \endcode

    \tparam LHS left hand side array type
    \tparam RHS right hand side array type
    \param a left operand
    \param b right operand
    \return mdarray with the expression template
    */
    template<typename LHS,
             typename RHS,
             typename = typename std::enable_if<
             is_array<LHS>::value && is_array<RHS>::value>::type
            >
    mdarray<div_op<LHS,RHS>,typename LHS::map_type,typename LHS::inplace_arithmetic>
    operator/(const LHS &a, const RHS &b)
    {
        typedef div_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename
            LHS::inplace_arithmetic> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary division operator

    Division of an array type by a scalar type
    \code
    mdarray<...> a = ...;
    mdarray<...> c = ...;
    float64 b = ...;

    c = a/b;
    \endcode

    \tparam LHS left hand side array type
    \tparam T right hand side scalar type
    \param a left operand
    \param b right operand 
    \return mdarray with the expression template
    */
    template<typename LHS,
             typename T,
             typename = typename std::enable_if<
             is_array<LHS>::value && !is_array<T>::value>::type
            >
    mdarray<div_op<LHS,scalar<T>>,typename LHS::map_type,typename LHS::inplace_arithmetic>
    operator/(const LHS &a, const T &b)
    {
        typedef div_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename
            LHS::inplace_arithmetic> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary division operator

    Division of a scalar by an array type
    \code
    mdarray<...> a = ...;
    mdarray<...> c = ...;
    float64 b = ...;

    c = b / a;
    \endcode

    \tparam T left hand side scalar type
    \tparam RHS right hand side array type
    \param a scalar value
    \param b array instance
    \return mdarray with the expression template
    */
    template<typename T,
             typename RHS,
             typename = typename std::enable_if<
             !is_array<T>::value && is_array<RHS>::value>::type
            >
    mdarray<div_op<scalar<T>,RHS>,typename RHS::map_type,typename RHS::inplace_arithmetic>
    operator/(const T &a, const RHS &b)
    {
        typedef div_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,typename RHS::map_type,typename RHS::inplace_arithmetic> result_type;

        return result_type(b.map(),operator_type(a,b));
    }
    
    //===================Multiplication operator================================
    /*!
    \ingroup numeric_array_classes
    \brief binary multiplication operator

    Multiplication between two array type instances
    \code
    mdarray<...> a = ...;
    mdarray<...> b = ...;
    mdarray<...> c = ...;
    c = a * b;
    \endcode

    \tparam LHS left hand side array type
    \tparam RHS right hand side array type
    \param a left operand
    \param b right operand
    \return return mdarray instance with expression template
    */
    template<typename LHS,
             typename RHS,
             typename = typename std::enable_if<
             is_array<LHS>::value && is_array<RHS>::value>::type
            >
    mdarray<mult_op<LHS,RHS>,typename LHS::map_type,typename LHS::inplace_arithmetic>
    operator*(const LHS &a, const RHS &b)
    {
        typedef mult_op<LHS,RHS> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename LHS::inplace_arithmetic> result_type;

        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary multiplication operator

    Multiplication between an array and a scalar
    \code
    dynamic_array<float32> a = ...;
    dynamic_array<float32> c = ...;
    float32 b = 200;

    c = a * b;
    \endcode

    \tparam LHS left hand side array type
    \tparam T right hand scalar type
    \param a left operand 
    \param b right operand 
    \return mdarray with the expression template
    */
    template<typename LHS,
             typename T,
             typename = typename std::enable_if<
             is_array<LHS>::value && !is_array<T>::value>::type
            >
    mdarray<mult_op<LHS,scalar<T>>,typename LHS::map_type,typename LHS::inplace_arithmetic>
    operator*(const LHS &a, const T &b)
    {
        typedef mult_op<LHS,scalar<T>> operator_type;
        typedef mdarray<operator_type,typename LHS::map_type,typename
            LHS::inplace_arithmetic>  result_type;
        
        return result_type(a.map(),operator_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary multiplication operator

    Multiplication between an array and a scalar
    \code
    dynamic_array<float32> a = ...;
    dynamic_array<float32> c = ...;
    float32 b = 200;

    c = b * a;
    \endcode

    \tparam T left hand side scalar type
    \tparam RHS right hand side array type
    \param a left operand
    \param b right operand 
    \return mdarray with the expression template
    */
    template<typename T,
             typename RHS,
             typename = typename std::enable_if<
             !is_array<T>::value  && is_array<RHS>::value >::type
            >
    mdarray<mult_op<scalar<T>,RHS>,typename RHS::map_type,typename RHS::inplace_arithmetic>
    operator*(const T &a, const RHS &b)
    {
        typedef mult_op<scalar<T>,RHS> operator_type;
        typedef mdarray<operator_type,typename RHS::map_type,typename RHS::inplace_arithmetic> result_type;

        return result_type(b.map(),operator_type(a,b));
    }

//end of namespace
}
}
