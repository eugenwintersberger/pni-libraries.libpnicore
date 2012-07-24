/*
 * SimpleArithmetics.hpp
 *
 *  Created on: Aug 31, 2011
 *      Author: eugen
 */

#ifndef INPLACEARITHMETICS_HPP_
#define INPLACEARITHMETICS_HPP_

#include <limits>
#include <functional>

#include "Exceptions.hpp"
#include "ExceptionUtils.hpp"
#include "TypeInfo.hpp"

namespace pni{
namespace utils{

//! \cond no_doc
//Inplace arithmetics of typed objects - the object can only be a left-value
    template<typename ATYPE>
    class InplaceArithmetics
    {
                 
        public:
            //===================public types==================================
            typedef typename ATYPE::value_type value_type;
            typedef typename ATYPE::iterator iterator;
            typedef typename ATYPE::const_iterator const_iterator;
            //==================inplace addition===============================
            //object with a scalar
            static void add(ATYPE &a,value_type b)
            {
                for(value_type &v: a) v+= b;
            }


            //-----------------------------------------------------------------
            //add with another array of same type
            static void add(ATYPE &a,const ATYPE &b)
            {
                const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v+=(*iter);
                    ++iter;
                }
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            static void add(ATYPE &a,const CTYPE<OTS...> &b)
            {
                typename CTYPE<OTS...>::const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v += (*iter);
                    ++iter;
                }
            }

            //==================inplace subtraction===============================
            //object with a scalar
            static void sub(ATYPE &a,value_type b)
            {
                for(value_type &v: a) v -= b;
            }

            //-----------------------------------------------------------------
            static void sub(ATYPE &a,const ATYPE &b)
            {
                const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v -= (*iter);
                    ++iter;
                }
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            static void sub(ATYPE &a,const CTYPE<OTS...> &b)
            {
                typename CTYPE<OTS...>::const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v -= (*iter);
                    ++iter;
                }
            }

            //=====================inplace multiplication======================
            //object with a scalar
            static void mult(ATYPE &a,value_type b)
            {
                for(value_type &v: a) v *= b;
            }

            //-----------------------------------------------------------------
            static void mult(ATYPE &a,const ATYPE &b)
            {
                const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v *= (*iter);
                    ++iter;
                }
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            static void mult(ATYPE &a,const CTYPE<OTS...> &b)
            {
                typename CTYPE<OTS...>::const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v *= (*iter);
                    ++iter;
                }
            }
            
            //=====================inplace division============================
            //object with a scalar
            static void div(ATYPE &a,value_type b)
            {
                for(value_type &v: a) v /= b;
            }

            //-----------------------------------------------------------------
            static void div(ATYPE &a,const ATYPE &b)
            {
                const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v /= (*iter);
                    ++iter;
                }
            }

            //-----------------------------------------------------------------
            template<template<typename ...> class CTYPE,typename ...OTS>
            static void div(ATYPE &a,const CTYPE<OTS...> &b)
            {
                typename CTYPE<OTS...>::const_iterator iter = b.begin();
                for(value_type &v: a)
                {
                    v /= (*iter);
                    ++iter;
                }
            }
            
    };

// \endcond



//end namespace
}
}

#endif /* INPLACEARITHMETICS_HPP_ */
