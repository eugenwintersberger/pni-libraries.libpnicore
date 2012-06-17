#ifndef __SIZETYPE_HPP__
#define __SIZETYPE_HPP__

namespace pni{
namespace utils{



    template<size_t ...NDIMS> class SizeType
    {
        private:
            constexpr size_t _compute_size(size_t d)
            {
                return d;
            }

            template<typename ...INDICES> 
                constexpr size_t _compute_size(size_t d,INDICES... is)
            {
                return d*compute_size(is...);
            }

        public:
            static const size_t size = compute_size(NDIMS...);
    };




//end of namespace
}
}

#endif
