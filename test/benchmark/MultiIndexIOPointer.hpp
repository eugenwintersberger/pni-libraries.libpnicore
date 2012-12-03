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

        //---------------------------------------------------------------------
        MultiIndexIOPointer(const MultiIndexIOPointer<T> &mip):
            _ptr(new T[mip._nx*mip._ny]),
            _nx(mip._nx),
            _ny(mip._ny)
        {
            for(size_t i=0;i<_nx*_ny;++i) _ptr[i] = mip._ptr[i]; 
        }

        //---------------------------------------------------------------------
        MultiIndexIOPointer(MultiIndexIOPointer<T> &&mip):
            _ptr(mip._ptr),
            _nx(mip._nx),
            _ny(mip._ny)
        {
            mip._ptr = nullptr;
            mip._nx = 0;
            mip._ny = 0;
        }

        //---------------------------------------------------------------------
        ~MultiIndexIOPointer()
        {
            if(_ptr) delete [] _ptr;
        }

        //=====================assignment operators============================
        MultiIndexIOPointer<T> &operator=(const MultiIndexIOPointer<T> &mip)
        {
            if(this == &mip) return *this;

            if(_ptr) delete [] _ptr;

            _nx = mip._nx;
            _ny = mip._ny;
            _ptr = new T[_nx*_ny];

            return *this;
        }

        MultiIndexIOPointer<T> &operator=(MultiIndexIOPointer<T> &&mip)
        {
            if(this == &mip) return *this;

            _ptr = mip._ptr;
            mip._ptr = nullptr;
            _nx  = mip._nx;
            mip._nx = 0;
            _ny  = mip._ny;
            mip._ny = 0;

            return *this;
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
