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
 * Created on: May 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include "exceptions.hpp" 

namespace pni{
namespace core{
   
    //=========================================================================
    /*! 
    \ingroup iterator_types
    \brief iterator return type map

    One of the difficult tasks in creating an iterator is to determine the
    return type for the dereferencing-operator (*). In the case of a read/write
    iterator the return type is a reference to the element the iterator actually
    points to. For const iterators this should be the value_type of the
    iterable (the const iterator returns by value to avoid modification of the
    element). 
    This is the default template without data members. Have a look on its
    specializations to for a particular return type
    \sa iter_types<ITERABLE,0>
    \sa iter_types<ITERABLE,1>
    \tparam ITERABLE container type over which to iterate
    \tparam const_flag 1 if the iterator is a const iterator.
    */
    template<typename ITERABLE,int const_flag> class iter_types
    {};

    //=========================================================================
    /*! \ingroup iterator_types
    \brief return types for non-const iterators

    Specialization of the IterTypes template for non-const iterators.
    In this case the return_type member type is a reference to the value_type of
    the ITERABLE.
    \tparam ITERABLE container over which the iterator should run
    \sa iter_types<ITERABLE,const_flag>
    */
    template<typename ITERABLE> class iter_types<ITERABLE,0>
    {
        public:
            typedef ITERABLE *cont_ptr; //!< container pointer
            //! return type for the dereferencing operator
            typedef typename ITERABLE::value_type& return_type;
            //! pointer type for -> operator
            typedef typename ITERABLE::value_type* ptr_type;    
            //! reference type 
            typedef typename ITERABLE::value_type& ref_type;
    };



    //=========================================================================
    /*! \ingroup iterator_types
    \brief return types for const iterators

    Specialization of the IterReturnType template for const iterators. Here the
    return type of the dereferencing operator is just value_type. 
    \tparam ITERABLE type over which the iterator should run
    \sa iter_types<ITERABLE,const_flag>
    */
    template<typename ITERABLE> class iter_types<ITERABLE,1>
    {
        public:
            typedef const ITERABLE *cont_ptr; //!< container pointer
            //! return type for dereferencing operator
            typedef typename ITERABLE::value_type return_type;    
            //! pointer type for -> operator
            typedef const typename ITERABLE::value_type *ptr_type; 
            //! reference type
            typedef const typename ITERABLE::value_type &ref_type;
    };
   

    //=========================================================================

