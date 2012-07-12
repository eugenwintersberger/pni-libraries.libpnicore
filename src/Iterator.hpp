#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "Exceptions.hpp" 
#include <iterator>

namespace pni{
namespace utils{
   
    //=========================================================================
    /*! \ingroup util_classes
    \brief iterator return type map

    Template whose specializations determine the return types for various 
    iterator operators depending on the const_flag in the template parameter
    list.
    */
    template<typename ITERABLE,int const_flag> class IterTypes;

    //=========================================================================
    /*! \ingroup util_classes
    \brief return types for non-const iterators

    Specialization of the IterReturnType template for non-const iterators.
    */
    template<typename ITERABLE> class IterTypes<ITERABLE,0>
    {
        public:
            typedef ITERABLE *cont_ptr; //!< container pointer
            //!< reference type for dereferencing operator
            typedef typename ITERABLE::value_type& return_type;
            //!< pointer type for -> operator
            typedef typename ITERABLE::value_type* ptr_type;    
            //!< reference type 
            typedef typename ITERABLE::value_type& ref_type;
    };

    //=========================================================================
    /*! \ingroup util_classes
    \brief return types for const iterators

    Specialization of the IterReturnType template for const iterators.
    */
    template<typename ITERABLE> class IterTypes<ITERABLE,1>
    {
        public:
            typedef const ITERABLE *cont_ptr; //!< container pointer
            //!< value type for dereferencing operator
            typedef typename ITERABLE::value_type return_type;    
            //!< pointer type for -> operator
            typedef const typename ITERABLE::value_type *ptr_type; 
            //!< reference type
            typedef const typename ITERABLE::value_type &ref_type;
    };

    //=========================================================================
    template<typename ITERABLE,int const_flag> class Iterator;

    template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag> 
        operator+(const Iterator<ITERABLE,const_flag> &a,
                  ssize_t b);
    template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag>
        operator+(ssize_t a,
                  const Iterator<ITERABLE,const_flag> &b);
    template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag>
        operator-(const Iterator<ITERABLE,const_flag> &a,
                  ssize_t b);
    template<typename ITERABLE,int const_flag> ssize_t
        operator-(const Iterator<ITERABLE,const_flag> &a,
                  const Iterator<ITERABLE,const_flag> &b);


