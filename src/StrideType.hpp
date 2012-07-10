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
 * along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jul 10, 2012
 *     Author: Eugen Wintersberger
 *
 */
#ifndef __STRIDETYPE__
#define __STRIDETYPE__

namespace pni{
namespace utils{

    /*!
    \ingroup util_classes
    \brief recursive stride computing type

    This type is used to compute the stride of a particular dimension of a 
    static array. This is just the basic definition of the class. All work is
    done in its specializations. The template parameters have the  
    \tparam N the index of the dimension 
    \tparam CNT dimension counter
    \tparam DO enable calculation
    \tparam DIMS number of elements along each dimension
    */
    template<size_t N,size_t CNT,bool DO,size_t ...DIMS> struct ComputeStride
    {};

    //=========================================================================
    /*!
    \ingroup util_classes
    \brief partial specialization of ComputeStride

    This specialization does nothing else than multiplying the stride value with
    one and proceeds to the next dimension. The DO template parameter of the
    original template is set to false. 
    \tparam N the index of the dimension 
    \tparam CNT dimension counter
    \tparam DIMS number of elements along each dimension
    */
    template<size_t N,size_t CNT,size_t d, size_t ...DIMS> 
        struct ComputeStride<N,CNT,false,d,DIMS...>
    {
        //!< stride value
        static const size_t value = 1*ComputeStride<N,CNT+1,((CNT+1)>N),DIMS...>::value; 
    };

    /*! 
    \ingroup util_classes
    \brief partial specialization of ComputeStride 

    This specialization of ComputeStride contributes the size of the dimension
    to the stride and moves on to the next dimension. The DO template parameter
    of ComputeStride is here set to true. 
    \tparam N the index of the dimension 
    \tparam CNT dimension counter
    \tparam DIMS number of elements along each dimension
    */
    template<size_t N,size_t CNT,size_t d,size_t ...DIMS> 
        struct ComputeStride<N,CNT,true,d,DIMS...>
    {
        //!< stride value
        static const size_t value = d*ComputeStride<N,CNT+1,((CNT+1)>N),DIMS...>::value;
    };

    /*! 
    \ingroup util_classes
    \brief partial specialization of ComputeStride

    The break condition for the case that we want the stride for a dimension
    being not the last dimension of the array
    \tparam N index of the dimension
    \tparam CNT dimension counter
    \tparam D number of elements of the last dimension
    */
    template<size_t N,size_t CNT,size_t D> struct ComputeStride<N,CNT,true,D>
    {
        static const size_t value = D; //!< stride value
    };
 
    /*!
    \ingroup util_classes
    \brief partial specialization of ComputeStride

    This is the case for the break condition if we want the stride for the 
    last dimension in the array. In this case CNT never reaches the condition
    CNT+1>N because this would point to a location beyond the arrays bounds.
    \tparam N index of the dimension
    \tparam CNT dimension counter
    \tparam D number of elements of the last dimension
    */
    template<size_t N,size_t CNT,size_t D> struct ComputeStride<N,CNT,false,D>
    {
        //!< stride value
        static const size_t value = 1; 
    };

   
    //=========================================================================
    /*! 
    \ingroup util_classes
    \brief type for a single stride

    Type representing the stride of dimension N of an array of dimension given
    by DIMS. 
    This little example shows how to compute the stride of dimension 2 of an 
    array of shape (3,4,5,6). 
    \code
    size_t stride = Stride<2,3,4,5,6>::value
    \endcode
    This type is not intended to be used by a user but is used inside static
    array types.
    */
    template<size_t N,size_t ...DIMS> struct Stride
    {
        //! stride value 
        static const size_t value = ComputeStride<N,0,false,DIMS...>::value; 
    };


    //=========================================================================
    /*! 
    \ingroup util_classes
    \brief stride computing type

    This type can be used to compute the stride of a particular dimension in a
    fixed size array using a constant expression static template function.

    To compute the stride of dimension 2 of a static array of shape (3,4,5,2)
    use the following code
    \code
    typedef StrideCalc<3,4,5,2> calc;
    std::cout<<"offset of dimension 2: "<<calc::value<2>()<<std::endl;
    \endcode
    This can be done in a single line of code too
    \code
    size_t stride = StrideCalc<3,4,5,2>::template value<2>();
    \endcode
    Note the additional \c template keyword required to make the compiler happy.
    */
    template<size_t ...DIMS> struct StrideCalc
    {

        /*! 
        \brief compute stride for a dimension

        This static method can be used to compute the stride for a particular
        dimension. The index of the dimension is passed as the template
        parameter N. The method is a constexpr and thus can be used in
        compile-time expressions.
        \return stride of dimension N
        */
        template<size_t N> static constexpr size_t value()
        {
            return Stride<N,DIMS...>::value;
        }
    };





//end of namespace
}
}
#endif
