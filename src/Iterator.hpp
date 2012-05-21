#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "Exceptions.hpp" 

namespace pni{
namespace utils{
    
    /*! \ingroup util_classes
    \brief iterator return type map

    Template whose specializations determine the return types for various
    iterator operators depending on the const_flag in the template parameter
    list.
    */
    template<typename ITERABLE,int const_flag> class IterTypes;

    /*! \ingroup util_classes
    \brief return types for non-const iterators

    Specialization of the IterReturnType template for non-const iterators.
    */
    template<typename ITERABLE> class IterTypes<ITERABLE,0>
    {
        public:
            typedef ITERABLE *cont_ptr; //!< container pointer
            typedef typename ITERABLE::value_type& return_type; //!< reference type for dereferencing operator
            typedef typename ITERABLE::value_type* ptr_type;    //!< pointer type for -> operator
    };

    /*! \ingroup util_classes
    \brief return types for const iterators

    Specialization of the IterReturnType template for const iterators.
    */
    template<typename ITERABLE> class IterTypes<ITERABLE,1>
    {
        public:
            typedef const ITERABLE *cont_ptr; //!< container pointer
            typedef typename ITERABLE::value_type return_type;     //!< value type for dereferencing operator
            typedef const typename ITERABLE::value_type *ptr_type; //!< pointer type for -> operator
    };


    /*! \ingroup util_classes   
    \brief iterator type

    Generic iterator used for several classes within this library.
    */
    template<typename ITERABLE,int const_flag> class Iterator
    {
        private:
            typename IterTypes<ITERABLE,const_flag>::cont_ptr _container; //!< pointer to the container object
            size_t _state;        //!< actual position state of the iterator
        public:
            //================constructor and destructor===========================
            //! no default constructor
            Iterator() = delete;

            //---------------------------------------------------------------------
            /*! \brief standard constructor

            This constructor takes a pointer to the container and an initial
            position.
            \param container pointer to the container object
            \param state initial position of the iterator
            */
            Iterator(typename IterTypes<ITERABLE,const_flag>::cont_ptr container,size_t state=0):
                _container(container),
                _state(state)
            { }

            //---------------------------------------------------------------------
            //! copy constructor
            Iterator(const Iterator<ITERABLE,const_flag> &i):
                _container(i._container),
                _state(i._state)
            {}

            //---------------------------------------------------------------------
            //! default constructor
            ~Iterator() {}

            //====================public methods and operators=====================
            /*! \brief conversion operator

            This operator allows the conversion of an iterator to bool. It will
            return true if the iterator is valid and false otherwise.
            \return boolean value
            */
            operator bool() const
            {
                return !(this->_state >= this->_container->size());
            }

            //---------------------------------------------------------------------
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

                return (*(this->_container))[this->_state];
            }

            //---------------------------------------------------------------------
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

                return &((*this->_container)[this->_state]);
            }

            //---------------------------------------------------------------------
            //! increment iterator position
            Iterator<ITERABLE,const_flag> &operator++()
            {
                this->_state++;
                return *this;
            }

            //---------------------------------------------------------------------
            //! increment iterator position
            Iterator<ITERABLE,const_flag> &operator++(int i)
            {
                this->_state++;
                return *this;
            }

            //---------------------------------------------------------------------
            //! comparsion operator - equality
            bool operator==(const Iterator<ITERABLE,const_flag> &a)
            {
                if(this->_container != a._container) return false;
                if(this->_state != a._state) return false;
                return true;
            }

            //---------------------------------------------------------------------
            //! comparison operator - inequality
            bool operator!=(const Iterator<ITERABLE,const_flag> &a)
            {
                if((*this)==a) return false;
                return true;
            }
    };


//end of namespace
}
}

#endif
