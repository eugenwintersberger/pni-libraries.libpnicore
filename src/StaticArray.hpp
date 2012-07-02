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
 * Static array template.
 *
 * Created on: 24.05.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __STATICARRAY_HPP__
#define __STATICARRAY_HPP__

#include "Types.hpp"
#include "Shape.hpp"
#include "StaticBuffer.hpp"

namespace pni{
namespace utils{

    /*! 
    \brief static array 

    Static arrays are multidimensional arrays which can be used to represent
    arrays whose size is fixed at compile time. Thus, the memory requirement for
    such an array should be sufficiently small (basically not more than the
    buffer required to store the data). This is quite usefull in the case where
    many arrays (think about matrices) must be stored. In such a case the memory
    overhead due to administrative data structures can become critical. 

    Lets have a look on how we use such an array 
    \code

    //create a static array of shape 4x5x10 of type double
    StaticArray<double,4,5,10> array;

    //data access is as usuall with the () operator
    double v = array(1,4,8);


    //global assignment works too
    array = 10;

    
    \endcode

    */
    template<typename T,size_t ...DIMS> class StaticArray
    {
        private:
            StaticBuffer<T,N> _data;     //!< static buffer holding the data
            StaticShape<DIMS...> _shape; //!< static shape describing the arrays dimensionality
        public:
            //================public types=====================================
            typedef T value_type; //!< data type of the elements stored in the array
            typedef std::shared_ptr<StaticArray<T,N> > shared_ptr; //!< shared pointer to this type
            typedef std::unique_ptr<StaticArray<T,N> > unique_ptr; //!< unique pointer to this type
            typedef StaticBuffer<T,N>::iterator iterator; //!< iterator
            typedef StaticBuffer<T,N>::const_iterator const_iterator; //!< const iterator
                
            //=================constructors and destructor=====================
            //! copy constructor from a different array
            template<typename T,typename ATYPE> StaticArray(const ATYPE &a)
            {
                if(a.size() != this->size())
                {
                    //throw an exception here
                }

                //copy data
                size_t cnt = 0;
                for(T &v: *this) v = a[cnt++];
            }

            //==============assignment operators===============================
            //! assignment operator of a constant
            template<typename T>
            StaticArray<T,DIMS...> &operator=(const &T value)
            {
                for(T &v: *this) v = value;
            }

            //!assignment operator for a StaticArray
            StaticArray<T,DIMS...> &operator=(const StaticArray<T,DIMS...> &a)
            {
                

            //============operators and methods for data access================
            template<typename ...ITYPES> T &operator(ITYPES ...indices)
            {
                return this->_data[this->_shape.offset(indices...)];
            }

            //-----------------------------------------------------------------
            template<typename ...ITYPES> T operator(ITYPES ...indices) const
            {
                return this->_data[this->_shape.offset(indices...)];
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> T &operator(const CTYPE &c)
            {
                return this->_data[this->_shape.offset(c)];
            }

            //-----------------------------------------------------------------
            template<typename CTYPE> T operator(const CTYPE &c) const
            {
                return this->_data[this->_shape.offset(c)];
            }

            //-----------------------------------------------------------------
            T &operator[](size_t i) { return this->_data[i]; }

            T operator[](size_t i) const { return this->_data[i]; }

            //-----------------------------------------------------------------
            iterator begin() { return this->_data.begin(); } 
            iterator end()   { return this->_data.end(); }
            const_iterator begin() const { return this->_data.begin(); }
            const_iterator end() const   { return this->_data.end(): }


            //=======================inquery methods===========================
            size_t size() const { return this->_shape.size(); }
            size_t rank() const { return this->_shape.rank(); }
            
            template<typename CTYPE> CTYPE shape() const
            {
                CTYPE s(this->rank());
               
                size_t index = 0;
                for(typename CTYPE::value_type &v: s) v = (*this)[index++];
                return s;
            }

    };

//end of namespace
}
}

#endif
