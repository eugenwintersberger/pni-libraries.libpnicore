/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jul 24, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <limits>
#include <functional>

#include "../exception_utils.hpp"
#include "../type_info.hpp"

namespace pni{
namespace core{

    /*! 
    \ingroup numeric_array_classes
    \brief single threaded inplace arithmetics

    This class provides single threaded arithmetic operations for numeric
    arrays. It is used for inplace arithmetic operators (*=,+=,-=,/=). 
    All member functions provided are static. See the NumArray template for how
    this class is used in inplace arithmetics. This is the single threaded
    version for inplace arithmetics.
    \tparam ATYPE array type
    */
    template<typename ATYPE> class inplace_arithmetics
    {
                 
        public:
            //===================public types==================================
            //! value type of the array type
            typedef typename ATYPE::value_type value_type;
            //! array type iterator type
            typedef typename ATYPE::iterator iterator;
            //! array type const iterator type
            typedef typename ATYPE::const_iterator const_iterator;
            //==================inplace addition===============================
            /*!
            \brief add scalar to array

            Adds a scalar value of the value_type of the array to the array. 
            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            
            //performe something like array += scalar

            inplace_arithmetics<ATYPE>::add(array,scalar);
            \endcode
            \param a array of type ATYPE
            \param b scalar value of type ATYPE::value_type
            */
            static void add(ATYPE &a,value_type b)
            {
#ifdef NOFOREACH
                for(auto iter = a.begin();iter!=a.end();++iter)
                {
                    value_type &v = *iter;
#else
                for(value_type &v: a)
                {
#endif
                    v+= b;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief add container to array
            
            Add a container to an array of type ATYPE.
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());

            inplace_arithmetics<ATYPE>::add(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS template parameters of the container template
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS...>
            */
            template<typename CTYPE> static void add(ATYPE &a,const CTYPE &b)
            {
                typename CTYPE::const_iterator iter = b.begin();
#ifdef NOFOREACH
                for(auto viter = a.begin();viter!=a.end();++viter)
                {
                    value_type &v = *viter;
#else
                for(value_type &v: a)
                {
#endif
                    v += (*iter);
                    ++iter;
                }
            }

            //==================inplace subtraction===============================
            /*!
            \brief subtract scalar from array

            Subtract a scalar value from an array. 
            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            inplace_arithmetics<ATYPE>::sub(array,scalar);
            \endcode
            \param a instance of ATYPE
            \param b scalar value
            */
            static void sub(ATYPE &a,value_type b)
            {
#ifdef NOFOREACH
                for(auto iter = a.begin();iter!=a.end();++iter)
                {
                    value_type &v = *iter;
#else
                for(value_type &v: a)
                {
#endif
                    v -= b;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief subtract a container from an array

            Subtract an arbitrary container from an array.
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());
            inplace_arithmetics<ATYPE>::sub(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS container templat parameters
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS...>
            */
            template<typename CTYPE> static void sub(ATYPE &a,const CTYPE &b)
            {
                typename CTYPE::const_iterator iter = b.begin();
#ifdef NOFOREACH
                for(auto viter = a.begin();viter!=a.end();++viter)
                {
                    value_type &v = *viter;
#else
                for(value_type &v: a)
                {
#endif
                    v -= (*iter);
                    ++iter;
                }
            }

            //=====================inplace multiplication======================
            /*!
            \brief multiply array with scalar

            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            inplace_arithmetics<ATYPE>::mult(array,scalar);
            \endcode
            \param a instance of ATYPE
            \param b scalar value
            */
            static void mult(ATYPE &a,value_type b)
            {
#ifdef NOFOREACH
                for(auto iter = a.begin();iter!=a.end();++iter)
                {
                    value_type &v = *iter;
#else
                for(value_type &v: a)
                {
#endif
                    v *= b;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief multiply container with array

            Multiply an arbitrary container with an array. 
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());
            inplace_arithmetics<ATYPE>::mult(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS CTYPE parameters
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS...>
            */
            template<typename CTYPE> static void mult(ATYPE &a,const CTYPE &b)
            {
                typename CTYPE::const_iterator iter = b.begin();
#ifdef NOFOREACH
                for(auto viter = a.begin();viter!=a.end();++viter)
                {
                    value_type &v = *viter;
#else
                for(value_type &v: a)
                {
#endif
                    v *= (*iter);
                    ++iter;
                }
            }
            
            //=====================inplace division============================
            /*!
            \brief divide array with scalar

            Divide each element of an array by a scalar value.
            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            inplace_arithmetics<ATYPE>::div(array,scalar);
            \endcode
            \param a instance of ATYPE
            \param b scalar value
            */
            static void div(ATYPE &a,value_type b)
            {
#ifdef NOFOREACH
                for(auto iter = a.begin();iter!=a.end();++iter)
                {
                    value_type &v = *iter;
#else
                for(value_type &v: a) 
                {
#endif
                    v /= b;
                }
            }

            //-----------------------------------------------------------------
            /*!
            \brief divde array with container

            Divides each element of an array by the corresponding element of a
            container. 
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());
            inplace_arithmetics<ATYPE>::div(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS container template parameters
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS..>
            */
            template<typename CTYPE> static void div(ATYPE &a,const CTYPE &b)
            {
                typename CTYPE::const_iterator iter = b.begin();
#ifdef NOFOREACH
                for(auto viter = a.begin();viter!=a.end();++viter)
                {
                    value_type &v = *viter;
#else
                for(value_type &v: a)
                {
#endif
                    v /= (*iter);
                    ++iter;
                }
            }
            
    };

//end namespace
}
}
