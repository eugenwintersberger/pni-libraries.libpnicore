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
#include <utility>

#include "../exception_utils.hpp"
#include "../type_info.hpp"
#include "../config/library_config.hpp"

namespace pni{
namespace core{

    class range_distributor
    {
        private:
            std::vector<std::pair<size_t,size_t> > _ranges;
        public:
            typedef std::pair<size_t,size_t> value_type;
            typedef std::vector<value_type>::iterator iterator;
            typedef std::vector<value_type>::const_iterator const_iterator;


            range_distributor(size_t nth,size_t s)
                :_ranges(nth)
            {
                size_t nres = s%nth;
                size_t npth = (s-nres)/nth;

                size_t start=0,stop=0;
               // std::cout<<a.size()<<std::endl;
                for(size_t i = 0;i<nth;++i)
                {
                    if(i==0) start = 0;
                    else start = stop;

                    stop = start+npth;
                    if(nres)
                    {
                        stop++;
                        nres--;
                    }
                    _ranges[i] = {start,stop};
                }
                
            }

            iterator begin() { return _ranges.begin(); }
            iterator end() { return _ranges.end(); }
            const_iterator begin() const { return _ranges.begin(); }
            const_iterator end() const { return _ranges.end(); }

            
    };

    /*! 
    \ingroup numeric_array_classes
    \brief single threaded inplace arithmetics

    This class provides single threaded arithmetic operations for numeric
    arrays. It is used for inplace arithmetic operators <Operator>=. 
    All member functions provided are static. See the NumArray template for how
    this class is used in inplace arithmetics. This is the multithreaded version
    of the library.
    \tparam ATYPE array type
    */
    template<typename ATYPE> class mt_inplace_arithmetics
    {
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
                std::vector<std::thread> threads(nth);

                size_t nres = size%nth;
                size_t npth = (size - nres)/nth;

                size_t start=0,stop=0;
                for(size_t i = 0; i<nth;++i)
                {

                    if(i==0) start = 0;
                    else start = stop;
                   
                    stop = start + npth;
                    
                    if(nres)
                    {
                        ++stop;
                        --nres;
                    }
                   
                    threads[i] = std::thread(f,start,stop);
                }

                //finally joind all threads and wait for execution end
                for(size_t i=0;i<nth;++i) threads[i].join();
            }
          
            //-----------------------------------------------------------------
            /*
            template<typename FTYPE,typename ITYPE>
            static void _run_threads(ATYPE &a,FTYPE &&f,ITYPE iter)
            {
                size_t nth = pnicore_config.n_arithmetic_threads();
                std::vector<std::thread> threads(nth);

                size_t index = 0;
                for(auto r: rd)
                {
                    threads[index++] = std::thread(f,a.begin(),index++,nth,iter);
                }

                //finally joind all threads and wait for execution end
                for(size_t i=0;i<nth;++i) threads[i].join();
            }
            */

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

            InplaceArithmetics<ATYPE>::add(array,scalar);
            \endcode
            \param a array of type ATYPE
            \param b scalar value of type ATYPE::value_type
            */
            static void add(ATYPE &a,value_type b)
            {
                using namespace std::placeholders;

                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] += b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b));
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
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start; //set the iterator to its starting value
                    for(size_t i=start;i<stop;++i)
                        a[i] += *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
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

                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] -= b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,a,b));
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
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start; //set iterator to start value
                    for(size_t i=start;i<stop;++i)
                        a[i] -= *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
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
                
                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] *= b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b));
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
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start; //set iterator to start position
                    for(size_t i=start;i<stop;++i)
                        a[i] *= *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
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
            \parma b scalar value
            */
            static void div(ATYPE &a,value_type b)
            {
                using namespace std::placeholders;
                
                auto f = [](size_t start,size_t stop,ATYPE &a,value_type b)
                {
                    for(size_t i=start;i<stop;++i) a[i] /= b;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b));
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
                auto f = [](size_t start,size_t stop,ATYPE &a,
                            typename CTYPE::const_iterator b)
                {
                    b += start;
                    for(size_t i=start;i<stop;++i)
                        a[i] /= *b++;
                };

                _run_threads(a.size(),std::bind(f,_1,_2,std::ref(a),b.begin()));
            }
            
    };

//end namespace
}
}
