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
#include "arrays.hpp"
#include "cindex_map.hpp"

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
    template<typename INDEXT,typename IMT=cindex_map> class index_iterator
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
            //! type to store the index
            typedef INDEXT value_type;
            //! pointer type to an index
            typedef const value_type* pointer;
            //! reference type to an index
            typedef const value_type& reference;
            //! container pointer type
            typedef const value_type* cptr_type;
            //! iterator difference type
            typedef ssize_t difference_type;
            //! type of the iterator
            typedef index_iterator<INDEXT,IMT> iterator_type;
            //===================constructors and destructor===================
            //! default constructor
            index_iterator();

            //-----------------------------------------------------------------
            /*! 
            \brief constructor

            Construct an index_iterator from a shape object.
            \param shape shape for which to iterate over indices
            \param state iterator state at creation
            */
            index_iterator(const shape_t &shape,size_t state=0):
                _index_map(shape),
                _state(state),
                _index(shape.size())
            {}

            //====================factory to create an index iterator==========
            /*!
            \brief static creation function

            Function to create an iterator to the first index of a particular
            shape.
            \param shape the shape of the array for which we want to create the
            index iterator
            \return iterator to first index
            */
            static iterator_type begin(const shape_t &shape)
            {
                return index_iterator(shape);
            }

            //-----------------------------------------------------------------
            /*!
            \brief static creation function

            Create iterator to the last index of an particular shape.
            \param shape the shape of the array for which the index should be
            created.
            \return iterator
            */
            static iterator_type end(const shape_t &shape)
            {
                size_t size=1;
                for(auto iter=shape.begin();iter!=shape.end();++iter)
                    size *= *iter;

                return index_iterator(shape,size);
            }

            //===================public member functions=======================
            /*!
            \brief dereferencing operator

            Returns the actual index. 
            \return index value
            */
            value_type operator*()
            {
                return _index;
            }

            //-----------------------------------------------------------------
            //! pointer access operator
            pointer operator->()
            {
                return &(this->_index);
            }

            //-----------------------------------------------------------------
            //! increment operator
            iterator_type &operator++()
            {
                this->_state++;
                if(this->_state<ssize_t(this->_index_map.size()))
                    this->_index_map.index(this->_state,this->_index);
                return *this;
            }

            //-----------------------------------------------------------------
            //! postfix increment operator
            iterator_type operator++(int i)
            {
                iterator_type temp = *this;
                ++(*this);
                return temp;
            }

            //-----------------------------------------------------------------
            //! decrement operator
            iterator_type &operator--()
            {
                this->_state--;
                if(this->_state>=0)
                    this->_index_map.index(this->_state,this->_index);

                return *this;
            }

            //-----------------------------------------------------------------
            //! postfix decrement operator
            iterator_type operator--(int i)
            {
                iterator_type temp = *this;
                --(*this);
                return temp;
            }

            //-----------------------------------------------------------------
            //! equality operator
            bool operator==(const iterator_type &a)
            {
                return this->_state==a._state;
            }

            //-----------------------------------------------------------------
            //! inequality operator
            bool operator!=(const iterator_type &a)
            {
                if(*this == a) return false;
                return true;
            }
    };


//end of namespace 
}
}
