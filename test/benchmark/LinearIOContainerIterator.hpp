#ifndef __LINEARIOCONTAINERITERATOR_HPP__
#define __LINEARIOCONTAINERITERATOR_HPP__

#include <pni/utils/Types.hpp>

using namespace pni::utils;

template<typename CTYPE> class LinearIOContainerIterator
{
    private:
        CTYPE _container;
        typename CTYPE::value_type _result;
    public:
        //==================construtors========================================
        LinearIOContainerIterator(CTYPE &&cont):_container(std::move(cont)) {}

        //================public member functions==============================
        void write_data()
        {
            typedef typename CTYPE::value_type value_t;
            value_t index(0);

            for(auto iter = _container.begin();iter!=_container.end();++iter) 
                *iter = index++;
        }

        //---------------------------------------------------------------------
        void read_data()
        {
            _result = typename CTYPE::value_type(0);

            for(auto iter = _container.begin();iter!=_container.end();++iter) 
                _result += *iter;
        }


        //---------------------------------------------------------------------
        String name() const
        {
            return String("Linear IO DBuffer template benchmark");
        }
            
};


#endif
