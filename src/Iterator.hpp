#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "Exceptions.hpp" 
#include <iterator>

namespace pni{
namespace utils{
   
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
    \sa IterTypes<ITERABLE,0>
    \sa IterTypes<ITERABLE,1>
    \tparam ITERABLE container type over which to iterate
    \tparam const_flag 1 if the iterator is a const iterator.
    */
    template<typename ITERABLE,int const_flag> class IterTypes
    {};

    //=========================================================================
    /*! \ingroup iterator_types
    \brief return types for non-const iterators

    Specialization of the IterTypes template for non-const iterators.
    In this case the return_type member type is a reference to the value_type of
    the ITERABLE.
    \tparam ITERABLE container over which the iterator should run
    \sa IterTypes<ITERABLE,const_flag>
    */
    template<typename ITERABLE> class IterTypes<ITERABLE,0>
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
    \sa IterTypes<ITERABLE,const_flag>
    */
    template<typename ITERABLE> class IterTypes<ITERABLE,1>
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

    This is the most generic iterator provided by libpniutils. It can be used
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
    template<typename ITERABLE,int const_flag> class Iterator
    {
        private:
            //! pointer to the container object
            typename IterTypes<ITERABLE,const_flag>::cont_ptr _container; 

            //! actual position state of the iterator
            ssize_t _state;                    

            //! set the item pointer
            void _set_item()
            {
                if(*this) 
                    this->_item = &(*(this->_container))[this->_state];
                else
                    this->_item = nullptr;
            }

        public:
            //====================public types==================================
            //! value type of the container
            typedef typename ITERABLE::value_type value_type;
            //! pointer type the iterator provides
            typedef typename IterTypes<ITERABLE,const_flag>::ptr_type pointer;
            //! reference type the iterator provides
            typedef typename IterTypes<ITERABLE,const_flag>::ref_type reference;
            //! pointer type of the container
            typedef typename IterTypes<ITERABLE,const_flag>::cont_ptr cptr_type;
            //! difference type of the iterator
            typedef ssize_t difference_type;
            //! type of iterator
            typedef std::random_access_iterator_tag iterator_category;
            //! iterator type
            typedef Iterator<ITERABLE,const_flag> iterator_type;
            //================constructor and destructor========================
            //! default constructor
            Iterator():_container(nullptr),_state(0) {}

            //------------------------------------------------------------------
            /*! \brief standard constructor

            This constructor takes a pointer to the container and an initial
            position.
            \param container pointer to the container object
            \param state initial position of the iterator
            */
            Iterator(cptr_type container,size_t state=0):
                _container(container),
                _state(state)
            { 
            }

            //------------------------------------------------------------------
            //! copy constructor
            Iterator(const iterator_type &i):
                _container(i._container),
                _state(i._state)
            { }

            //------------------------------------------------------------------
            //! move constructor
            Iterator(iterator_type &&i):
                _container(i._container),
                _state(i._state)
            {
                i._container = nullptr;
                i._state = 0;
            }

            //------------------------------------------------------------------
            //! default constructor
            ~Iterator() {}

            //=================assignment operator==============================
            //! copy assignment operator
            iterator_type &operator=(const iterator_type &i)
            {
                if(this == &i) return *this;
                this->_container = i._container;
                this->_state     = i._state;
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
            operator bool() const
#else
            explicit operator bool() const
#endif
            {
                if(!this->_container) return false;
                ssize_t size = (ssize_t)(this->_container->size());
                return !((this->_state >= size)||(this->_state<0));
            }

            //------------------------------------------------------------------
            /*! \brief dereferencing operator

            Returns a reference on the object the iterator is actually pointer
            or the object by value. The return type depends if the iterator is
            used as a standard iterator or a const iterator.
            \throws IteratorError if the iterator is invalid
            \return reference or value of the actual object
            */
            typename IterTypes<ITERABLE,const_flag>::return_type operator*()
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
                    throw IteratorError(EXCEPTION_RECORD,"Iterator invalid!");

                return &(*this);
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
    template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag> 
        operator+(const Iterator<ITERABLE,const_flag> &a, ssize_t b)
    {
        Iterator<ITERABLE,const_flag> iter = a;
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
    template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag>
        operator+(ssize_t a, const Iterator<ITERABLE,const_flag> &b)
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
    template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag>
        operator-(const Iterator<ITERABLE,const_flag> &a, ssize_t b)
    {
        Iterator<ITERABLE,const_flag> iter = a;
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
        operator-(const Iterator<ITERABLE,const_flag> &a, 
                const Iterator<ITERABLE,const_flag> &b)
    {
        return a.state() - b.state();
    }

//end of namespace
}
}

#endif
