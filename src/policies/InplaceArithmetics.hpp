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

#include "../Exceptions.hpp"
#include "../ExceptionUtils.hpp"
#include "TypeInfo.hpp"

namespace pni{
namespace utils{

//! \cond no_doc
//Inplace arithmetics of typed objects - the object can only be a left-value
    template<typename T,
             template<typename,typename ...> class ATYPE,
             typename ...OPS
            >
    class InplaceArithmetics{
        private:
            //-----------------------------------------------------------------
            template<typename OPERATOR>
            static void _apply_inplace(ATYPE<T,OPS...> &a, T b, OPERATOR op) 
            {
                for(T &v: a) v = op(v,b);
            }

            //-----------------------------------------------------------------
            template<typename OPERATOR>
            static void _apply_inplace(ATYPE<T,OPS...> &a,
                                       ATYPE<T,OPS...> &b,
                                       OPERATOR op)
            {
                check_equal_shape(a.shape(),b.shape(),
                    "template<typename ATYPE,template<typename> OP>"
                    "static void apply_inplace(ATYPE &a,ATYPE &b)");

                size_t index = 0;
                for(T &v: a)
                {
                    v = op(v,b[index]);
                    index++;
                }
            }

            //-----------------------------------------------------------------
            template
            <
                typename U,
                template<typename,typename ...> class UATYPE,
                typename OPERATOR,
                typename ...UOPS
            >
            static void _apply_inplace(ATYPE<T,OPS...> &a,
                                       UATYPE<U,UOPS...> &b,
                                       OPERATOR op)
            {
                //check shapes 
                check_equal_shape(a.shape(),b.shape());

                //compute values
                size_t index = 0;
                for(T &v: a)
                {
                    v = op(v,convert_type<T>(b[index]));
                    index ++;
                }
            }
                 
        public:
            //==================inplace addition===============================
            //object with a scalar
            static void add_inplace(ATYPE<T,OPS...> &a,T b)
            {
                _apply_inplace(a,b,std::plus<T>());
            }

            //-----------------------------------------------------------------
            static void add_inplace(ATYPE<T,OPS...> &a,const ATYPE<T,OPS...> &b)
            {
                _apply_inplace(a,b,std::plus<T>());
            }

            //-----------------------------------------------------------------
            template
            <
                typename U,
                template<typename,typename ...> class UATYPE,
                typename ...UOPS
            >
            static void add_inplace(ATYPE<T,OPS...> &a,const UATYPE<U,UOPS...> &b)
            {
                _apply_inplace(a,b,std::plus<T>());
            }

            //==================inplace subtraction===============================
            //object with a scalar
            static void sub_inplace(ATYPE<T,OPS...> &a,T b)
            {
                _apply_inplace(a,b,std::minus<T>());
            }

            //-----------------------------------------------------------------
            static void sub_inplace(ATYPE<T,OPS...> &a,const ATYPE<T,OPS...> &b)
            {
                _apply_inplace(a,b,std::minus<T>());
            }

            //-----------------------------------------------------------------
            template
            <
                typename U,
                template<typename,typename ...> class UATYPE,
                typename ...UOPS
            >
            static void sub_inplace(ATYPE<T,OPS...> &a,const UATYPE<U,UOPS...> &b)
            {
                _apply_inplace(a,b,std::minus<T>());
            }
            
    };

// \endcond



//end namespace
}
}

#endif /* INPLACEARITHMETICS_HPP_ */
