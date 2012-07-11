#ifndef __BUFFERFACTORY_HPP__
#define __BUFFERFACTORY_HPP__

class BufferFactory
{
    public:
        template<typename BTYPE,typename CTYPE> 
            static BTYPE create(const CTYPE &c);

        template<typename BTYPE,typename U>
            static BTYPE create(size_t n,const U *ptr);

        template<typename BTYPE,typename U>
            static BTYPE create(size_t n,const U &ref);

        template<typename BTYPE

#endif
