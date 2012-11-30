#ifndef __MULTIINDEXIOPOINTER_HPP__
#define __MULTIINDEXIOPOINTER_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>

using namespace pni::utils;

template<typename T> class MultiIndexIOPointer
{
    private:
        T *_ptr;
        size_t _nx;
        size_t _ny;
    public:
        //==================construtors========================================
        MultiIndexIOPointer(size_t nx,size_t ny):
            _ptr(new T[nx*ny]),
            _nx(nx),
            _ny(ny)
        { }

        ~MultiIndexIOPointer()
        {
            if(_ptr) delete [] _ptr;
        }

        //================public member functions==============================
        void write_data()
        {
            T index(0);

            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    _ptr[i*_ny+j] = index++;

        }

        //---------------------------------------------------------------------
        void read_data()
        {
            T result(0);

            for(size_t i=0;i<_nx;++i)
                for(size_t j=0;j<_ny;++j)
                    result += _ptr[i*_ny+j];
        }


        //---------------------------------------------------------------------
        String name() const
        {
            return String("Linear IO DBuffer template benchmark");
        }
            
};


#endif
