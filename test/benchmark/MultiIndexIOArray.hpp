#ifndef __MULTIINDEXIOARRAY_HPP__
#define __MULTIINDEXIOARRAY_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

using namespace pni::utils;

template<typename ATYPE> class MultiIndexIOArray
{
    private:
        ATYPE _array;
        shape_t _shape;
        typename ATYPE::value_type _result;
    public:
        //==================construtors========================================
        MultiIndexIOArray(ATYPE &&array):
            _array(std::move(array)),
            _shape(_array.template shape<shape_t>())
        { }

        //================public member functions==============================
        void write_data()
        {
            typedef typename ATYPE::value_type value_t;
            value_t index(0);


            for(size_t i=0;i<_shape[0];++i)
                for(size_t j=0;j<_shape[1];++j)
                    _array(i,j) = index++;

        }

        //---------------------------------------------------------------------
        void read_data()
        {
            _result = typename ATYPE::value_type(0);

            for(size_t i=0;i<_shape[0];++i)
                for(size_t j=0;j<_shape[1];++j)
                    _result += _array(i,j);
        }


        //---------------------------------------------------------------------
        String name() const
        {
            return String("Linear IO DBuffer template benchmark");
        }
            
};


#endif
