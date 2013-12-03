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
             !std::is_pos<LHS>::value && !std::is_pos<RHS>::value
                 >::type
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

    Subtraction operator between an instance of NumArray and a scalar value.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a - b;

    \endcode
    \tparam AT storage type of the NumArray on the left side
    \param a left operand (NumArray)
    \param b right operand (scalar)
    \return NumArray instance with an expression template storage type
    */
    template<typename AT,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<sub<numarray<AT,TAGTYPE,IPA,BMT_FLAG>,
                 scalar<typename AT::value_type> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator-(const numarray<AT,TAGTYPE,IPA,BMT_FLAG> &a,
              typename AT::value_type const &b)
    {
        typedef numarray<AT,TAGTYPE,IPA,BMT_FLAG> atype;
        typedef scalar<typename AT::value_type> stype;
        typedef sub<atype,stype> op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary subtraction operator

    Subtraction operator between an instance of NumArray and 
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b - a;

    \endcode
    \tparam AT storage type of the right operand (NumArray)
    \param a scalar value
    \param b instance of NumArray
    \return instance of NumArray with an expression template
    */
    template<typename AT,typename TAGTYPE,
             template<typename> class IPA,bool BMT_FLAG>
    numarray<sub<scalar<typename AT::value_type>,
                 numarray<AT,TAGTYPE,IPA,BMT_FLAG> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator-(typename AT::value_type const &a,
              const numarray<AT,TAGTYPE,IPA,BMT_FLAG> &b)
    {
        typedef numarray<AT,TAGTYPE,IPA,BMT_FLAG> atype;
        typedef scalar<typename AT::value_type> stype;
        typedef sub<stype,atype> op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(stype(a),b));
    }
    
    //=================binary division operator================================
    /*!
    \ingroup numeric_array_classes
    \brief binary division operator 

    Division operator between two instances of NumArray using expression
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

    c = a / b;

    \endcode

    \throws ShapeMissmatchError if array shapes do not coincide
    \tparam AT1 storage type of the left NumArray
    \tparam AT2 storage type of the right NumArray
    \param a left operand
    \param b right operand
    \return instance of NumArray with an expression template as storage type
    */
    template<typename AT1,
             typename AT2,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<div_op<numarray<AT1,TAGTYPE,IPA,BMT_FLAG>,
                    numarray<AT2,TAGTYPE,IPA,BMT_FLAG> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator/(const numarray<AT1,TAGTYPE,IPA,BMT_FLAG> &a,
              const numarray<AT2,TAGTYPE,IPA,BMT_FLAG> &b)
    {
        typedef div_op<numarray<AT1,TAGTYPE,IPA,BMT_FLAG>,
                       numarray<AT2,TAGTYPE,IPA,BMT_FLAG> > op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief binary division operator

    Division operator between an instance of NumArray and a scalar value.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a / b;

    \endcode
    \tparam AT storage type of the NumArray on the left side
    \param a left operand (NumArray)
    \param b right operand (scalar)
    \return NumArray instance with an expression template storage type
    */
    template<typename AT,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<div_op<numarray<AT,TAGTYPE,IPA,BMT_FLAG>,
                    scalar<typename AT::value_type> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator/(const numarray<AT,TAGTYPE,IPA,BMT_FLAG> &a,
              typename AT::value_type const &b)
    {
        typedef numarray<AT,TAGTYPE,IPA,BMT_FLAG> atype;
        typedef scalar<typename AT::value_type> stype;
        typedef div_op<atype,stype> op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup numeric_array_classes
    \brief binary division operator

    Division operator between an instance of NumArray and 
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b / a;

    \endcode
    \tparam AT storage type of the right operand (NumArray)
    \param a scalar value
    \param b instance of NumArray
    \return instance of NumArray with an expression template
    */
    template<typename AT,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<div_op<scalar<typename AT::value_type>,
                    numarray<AT,TAGTYPE,IPA,BMT_FLAG> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator/(typename AT::value_type const &a,
              const numarray<AT,TAGTYPE,IPA,BMT_FLAG> &b)
    {
        typedef numarray<AT,TAGTYPE,IPA,BMT_FLAG> atype;
        typedef scalar<typename AT::value_type> stype;
        typedef div_op<stype,atype> op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(stype(a),b));
    }
    
    //===================Multiplication operator================================
    /*!
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of two instances of 
    the NumArray template.For this operation to succeed the arrays must have
    equal shape.
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > b(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));

    std::fill(a.begin(),a.end(),100);
    std::fill(b.begin(),b.end(),200);

    c = a * b;

    \endcode

    \throws shape_mismatch_error if shapes do not match
    \tparam AT1 storage type of left operand
    \tparam AT2 storage type of right operand
    \param a left operand
    \param b right operand
    \return instance of NumArray with result
    */
    template<typename AT1,
             typename AT2,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<mult<numarray<AT1,TAGTYPE,IPA,BMT_FLAG>,
                  numarray<AT2,TAGTYPE,IPA,BMT_FLAG> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator*(const numarray<AT1,TAGTYPE,IPA,BMT_FLAG> &a,
              const numarray<AT2,TAGTYPE,IPA,BMT_FLAG> &b)
    {
        typedef mult<numarray<AT1,TAGTYPE,IPA,BMT_FLAG>,
                     numarray<AT2,TAGTYPE,IPA,BMT_FLAG> > op_type;
        //check_equal_shape(a,b,EXCEPTION_RECORD);

        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(a,b));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of an instance of
    NumArray with a scalar.  
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = a * b;

    \endcode
    \tparam AT storage type of the NumArray instance
    \param a left operand (array type)
    \param b right operand (scalar)
    \return instance of NumArray with result
    */
    template<typename AT,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<mult<numarray<AT,TAGTYPE,IPA,BMT_FLAG>,
                  scalar<typename AT::value_type> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator*(const numarray<AT,TAGTYPE,IPA,BMT_FLAG> &a,
              typename AT::value_type const &b)
    {
        typedef numarray<AT,TAGTYPE,IPA,BMT_FLAG> atype;
        typedef scalar<typename AT::value_type> stype;
        typedef mult<atype,stype> op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(a,stype(b)));
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup numeric_array_classes
    \brief multiplication operator

    Expression template operator for the multiplication of an instance of
    numarray and a scalar.    
    \code
    typedef std::vector<size_t> shape_t;
    shape_t shape{3,4,100};

    numarray<darray<float32> > a(darray<float32>(shape));
    numarray<darray<float32> > c(darray<float32>(shape));
    float32 b = 200;

    std::fill(a.begin(),a.end(),100);
    c = b * a;

    \endcode
    \tparam AT storage type for the NumArray instance
    \param a left operand (scalar value)
    \param b right operand (array type)
    \return NumArray instance representing the result
    */
    template<typename AT,
             typename TAGTYPE,
             template<typename> class IPA,
             bool BMT_FLAG>
    numarray<mult<scalar<typename AT::value_type>,
                  numarray<AT,TAGTYPE,IPA,BMT_FLAG> >,TAGTYPE,
             IPA,BMT_FLAG>
    operator*(typename AT::value_type const &a,
              const numarray<AT,TAGTYPE,IPA,BMT_FLAG> &b)
    {
        typedef numarray<AT,TAGTYPE,IPA,BMT_FLAG> atype;
        typedef scalar<typename AT::value_type> stype;
        typedef mult<stype,atype> op_type;
        return numarray<op_type,TAGTYPE,IPA,BMT_FLAG>(op_type(stype(a),b));
    }
//end of namespace
}
}
