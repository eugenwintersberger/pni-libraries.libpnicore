#ifndef __ARRAYVIEWSELECTOR_HPP__
#define __ARRAYVIEWSELECTOR_HPP__

#include "ArrayView.hpp"


namespace pni {
namespace utils {

    template<typename ATYPE,typename ...ITYPES> struct ArrayViewSelector;

    template<typename ATYPE,size_t i,typename ...ITYPES> struct
        ArrayViewSlector<ATYPE,i,ITYPES...>
    {
        typedef typename ArrayViewSelector<ATYPE,ITYPES...>::viewtype viewtype;
    }

    template<typename ATYPE,Slice s,typename ...ITYPES> struct
        ArrayViewSelector<ATYPE,s,ITYPES...>
    {
        typedef ArrayView<ATYPE> viewtype;
    }

    template<typename ATYPE,size_t i> struct ArrayViewSelector<ATYPE,i>
    {
        typedef typename ATYPE::value_type viewtype;
    }

//end of namespace
}
}

#endif
