#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <exception>

template<typename ITERABLE> class Iterator
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
        Iterator(const Iterator<ITERABLE> &i):
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
        typename ITERABLE::value_type &operator*()
        {
            if(!(*this)) throw std::exception();
            ITERABLE &c = *(this->_container);
            return c[this->_state];
        }

        //---------------------------------------------------------------------
        typename ITERABLE::value_type *operator->()
        {
            if(!(*this)) throw std::exception();
            return &((*this->_container)[this->_state]);
        }

        //---------------------------------------------------------------------
        Iterator<ITERABLE> &operator++()
        {
            this->_state++;
            return *this;
        }

        //---------------------------------------------------------------------
        Iterator<ITERABLE> &operator++(int i)
        {
            this->_state++;
            return *this;
        }

        //---------------------------------------------------------------------
        bool operator==(const Iterator<ITERABLE> &a)
        {
            if(this->_container != a._container) return false;
            if(this->_state != a._state) return false;
            return true;
        }

        //---------------------------------------------------------------------
        bool operator!=(const Iterator<ITERABLE> &a)
        {
            if((*this)==a) return false;
            return true;
        }
};

#endif
