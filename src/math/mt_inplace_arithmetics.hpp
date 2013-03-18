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
 *  Created on: Dec 27, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <limits>
#include <functional>
#include <thread>
#include <vector>
#include <list>
#include <utility>

#include "../exception_utils.hpp"
#include "../type_info.hpp"
#include "../config/library_config.hpp"
#include "../range_distributor.hpp"

namespace pni{
namespace core{


    /*! 
    \ingroup numeric_array_classes
    \brief single threaded inplace arithmetics

    This class provides single threaded arithmetic operations for numeric
    arrays. It is used for inplace arithmetic operators [Operator]=. 
    All member functions provided are static. See the NumArray template for how
    this class is used in inplace arithmetics. This is the multithreaded version
    of the library.
    \tparam ATYPE array type
    */
    template<typename ATYPE> class mt_inplace_arithmetics
    {
        public:
            //===================public types==================================
            //! value type of the array type
            typedef typename ATYPE::value_type value_type;
            //! array type iterator type
            typedef typename ATYPE::iterator iterator;
            //! array type const iterator type
            typedef typename ATYPE::const_iterator const_iterator;
        private:

            /*!
            \brief run threads

            Distributs a working function on several threads
            \tparam FTYPE function object type
            \param size the total size of the array
            \param f rvalue reference to the function objecct
            */
            template<typename FTYPE>
            static void _run_threads(size_t size,FTYPE &&f)
            {
                size_t nth = pnicore_config.n_arithmetic_threads();
                std::list<std::thread> threads;
                range_distributor ranges(nth,size);

                for(auto iter=ranges.begin();iter!=ranges.end();++iter)
                    threads.push_back(std::move(std::thread(f,iter->first,iter->second)));

                //finally joind all threads and wait for execution end
                for(auto iter=threads.begin();iter!=threads.end();++iter) 
                    iter->join();
            }
          

#ifdef NO_LAMBDA_FUNC
            static void _add_worker(size_t start,size_t stop,ATYPE &a,value_type b)
            {
                    for(size_t i=start;i<stop;++i) a[i] += b;
            }

            template<typename CTYPE> static
            void _add_worker_c(size_t start,size_t stop,ATYPE &a,
                             typename CTYPE::const_iterator b)
            {
                b += start; //set the iterator to its starting value
                for(size_t i=start;i<stop;++i)
                    a[i] += *b++;
            }
                
            static void _sub_worker(size_t start,size_t stop,ATYPE &a,value_type b)
            {
                for(size_t i=start;i<stop;++i) a[i] -= b;
            }

            template<typename CTYPE> static
            void _sub_worker_c(size_t start,size_t stop,ATYPE &a,
                             typename CTYPE::const_iterator b)
            {
                b += start; //set iterator to start value
                for(size_t i=start;i<stop;++i)
                    a[i] -= *b++;
            }

            static void _mult_worker(size_t start,size_t stop,ATYPE &a,value_type b)
            {
                for(size_t i=start;i<stop;++i) a[i] *= b;
            }
                
            template<typename CTYPE> static
            void _mult_worker_c(size_t start,size_t stop,ATYPE &a,
                        typename CTYPE::const_iterator b)
            {
                b += start; //set iterator to start position
                for(size_t i=start;i<stop;++i)
                    a[i] *= *b++;
            }
                
            static void _div_worker(size_t start,size_t stop,ATYPE &a,value_type b)
            {
                for(size_t i=start;i<stop;++i) a[i] /= b;
            }

            template<typename CTYPE> static
            void _div_worker_c(size_t start,size_t stop,ATYPE &a,
                             typename CTYPE::const_iterator b)
            {
                b += start;
                for(size_t i=start;i<stop;++i)
                    a[i] /= *b++;
            }

#endif 

        public:
            //==================inplace addition===============================
            /*!
            \brief add scalar to array

            Adds a scalar value of the value_type of the array to the array. 
            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            
            //performe something like array += scalar

            InplaceArithmetics<ATYPE>::add(array,scalar);
            \endcode
            \param a array of type ATYPE
            \param b scalar value of type ATYPE::value_type
            */
            static void add(ATYPE &a,value_type b)
            {
                using namespace std::placeholders;

#ifndef NO_LAMBDA_FUNC
                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] += b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::_add_worker,_1,_2,std::ref(a),b));
#endif
            }

            //-----------------------------------------------------------------
            /*!
            \brief add container to array
            
            Add a container to an array of type ATYPE.
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());

            InplaceArithmetics<ATYPE>::add(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS template parameters of the container template
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS...>
            */
            template<typename CTYPE> static void add(ATYPE &a,const CTYPE &b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start; //set the iterator to its starting value
                    for(size_t i=start;i<stop;++i)
                        a[i] += *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
#else
                auto f = std::bind(&mt_inplace_arithmetics::template _add_worker_c<CTYPE>,_1,_2,std::ref(a),b.begin());
                _run_threads(a.size(),f);
#endif
            }


            //==================inplace subtraction=============================
            /*!
            \brief subtract scalar from array

            Subtract a scalar value from an array. 
            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            InplaceArithmetics<ATYPE>::sub(array,scalar);
            \endcode
            \param a instance of ATYPE
            \param b scalar value
            */
            static void sub(ATYPE &a,value_type b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC
                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] -= b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,a,b));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::_sub_worker,_1,_2,a,b));
