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
 * Created on: Jan 8, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <vector>
#include "Array.hpp"
#include "CIndexMap.hpp"

namespace pni{
namespace core{

    /*!
    \brief index iterator

    This iterator runs over a set of multidimensional indices where each of
    these indices is identified by its linear offset. 
    Via the template parameters the user can control what container type he
    wants to use for the index and which index map he wants to use. By setting
    the index map one can be sure that the indices are iterated in a way so that
    the number of chache misses during memory access is minimal.

    In C++ terminology this iterator is a random access input iterator (one can
    only read from the elements the iterator points to).
    \tparam INDEXT type of the index container
    \tparam IMT index map type
    */
    template<typename INDEXT,typename IMT=CIndexMap> class index_iterator
    {
        private:
            //! the index map used to compute the indices
            IMT _index_map;
            //! the actual state of the iterator
            ssize_t _state;
            //! index buffer
            INDEXT _index;

        public:
            //===================public types==================================
            typedef INDEXT value_type;
            typedef const value_type* pointer;
            typedef const value_type& reference;
            typedef const value_type* cptr_type;
            typedef ssize_t difference_type;
            typedef index_iterator<INDEXT,IMT> iterator_type;
            //===================constructors and destructor===================
            //! default constructor
            index_iterator();

            //-----------------------------------------------------------------
            /*! 
            \brief constructor

            Construct an index_iterator from a shape object.
            \param shape shape for which to iterate over indices
            */
            index_iterator(const shape_t &shape,size_t state=0):
                _index_map(shape),
                _state(state),
                _index(shape.size())
            {}

            //====================factory to create an index iterator==========
            static iterator_type begin(const shape_t &shape)
            {
                return index_iterator(shape);
            }

            //-----------------------------------------------------------------
            static iterator_type end(const shape_t &shape)
            {
                size_t size=1;
                for(auto s: shape) size *= s;

                return index_iterator(shape,size);
            }

            //===================public member functions=======================
            value_type operator*()
            {
                return _index;
            }

            //-----------------------------------------------------------------
            pointer operator->()
            {
                return &(this->_index);
            }

            //-----------------------------------------------------------------
            iterator_type &operator++()
            {
                this->_state++;
                if(this->_state<ssize_t(this->_index_map.size()))
                    this->_index_map.index(this->_state,this->_index);
                return *this;
            }

            //-----------------------------------------------------------------
            iterator_type operator++(int i)
            {
                iterator_type temp = *this;
                ++(*this);
                return temp;
            }

            //-----------------------------------------------------------------
            iterator_type &operator--()
            {
                this->_state--;
                if(this->_state>=0)
                    this->_index_map.index(this->_state,this->_index);

                return *this;
            }

            //-----------------------------------------------------------------
            iterator_type operator--(int i)
            {
                iterator_type temp = *this;
                --(*this);
                return temp;
            }

            //-----------------------------------------------------------------
            bool operator==(const iterator_type &a)
            {
                return this->_state==a._state;
            }

            //-----------------------------------------------------------------
            bool operator!=(const iterator_type &a)
            {
                if(*this == a) return false;
                return true;
            }
    };


//end of namespace 
}
}
