#ifndef __OPTRAITS_HPP__
#define __OPTRAITS_HPP__

#include "../Scalar.hpp"

namespace pni{
namespace utils{
    
    /*! 
    \ingroup numeric_array_classes
    \brief operator reference trait

    */
    template<typename OT> struct OpTrait
    {
        //! reference type for the operand
        typedef OT const& ref_type; 
    };

    /*! 
    \ingroup numeric_array_classes
    \brief operator reference trait - specialization
    */
    template<typename T> struct OpTrait<Scalar<T> >
    {
        //! reference type for a scalar operand
        typedef Scalar<T> ref_type;
    };
//end of namespace
}
}


#endif
