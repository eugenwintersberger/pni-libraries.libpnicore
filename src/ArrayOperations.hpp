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
 * Header files with template functions for array opterations
 *
 * Created on: 22.05.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __ARRAYOPERATIONS_HPP__
#define __ARRAYOPERATIONS_HPP__

#include "Array.hpp"

namespace pni{
namespace utils{

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes
\brief compute the sum of all element in the array

Sum over all the elements in an Array type. The return type is choosen in a way
that no overflow can occur. This is necessary in particular for very small types
like 8Bit integers.
\param a array object over which to sum
\return number of type T
*/
template<typename ARRAYT> 
    typename ArrayType<ARRAYT::value_type>::Type sum(const ARRAYT &a)
{
    typedef typename ArrayType<ARRAYT::value_type>::Type RType;
    RType result(0);

    for(auto v: a) result += v;
    return result;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes
\brief get minimum value of an array type

Returns the minimum value stored in an array type. The result is of the same
type as the array elements. This function does not work for array types with
complex numbers as their elements as there are no order relations defined for
complex numbers.
\param a array type
\return value of type T
*/
template<typename ARRAYT> typename ARRAYT::value_type min(const ARRAYT &a) 
{
    typedef typename ARRAYT::value_type RType;
    RType result(0);

    for(auto v: a)
        if(v<result) result = v;

    return result;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_clases
\brief get maximum value of an array type

Returns the larges value in an array type object. The result is of same type as
the elements in the array type. This function does not work for arrays of
complex numbers as there are no order relations for complex numbers.

\param a array for which to determine the maximum
\return value of type T
*/
template<typename ARRAYT> typename ARRAYT::value_type max(const ARRAYT &a)
{
    typedef typename ARRAYT::value_type RType;

    RType result(0);

    for(auto v: a)
        if(v>result) result = v;

    return result;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes  
\brief minimum and maximum in the array

Return the minimunm and maximum values appearing in an array type. This function
will not work on arrays with complex elements as there are no order relations
for complex numbers.
\param a array object
\param min minimum value
\param max maximum value
*/
template<typename ARRAYT> void min_max(const ARRAYT &a,
                                       typename ARRAYT::value_type &min,
                                       typename ARRAYT::value_type &max)
{
    min=typename ARRAYT::value_type(0);
    max=typename ARRAYT::value_type(0);
    for(auto v: a)
    {
        if(v<min) min = v;
        if(v>max) max = v;
    }
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes  
\brief clip the array data

Set values greater or equal maxth to maxval and those smaller or equal minth
to minval. By default maxval and minval are equal to maxth and minth
respectively.
\param a array which to clip
\param minth minimum threshold
\param maxth maximum threshold
\param minval optional value to which values small minth will be set
\param maxval optional value to which values larger maxth will be set
*/
template<typename ARRAYT> void clip(ARRAYT &a,
                                    typename ARRAYT::value_type minth, 
                                    typename ARRAYT::value_type maxth,
                                    typename ARRAYT::value_type minval=minth,
                                    typename ARRAYT::value_type maxval=maxth)
{
    for(typename ARRAYT::value_type &v: a)
    {
        if(v <= minth) v = minval;
        if(v >= maxth) v = maxval;
    }
}


//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes 
\brief clip minimum values

Set values smaller or equal than threshold to value. By default value is equal
to the threshold.
\param a array which to clip
\param threshold threshold value
\param value the value to which to set data
*/
template<typename ARRAYT>
void min_clip(ARRAYT &a,typename ARRAYT::value_type threshold,
                        typename ARRAYT::value_type value=threshold)
{
    for(typename ARRAYT::value_type &v: a)
        if(v<=threshold) v = value;
}

//-----------------------------------------------------------------------------
//! clip maximum values

//! Set values larger or equal than threshold to threshold.
//! \param threshold threshold value
template<typename ARRAYT> 
void max_clip(ARRAYT &a,typename ARRAYT::value_type threshold,
                        typename ARRAYT::value_type value=threshold)
{
    for(typename ARRAYT::value_type &v: a)
        if(v>=threshold) v = value;
}


//end of namespace
}
}


#endif