#endif
            }

            //-----------------------------------------------------------------
            /*!
            \brief subtract a container from an array

            Subtract an arbitrary container from an array.
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());
            InplaceArithmetics<ATYPE>::sub(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS container templat parameters
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS...>
            */
            template<typename CTYPE>
            static void sub(ATYPE &a,const CTYPE &b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start; //set iterator to start value
                    for(size_t i=start;i<stop;++i)
                        a[i] -= *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::template _sub_worker_c<CTYPE>,_1,_2,std::ref(a),b.begin()));
#endif
            }

            //=====================inplace multiplication======================
            /*!
            \brief multiply array with scalar

            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            InplaceArithmetics<ATYPE>::mult(array,scalar);
            \endcode
            \param a instance of ATYPE
            \param b scalar value
            */
            static void mult(ATYPE &a,value_type b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC 
                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] *= b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::_mult_worker,_1,_2,std::ref(a),b));
#endif
            }


            //-----------------------------------------------------------------
            /*!
            \brief multiply container with array

            Multiply an arbitrary container with an array. 
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());
            InplaceArithmetics<ATYPE>::mult(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS CTYPE parameters
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS...>
            */
            template<typename CTYPE>
            static void mult(ATYPE &a,const CTYPE &b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start; //set iterator to start position
                    for(size_t i=start;i<stop;++i)
                        a[i] *= *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::template _mult_worker_c<CTYPE>,_1,_2,std::ref(a),b.begin()));
#endif
            }
            
            //=====================inplace division============================
            /*!
            \brief divide array with scalar

            Divide each element of an array by a scalar value.
            \code
            ATYPE array(...);
            typename ATYPE::value_type scalar(5);
            InplaceArithmetics<ATYPE>::div(array,scalar);
            \endcode
            \param a instance of ATYPE
            \param b scalar value
            */
            static void div(ATYPE &a,value_type b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC 
                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] /= b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::_div_worker,_1,_2,std::ref(a),b));
#endif
            }


            //-----------------------------------------------------------------
            /*!
            \brief divde array with container

            Divides each element of an array by the corresponding element of a
            container. 
            \code
            ATYPE array(...);
            std::vector<typename ATYPE::value_type> v(array.size());
            InplaceArithmetics<ATYPE>::div(array,v);
            \endcode
            \tparam CTYPE container template
            \tparam OTS container template parameters
            \param a instance of ATYPE
            \param b instance of CTYPE<OTS..>
            */
            template<typename CTYPE>
            static void div(ATYPE &a,const CTYPE &b)
            {
                using namespace std::placeholders;
#ifndef NO_LAMBDA_FUNC
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start;
                    for(size_t i=start;i<stop;++i)
                        a[i] /= *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
#else
                _run_threads(a.size(),std::bind(&mt_inplace_arithmetics::template _div_worker_c<CTYPE>,_1,_2,std::ref(a),b.begin()));
#endif
            }
            
    };

//end namespace
}
}
