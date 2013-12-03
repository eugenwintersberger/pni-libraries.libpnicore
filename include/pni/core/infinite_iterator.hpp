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
 * Created on: Dec 2, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <type_traits>
#include "exceptions.hpp" 

namespace pni{
namespace core{

    //=========================================================================

    /*! 
    \ingroup iterator_types   
    \brief infinite iterator

    This iterator circles forever.
    */
    template<typename ITERABLE> class infinite_iterator
    {
        private:
            //! pointer to the container object
            ITERABLE* _container;

            //! the internal state of the iterator
            ssize_t _state;

            typedef typename std::remove_const<ITERABLE>::type container_type;
        public:
            //====================public types==================================
            typedef infinite_iterator<ITERABLE> iterator_type;
            //! value type of the container
            typedef typename container_type::value_type value_type;
            //! pointer type the iterator provides
            typedef typename std::conditional<std::is_const<ITERABLE>::value,
                                              const value_type*,value_type *>::type  pointer;
            //! reference type the iterator provides
            typedef typename std::conditional<std::is_const<ITERABLE>::value,
                                              const value_type&,value_type&>::type reference;
            //! difference type of the iterator
            typedef ssize_t difference_type;
            //! type of iterator
            typedef std::random_access_iterator_tag iterator_category;
            //================constructor and destructor========================
            //------------------------------------------------------------------
            /*! \brief standard constructor

            This constructor takes a pointer to the container and an initial
            position.
            \param container pointer to the container object
            \param state initial position of the iterator
            */
            infinite_iterator(ITERABLE *container,size_t state=0):
                _container(container),
                _state(state)
            { }

            infinite_iterator(const iterator_type &i):
                _container(i._container),
                _state(i._state)
            {}

            //====================public methods and operators==================
            /*! \brief conversion operator

            This operator allows the conversion of an iterator to bool. It will
            return true if the iterator is valid and false otherwise.
            The iterator is consideres as invalid if its internal state is at
            least one after the last element or smaller than 0. It is important
            that this conversion operator is set \c explicit. Otherwise the
            iterator would be implicitly convertible to integer (via bool).
            \return boolean value
            */
            explicit operator bool() const { return true; }
            //------------------------------------------------------------------
            /*! \brief dereferencing operator

            Returns a reference on the object the iterator is actually pointer
            or the object by value. The return type depends if the iterator is
            used as a standard iterator or a const iterator.
            \throws IteratorError if the iterator is invalid
            \return reference or value of the actual object
            */
            reference operator*() { return (*_container)[_state]; }

            //------------------------------------------------------------------
            /*! \brief pointer access operator

            Returns a const or non-const pointer to the object the iterator
            actually points to. 
            \throws IteratorError if the iterator is invalid
            \return pointer to actual object
            */
            pointer operator->() { return &((*_container)[_state]); }

            //------------------------------------------------------------------
            //! increment iterator position
            iterator_type &operator++()
            {
                this->_state++;
                return *this;
            }

            //------------------------------------------------------------------
            //! increment iterator position
            iterator_type operator++(int i)
            {
                iterator_type temp(*this);
                ++(*this);
                return temp;
            }

            //------------------------------------------------------------------
            //! decrement operators
            iterator_type &operator--()
            {
                this->_state--;
                return *this;
            }

            //------------------------------------------------------------------
            //! decrement operators
            iterator_type operator--(int i)
            {
                iterator_type tmp = *this;
                --(*this);
                return tmp;
            }

            //------------------------------------------------------------------
            //! compound assignment with +=
            iterator_type &operator+=(ssize_t i)
            {
                this->_state += i;
                return *this;
            }

            //------------------------------------------------------------------
            //! compound assignment with -=
            iterator_type &operator-=(ssize_t i)
            {
                this->_state -= i;
                return *this;
            }
            //------------------------------------------------------------------
            //! comparsion operator - equality
            bool operator==(const iterator_type &a)
            {
                //return true only if this is the same iterator instance
                if(this == &a) return true; 
                return false;
            }

            //------------------------------------------------------------------
            //! comparison operator - inequality
            bool operator!=(const iterator_type &a)
            {
                if(this==a) return false;
                return true;
            }

            //===============comparison operators==============================
            //! lesser than operator
            bool operator<(const iterator_type &b)
            {
                return this->_state < b._state;
            }

            //-----------------------------------------------------------------
            //! lesser than equal operator
            bool operator<=(const iterator_type &b)
            {
                return this->_state <= b._state;
            }

            //-----------------------------------------------------------------
            //! greater than operator
            bool operator>(const iterator_type &b)
            {
                return this->_state > b._state;
            }

            //-----------------------------------------------------------------
            //! greater equal than operator
            bool operator>=(const iterator_type &b)
            {
                return this->_state >= b._state;
            }

            //! get state of the iterator
            ssize_t state() const { return this->_state; }

    };

    //================binary arithmetic operators===============================
    /*! 
    \brief add scalar to iterator

    Add an offset to the iterator and thus increment its internal state by this
    offset.
    \code
    Iteartor<...> iter = ...'
    Iteartor<...> iter2 = iter+2;
    \endcode
    \param a original iterator
    \param b offset to add
    \return new iterator 
    */
    template<typename ITERABLE>
    infinite_iterator<ITERABLE> 
    operator+(const infinite_iterator<ITERABLE> &a, ssize_t b)
    {
        infinite_iterator<ITERABLE> iter = a;
        iter += b;
        return iter;
    }

    //--------------------------------------------------------------------------
    /*!
    \brief add offset to iterator
    
    Add an offset to the iterator and thus increment its internal state by this
    offset.
    \param a offset to add
    \param b original iterator
    \return new iterator
    */
    template<typename ITERABLE> infinite_iterator<ITERABLE>
        operator+(ssize_t a, const infinite_iterator<ITERABLE> &b)
    {
        return b+a;
    }

    //--------------------------------------------------------------------------
    /*!
    \brief subtract offset from iterator

    Subtract an integer offset from the iterator and thus decrement the internal
    state of the iterator by this value. 
    \param a original iterator
    \param b offset
    \return new iterator to new position
    */
    template<typename ITERABLE> infinite_iterator<ITERABLE>
        operator-(const infinite_iterator<ITERABLE> &a, ssize_t b)
    {
        infinite_iterator<ITERABLE> iter = a;
        iter -= b;
        return iter;
    }

    //--------------------------------------------------------------------------
    /*!
    \brief subtract two iterators

    Subtract to iterators and return the offset difference between this
    two iterators.
    \param a first iterator
    \param b second iterator
    \return offset difference
    */
    template<typename ITERABLE> 
    ssize_t operator-(const infinite_iterator<ITERABLE> &a, 
                      const infinite_iterator<ITERABLE> &b)
    {
        return a.state() - b.state();
    }

//end of namespace
}
}
