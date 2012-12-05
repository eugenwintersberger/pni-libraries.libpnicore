#pragma once

namespace pni{
namespace utils{

    /*! 
    \ingroup util_classes
    \brief type computes the array size

    The idea of this type is to compute the size of a static array or shape
    object. Indeed it computes the product of all the template parameters.
    */
    template<size_t ...indices> class SizeType;

    /*! 
    \ingroup util_classes
    \brief specialization of SizeType

    The first real specialization of the SizeType template. 
    */
    template<size_t i,size_t ...indices> class SizeType<i,indices...>
    {
        public:
            //!< size
            static const size_t size = i*SizeType<indices...>::size;
    };

    //! type breaking the template recursion
    template<> class SizeType<>
    {
        public:
            static const size_t size = 1; //!< size
    };


//end of namespace
}
}
