#ifndef __SIZETYPE_HPP__
#define __SIZETYPE_HPP__

namespace pni{
namespace utils{

    template<size_t d,size_t ...NDIMS> class SizeType
    {
        public:
            static const size_t size = d*SizeType<NDIMS...>::size;
    };

    template<size_t d,size_t ...NDIMS> class SizeType<NDIMS...>
    {
        public:
            static const size_t size = d;
    };

//end of namespace
}
}

#endif
