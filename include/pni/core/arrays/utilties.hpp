
#pragma once

namespace pni{
namespace core{

    /*!
    \brief get pointer to data

    This function returns the pointer to  the raw data stored in an object. 

    */
    template<typename ATYPE> ATYPE::value_type *data(ATYPE &a) 
    {
        return data(a.storage());
    }

    template<typename ATYPE> const ATYPE::value_type *data(const ATYPE &a)
    {
        typedef const ATYPE::value_type *pointer_type;
        return (pointer_type)data(a);
    }
    
    template<typename T> T *data(std::vector<T> &a)
    {
        return a.data();
    }

    template<typename T,size_t N> T *data(std::array<T,N> &a)
    {
        return a.data();
    }


//end of namespace
}
}
