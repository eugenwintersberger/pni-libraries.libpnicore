#ifndef __INDEXMAP_HPP__
#define __INDEXMAP_HPP__

namespace pni{
namespace utils{

    /*! 
    \brief C-order index map

    Maps multidimensional indices to linear offsets and vicer verse in C-order.
    This type can be used in any array or shape object to compute offsets and
    indices. The static method provided are entirely generic and assume only a
    containers that supports reverse iterators. This includes all STL container
    types.
    */
    struct CIndexMap
    {
        public:
        template<typename STYPE,typename ...ITYPES> 
            static size_t offset(const STYPE &s,size_t i,ITYPES ...indices);

        template<typename STYPE,typename CTYPE> 
            static size_t offset(const STYPE &s,const CTYPE &c);
        

        template<typename ITYPE,typename STYPE> 
            static ITYPE index(const STYPE &s,size_t offset);

        template<typename STYPE,typename ITYPE>
            static void index(const STYPE &s,size_t offset,ITYPE &index);


    };

    //-------------------------------------------------------------------------
    template<typename STYPE,typename ...ITYPES>
        size_t CIndexMap::offset(const STYPE &s,size_t i,ITYPES ...indices)
    {
        std::vector<size_t> index{i,size_t(indices)...};

        return offset(s,index);
    }

    //-------------------------------------------------------------------------
    template<typename STYPE,typename CTYPE>
        size_t CIndexMap::offset(const STYPE &shape,const CTYPE &index)
    {
        size_t dstride = 1,offset = 0;
        for(auto siter=shape.rbegin(),iiter=index.rbegin();
                siter!=shape.rend();
                ++siter,++iiter)
        {
            offset += *iiter*dstride;
            dstride *= *siter;
        }

        return offset;
    }

    //-------------------------------------------------------------------------
    template<typename ITYPE,typename STYPE>
        ITYPE CIndexMap::index(const STYPE &shape,size_t offset)
    {
        ITYPE index(shape.size());
        CIndexMap::index(shape,offset,index);
        return index;
    }

    //-------------------------------------------------------------------------
    template<typename STYPE,typename ITYPE>
        void CIndexMap::index(const STYPE &s,size_t offset,ITYPE &index)
    {
        STYPE dstrides(s.size());
        //compute dimension strides
        STYPE &shape = const_cast<STYPE &>(s);
        size_t ds = 1;
        for(auto siter = shape.rbegin(),dsiter=dstrides.rbegin();
                siter!=shape.rend();
                ++siter,++dsiter)
        {
            *dsiter = ds;
            ds *= *siter;
        }
       
        size_t t;
        for(auto iiter=index.begin(),diter=dstrides.begin();
                iiter!=index.end();
                ++iiter,++diter)
        {
            t = offset%(*diter);
            *iiter = (offset-t)/(*diter);
            offset = t;
        }

    }


//end of namespace
}
}

#endif
