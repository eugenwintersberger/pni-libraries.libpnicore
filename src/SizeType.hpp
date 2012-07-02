#ifndef __SIZETYPE_HPP__
#define __SIZETYPE_HPP__

namespace pni{
namespace utils{

    /*! 
    \brief type computes the array size

    The idea of this type is to compute the size of a static array or shape
    object. Indeed it computes the product of all the template parameters.
    */
    template<size_t ...indices> class SizeType;

    /*! 
    \brief specialization of SizeType

    The first real specialization of the SizeType template. 
    */
    template<size_t i,size_t ...indices> class SizeType<i,indices...>
    {
        public:
            static const size_t size = i*SizeType<indices...>::size;
    };

    //! type breaking the template recursion
    template<> class SizeType<>
    {
        public:
            static const size_t size = 1;
    };


//end of namespace
}
}

#endif
