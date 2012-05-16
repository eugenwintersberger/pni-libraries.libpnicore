#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <exception>

namespace pni{
namespace utils{
    
    template<typename ITEMTYPE,int const_flag> class IterReturnType;

    template<typename ITEMTYPE> class IterReturnType<ITEMTYPE,0>
    {
        public:
            typedef ITEMTYPE& return_type;
            typedef ITEMTYPE* ptr_type;
    };

    template<typename ITEMTYPE> class IterReturnType<ITEMTYPE,1>
    {
        public:
            typedef ITEMTYPE return_type;
            typedef const ITEMTYPE *ptr_type;
    };


    template<typename ITERABLE,int const_flag> class Iterator
    {
        private:
            ITERABLE *_container;
            size_t _state;
        public:
            //================constructor and destructor===========================
            Iterator() = delete;

            //---------------------------------------------------------------------
            Iterator(ITERABLE *container,size_t state=0):
                _container(container),
                _state(state)
            { }

            //---------------------------------------------------------------------
            Iterator(const Iterator<ITERABLE,const_flag> &i):
                _container(i._container),
                _state(i._state)
            {}

            //---------------------------------------------------------------------
            ~Iterator() {}

            //====================public methods and operators=====================
            operator bool() const
            {
                return !(this->_state >= this->_container->size());
            }

            //---------------------------------------------------------------------
            typename IterReturnType<typename ITERABLE::value_type,const_flag>::return_type operator*()
            {
                if(!(*this)) throw std::exception();
                ITERABLE &c = *(this->_container);
                return c[this->_state];
            }

            //---------------------------------------------------------------------
            typename IterReturnType<typename ITERABLE::value_type,const_flag>::ptr_type operator->()
            {
                if(!(*this)) throw std::exception();
                return &((*this->_container)[this->_state]);
            }

            //---------------------------------------------------------------------
            Iterator<ITERABLE,const_flag> &operator++()
            {
                this->_state++;
                return *this;
            }

            //---------------------------------------------------------------------
            Iterator<ITERABLE,const_flag> &operator++(int i)
            {
                this->_state++;
                return *this;
            }

            //---------------------------------------------------------------------
            bool operator==(const Iterator<ITERABLE,const_flag> &a)
            {
                if(this->_container != a._container) return false;
                if(this->_state != a._state) return false;
                return true;
            }

            //---------------------------------------------------------------------
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
