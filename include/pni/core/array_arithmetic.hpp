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
 * Created on: Dec 2, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include "mdarray.hpp"
#include "math/add_op.hpp"

namespace pni{
namespace core{

    //======================binary addition operator===========================
    /*!
    \ingroup numeric_array_classes
    \brief addition operator 

    Addition operator between two instances of NumArray using expression
    templates to perform the operation.
    Both arrays must be of same shape.
    
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > b(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));

    std::fill(a.begin(),a.end(),100);
    std::fill(b.begin(),b.end(),200);

    c = a + b;

    \endcode

    \throws ShapeMissmatchError if array shapes do not coincide
    \tparam AT1 storage type of the left NumArray
    \tparam AT2 storage type of the right NumArray
    \param a left operand
    \param b right operand
    \return instance of NumArray with an expression template as storage type
    */
    template<typename LHS,typename RHS,
            typename = typename std::enable_if<
            (!std::is_pod<LHS>::value) && (!std::is_pod<RHS>::value)
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
    \brief addition operator

    Addition operator between an instance of NumArray and a scalar value.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a + b;

    \endcode
    \tparam AT storage type of the NumArray on the left side
    \param a left operand (NumArray)
    \param b right operand (scalar)
    \return NumArray instance with an expression template storage type
    */
    template<typename LHS,
             typename T,
             typename = typename std::enable_if<
              (!std::is_pod<LHS>::value) && std::is_pod<T>::value
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
    \brief addition operator

    Addition operator between an instance of NumArray and 
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b + a;

    \endcode
    \tparam AT storage type of the right operand (NumArray)
    \param a scalar value
    \param b instance of NumArray
    \return instance of NumArray with an expression template
    */
    template<typename T,
             typename RHS,
             typename = typename std::enable_if<
             std::is_pod<T>::value && (!std::is_pod<RHS>::value)
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

//end of namespace
}
}