    /*! 
    \ingroup iterator_types   
    \brief iterator type

    This is the most generic iterator provided by libpnicore. It can be used
    with all container types provided by the library. A container that wants to
    use this iterator must implement the following interface
    \code
    template<typename T> class ITERABLE<T>
    {
        public:
            typedef T value_type;
            size_t size() const;
            T &operator[](size_t i);
            T operator[](size_t i) const;
    };
    \endcode
    This template implements a simple forward iterator. It must be mentioned
    that this iterator, unlike the standard C++ iterators, throws an exception
    if one tries to dereference an invalid iterator.
    */
    template<typename ITERABLE,int const_flag> class iterator
    {
        private:
            //! pointer to the container object
            typename iter_types<ITERABLE,const_flag>::cont_ptr _container; 

            //! actual position state of the iterator
            ssize_t _state;                    

            //! maximum number of elements in the container
            ssize_t _maxsize;

            //! set the item pointer
            void _set_item()
            {
                if(*this) 
                    this->_item = &(*(this->_container))[this->_state];
                else
                    this->_item = nullptr;
            }

#ifdef NOEXPLICITCONV 
            typedef void (iterator<ITERABLE,const_flag>::*bool_type)() const;
            void bool_operator_function() const {}
#endif

        public:
            //====================public types==================================
            //! value type of the container
            typedef typename ITERABLE::value_type value_type;
            //! pointer type the iterator provides
            typedef typename iter_types<ITERABLE,const_flag>::ptr_type pointer;
            //! reference type the iterator provides
            typedef typename iter_types<ITERABLE,const_flag>::ref_type reference;
            //! pointer type of the container
            typedef typename iter_types<ITERABLE,const_flag>::cont_ptr cptr_type;
            //! difference type of the iterator
            typedef ssize_t difference_type;
            //! type of iterator
            typedef std::random_access_iterator_tag iterator_category;
            //! iterator type
            typedef iterator<ITERABLE,const_flag> iterator_type;
            //================constructor and destructor========================
            //! default constructor
            iterator():_container(nullptr),_state(0),_maxsize(0) {}

            //------------------------------------------------------------------
            /*! \brief standard constructor

            This constructor takes a pointer to the container and an initial
            position.
            \param container pointer to the container object
            \param state initial position of the iterator
            */
            iterator(cptr_type container,size_t state=0):
                _container(container),
                _state(state),
                _maxsize(container->size())
            { }

            //------------------------------------------------------------------
            //! copy constructor
            iterator(const iterator_type &i):
                _container(i._container),
                _state(i._state),
                _maxsize(i._maxsize)
            { }

            //------------------------------------------------------------------
            //! move constructor
            Iterator(iterator_type &&i):
                _container(i._container),
                _state(i._state),
                _maxsize(i._maxsize)
            {
                i._container = nullptr;
                i._state = 0;
                i._maxsize = 0;
            }

            //------------------------------------------------------------------
            //! default constructor
            ~iterator() {}

            //=================assignment operator==============================
            //! copy assignment operator
            iterator_type &operator=(const iterator_type &i)
            {
                if(this == &i) return *this;
                this->_container = i._container;
                this->_state     = i._state;
                this->_maxsize   = i._maxsize;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            iterator_type &operator=(iterator_type &&i)
            {
                if(this == &i) return *this;
                this->_container = i._container;
                i._container = nullptr;
                this->_state = i._state;
                i._state = 0;
                this->_maxsize = i._maxsize;
                i._maxsize = 0;
                return *this;
            }

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
#ifdef NOEXPLICITCONV
            operator bool_type() const
            {
                return  !((!this->_container)||(this->_state >= this->_maxsize)||(this->_state<0)) ? &iterator_type::bool_operator_function : 0;
            }
#else
            explicit operator bool() const
            {
                //if(!this->_container) return false;
                //ssize_t size = (ssize_t)(this->_container->size());
                return !((!this->_container)||(this->_state >= this->_maxsize)||(this->_state<0));
            }
#endif
            //------------------------------------------------------------------
            /*! \brief dereferencing operator

            Returns a reference on the object the iterator is actually pointer
            or the object by value. The return type depends if the iterator is
            used as a standard iterator or a const iterator.
            \throws IteratorError if the iterator is invalid
            \return reference or value of the actual object
            */
            typename iter_types<ITERABLE,const_flag>::return_type operator*()
            {
                if(!(*this))
                    throw IteratorError(EXCEPTION_RECORD,"Iterator invalid!");

                return (*(this->_container))[this->_state];
            }

            //------------------------------------------------------------------
            /*! \brief pointer access operator

            Returns a const or non-const pointer to the object the iterator
            actually points to. 
            \throws IteratorError if the iterator is invalid
            \return pointer to actual object
            */
            pointer operator->()
            {
                if(!(*this))
                    throw iterator_error(EXCEPTION_RECORD,"Iterator invalid!");

                return &(*(this->_container))[this->_state];
            }

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
                Iterator<ITERABLE,const_flag> temp = *this;
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
                Iterator<ITERABLE,const_flag> tmp = *this;
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
                //check if the iterators point to the same container
                if(this->_container != a._container) return false;
                //check if the iterators point to the same element
                //within the container
                if(this->_state != a._state) return false;

                return true;
            }

            //------------------------------------------------------------------
            //! comparison operator - inequality
            bool operator!=(const iterator_type &a)
            {
                if((*this)==a) return false;
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
    template<typename ITERABLE,int const_flag> iterator<ITERABLE,const_flag> 
        operator+(const iterator<ITERABLE,const_flag> &a, ssize_t b)
    {
        iterator<ITERABLE,const_flag> iter = a;
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
    template<typename ITERABLE,int const_flag> iterator<ITERABLE,const_flag>
        operator+(ssize_t a, const iterator<ITERABLE,const_flag> &b)
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
    template<typename ITERABLE,int const_flag> iterator<ITERABLE,const_flag>
        operator-(const iterator<ITERABLE,const_flag> &a, ssize_t b)
    {
        iterator<ITERABLE,const_flag> iter = a;
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
    template<typename ITERABLE,int const_flag> ssize_t
        operator-(const iterator<ITERABLE,const_flag> &a, 
                const iterator<ITERABLE,const_flag> &b)
    {
        return a.state() - b.state();
    }

//end of namespace
}
}
