#ifndef __CONTAINERUTILS_HPP__
#define __CONTAINERUTILS_HPP__

namespace pni{
namespace utils{
    
    template<typename TARGET,typename CONT> 
        TARGET &copy(TARGET &t,const CONT &c)
    {
        check_equal_size(t,c,"template<typename TARGET,typename CONT> TARGET "
                             "&copy(TARGET &t,const CONT &c)");

        size_t index = 0;
        for(auto v: c) t[index++] = v;

        return t;
    }

    template<typename TARGET,typename T>
        TARGET &copy(TARGET &g,size_t n,const T *ptr)
    {
        
    }

//end of namespace
}
}

#endif