    /*! \ingroup util_classes   
    \brief iterator type

    Generic iterator used for several classes within this library. The container
    type that can be used with this iterator must provide the following
    interface
    \code
    template<typename T> class ITERABLE<T>
    {
        public:
            typedef T valuee_type;
            size_t size() const;
            T &operator[](size_t i);
            T operator[](size_t i) const;
    };
    \endcode
    This template implements a simple forward iterator. 
    */
    template<typename ITERABLE,int const_flag> class Iterator
    {
        private:
            //!< pointer to the container object
            typename IterTypes<ITERABLE,const_flag>::cont_ptr _container; 
            //!< pointer to the actual item
            typename IterTypes<ITERABLE,const_flag>::ptr_type _item;
            ssize_t _state;        //!< actual position state of the iterator
            
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
            //!< value type of the container
            typedef typename ITERABLE::value_type value_type;
            //!< pointer type the iterator provides
            typedef typename IterTypes<ITERABLE,const_flag>::ptr_type pointer;
            //!< reference type the iterator provides
            typedef typename IterTypes<ITERABLE,const_flag>::ref_type reference;
            //!< difference type of the iterator
            typedef ssize_t difference_type;
            //!< type of iterator
            typedef std::random_access_iterator_tag iterator_category;
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
            Iterator(typename IterTypes<ITERABLE,const_flag>::cont_ptr container
                     ,size_t state=0):
                _container(container),
                _item(nullptr),
                _state(state)
            { 
                this->_set_item(); 
            }

            //------------------------------------------------------------------
            //! copy constructor
            Iterator(const Iterator<ITERABLE,const_flag> &i):
                _container(i._container),
                _item(i._item),
                _state(i._state)
            { }

            //------------------------------------------------------------------
            //! move constructor
            Iterator(Iterator<ITERABLE,const_flag> &&i):
                _container(i._container),
                _item(i._item),
                _state(i._state)
            {
                i._container = nullptr;
                i._item = nullptr;
                i._state = 0;
            }

            //------------------------------------------------------------------
            //! default constructor
            ~Iterator() {}

            //=================assignment operator==============================
            //! copy assignment operator
            Iterator<ITERABLE,const_flag> &
                operator=(const Iterator<ITERABLE,const_flag> &i)
            {
                if(this == &i) return *this;
                this->_container = i._container;
                this->_item      = i._item;
                this->_state     = i._state;
                return *this;
            }

            //------------------------------------------------------------------
            //! move assignment operator
            Iterator<ITERABLE,const_flag> &
                operator=(Iterator<ITERABLE,const_flag> &&i)
            {
                if(this == &i) return *this;
                this->_container = i._container;
                i._container = nullptr;
                this->_item = i._item;
                i._item = nullptr;
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
            explicit operator bool() const
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
                EXCEPTION_SETUP("typename IterReturnType<typename ITERABLE::"
                                "value_type,const_flag>::return_type"
                                "operator*()");

                if(!(*this))
                {
                    EXCEPTION_INIT(IteratorError,"Iterator invalid!");
                    EXCEPTION_THROW();
                }

                return *(this->_item);
            }

            //------------------------------------------------------------------
            /*! \brief pointer access operator

            Returns a const or non-const pointer to the object the iterator
            actually points to. 
            \throws IteratorError if the iterator is invalid
            \return pointer to actual object
            */
            typename IterTypes<ITERABLE,const_flag>::ptr_type operator->()
            {
                EXCEPTION_SETUP("typename IterReturnType<typename ITERABLE::"
                                "value_type,const_flag>::ptr_type"
                                "operator->()");
                if(!(*this))
                {
                    EXCEPTION_INIT(IteratorError,"Iterator invalid!");
                    EXCEPTION_THROW();
                }

                return this->_item;
            }

            //------------------------------------------------------------------
            //! increment iterator position
            Iterator<ITERABLE,const_flag> &operator++()
            {
                this->_state++;
                this->_set_item();
                return *this;
            }

            //------------------------------------------------------------------
            //! increment iterator position
            Iterator<ITERABLE,const_flag> operator++(int i)
            {
                Iterator<ITERABLE,const_flag> temp = *this;
                this->_state++;
                this->_set_item();
                return temp;
            }

            //------------------------------------------------------------------
            //! decrement operators
            Iterator<ITERABLE,const_flag> &operator--()
            {
                this->_state--;
                this->_set_item();
                return *this;
            }

            //------------------------------------------------------------------
            //! decrement operators
            Iterator<ITERABLE,const_flag> operator--(int i)
            {
                Iterator<ITERABLE,const_flag> tmp = *this;
                this->_state--;
                this->_set_item();
                return tmp;
            }

            //------------------------------------------------------------------
            //! compound assignment with +=
            Iterator<ITERABLE,const_flag> &operator+=(ssize_t i)
            {
                this->_state += i;
                this->_set_item();
                return *this;
            }

            //------------------------------------------------------------------
            //! compound assignment with -=
            Iterator<ITERABLE,const_flag> &operator-=(ssize_t i)
            {
                this->_state -= i;
                this->_set_item();
                return *this;
            }
            //------------------------------------------------------------------
            //! comparsion operator - equality
            bool operator==(const Iterator<ITERABLE,const_flag> &a)
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
            bool operator!=(const Iterator<ITERABLE,const_flag> &a)
            {
                if((*this)==a) return false;
                return true;
            }

            //===============comparison operators==============================
            //! lesser than operator
            bool operator<(const Iterator<ITERABLE,const_flag> &b)
            {
                return this->_state < b._state;
            }

            //-----------------------------------------------------------------
            //! lesser than equal operator
            bool operator<=(const Iterator<ITERABLE,const_flag> &b)
            {
                return this->_state <= b._state;
            }

            //-----------------------------------------------------------------
            //! greater than operator
            bool operator>(const Iterator<ITERABLE,const_flag> &b)
            {
                return this->_state > b._state;
            }

            //-----------------------------------------------------------------
            //! greater equal than operator
            bool operator>=(const Iterator<ITERABLE,const_flag> &b)
            {
                return this->_state >= b._state;
            }

            //=======friend declarations for binary arithmetic operators=======
            
            friend Iterator<ITERABLE,const_flag> 
                operator + <> (const Iterator<ITERABLE,const_flag> &a, ssize_t b);
            friend Iterator<ITERABLE,const_flag> 
                operator + <> (ssize_t a,const Iterator<ITERABLE,const_flag> &b);
            friend Iterator<ITERABLE,const_flag> 
                operator - <> (const Iterator<ITERABLE,const_flag> &a,ssize_t b);
            friend ssize_t
                operator - <> (const Iterator<ITERABLE,const_flag> &a,
                          const Iterator<ITERABLE,const_flag> &b);
    };

//================binary arithmetic operators==================================
template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag> 
    operator+(const Iterator<ITERABLE,const_flag> &a, ssize_t b)
{
    Iterator<ITERABLE,const_flag> iter = a;
    iter += b;
    return iter;
}

//-----------------------------------------------------------------------------
template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag>
    operator+(ssize_t a, const Iterator<ITERABLE,const_flag> &b)
{
    return b+a;
}

//-----------------------------------------------------------------------------
template<typename ITERABLE,int const_flag> Iterator<ITERABLE,const_flag>
    operator-(const Iterator<ITERABLE,const_flag> &a, ssize_t b)
{
    Iterator<ITERABLE,const_flag> iter = a;
    iter -= b;
    return iter;
}

//-----------------------------------------------------------------------------
template<typename ITERABLE,int const_flag> ssize_t
    operator-(const Iterator<ITERABLE,const_flag> &a, 
            const Iterator<ITERABLE,const_flag> &b)
{
    return a._state - b._state;
}

//end of namespace
}
}

#endif
